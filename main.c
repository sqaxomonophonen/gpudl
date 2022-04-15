#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include <X11/Xlib.h>

#include "webgpux.h"

#if 0
const char* my_shader =
"@stage(vertex)\n"
"fn vs_main(@builtin(vertex_index) in_vertex_index: u32) -> @builtin(position) vec4<f32> {\n"
"	let x = f32(i32(in_vertex_index) - 1) * 0.5;\n"
"	let y = f32(i32(in_vertex_index & 1u) * 2 - 1);\n"
"	return vec4<f32>(x, y, 0.0, 1.0);\n"
"}\n"
"\n"
"@stage(fragment)\n"
"fn fs_main() -> @location(0) vec4<f32> {\n"
"	return vec4<f32>(1.0, 0.0, 1.0, 1.0);\n"
"}\n";
#endif

const char* my_shader2 =
"struct VertexOutput {\n"
	"@location(0) rgba: vec4<f32>,\n"
	"@builtin(position) position: vec4<f32>,\n"
"};\n"
"\n"
"struct Uniforms {\n"
"	distort: f32,\n"
"	alpha: f32,\n"
"	frame: u32,\n"
"};\n"
"@group(0) @binding(0)\n"
"var<uniform> uniforms: Uniforms;\n"
"\n"
"@stage(vertex)\n"
"fn vs_main(\n"
"	@location(0) xyzw: vec4<f32>,\n"
"	@location(1) rgba: vec4<f32>,\n"
") -> VertexOutput {\n"
"	let m: f32 = 7.0;\n"
"	let a: f32 = f32(uniforms.frame) * 0.01;\n"
"	let ud: f32 = uniforms.distort;\n"
"	let distort = vec2<f32>(ud*sin(m*xyzw.x + a), ud*cos(m*xyzw.y + a));\n"
"	let pos = xyzw.xy;\n"
"	var out: VertexOutput;\n"
"	out.position = vec4<f32>(pos+distort, 0.0, 1.0);\n"
"	out.rgba = rgba;\n"
"	return out;\n"
"}\n"
"\n"
"@group(0) @binding(1)\n"
"var tex: texture_2d<u32>;\n"
"@stage(fragment)\n"
"fn fs_main(in: VertexOutput) -> @location(0) vec4<f32> {\n"
"	let dim = vec2<f32>(textureDimensions(tex));\n"
"	return in.rgba * uniforms.alpha * (1.0/256.0) * f32(textureLoad(tex, vec2<i32>(in.rgba.xy * dim), 0).x);\n"
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

struct Vertex {
	float xyzw[4];
	float rgba[4];
};

struct Uniforms {
	float distort;
	float alpha;
	int frame;
};

static void write_vertices(int iteration, int n_triangles, struct Vertex* vertices)
{
	struct Vertex* p = vertices;
	for (int i = 0; i < n_triangles; i++) {
		float x = -1.0f + 2.0f * ((float)i / (float)(n_triangles-1));
		float y = -1.0f + 2.0f * ((float)i / (float)(n_triangles-1));

		float a = (float)i + ((float)iteration) * 0.01f;
		const float a120 = (M_PI/3)*2;
		const float a240 = a120 * 2;

		const float r = 0.05f;
		float dx0 = r * sinf(a);
		float dy0 = r * cosf(a);
		float dx1 = r * sinf(a + a120);
		float dy1 = r * cosf(a + a120);
		float dx2 = r * sinf(a + a240);
		float dy2 = r * cosf(a + a240);

		*(p++) = (struct Vertex){
			.xyzw = { x+dx0, y+dy0 },
			.rgba = {1,0,0,1},
		};
		*(p++) = (struct Vertex){
			.xyzw = { x+dx1, y+dy1 },
			.rgba = {0,1,0,1},
		};
		*(p++) = (struct Vertex){
			.xyzw = { x+dx2, y+dy2 },
			.rgba = {0,0,1,1},
		};
	}
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
			.nextInChain = (const WGPUChainedStruct *)&(WGPUSurfaceDescriptorFromXlibWindow){
				.chain = (WGPUChainedStruct){
					.next = NULL,
					.sType = WGPUSType_SurfaceDescriptorFromXlibWindow,
				},
				.display = display,
				.window = window,
			},
	});

	WGPUInstance instance = NULL; // XXX no wgpuCreateInstance() yet

	WGPUAdapter adapter = NULL;
	wgpuInstanceRequestAdapter(
		instance,
		&(WGPURequestAdapterOptions){
			.compatibleSurface = surface,
			.nextInChain = (const WGPUChainedStruct*) &(WGPUAdapterExtras) {
				.chain = (WGPUChainedStruct) {
					.next = NULL,
					.sType = WGPUSType_AdapterExtras,
				},
				.backend = WGPUBackendType_Vulkan,
				//.backend = WGPUBackendType_OpenGL, // XXX not supported
				//.backend = WGPUBackendType_OpenGLES, // XXX not supported
			},
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

	WGPUQueue queue = wgpuDeviceGetQueue(device);
	assert(queue);

	wgpuDeviceSetUncapturedErrorCallback(device, wgpu_error_callback, NULL);
	//wgpuGetProcAddress(device, "uhuh buhuh");

	#if 1
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

	const int n_triangles = 200;
	const int n_vertices = 3 * n_triangles;
	const size_t vtxbuf_sz = n_vertices * sizeof(struct Vertex);

	WGPUBuffer vtxbuf = wgpuDeviceCreateBuffer(device, &(WGPUBufferDescriptor){
		.usage = WGPUBufferUsage_Vertex | WGPUBufferUsage_MapWrite | WGPUBufferUsage_CopyDst,
		.size = vtxbuf_sz,
	});
	assert(vtxbuf);

	WGPUBuffer unibuf = wgpuDeviceCreateBuffer(device, &(WGPUBufferDescriptor){
		.usage = WGPUBufferUsage_Uniform | WGPUBufferUsage_MapWrite,
		.size = sizeof(struct Uniforms),
	});
	assert(unibuf);

	const int texture_width = 256;
	const int texture_height = 256;
	const size_t texture_sz = texture_width * texture_height;

	WGPUTexture texture = wgpuDeviceCreateTexture(device, &(WGPUTextureDescriptor) {
		.usage = WGPUTextureUsage_TextureBinding | WGPUTextureUsage_CopyDst,
		.dimension = WGPUTextureDimension_2D,
		.size = (WGPUExtent3D){
			.width = 256,
			.height = 256,
			.depthOrArrayLayers = 1,
		},
		.mipLevelCount = 1,
		.sampleCount = 1,
		.format = WGPUTextureFormat_R8Uint,
	});
	assert(texture);

	WGPUTextureView texture_view = wgpuTextureCreateView(texture, &(WGPUTextureViewDescriptor) {});
	assert(texture_view);

	uint8_t* texture_data = calloc(texture_sz, 1);

	uint8_t* tp = texture_data;
	for (int y = 0; y < texture_height; y++) {
		for (int x = 0; x < texture_width; x++) {
			*(tp++) = (((x>>4)&1) ^ ((y>>4)&1)) ? 255 : 0;
		}
	}

	wgpuQueueWriteTexture(
		queue,
		&(WGPUImageCopyTexture) {
			.texture = texture,
		},
		texture_data,
		texture_sz,
		&(WGPUTextureDataLayout) {
			.offset = 0,
			.bytesPerRow = texture_width,
			.rowsPerImage = texture_height,
		},
		&(WGPUExtent3D) {
			.width = texture_width,
			.height = texture_height,
			.depthOrArrayLayers = 1,
		}
	);

	//wgpuDeviceCreateSampler

	WGPUBindGroupLayout bind_group_layout = wgpuDeviceCreateBindGroupLayout(device, &((WGPUBindGroupLayoutDescriptor){
		.entryCount = 2,
		.entries = (WGPUBindGroupLayoutEntry[]){
			(WGPUBindGroupLayoutEntry){
				.binding = 0,
				.visibility = WGPUShaderStage_Vertex | WGPUShaderStage_Fragment,
				.buffer = (WGPUBufferBindingLayout){
					.type = WGPUBufferBindingType_Uniform,
					//.type = WGPUBufferBindingType_Storage,
					.hasDynamicOffset = false,
					.minBindingSize = sizeof(struct Uniforms),
				},
			},
			(WGPUBindGroupLayoutEntry){
				.binding = 1,
				.visibility = WGPUShaderStage_Fragment,
				.texture = (WGPUTextureBindingLayout) {
					.sampleType = WGPUTextureSampleType_Uint,
					.viewDimension = WGPUTextureViewDimension_2D,
					.multisampled = false,
				},
			},
		},
	}));
	assert(bind_group_layout);

	WGPUShaderModuleDescriptor shaderSource = load_wgsl(my_shader2);
	WGPUShaderModule shader = wgpuDeviceCreateShaderModule(device, &shaderSource);
	assert(shader);

	WGPUPipelineLayout pipeline_layout = wgpuDeviceCreatePipelineLayout(
		device,
		&(WGPUPipelineLayoutDescriptor){
			.bindGroupLayoutCount = 1,
			.bindGroupLayouts = (WGPUBindGroupLayout[]){
				bind_group_layout,
			},
		}
	);

	WGPUBindGroup bind_group = wgpuDeviceCreateBindGroup(device, &(WGPUBindGroupDescriptor){
		.layout = bind_group_layout,
		.entryCount = 2,
		.entries = (WGPUBindGroupEntry[]){
			(WGPUBindGroupEntry){
				.binding = 0,
				.buffer = unibuf,
				.offset = 0,
				.size = sizeof(struct Uniforms),
			},
			(WGPUBindGroupEntry){
				.binding = 1,
				.textureView = texture_view,
			}, 
		},
	});

	WGPUTextureFormat swapChainFormat = wgpuSurfaceGetPreferredFormat(surface, adapter);

	WGPURenderPipeline pipeline = wgpuDeviceCreateRenderPipeline(
		device,
		&(WGPURenderPipelineDescriptor){
			.label = "Render pipeline",
			.layout = pipeline_layout,
			.vertex = (WGPUVertexState){
				.module = shader,
				.entryPoint = "vs_main",
				.bufferCount = 1,
				.buffers = (WGPUVertexBufferLayout[]){
					(WGPUVertexBufferLayout){
						.arrayStride = sizeof(struct Vertex),
						.stepMode = WGPUVertexStepMode_Vertex,
						.attributeCount = 2,
						.attributes = (WGPUVertexAttribute[]) {
							(WGPUVertexAttribute){
								.format = WGPUVertexFormat_Float32x4,
								.offset = 0,
								.shaderLocation = 0,
							},
							(WGPUVertexAttribute){
								.format = WGPUVertexFormat_Float32x4,
								.offset = 4*4,
								.shaderLocation = 1,
							},
						},
					},
				},
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
	int mx = 0;
	int my = 0;
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

					swapChain = wgpuDeviceCreateSwapChain(
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
				mx = xe.xmotion.x;
				my = xe.xmotion.y;
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

		{
			#if 0
			struct Vertex* vertices = wgpuBufferMap(device, vtxbuf, WGPUMapMode_Write, 0, vtxbuf_sz);
			write_vertices(iteration, n_triangles, vertices);
			wgpuBufferUnmap(vtxbuf);
			#else
			// everybody seems to recommend queue.write_buffer() over buffer.map()?
			struct Vertex vs[n_vertices];
			write_vertices(iteration, n_triangles, vs);
			wgpuQueueWriteBuffer(queue, vtxbuf, 0, vs, vtxbuf_sz);
			#endif
		}

		{
			struct Uniforms* u = wgpuBufferMap(device, unibuf, WGPUMapMode_Write, 0, sizeof(*u));
			u->frame = iteration;
			u->distort = (((float)my / (float)height) - 0.5f) * 2.5f;
			u->alpha = ((float)mx / (float)width) * 5.0f;
			wgpuBufferUnmap(unibuf);
		}

		WGPUCommandEncoder encoder = wgpuDeviceCreateCommandEncoder(
			device,
			&(WGPUCommandEncoderDescriptor){.label = "Command Encoder"}
		);

		WGPURenderPassEncoder renderPass = wgpuCommandEncoderBeginRenderPass(
			encoder,
			&(WGPURenderPassDescriptor){
				.colorAttachmentCount = 1,
				.colorAttachments = &(WGPURenderPassColorAttachment){
					.view = nextTexture,
					.resolveTarget = 0,
					.loadOp = WGPULoadOp_Clear,
					.storeOp = WGPUStoreOp_Store,
					.clearValue = (WGPUColor){.b=0.1},
				},
				.depthStencilAttachment = NULL,
			}
		);

		wgpuRenderPassEncoderSetPipeline(renderPass, pipeline);
		wgpuRenderPassEncoderSetBindGroup(renderPass, 0, bind_group, 0, 0);
		wgpuRenderPassEncoderSetVertexBuffer(renderPass, 0, vtxbuf, 0, vtxbuf_sz);
		wgpuRenderPassEncoderDraw(renderPass, n_vertices, 1, 0, 0);
		wgpuRenderPassEncoderEnd(renderPass);

		WGPUCommandBuffer cmdBuffer = wgpuCommandEncoderFinish(
			encoder,
			&(WGPUCommandBufferDescriptor){.label = NULL}
		);
		wgpuQueueSubmit(queue, 1, &cmdBuffer);
		wgpuSwapChainPresent(swapChain);

		iteration++;
	}

	wgpuRenderPipelineDrop(pipeline);
	wgpuPipelineLayoutDrop(pipeline_layout);
	wgpuShaderModuleDrop(shader);

	XCloseDisplay(display);

	printf("EXIT\n");

	return EXIT_SUCCESS;
}
