#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

#include <X11/Xlib.h>

#include "wgpu.h"

const char* my_shader =
"[[stage(vertex)]]\n"
"fn vs_main([[builtin(vertex_index)]] in_vertex_index: u32) -> [[builtin(position)]] vec4<f32> {\n"
"	let x = f32(i32(in_vertex_index) - 1) * 0.5;\n"
"	let y = f32(i32(in_vertex_index & 1u) * 2 - 1);\n"
"	return vec4<f32>(x, y, 0.0, 1.0);\n"
"}\n"
"\n"
"[[stage(fragment)]]\n"
"fn fs_main() -> [[location(0)]] vec4<f32> {\n"
"	return vec4<f32>(1.0, 0.0, 1.0, 1.0);\n"
"}\n";

static int error_handler(Display* display, XErrorEvent* event) {
	printf("X11 ERRORRGGH!\n");
	return 0;
}

void request_adapter_callback(WGPURequestAdapterStatus status, WGPUAdapter received, const char *message, void *userdata) {
	*(WGPUAdapter *)userdata = received;
}

void request_device_callback(WGPURequestDeviceStatus status, WGPUDevice received, const char *message, void *userdata) {
	*(WGPUDevice *)userdata = received;
}

WGPUShaderModuleDescriptor load_wgsl(const char* code) {
	WGPUShaderModuleWGSLDescriptor *desc = malloc(sizeof *desc);
	desc->chain.next = NULL;
	desc->chain.sType = WGPUSType_ShaderModuleWGSLDescriptor;
	desc->code = code;

	return (WGPUShaderModuleDescriptor){
		.nextInChain = (const WGPUChainedStruct *)desc,
		.label = "shader",
	};
}

Display* display;
Window root;

static void get_window_dim(Window window, int* return_width, int* return_height)
{
	int x;
	int y;
	unsigned int width;
	unsigned int height;
	unsigned int border_width;
	unsigned int depth;

	XGetGeometry(
		display,
		window,
		&root,
		&x, &y,
		&width, &height,
		&border_width,
		&depth
	);

	if (return_width) *return_width = width;
	if (return_height) *return_height = height;
}

static WGPUSwapChain mk_swap_chain(WGPUDevice device, WGPUSurface surface, WGPUTextureFormat swapChainFormat, int width, int height)
{
	return wgpuDeviceCreateSwapChain(
		device,
		surface,
		&(WGPUSwapChainDescriptor){
			.usage = WGPUTextureUsage_RenderAttachment,
			.format = swapChainFormat,
			.width = width,
			.height = height,
			.presentMode = WGPUPresentMode_Fifo,
			//.presentMode = WGPUPresentMode_Mailbox,
		}
	);
}


static void wgpu_log(WGPULogLevel level, const char *msg)
{
	printf("LOG[%d] :: %s\n", level, msg ? msg : "<nil>");
}

static void wgpu_error_callback(WGPUErrorType type, char const* message, void* userdata)
{
	const char* ts = "(?!)";
	switch (type) {
	case WGPUErrorType_NoError: ts = "(noerror)"; break;
	case WGPUErrorType_Validation: ts = "(validation)"; break;
	case WGPUErrorType_OutOfMemory: ts = "(outofmemory)"; break;
	case WGPUErrorType_Unknown: ts = "(unknown)"; break;
	case WGPUErrorType_DeviceLost: ts = "(devicelost)"; break;
	}
	fprintf(stderr, "WGPU UNCAPTURED ERROR %s: %s\n", ts, message);
}

int main(int argc, char** argv)
{
	//wgpuSetLogLevel(WGPULogLevel_Trace);
	//wgpuSetLogLevel(WGPULogLevel_Debug);
	//wgpuSetLogCallback(wgpu_log);

	XSetErrorHandler(error_handler);
	XInitThreads();
	display = XOpenDisplay(NULL);
	assert((display != NULL) && "XOpenDisplay() failed");

	int screen = DefaultScreen(display);
	root = XRootWindow(display, screen);
	Visual* visual = DefaultVisual(display, screen);
	int depth = DefaultDepth(display, screen);
	Colormap colormap = XCreateColormap(display, root, visual, AllocNone);

	Window window = XCreateWindow(
		display,
		root,
		0, 0,
		1920, 1080,
		0, // border width
		depth,
		InputOutput,
		visual,
		CWBorderPixel | CWColormap | CWEventMask,
		&(XSetWindowAttributes) {
			.background_pixmap = None,
			.colormap = colormap,
			.border_pixel = 0,
			.event_mask =
				  StructureNotifyMask
				| EnterWindowMask
				| LeaveWindowMask
				| ButtonPressMask
				| ButtonReleaseMask
				| PointerMotionMask
				| KeyPressMask
				| KeyReleaseMask
				| ExposureMask
				| FocusChangeMask
				| PropertyChangeMask
				| VisibilityChangeMask
		}
	);
	assert(window);

	XStoreName(display, window, "WEBGPU DEMO");
	XMapWindow(display, window);

	Atom WM_DELETE_WINDOW = XInternAtom(display, "WM_DELETE_WINDOW", False);
	XSetWMProtocols(display, window, &WM_DELETE_WINDOW, 1);

	WGPUSurface surface = wgpuInstanceCreateSurface(
		NULL,
		&(WGPUSurfaceDescriptor){
			.label = NULL,
			.nextInChain = (const WGPUChainedStruct *)&(WGPUSurfaceDescriptorFromXlib){
				.chain = (WGPUChainedStruct){
					.next = NULL,
					.sType = WGPUSType_SurfaceDescriptorFromXlib,
				},
				.display = display,
				.window = window,
			},
	});

	WGPUAdapter adapter = NULL;
	wgpuInstanceRequestAdapter(
		NULL,
		&(WGPURequestAdapterOptions){
			.nextInChain = NULL,
			.compatibleSurface = surface,
		},
		request_adapter_callback,
		(void*)&adapter
	);
	// request_adapter_callback is not called async, at least not with the
	// wgpu-native library :)
	assert((adapter != NULL) && "got no adapter");

	WGPUDevice device = NULL;
	wgpuAdapterRequestDevice(
		adapter,
		&(WGPUDeviceDescriptor){
			.nextInChain = (const WGPUChainedStruct *)&(WGPUDeviceExtras){
				.chain = (WGPUChainedStruct){
					.next = NULL,
					.sType = WGPUSType_DeviceExtras,
				},
				.label = "Device",
				.tracePath = NULL,
			},
			.requiredLimits = &(WGPURequiredLimits){
				.nextInChain = NULL,
				.limits = (WGPULimits){
					.maxBindGroups = 1,
				},
			},
		},
		request_device_callback, (void*)&device
	);
	assert((device != NULL) && "got no device");

	//wgpuDeviceSetUncapturedErrorCallback(device, wgpu_error_callback, NULL);
	//wgpuGetProcAddress(device, "uhuh buhuh");

	#if 0
	WGPUAdapterProperties properties = {0};
	wgpuAdapterGetProperties(adapter, &properties);
	printf("vendor id: %d\n", properties.vendorID);
	printf("device id: %d\n", properties.deviceID);
	printf("adapter type: %d\n", properties.adapterType);
	printf("backend type: %d\n", properties.backendType);
	//printf("name: %s\n", properties.name);
	//printf("driver: %s\n", properties.driverDescription);

	WGPUSupportedLimits limits = {0};
	wgpuAdapterGetLimits(adapter, &limits);

	#define DUMP32(s) printf("  " #s ": %u\n", limits.limits.s);
	#define DUMP64(s) printf("  " #s ": %lu\n", limits.limits.s);
	DUMP32(maxTextureDimension1D)
	DUMP32(maxTextureDimension2D)
	DUMP32(maxTextureDimension3D)
	DUMP32(maxTextureArrayLayers)
	DUMP32(maxBindGroups)
	DUMP32(maxDynamicUniformBuffersPerPipelineLayout)
	DUMP32(maxDynamicStorageBuffersPerPipelineLayout)
	DUMP32(maxSampledTexturesPerShaderStage)
	DUMP32(maxSamplersPerShaderStage)
	DUMP32(maxStorageBuffersPerShaderStage)
	DUMP32(maxStorageTexturesPerShaderStage)
	DUMP32(maxUniformBuffersPerShaderStage)
	DUMP64(maxUniformBufferBindingSize)
	DUMP64(maxStorageBufferBindingSize)
	DUMP32(minUniformBufferOffsetAlignment)
	DUMP32(minStorageBufferOffsetAlignment)
	DUMP32(maxVertexBuffers)
	DUMP32(maxVertexAttributes)
	DUMP32(maxVertexBufferArrayStride)
	DUMP32(maxInterStageShaderComponents)
	DUMP32(maxComputeWorkgroupStorageSize)
	DUMP32(maxComputeInvocationsPerWorkgroup)
	DUMP32(maxComputeWorkgroupSizeX)
	DUMP32(maxComputeWorkgroupSizeY)
	DUMP32(maxComputeWorkgroupSizeZ)
	DUMP32(maxComputeWorkgroupsPerDimension)
	#undef DUMP64
	#undef DUMP32
	#endif

	WGPUShaderModuleDescriptor shaderSource = load_wgsl(my_shader);
	WGPUShaderModule shader = wgpuDeviceCreateShaderModule(device, &shaderSource);

	WGPUPipelineLayout pipelineLayout = wgpuDeviceCreatePipelineLayout(
		device,
		&(WGPUPipelineLayoutDescriptor){
			.bindGroupLayouts = NULL,
			.bindGroupLayoutCount = 0,
		}
	);

	WGPUTextureFormat swapChainFormat = wgpuSurfaceGetPreferredFormat(surface, adapter);

	WGPURenderPipeline pipeline = wgpuDeviceCreateRenderPipeline(
		device,
		&(WGPURenderPipelineDescriptor){
			.label = "Render pipeline",
			.layout = pipelineLayout,
			.vertex = (WGPUVertexState){
				.module = shader,
				.entryPoint = "vs_main",
				.bufferCount = 0,
				.buffers = NULL,
			},
			.primitive = (WGPUPrimitiveState){
				.topology = WGPUPrimitiveTopology_TriangleList,
				.stripIndexFormat = WGPUIndexFormat_Undefined,
				.frontFace = WGPUFrontFace_CCW,
				.cullMode = WGPUCullMode_None
			},
			.multisample = (WGPUMultisampleState){
				.count = 1,
				.mask = ~0,
				.alphaToCoverageEnabled = false,
			},
			.fragment = &(WGPUFragmentState){
				.module = shader,
				.entryPoint = "fs_main",
				.targetCount = 1,
				.targets = &(WGPUColorTargetState){
					.format = swapChainFormat,
					.blend = &(WGPUBlendState){
						.color = (WGPUBlendComponent){
							.srcFactor = WGPUBlendFactor_One,
							.dstFactor = WGPUBlendFactor_Zero,
							.operation = WGPUBlendOperation_Add,
						},
						.alpha = (WGPUBlendComponent){
							.srcFactor = WGPUBlendFactor_One,
							.dstFactor = WGPUBlendFactor_Zero,
							.operation = WGPUBlendOperation_Add,
						}
					},
					.writeMask = WGPUColorWriteMask_All
				},
			},
			.depthStencil = NULL,
		}
	);


	int width = -1;
	int height = -1;

	WGPUSwapChain swapChain = NULL;

	int iteration = 0;
	int exiting = 0;
	int new_swap_chain = 0;
	while (!exiting) {
		while (XPending(display)) {
			XEvent xe;
			XNextEvent(display, &xe);
			Window w = xe.xany.window;
			if (XFilterEvent(&xe, w)) continue;

			if (w != window) continue; // XXX does this work?

			switch (xe.type) {
			case ConfigureNotify:
				if (xe.xconfigure.width != width || xe.xconfigure.height != height) {
					printf("EV: configure %d×%d (was %d×%d)\n", xe.xconfigure.width, xe.xconfigure.height, width, height);
					width = xe.xconfigure.width;
					height = xe.xconfigure.height;
					swapChain = mk_swap_chain(device, surface, swapChainFormat, width, height);
					new_swap_chain = 1;
					assert(swapChain);
				}
				break;
			case EnterNotify:
				printf("EV: enter\n");
				break;
			case LeaveNotify:
				printf("EV: leave\n");
				break;
			case ButtonPress:
			case ButtonRelease:
				printf("EV: button\n");
				exiting = 1;
				break;
			case MotionNotify:
				printf("EV: motion\n");
				break;
			case KeyPress:
			case KeyRelease:
				printf("EV: key\n");
				break;
			case ClientMessage: {
				const Atom protocol = xe.xclient.data.l[0];
				if (protocol == WM_DELETE_WINDOW) {
					exiting = 1;
				}
				break;
			}
			defualt:
				printf("EV: ???\n");
				break;
			}
		}

		if (!swapChain) continue;

		WGPUTextureView nextTexture = wgpuSwapChainGetCurrentTextureView(swapChain);
		if (!nextTexture) {
			swapChain = NULL;
			continue;
		}
		new_swap_chain = 0;

		WGPUCommandEncoder encoder = wgpuDeviceCreateCommandEncoder(
			device,
			&(WGPUCommandEncoderDescriptor){.label = "Command Encoder"}
		);

		WGPURenderPassEncoder renderPass = wgpuCommandEncoderBeginRenderPass(
			encoder,
			&(WGPURenderPassDescriptor){
				.colorAttachments = &(WGPURenderPassColorAttachment){
					.view = nextTexture,
					.resolveTarget = 0,
					.loadOp = WGPULoadOp_Clear,
					.storeOp = WGPUStoreOp_Store,
					.clearColor = (WGPUColor){
						.r = (iteration & 32) ? 1.0 : 0.0,
						.g = 1.0,
						.b = 1.0,
						.a = 1.0,
					},
				},
				.colorAttachmentCount = 1,
				.depthStencilAttachment = NULL,
			}
		);

		wgpuRenderPassEncoderSetPipeline(renderPass, pipeline);
		wgpuRenderPassEncoderDraw(renderPass, 3, 1, 0, 0);
		wgpuRenderPassEncoderEndPass(renderPass);

		WGPUQueue queue = wgpuDeviceGetQueue(device);
		WGPUCommandBuffer cmdBuffer = wgpuCommandEncoderFinish(
			encoder,
			&(WGPUCommandBufferDescriptor){.label = NULL}
		);
		wgpuQueueSubmit(queue, 1, &cmdBuffer);
		wgpuSwapChainPresent(swapChain);

		iteration++;
	}

	wgpuRenderPipelineDrop(pipeline);
	wgpuPipelineLayoutDrop(pipelineLayout);
	wgpuShaderModuleDrop(shader);

	XCloseDisplay(display);

	printf("EXIT\n");

	return EXIT_SUCCESS;
}
