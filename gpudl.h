#ifndef GPUDL_H_

// TODO inline webgpu.h? or is that a bad idea?
#define WGPU_SKIP_DECLARATIONS
#include "webgpu.h"


typedef enum WGPULogLevel {
	WGPULogLevel_Off = 0x00000000,
	WGPULogLevel_Error = 0x00000001,
	WGPULogLevel_Warn = 0x00000002,
	WGPULogLevel_Info = 0x00000003,
	WGPULogLevel_Debug = 0x00000004,
	WGPULogLevel_Trace = 0x00000005,
	WGPULogLevel_Force32 = 0x7FFFFFFF
} WGPULogLevel;


typedef void (*WGPULogCallback)(WGPULogLevel level, const char *msg);

// XXX these are currently non-standard APIs defined by wgpu-native only.
// webgpu.h is somewhat useless without the ability to free temporaary
// resources, but the webgpu-native header team haven't come to a resolution
// the past couple of years.
// see also: https://github.com/webgpu-native/webgpu-headers/issues/9
typedef void (*WGPUProcTextureDrop)(WGPUTexture);
typedef void (*WGPUProcTextureViewDrop)(WGPUTextureView);
typedef void (*WGPUProcBindGroupDrop)(WGPUBindGroup);
typedef void (*WGPUProcSetLogCallback)(WGPULogCallback callback);
typedef void (*WGPUProcSetLogLevel)(WGPULogLevel level);


// procs defined in libwgpu_native.so; Dawn is currently not considered
#define GPUDL_WGPU_PROCS \
	GPUDL_WGPU_PROC(CreateInstance) \
	GPUDL_WGPU_PROC(AdapterGetLimits) \
	GPUDL_WGPU_PROC(AdapterGetProperties) \
	GPUDL_WGPU_PROC(AdapterRequestDevice) \
	GPUDL_WGPU_PROC(BufferDestroy) \
	GPUDL_WGPU_PROC(BufferGetMappedRange) \
	GPUDL_WGPU_PROC(BufferMapAsync) \
	GPUDL_WGPU_PROC(BufferUnmap) \
	GPUDL_WGPU_PROC(CommandEncoderBeginComputePass) \
	GPUDL_WGPU_PROC(CommandEncoderBeginRenderPass) \
	GPUDL_WGPU_PROC(CommandEncoderCopyBufferToBuffer) \
	GPUDL_WGPU_PROC(CommandEncoderCopyBufferToTexture) \
	GPUDL_WGPU_PROC(CommandEncoderCopyTextureToBuffer) \
	GPUDL_WGPU_PROC(CommandEncoderCopyTextureToTexture) \
	GPUDL_WGPU_PROC(CommandEncoderFinish) \
	GPUDL_WGPU_PROC(ComputePassEncoderDispatch) \
	GPUDL_WGPU_PROC(ComputePassEncoderDispatchIndirect) \
	GPUDL_WGPU_PROC(ComputePassEncoderEnd) \
	GPUDL_WGPU_PROC(ComputePassEncoderSetBindGroup) \
	GPUDL_WGPU_PROC(ComputePassEncoderSetPipeline) \
	GPUDL_WGPU_PROC(DeviceCreateBindGroup) \
	GPUDL_WGPU_PROC(DeviceCreateBindGroupLayout) \
	GPUDL_WGPU_PROC(DeviceCreateBuffer) \
	GPUDL_WGPU_PROC(DeviceCreateCommandEncoder) \
	GPUDL_WGPU_PROC(DeviceCreateComputePipeline) \
	GPUDL_WGPU_PROC(DeviceCreatePipelineLayout) \
	GPUDL_WGPU_PROC(DeviceCreateRenderPipeline) \
	GPUDL_WGPU_PROC(DeviceCreateSampler) \
	GPUDL_WGPU_PROC(DeviceCreateShaderModule) \
	GPUDL_WGPU_PROC(DeviceCreateSwapChain) \
	GPUDL_WGPU_PROC(DeviceCreateTexture) \
	GPUDL_WGPU_PROC(DeviceGetLimits) \
	GPUDL_WGPU_PROC(DeviceGetQueue) \
	GPUDL_WGPU_PROC(DeviceSetDeviceLostCallback) \
	GPUDL_WGPU_PROC(DeviceSetUncapturedErrorCallback) \
	GPUDL_WGPU_PROC(InstanceCreateSurface) \
	GPUDL_WGPU_PROC(InstanceRequestAdapter) \
	GPUDL_WGPU_PROC(QueueSubmit) \
	GPUDL_WGPU_PROC(QueueWriteBuffer) \
	GPUDL_WGPU_PROC(QueueWriteTexture) \
	GPUDL_WGPU_PROC(RenderPassEncoderDraw) \
	GPUDL_WGPU_PROC(RenderPassEncoderDrawIndexed) \
	GPUDL_WGPU_PROC(RenderPassEncoderDrawIndexedIndirect) \
	GPUDL_WGPU_PROC(RenderPassEncoderDrawIndirect) \
	GPUDL_WGPU_PROC(RenderPassEncoderEnd) \
	GPUDL_WGPU_PROC(RenderPassEncoderSetBindGroup) \
	GPUDL_WGPU_PROC(RenderPassEncoderSetBlendConstant) \
	GPUDL_WGPU_PROC(RenderPassEncoderSetIndexBuffer) \
	GPUDL_WGPU_PROC(RenderPassEncoderSetPipeline) \
	GPUDL_WGPU_PROC(RenderPassEncoderSetScissorRect) \
	GPUDL_WGPU_PROC(RenderPassEncoderSetStencilReference) \
	GPUDL_WGPU_PROC(RenderPassEncoderSetVertexBuffer) \
	GPUDL_WGPU_PROC(RenderPassEncoderSetViewport) \
	GPUDL_WGPU_PROC(SurfaceGetPreferredFormat) \
	GPUDL_WGPU_PROC(SwapChainGetCurrentTextureView) \
	GPUDL_WGPU_PROC(SwapChainPresent) \
	GPUDL_WGPU_PROC(TextureCreateView) \
	GPUDL_WGPU_PROC(TextureDestroy) \
	GPUDL_WGPU_PROC(TextureDrop) \
	GPUDL_WGPU_PROC(TextureViewDrop) \
	GPUDL_WGPU_PROC(BindGroupDrop) \
	GPUDL_WGPU_PROC(SetLogCallback) \
	GPUDL_WGPU_PROC(SetLogLevel)

#define GPUDL_WGPU_PROC(NAME) extern WGPUProc##NAME wgpu##NAME;
GPUDL_WGPU_PROCS
#undef GPUDL_WGPU_PROC

enum gpudl_event_type {
	GPUDL_MOTION = 1,
	GPUDL_BUTTON,
	GPUDL_KEY,
	GPUDL_CLOSE,
	GPUDL_ENTER,
	GPUDL_LEAVE,
	GPUDL_FOCUS,
	GPUDL_UNFOCUS,
};

enum gpudl_keycode {
	GK_UNKNOWN = -1,

	GK_SPECIAL_BEGIN = 256,

	GK_INSERT, GK_DELETE, GK_HOME, GK_END,
	GK_LEFT, GK_UP, GK_RIGHT, GK_DOWN,
	GK_PGUP, GK_PGDN,
	GK_PRINT,

	GK_F1, GK_F2, GK_F3, GK_F4, GK_F5, GK_F6, GK_F7, GK_F8, GK_F9, GK_F10, GK_F11, GK_F12,

	GK_LSHIFT, GK_RSHIFT,
	GK_LCTRL,  GK_RCTRL,
	GK_LALT,   GK_RALT,
	GK_LSUPER, GK_RSUPER,

	GK_SPECIAL_END,
};


struct gpudl_event_motion {
	float x;
	float y;
};

struct gpudl_event_button {
	int which;
	int pressed;
	float x;
	float y;
};

struct gpudl_event_key {
	int pressed;
	int code;
};

struct gpudl_event {
	int window_id;
	enum gpudl_event_type type;
	union {
		struct gpudl_event_motion motion;
		struct gpudl_event_button button;
		struct gpudl_event_key    key;
	};
};

void gpudl_init();
void gpudl_set_required_limits(WGPULimits* limits);
int gpudl_window_open(const char* title);
WGPUSurface gpudl_window_get_surface(int window_id);
void gpudl_window_get_size(int window_id, int* width, int* height);
void gpudl_window_close(int window_id);
void gpudl_get_wgpu(WGPUInstance* instance, WGPUAdapter* adapter, WGPUDevice* device, WGPUQueue* queue);
int gpudl_poll_event(struct gpudl_event* e);
WGPUTextureView gpudl_render_begin(int window_id);
void gpudl_render_end();
WGPUTextureFormat gpudl_get_preferred_swap_chain_texture_format();

#ifdef GPUDL_IMPLEMENTATION

// std
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <dlfcn.h>

#include <X11/Xlib.h>
#include <X11/keysym.h>

#define GPUDL__MAX_WINDOWS (256)

#define GPUDL_WGPU_PROC(NAME) WGPUProc##NAME wgpu##NAME;
GPUDL_WGPU_PROCS
#undef GPUDL_WGPU_PROC

struct gpudl__window {
	int id;
	WGPUSurface         wgpu_surface;
	WGPUSwapChain       wgpu_swap_chain;
	Window x11_window;
	int width;
	int height;
};

static struct gpudl__runtime {
	int is_initialized;

	int serial_counter;

	void* dh;
	WGPUInstance      wgpu_instance;
	WGPUAdapter       wgpu_adapter;
	WGPUDevice        wgpu_device;
	WGPUQueue         wgpu_queue;
	WGPUPresentMode   wgpu_present_mode;
	WGPUTextureFormat wgpu_swap_chain_format;

	WGPULimits limits;

	int n_windows;
	struct gpudl__window windows[GPUDL__MAX_WINDOWS];

	int rendering_window_id;
	WGPUTextureView rendering_swap_chain_texture_view;

	Display* x11_display;
	int      x11_screen;
	Window   x11_root_window;
	Visual*  x11_visual;
	int      x11_depth;
	Colormap x11_colormap;
	Atom     x11_WM_DELETE_WINDOW;
} gpudl__runtime;


static int gpudl__x_error_handler(Display* display, XErrorEvent* event) {
        fprintf(stderr, "X11 ERROR?\n");
	return 0;
}

void gpudl_init()
{
	if (gpudl__runtime.is_initialized) return;

	{
		// XXX users should probably have some options in how their
		// application finds the webgpu-native library?
		static const char* try_paths[] = {
			"./libwgpu_native.so", // <- name when doing `cargo build`
			"./libwgpu.so",        // <- name in releases
		};
		void* dh = NULL;
		for (int i = 0; i < (sizeof(try_paths) / sizeof(try_paths[0])); i++) {
			dh = dlopen(try_paths[i], RTLD_NOW | RTLD_GLOBAL);
			if (dh) break;
		}
		if (dh == NULL) {
			fprintf(stderr, "Could not find webgpu-native dynamic library\n");
			abort();
		}

		gpudl__runtime.dh = dh;
		assert(gpudl__runtime.dh != NULL && "could not load ./libwgpu_native.so");
		#define GPUDL_WGPU_PROC(NAME) \
			wgpu##NAME = dlsym(dh, "wgpu" #NAME); \
			if (wgpu##NAME == NULL) fprintf(stderr, "WARNING: symbol wgpu%s not found\n", #NAME);
		GPUDL_WGPU_PROCS
		#undef GPUDL_WGPU_PROC
	}

	gpudl__runtime.wgpu_instance = wgpuCreateInstance(&(WGPUInstanceDescriptor){});
	assert(gpudl__runtime.wgpu_instance && "wgpuCreateInstance() failed");

	gpudl__runtime.wgpu_present_mode = WGPUPresentMode_Fifo; // XXX

	gpudl__runtime.limits.maxBindGroups = 4;

	XSetErrorHandler(gpudl__x_error_handler);
	XInitThreads();

	gpudl__runtime.x11_display = XOpenDisplay(NULL);
	assert(gpudl__runtime.x11_display && "XOpenDisplay() failed");

	gpudl__runtime.x11_screen = DefaultScreen(gpudl__runtime.x11_display);
	gpudl__runtime.x11_root_window = XRootWindow(
		gpudl__runtime.x11_display,
		gpudl__runtime.x11_screen);
	gpudl__runtime.x11_visual = DefaultVisual(
		gpudl__runtime.x11_display,
		gpudl__runtime.x11_screen);
	gpudl__runtime.x11_depth = DefaultDepth(
		gpudl__runtime.x11_display,
		gpudl__runtime.x11_screen);
	gpudl__runtime.x11_colormap = XCreateColormap(
		gpudl__runtime.x11_display,
		gpudl__runtime.x11_root_window,
		gpudl__runtime.x11_visual,
		AllocNone);

}

void gpudl_set_required_limits(WGPULimits* limits)
{
	memcpy(&gpudl__runtime.limits, limits, sizeof *limits);
}

static int gpudl__get_next_serial()
{
	return ++gpudl__runtime.serial_counter;
}

static int gpudl__get_window_index(int id)
{
	const int n_windows = gpudl__runtime.n_windows;
	for (int i = 0; i < n_windows; i++) {
		struct gpudl__window* win = &gpudl__runtime.windows[i];
		if (win->id == id) return i;
	}
	fprintf(stderr, "no window with id %d\n", id);
	abort();
}

static struct gpudl__window* gpudl__get_window(int id)
{
	return &gpudl__runtime.windows[gpudl__get_window_index(id)];
}


// lifting some stuff from wgpu.h here...
#define gpudl__WGPUSType_DeviceExtras  (0x60000001)
#define gpudl__WGPUSType_AdapterExtras (0x60000002)
struct gpudl__WGPUAdapterExtras {
    WGPUChainedStruct chain;
    WGPUBackendType backend;
};

enum gpudl__WGPUNativeFeature {
    WGPUNativeFeature_TEXTURE_ADAPTER_SPECIFIC_FORMAT_FEATURES = 0x10000000
};

struct gpudl__WGPUDeviceExtras {
    WGPUChainedStruct chain;
    enum gpudl__WGPUNativeFeature nativeFeatures;
    const char* label;
    const char* tracePath;
};


static void gpudl__request_adapter_callback(WGPURequestAdapterStatus status, WGPUAdapter received, const char *message, void *userdata) {
	*(WGPUAdapter *)userdata = received;
}

static void gpudl__request_device_callback(WGPURequestDeviceStatus status, WGPUDevice received, const char *message, void *userdata) {
	*(WGPUDevice *)userdata = received;
}

static void gpudl__wgpu_error_callback(WGPUErrorType type, char const* message, void* userdata)
{
	const char* ts = NULL;
	switch (type) {
	case WGPUErrorType_NoError: ts = "(noerror)"; break;
	case WGPUErrorType_Validation: ts = "(validation)"; break;
	case WGPUErrorType_OutOfMemory: ts = "(outofmemory)"; break;
	case WGPUErrorType_Unknown: ts = "(unknown)"; break;
	case WGPUErrorType_DeviceLost: ts = "(devicelost)"; break;
	default: ts = "(unhandled)"; break;
	}
	assert(ts);
	fprintf(stderr, "WGPU UNCAPTURED ERROR %s: %s\n", ts, message);
}

static void gpudl__wgpu_post_init(struct gpudl__window* win)
{
	if (gpudl__runtime.wgpu_adapter) return;

	wgpuInstanceRequestAdapter(
		gpudl__runtime.wgpu_instance,
		&(WGPURequestAdapterOptions){
			.compatibleSurface = win->wgpu_surface,
			.nextInChain = (const WGPUChainedStruct*) &(struct gpudl__WGPUAdapterExtras) {
				.chain = (WGPUChainedStruct) {
					.next = NULL,
					.sType = gpudl__WGPUSType_AdapterExtras,
				},
				.backend = WGPUBackendType_Vulkan,
				//.backend = WGPUBackendType_OpenGL, // XXX not supported
				//.backend = WGPUBackendType_OpenGLES, // XXX not supported
			},
		},
		gpudl__request_adapter_callback,
		&gpudl__runtime.wgpu_adapter);
	assert((gpudl__runtime.wgpu_adapter != NULL) && "got no adapter; expected wgpuInstanceRequestAdapter() to not actually be async");

	WGPURequiredLimits* required_limits = &(WGPURequiredLimits){
		.nextInChain = NULL,
	};
	memcpy(&required_limits->limits, &gpudl__runtime.limits, sizeof required_limits->limits);

	wgpuAdapterRequestDevice(
		gpudl__runtime.wgpu_adapter,
		&(WGPUDeviceDescriptor){
			// XXX isn't this useless?
			.nextInChain = (const WGPUChainedStruct *)&(struct gpudl__WGPUDeviceExtras){
				.chain = (WGPUChainedStruct){
					.next = NULL,
					.sType = gpudl__WGPUSType_DeviceExtras,
				},
				.label = "Device",
				.tracePath = NULL,
			},
			.requiredLimits = required_limits,
		},
		gpudl__request_device_callback,
		&gpudl__runtime.wgpu_device);
	assert((gpudl__runtime.wgpu_device != NULL) && "got no device; expected wgpuAdapterRequestDevice() to not actually be async");


	gpudl__runtime.wgpu_queue = wgpuDeviceGetQueue(gpudl__runtime.wgpu_device);
	assert(gpudl__runtime.wgpu_queue);

	gpudl__runtime.wgpu_swap_chain_format = wgpuSurfaceGetPreferredFormat(win->wgpu_surface, gpudl__runtime.wgpu_adapter);

	wgpuDeviceSetUncapturedErrorCallback(gpudl__runtime.wgpu_device, gpudl__wgpu_error_callback, NULL);
}

int gpudl_window_open(const char* title)
{
	assert((gpudl__runtime.n_windows < GPUDL__MAX_WINDOWS) && "too many windowz!");
	struct gpudl__window* win = &gpudl__runtime.windows[gpudl__runtime.n_windows++];

	win->id = gpudl__get_next_serial();

	win->x11_window = XCreateWindow(
		gpudl__runtime.x11_display,
		gpudl__runtime.x11_root_window,
		0, 0,
		256, 256, // XXX default dimensions?
		0, // border width
		gpudl__runtime.x11_depth,
		InputOutput,
		gpudl__runtime.x11_visual,
		CWBorderPixel | CWColormap | CWEventMask,
		&(XSetWindowAttributes) {
			.background_pixmap = None,
			.colormap = gpudl__runtime.x11_colormap,
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
	assert(win->x11_window && "XCreateWindow() failed");

	XStoreName(gpudl__runtime.x11_display, win->x11_window, title);
	XMapWindow(gpudl__runtime.x11_display, win->x11_window);

	gpudl__runtime.x11_WM_DELETE_WINDOW = XInternAtom(gpudl__runtime.x11_display, "WM_DELETE_WINDOW", False);
	XSetWMProtocols(gpudl__runtime.x11_display, win->x11_window, &gpudl__runtime.x11_WM_DELETE_WINDOW, 1);

	win->wgpu_surface = wgpuInstanceCreateSurface(
		gpudl__runtime.wgpu_instance,
		&(WGPUSurfaceDescriptor){
			.label = NULL,
			.nextInChain = (const WGPUChainedStruct *)&(WGPUSurfaceDescriptorFromXlibWindow){
				.chain = (WGPUChainedStruct){
					.next = NULL,
					.sType = WGPUSType_SurfaceDescriptorFromXlibWindow,
				},
				.display = gpudl__runtime.x11_display,
				.window = win->x11_window,
			},
		}
	);
	assert(win->wgpu_surface);

	gpudl__wgpu_post_init(win);

	return win->id;
}

WGPUSurface gpudl_window_get_surface(int window_id)
{
	struct gpudl__window* win = gpudl__get_window(window_id);
	return win->wgpu_surface;
}

void gpudl_window_get_size(int window_id, int* width, int* height)
{
	struct gpudl__window* win = gpudl__get_window(window_id);
	if (width)  *width  = win->width;
	if (height) *height = win->height;
}

void gpudl_window_close(int window_id)
{
	int index = gpudl__get_window_index(window_id);
	struct gpudl__window* win = &gpudl__runtime.windows[index];
	XDestroyWindow(gpudl__runtime.x11_display, win->x11_window);
	int n_move = (gpudl__runtime.n_windows - index) - 1;
	if (n_move > 0) {
		memmove(
			&gpudl__runtime.windows[index],
			&gpudl__runtime.windows[index+1],
			n_move * sizeof(gpudl__runtime.windows[0])
		);
	}
	gpudl__runtime.n_windows--;
}

void gpudl_get_wgpu(WGPUInstance* instance, WGPUAdapter* adapter, WGPUDevice* device, WGPUQueue* queue)
{
	if (instance) {
		assert((gpudl__runtime.wgpu_instance != NULL) && "no wgpu instance yet; did you forget gpudl_init()?");
		*instance = gpudl__runtime.wgpu_instance;
	}

	if (adapter) {
		assert((gpudl__runtime.wgpu_adapter != NULL) && "no wgpu adapter yet; it is available after first gpudl_window_open() call");
		*adapter = gpudl__runtime.wgpu_adapter;
	}

	if (device) {
		assert((gpudl__runtime.wgpu_adapter != NULL) && "no wgpu device yet; it is available after first gpudl_window_open() call");
		*device = gpudl__runtime.wgpu_device;
	}

	if (queue) {
		assert((gpudl__runtime.wgpu_adapter != NULL) && "no wgpu queue yet; it is available after first gpudl_window_open() call");
		*queue = gpudl__runtime.wgpu_queue;
	}
}

int gpudl_poll_event(struct gpudl_event* e)
{
	memset(e, 0, sizeof *e);
	while (XPending(gpudl__runtime.x11_display)) {
		XEvent xe;
		XNextEvent(gpudl__runtime.x11_display, &xe);
		Window w = xe.xany.window;
		if (XFilterEvent(&xe, w)) continue;

		struct gpudl__window* win = NULL;
		const int n_windows = gpudl__runtime.n_windows;
		for (int i = 0; i < n_windows; i++) {
			struct gpudl__window* maybe_win = &gpudl__runtime.windows[i];
			if (maybe_win->x11_window == w) {
				win = maybe_win;
				break;
			}
		}
		if (win == NULL) continue;

		e->window_id = win->id;

		switch (xe.type) {
		case ConfigureNotify:
			if (xe.xconfigure.width != win->width || xe.xconfigure.height != win->height) {
				printf("EV: configure %d×%d -> %d×%d\n", win->width, win->height, xe.xconfigure.width, xe.xconfigure.height);
				win->width = xe.xconfigure.width;
				win->height = xe.xconfigure.height;

				win->wgpu_swap_chain = wgpuDeviceCreateSwapChain(
					gpudl__runtime.wgpu_device,
					win->wgpu_surface,
					&(WGPUSwapChainDescriptor){
						.usage = WGPUTextureUsage_RenderAttachment,
						.format = gpudl__runtime.wgpu_swap_chain_format,
						.width = win->width,
						.height = win->height,
						.presentMode = gpudl__runtime.wgpu_present_mode,
					}
				);
				assert(win->wgpu_swap_chain);
				assert((win->wgpu_surface == (WGPUSurface)win->wgpu_swap_chain) && "wgpu-native assumption: wgpuDeviceCreateSwapChain() should return the passed surface; otherwise this code must free the previous swap chain?");
			}
			break;
		case EnterNotify:
			e->type = GPUDL_ENTER;
			return 1;
		case LeaveNotify:
			e->type = GPUDL_LEAVE;
			return 1;
		case FocusIn:
			e->type = GPUDL_FOCUS;
			return 1;
		case FocusOut:
			e->type = GPUDL_UNFOCUS;
			return 1;
		case ButtonPress:
		case ButtonRelease:
			e->type = GPUDL_BUTTON;
			if (1 <= xe.xbutton.button && xe.xbutton.button <= 3) {
				e->button.which = xe.xbutton.button;
				e->button.pressed = (xe.type == ButtonPress);
				e->button.x = xe.xbutton.x;
				e->button.y = xe.xbutton.y;
				return 1;
			}
			break;
		case MotionNotify:
			e->type = GPUDL_MOTION;
			e->motion.x = xe.xmotion.x;
			e->motion.y = xe.xmotion.y;
			return 1;
		case KeyPress:
		case KeyRelease: {
			e->type = GPUDL_KEY;
			e->key.pressed = (xe.type == KeyPress);
			KeySym sym = XLookupKeysym(&xe.xkey, 0);
			int code = GK_UNKNOWN;
			if (' ' <= sym && sym <= '~') {
				// simple 1:1 key<->ascii mapping
				code = sym;
			} else {
				switch (sym) {
				// some convenient ASCII mappings (like in SDL2)
				case XK_Escape:    code = '\033'; break;
				case XK_Tab:       code = '\t';   break;
				case XK_BackSpace: code = '\b';   break;
				case XK_Return:    code = '\r';   break;

				case XK_Insert:       code = GK_INSERT;   break;
				case XK_Delete:       code = GK_DELETE;   break;
				case XK_Home:         code = GK_HOME;     break;
				case XK_End:          code = GK_END;      break;
				case XK_Left:         code = GK_LEFT;     break;
				case XK_Up:           code = GK_UP;       break;
				case XK_Right:        code = GK_RIGHT;    break;
				case XK_Down:         code = GK_DOWN;     break;
				case XK_Page_Up:      code = GK_PGUP;     break;
				case XK_Page_Down:    code = GK_PGDN;     break;

				case XK_F1:           code = GK_F1;   break;
				case XK_F2:           code = GK_F2;   break;
				case XK_F3:           code = GK_F3;   break;
				case XK_F4:           code = GK_F4;   break;
				case XK_F5:           code = GK_F5;   break;
				case XK_F6:           code = GK_F6;   break;
				case XK_F7:           code = GK_F7;   break;
				case XK_F8:           code = GK_F8;   break;
				case XK_F9:           code = GK_F9;   break;
				case XK_F10:          code = GK_F10;  break;
				case XK_F11:          code = GK_F11;  break;
				case XK_F12:          code = GK_F12;  break;

				case XK_Shift_L:      code = GK_LSHIFT;  break;
				case XK_Shift_R:      code = GK_RSHIFT;  break;
				case XK_Control_L:    code = GK_LCTRL;   break;
				case XK_Control_R:    code = GK_RCTRL;   break;
				case XK_Alt_L:        code = GK_LALT;    break;
				case XK_Alt_R:        code = GK_RALT;    break;
				case XK_Super_L:      code = GK_LSUPER;  break;
				case XK_Super_R:      code = GK_RSUPER;  break;

				case XK_Print:        code = GK_PRINT;   break;

				default:              code = GK_UNKNOWN; break;
				}
			}
			e->key.code = code;
			return 1;
			} break;
		case ClientMessage: {
			const Atom protocol = xe.xclient.data.l[0];
			if (protocol == gpudl__runtime.x11_WM_DELETE_WINDOW) {
				e->type = GPUDL_CLOSE;
				return 1;
			}
			break;
		}
		default: break;
		}
	}

	return 0;
}

WGPUTextureView gpudl_render_begin(int window_id)
{
	assert((window_id > 0) && "invalid window id");
	assert((gpudl__runtime.rendering_window_id == 0) && "already rendering a window");
	struct gpudl__window* win = gpudl__get_window(window_id);
	if (!win->wgpu_swap_chain) {
		return NULL;
	}
	WGPUTextureView view = wgpuSwapChainGetCurrentTextureView(win->wgpu_swap_chain);
	if (view != NULL) {
		gpudl__runtime.rendering_swap_chain_texture_view = view;
		gpudl__runtime.rendering_window_id = win->id;
		return view;
	} else {
		return NULL;
	}
}

void gpudl_render_end()
{
	assert((gpudl__runtime.rendering_window_id > 0) && "not rendering a window");
	struct gpudl__window* win = gpudl__get_window(gpudl__runtime.rendering_window_id);
	wgpuSwapChainPresent(win->wgpu_swap_chain);
	gpudl__runtime.rendering_window_id = 0;
	wgpuTextureViewDrop(gpudl__runtime.rendering_swap_chain_texture_view);
	gpudl__runtime.rendering_swap_chain_texture_view = NULL;
}

WGPUTextureFormat gpudl_get_preferred_swap_chain_texture_format()
{
	return gpudl__runtime.wgpu_swap_chain_format;
}

#if 0
struct WgpuxBufferMapResult {
	WGPUBufferMapAsyncStatus status;
};

static void wgpuxBufferMapCallback(WGPUBufferMapAsyncStatus status, void* userdata)
{
	struct WgpuxBufferMapResult* result = userdata;
	result->status = status;
}

// Non-standard synchronous buffer mapping. In practice this is only useful for
// _reading_ buffers, because wgpuQueueWriteBuffer() is more convenient for
// _writing_ buffers.
// NOTE: this goes against the WebGPU standard which is asynchronous in nature,
// but I'm putting my money on this eventually being "fixed in the substrate",
// e.g. see:
//   https://github.com/WebAssembly/WASI/issues/276
// i.e. WASM would be able to pause/restart on bytecode level in order to
// support synchronous programming
// XXX can I avoid WGPUDevice?
static void* wgpuBufferMap(WGPUDevice device, WGPUBuffer buffer, WGPUMapModeFlags mode, size_t offset, size_t size)
{
	struct WgpuxBufferMapResult result;
	const int tracer = 0x12344321;
	result.status = tracer;
	wgpuBufferMapAsync(buffer, mode, offset, size, wgpuxBufferMapCallback, &result);
	wgpuDevicePoll(device, true); // XXX non-standard
	assert((result.status != tracer) && "callback not called");
	if (result.status == WGPUBufferMapAsyncStatus_Success) {
		return wgpuBufferGetMappedRange(buffer, offset, size);
	} else {
		return NULL;
	}
}
#endif

#endif //GPUDL_IMPLEMENTATION

#define GPUDL_H_
#endif
