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
	GPUDL_WGPU_PROC(ComputePassEncoderDispatchWorkgroups) \
	GPUDL_WGPU_PROC(ComputePassEncoderDispatchWorkgroupsIndirect) \
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

enum gpudl_button {
	GPUDL_BUTTON_LEFT,
	GPUDL_BUTTON_MIDDLE,
	GPUDL_BUTTON_RIGHT,
	//GPUDL_BUTTON_X1,
	//GPUDL_BUTTON_X2,
	GPUDL_BUTTON_END,
};

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

enum gpudl_system_cursor {
	GPUDL_CURSOR_DEFAULT = 0,
	GPUDL_CURSOR_HAND,
	GPUDL_CURSOR_H_ARROW,
	GPUDL_CURSOR_V_ARROW,
	GPUDL_CURSOR_CROSS,
	GPUDL_CURSOR_END
};

#define GPUDL_KEYS \
	GPUDL_KEY(INSERT) \
	GPUDL_KEY(DELETE) \
	GPUDL_KEY(HOME) \
	GPUDL_KEY(END) \
	GPUDL_KEY(LEFT) \
	GPUDL_KEY(UP) \
	GPUDL_KEY(RIGHT) \
	GPUDL_KEY(DOWN) \
	GPUDL_KEY(PGUP) \
	GPUDL_KEY(PGDN) \
	GPUDL_KEY(PRINT) \
	GPUDL_KEY(F1) \
	GPUDL_KEY(F2) \
	GPUDL_KEY(F3) \
	GPUDL_KEY(F4) \
	GPUDL_KEY(F5) \
	GPUDL_KEY(F6) \
	GPUDL_KEY(F7) \
	GPUDL_KEY(F8) \
	GPUDL_KEY(F9) \
	GPUDL_KEY(F10) \
	GPUDL_KEY(F11) \
	GPUDL_KEY(F12) \
	GPUDL_KEY(LSHIFT) \
	GPUDL_KEY(RSHIFT) \
	GPUDL_KEY(LCTRL) \
	GPUDL_KEY(RCTRL) \
	GPUDL_KEY(LALT) \
	GPUDL_KEY(RALT) \
	GPUDL_KEY(LSUPER) \
	GPUDL_KEY(RSUPER)

enum gpudl_special_keysym {
	GK_UNKNOWN = -1,
	GK_SPECIAL_BEGIN = 1<<24, // safely outside of unicode's 21-bit codepoint range
	#define GPUDL_KEY(K) GK_ ## K,
	GPUDL_KEYS
	#undef GPUDL_KEY
	GK_SPECIAL_END,
};

struct gpudl_event_motion {
	float x;
	float y;
};

struct gpudl_event_button {
	enum gpudl_button which;
	int pressed;
	float x;
	float y;
};

// About key events...
//  - The keysym for a printable character, or a control code, is its unicode
//    codepoint value. The keysym ignores modifier keys, i.e. for [shift]+[a]
//    you get {.pressed=1,.keysym='a',.codepoint='A'}
//  - Special keys like F1-F12, HOME, arrow keys, etc, are defined as GK_*, and
//    have values safely outside of unicode's 21-bit codepoint range
//  - codepoint is non-zero when a keypress sends text input. codepoint is
//    always zero for release events (pressed==0)
struct gpudl_event_key {
	int pressed;
	int keysym;
	int codepoint;
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
void gpudl_render_end(void);
WGPUTextureFormat gpudl_get_preferred_swap_chain_texture_format();
void gpudl_set_cursor(int cursor);
int gpudl_make_bitmap_cursor(const char* bitmap);
int gpudl_utf8_decode(const char** c0z, int* n);

#ifdef GPUDL_IMPLEMENTATION

// std
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <dlfcn.h>

#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <X11/cursorfont.h>

#define GPUDL__MAX_WINDOWS (256)

#define GPUDL_WGPU_PROC(NAME) WGPUProc##NAME wgpu##NAME;
GPUDL_WGPU_PROCS
#undef GPUDL_WGPU_PROC

struct gpudl__window {
	int id;
	WGPUSurface         wgpu_surface;
	WGPUSwapChain       wgpu_swap_chain;
	Window x11_window;
	XIC    x11_ic;
	int width;
	int height;
};

#define GPUDL__MAX_CURSORS (256)
struct gpudl__cursor {
	int in_use;
	Cursor cursor;
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
	XIM      x11_im;

	XColor   x11_color_white;
	XColor   x11_color_black;

	struct gpudl__cursor cursors[GPUDL__MAX_CURSORS];
} gpudl__runtime;


static int gpudl__x_error_handler(Display* display, XErrorEvent* event) {
        fprintf(stderr, "X11 ERROR?\n");
	return 0;
}

int gpudl_utf8_decode(const char** c0z, int* n)
{
	const unsigned char** c0 = (const unsigned char**)c0z;
	if (*n <= 0) return -1;
	unsigned char c = **c0;
	(*n)--;
	(*c0)++;
	if ((c & 0x80) == 0) return c & 0x7f;
	int mask = 192;
	int d;
	for (d = 1; d <= 3; d++) {
		int match = mask;
		mask = (mask >> 1) | 0x80;
		if ((c & mask) == match) {
			int codepoint = (c & ~mask) << (6*d);
			while (d > 0 && *n > 0) {
				c = **c0;
				if ((c & 192) != 128) return -1;
				(*c0)++;
				(*n)--;
				d--;
				codepoint += (c & 63) << (6*d);
			}
			return d == 0 ? codepoint : -1;
		}
	}
	return -1;
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
	gpudl__runtime.x11_im = XOpenIM(
		gpudl__runtime.x11_display,
		NULL, NULL, NULL);

	for (enum gpudl_system_cursor i = 0; i < GPUDL_CURSOR_END; i++) {
		unsigned int shape;
		switch (i) {
			case GPUDL_CURSOR_DEFAULT: shape = XC_left_ptr; break;
			case GPUDL_CURSOR_HAND:    shape = XC_hand1; break;
			case GPUDL_CURSOR_H_ARROW: shape = XC_sb_h_double_arrow; break;
			case GPUDL_CURSOR_V_ARROW: shape = XC_sb_v_double_arrow; break;
			case GPUDL_CURSOR_CROSS:   shape = XC_fleur; break;
			case GPUDL_CURSOR_END: break;
		}
		gpudl__runtime.cursors[i].cursor = XCreateFontCursor(gpudl__runtime.x11_display, shape);
		gpudl__runtime.cursors[i].in_use = 1;
	}

	gpudl__runtime.x11_color_white.red = 0xffff;
	gpudl__runtime.x11_color_white.green = 0xffff;
	gpudl__runtime.x11_color_white.blue = 0xffff;
	gpudl__runtime.x11_color_black.red = 0;
	gpudl__runtime.x11_color_black.green = 0;
	gpudl__runtime.x11_color_black.blue = 0;

	XAllocColor(gpudl__runtime.x11_display, gpudl__runtime.x11_colormap, &gpudl__runtime.x11_color_white);
	XAllocColor(gpudl__runtime.x11_display, gpudl__runtime.x11_colormap, &gpudl__runtime.x11_color_black);
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

	win->x11_ic = XCreateIC(
		gpudl__runtime.x11_im,
		XNInputStyle,
		XIMPreeditNothing | XIMStatusNothing,
		XNClientWindow,
		win->x11_window,
		XNFocusWindow,
		win->x11_window,
		NULL);
	assert(win->x11_ic != NULL);

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

		if (XFilterEvent(&xe, None)) continue;

		struct gpudl__window* win = NULL;
		const int n_windows = gpudl__runtime.n_windows;
		for (int i = 0; i < n_windows; i++) {
			struct gpudl__window* maybe_win = &gpudl__runtime.windows[i];
			if (maybe_win->x11_window == xe.xany.window) {
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
		case ButtonRelease: {
			e->type = GPUDL_BUTTON;
			const int b = xe.xbutton.button;
			if (1 <= b && b <= 3) {
				e->button.which =
					b == 1 ? GPUDL_BUTTON_LEFT :
					b == 2 ? GPUDL_BUTTON_MIDDLE :
					b == 3 ? GPUDL_BUTTON_RIGHT : 0;
				e->button.pressed = (xe.type == ButtonPress);
				e->button.x = xe.xbutton.x;
				e->button.y = xe.xbutton.y;
				return 1;
			}
			} break;
		case MotionNotify:
			e->type = GPUDL_MOTION;
			e->motion.x = xe.xmotion.x;
			e->motion.y = xe.xmotion.y;
			return 1;
		case KeyPress:
		case KeyRelease: {
			e->type = GPUDL_KEY;
			struct gpudl_event_key* ke = &e->key;

			ke->pressed = (xe.type == KeyPress);

			KeySym sym = XLookupKeysym(&xe.xkey, 0);
			{
				int ks;
				sym = XLookupKeysym(&xe.xkey, 0);
				if (32 <= sym && sym <= 255) {
					// there's an 1:1 relation between
					// KeySym/latin-1/unicode
					ks = sym;
				} else {
					switch (sym) {

					case XK_Escape:    ks = '\033'; break;
					case XK_Tab:       ks = '\t';   break;
					case XK_BackSpace: ks = '\b';   break;
					case XK_Return:    ks = '\r';   break;

					case XK_Insert:       ks = GK_INSERT;  break;
					case XK_Delete:       ks = GK_DELETE;  break;
					case XK_Home:         ks = GK_HOME;    break;
					case XK_End:          ks = GK_END;     break;
					case XK_Left:         ks = GK_LEFT;    break;
					case XK_Up:           ks = GK_UP;      break;
					case XK_Right:        ks = GK_RIGHT;   break;
					case XK_Down:         ks = GK_DOWN;    break;
					case XK_Page_Up:      ks = GK_PGUP;    break;
					case XK_Page_Down:    ks = GK_PGDN;    break;
					case XK_Print:        ks = GK_PRINT;   break;

					case XK_F1:           ks = GK_F1;   break;
					case XK_F2:           ks = GK_F2;   break;
					case XK_F3:           ks = GK_F3;   break;
					case XK_F4:           ks = GK_F4;   break;
					case XK_F5:           ks = GK_F5;   break;
					case XK_F6:           ks = GK_F6;   break;
					case XK_F7:           ks = GK_F7;   break;
					case XK_F8:           ks = GK_F8;   break;
					case XK_F9:           ks = GK_F9;   break;
					case XK_F10:          ks = GK_F10;  break;
					case XK_F11:          ks = GK_F11;  break;
					case XK_F12:          ks = GK_F12;  break;

					case XK_Shift_L:      ks = GK_LSHIFT;  break;
					case XK_Shift_R:      ks = GK_RSHIFT;  break;
					case XK_Control_L:    ks = GK_LCTRL;   break;
					case XK_Control_R:    ks = GK_RCTRL;   break;
					case XK_Alt_L:        ks = GK_LALT;    break;
					case XK_Alt_R:        ks = GK_RALT;    break;
					case XK_Super_L:      ks = GK_LSUPER;  break;
					case XK_Super_R:      ks = GK_RSUPER;  break;

					// auto-generated with `./keysymdef_converter.py /usr/include/X11/keysymdef.h`
					case 0x1a1: ks = 0x0104; break; // XK_Aogonek / LATIN CAPITAL LETTER A WITH OGONEK
					case 0x1a2: ks = 0x02D8; break; // XK_breve / BREVE
					case 0x1a3: ks = 0x0141; break; // XK_Lstroke / LATIN CAPITAL LETTER L WITH STROKE
					case 0x1a5: ks = 0x013D; break; // XK_Lcaron / LATIN CAPITAL LETTER L WITH CARON
					case 0x1a6: ks = 0x015A; break; // XK_Sacute / LATIN CAPITAL LETTER S WITH ACUTE
					case 0x1a9: ks = 0x0160; break; // XK_Scaron / LATIN CAPITAL LETTER S WITH CARON
					case 0x1aa: ks = 0x015E; break; // XK_Scedilla / LATIN CAPITAL LETTER S WITH CEDILLA
					case 0x1ab: ks = 0x0164; break; // XK_Tcaron / LATIN CAPITAL LETTER T WITH CARON
					case 0x1ac: ks = 0x0179; break; // XK_Zacute / LATIN CAPITAL LETTER Z WITH ACUTE
					case 0x1ae: ks = 0x017D; break; // XK_Zcaron / LATIN CAPITAL LETTER Z WITH CARON
					case 0x1af: ks = 0x017B; break; // XK_Zabovedot / LATIN CAPITAL LETTER Z WITH DOT ABOVE
					case 0x1b1: ks = 0x0105; break; // XK_aogonek / LATIN SMALL LETTER A WITH OGONEK
					case 0x1b2: ks = 0x02DB; break; // XK_ogonek / OGONEK
					case 0x1b3: ks = 0x0142; break; // XK_lstroke / LATIN SMALL LETTER L WITH STROKE
					case 0x1b5: ks = 0x013E; break; // XK_lcaron / LATIN SMALL LETTER L WITH CARON
					case 0x1b6: ks = 0x015B; break; // XK_sacute / LATIN SMALL LETTER S WITH ACUTE
					case 0x1b7: ks = 0x02C7; break; // XK_caron / CARON
					case 0x1b9: ks = 0x0161; break; // XK_scaron / LATIN SMALL LETTER S WITH CARON
					case 0x1ba: ks = 0x015F; break; // XK_scedilla / LATIN SMALL LETTER S WITH CEDILLA
					case 0x1bb: ks = 0x0165; break; // XK_tcaron / LATIN SMALL LETTER T WITH CARON
					case 0x1bc: ks = 0x017A; break; // XK_zacute / LATIN SMALL LETTER Z WITH ACUTE
					case 0x1bd: ks = 0x02DD; break; // XK_doubleacute / DOUBLE ACUTE ACCENT
					case 0x1be: ks = 0x017E; break; // XK_zcaron / LATIN SMALL LETTER Z WITH CARON
					case 0x1bf: ks = 0x017C; break; // XK_zabovedot / LATIN SMALL LETTER Z WITH DOT ABOVE
					case 0x1c0: ks = 0x0154; break; // XK_Racute / LATIN CAPITAL LETTER R WITH ACUTE
					case 0x1c3: ks = 0x0102; break; // XK_Abreve / LATIN CAPITAL LETTER A WITH BREVE
					case 0x1c5: ks = 0x0139; break; // XK_Lacute / LATIN CAPITAL LETTER L WITH ACUTE
					case 0x1c6: ks = 0x0106; break; // XK_Cacute / LATIN CAPITAL LETTER C WITH ACUTE
					case 0x1c8: ks = 0x010C; break; // XK_Ccaron / LATIN CAPITAL LETTER C WITH CARON
					case 0x1ca: ks = 0x0118; break; // XK_Eogonek / LATIN CAPITAL LETTER E WITH OGONEK
					case 0x1cc: ks = 0x011A; break; // XK_Ecaron / LATIN CAPITAL LETTER E WITH CARON
					case 0x1cf: ks = 0x010E; break; // XK_Dcaron / LATIN CAPITAL LETTER D WITH CARON
					case 0x1d0: ks = 0x0110; break; // XK_Dstroke / LATIN CAPITAL LETTER D WITH STROKE
					case 0x1d1: ks = 0x0143; break; // XK_Nacute / LATIN CAPITAL LETTER N WITH ACUTE
					case 0x1d2: ks = 0x0147; break; // XK_Ncaron / LATIN CAPITAL LETTER N WITH CARON
					case 0x1d5: ks = 0x0150; break; // XK_Odoubleacute / LATIN CAPITAL LETTER O WITH DOUBLE ACUTE
					case 0x1d8: ks = 0x0158; break; // XK_Rcaron / LATIN CAPITAL LETTER R WITH CARON
					case 0x1d9: ks = 0x016E; break; // XK_Uring / LATIN CAPITAL LETTER U WITH RING ABOVE
					case 0x1db: ks = 0x0170; break; // XK_Udoubleacute / LATIN CAPITAL LETTER U WITH DOUBLE ACUTE
					case 0x1de: ks = 0x0162; break; // XK_Tcedilla / LATIN CAPITAL LETTER T WITH CEDILLA
					case 0x1e0: ks = 0x0155; break; // XK_racute / LATIN SMALL LETTER R WITH ACUTE
					case 0x1e3: ks = 0x0103; break; // XK_abreve / LATIN SMALL LETTER A WITH BREVE
					case 0x1e5: ks = 0x013A; break; // XK_lacute / LATIN SMALL LETTER L WITH ACUTE
					case 0x1e6: ks = 0x0107; break; // XK_cacute / LATIN SMALL LETTER C WITH ACUTE
					case 0x1e8: ks = 0x010D; break; // XK_ccaron / LATIN SMALL LETTER C WITH CARON
					case 0x1ea: ks = 0x0119; break; // XK_eogonek / LATIN SMALL LETTER E WITH OGONEK
					case 0x1ec: ks = 0x011B; break; // XK_ecaron / LATIN SMALL LETTER E WITH CARON
					case 0x1ef: ks = 0x010F; break; // XK_dcaron / LATIN SMALL LETTER D WITH CARON
					case 0x1f0: ks = 0x0111; break; // XK_dstroke / LATIN SMALL LETTER D WITH STROKE
					case 0x1f1: ks = 0x0144; break; // XK_nacute / LATIN SMALL LETTER N WITH ACUTE
					case 0x1f2: ks = 0x0148; break; // XK_ncaron / LATIN SMALL LETTER N WITH CARON
					case 0x1f5: ks = 0x0151; break; // XK_odoubleacute / LATIN SMALL LETTER O WITH DOUBLE ACUTE
					case 0x1f8: ks = 0x0159; break; // XK_rcaron / LATIN SMALL LETTER R WITH CARON
					case 0x1f9: ks = 0x016F; break; // XK_uring / LATIN SMALL LETTER U WITH RING ABOVE
					case 0x1fb: ks = 0x0171; break; // XK_udoubleacute / LATIN SMALL LETTER U WITH DOUBLE ACUTE
					case 0x1fe: ks = 0x0163; break; // XK_tcedilla / LATIN SMALL LETTER T WITH CEDILLA
					case 0x1ff: ks = 0x02D9; break; // XK_abovedot / DOT ABOVE
					case 0x2a1: ks = 0x0126; break; // XK_Hstroke / LATIN CAPITAL LETTER H WITH STROKE
					case 0x2a6: ks = 0x0124; break; // XK_Hcircumflex / LATIN CAPITAL LETTER H WITH CIRCUMFLEX
					case 0x2a9: ks = 0x0130; break; // XK_Iabovedot / LATIN CAPITAL LETTER I WITH DOT ABOVE
					case 0x2ab: ks = 0x011E; break; // XK_Gbreve / LATIN CAPITAL LETTER G WITH BREVE
					case 0x2ac: ks = 0x0134; break; // XK_Jcircumflex / LATIN CAPITAL LETTER J WITH CIRCUMFLEX
					case 0x2b1: ks = 0x0127; break; // XK_hstroke / LATIN SMALL LETTER H WITH STROKE
					case 0x2b6: ks = 0x0125; break; // XK_hcircumflex / LATIN SMALL LETTER H WITH CIRCUMFLEX
					case 0x2b9: ks = 0x0131; break; // XK_idotless / LATIN SMALL LETTER DOTLESS I
					case 0x2bb: ks = 0x011F; break; // XK_gbreve / LATIN SMALL LETTER G WITH BREVE
					case 0x2bc: ks = 0x0135; break; // XK_jcircumflex / LATIN SMALL LETTER J WITH CIRCUMFLEX
					case 0x2c5: ks = 0x010A; break; // XK_Cabovedot / LATIN CAPITAL LETTER C WITH DOT ABOVE
					case 0x2c6: ks = 0x0108; break; // XK_Ccircumflex / LATIN CAPITAL LETTER C WITH CIRCUMFLEX
					case 0x2d5: ks = 0x0120; break; // XK_Gabovedot / LATIN CAPITAL LETTER G WITH DOT ABOVE
					case 0x2d8: ks = 0x011C; break; // XK_Gcircumflex / LATIN CAPITAL LETTER G WITH CIRCUMFLEX
					case 0x2dd: ks = 0x016C; break; // XK_Ubreve / LATIN CAPITAL LETTER U WITH BREVE
					case 0x2de: ks = 0x015C; break; // XK_Scircumflex / LATIN CAPITAL LETTER S WITH CIRCUMFLEX
					case 0x2e5: ks = 0x010B; break; // XK_cabovedot / LATIN SMALL LETTER C WITH DOT ABOVE
					case 0x2e6: ks = 0x0109; break; // XK_ccircumflex / LATIN SMALL LETTER C WITH CIRCUMFLEX
					case 0x2f5: ks = 0x0121; break; // XK_gabovedot / LATIN SMALL LETTER G WITH DOT ABOVE
					case 0x2f8: ks = 0x011D; break; // XK_gcircumflex / LATIN SMALL LETTER G WITH CIRCUMFLEX
					case 0x2fd: ks = 0x016D; break; // XK_ubreve / LATIN SMALL LETTER U WITH BREVE
					case 0x2fe: ks = 0x015D; break; // XK_scircumflex / LATIN SMALL LETTER S WITH CIRCUMFLEX
					case 0x3a2: ks = 0x0138; break; // XK_kra / LATIN SMALL LETTER KRA
					case 0x3a3: ks = 0x0156; break; // XK_Rcedilla / LATIN CAPITAL LETTER R WITH CEDILLA
					case 0x3a5: ks = 0x0128; break; // XK_Itilde / LATIN CAPITAL LETTER I WITH TILDE
					case 0x3a6: ks = 0x013B; break; // XK_Lcedilla / LATIN CAPITAL LETTER L WITH CEDILLA
					case 0x3aa: ks = 0x0112; break; // XK_Emacron / LATIN CAPITAL LETTER E WITH MACRON
					case 0x3ab: ks = 0x0122; break; // XK_Gcedilla / LATIN CAPITAL LETTER G WITH CEDILLA
					case 0x3ac: ks = 0x0166; break; // XK_Tslash / LATIN CAPITAL LETTER T WITH STROKE
					case 0x3b3: ks = 0x0157; break; // XK_rcedilla / LATIN SMALL LETTER R WITH CEDILLA
					case 0x3b5: ks = 0x0129; break; // XK_itilde / LATIN SMALL LETTER I WITH TILDE
					case 0x3b6: ks = 0x013C; break; // XK_lcedilla / LATIN SMALL LETTER L WITH CEDILLA
					case 0x3ba: ks = 0x0113; break; // XK_emacron / LATIN SMALL LETTER E WITH MACRON
					case 0x3bb: ks = 0x0123; break; // XK_gcedilla / LATIN SMALL LETTER G WITH CEDILLA
					case 0x3bc: ks = 0x0167; break; // XK_tslash / LATIN SMALL LETTER T WITH STROKE
					case 0x3bd: ks = 0x014A; break; // XK_ENG / LATIN CAPITAL LETTER ENG
					case 0x3bf: ks = 0x014B; break; // XK_eng / LATIN SMALL LETTER ENG
					case 0x3c0: ks = 0x0100; break; // XK_Amacron / LATIN CAPITAL LETTER A WITH MACRON
					case 0x3c7: ks = 0x012E; break; // XK_Iogonek / LATIN CAPITAL LETTER I WITH OGONEK
					case 0x3cc: ks = 0x0116; break; // XK_Eabovedot / LATIN CAPITAL LETTER E WITH DOT ABOVE
					case 0x3cf: ks = 0x012A; break; // XK_Imacron / LATIN CAPITAL LETTER I WITH MACRON
					case 0x3d1: ks = 0x0145; break; // XK_Ncedilla / LATIN CAPITAL LETTER N WITH CEDILLA
					case 0x3d2: ks = 0x014C; break; // XK_Omacron / LATIN CAPITAL LETTER O WITH MACRON
					case 0x3d3: ks = 0x0136; break; // XK_Kcedilla / LATIN CAPITAL LETTER K WITH CEDILLA
					case 0x3d9: ks = 0x0172; break; // XK_Uogonek / LATIN CAPITAL LETTER U WITH OGONEK
					case 0x3dd: ks = 0x0168; break; // XK_Utilde / LATIN CAPITAL LETTER U WITH TILDE
					case 0x3de: ks = 0x016A; break; // XK_Umacron / LATIN CAPITAL LETTER U WITH MACRON
					case 0x3e0: ks = 0x0101; break; // XK_amacron / LATIN SMALL LETTER A WITH MACRON
					case 0x3e7: ks = 0x012F; break; // XK_iogonek / LATIN SMALL LETTER I WITH OGONEK
					case 0x3ec: ks = 0x0117; break; // XK_eabovedot / LATIN SMALL LETTER E WITH DOT ABOVE
					case 0x3ef: ks = 0x012B; break; // XK_imacron / LATIN SMALL LETTER I WITH MACRON
					case 0x3f1: ks = 0x0146; break; // XK_ncedilla / LATIN SMALL LETTER N WITH CEDILLA
					case 0x3f2: ks = 0x014D; break; // XK_omacron / LATIN SMALL LETTER O WITH MACRON
					case 0x3f3: ks = 0x0137; break; // XK_kcedilla / LATIN SMALL LETTER K WITH CEDILLA
					case 0x3f9: ks = 0x0173; break; // XK_uogonek / LATIN SMALL LETTER U WITH OGONEK
					case 0x3fd: ks = 0x0169; break; // XK_utilde / LATIN SMALL LETTER U WITH TILDE
					case 0x3fe: ks = 0x016B; break; // XK_umacron / LATIN SMALL LETTER U WITH MACRON
					case 0x1000174: ks = 0x0174; break; // XK_Wcircumflex / LATIN CAPITAL LETTER W WITH CIRCUMFLEX
					case 0x1000175: ks = 0x0175; break; // XK_wcircumflex / LATIN SMALL LETTER W WITH CIRCUMFLEX
					case 0x1000176: ks = 0x0176; break; // XK_Ycircumflex / LATIN CAPITAL LETTER Y WITH CIRCUMFLEX
					case 0x1000177: ks = 0x0177; break; // XK_ycircumflex / LATIN SMALL LETTER Y WITH CIRCUMFLEX
					case 0x1001e02: ks = 0x1E02; break; // XK_Babovedot / LATIN CAPITAL LETTER B WITH DOT ABOVE
					case 0x1001e03: ks = 0x1E03; break; // XK_babovedot / LATIN SMALL LETTER B WITH DOT ABOVE
					case 0x1001e0a: ks = 0x1E0A; break; // XK_Dabovedot / LATIN CAPITAL LETTER D WITH DOT ABOVE
					case 0x1001e0b: ks = 0x1E0B; break; // XK_dabovedot / LATIN SMALL LETTER D WITH DOT ABOVE
					case 0x1001e1e: ks = 0x1E1E; break; // XK_Fabovedot / LATIN CAPITAL LETTER F WITH DOT ABOVE
					case 0x1001e1f: ks = 0x1E1F; break; // XK_fabovedot / LATIN SMALL LETTER F WITH DOT ABOVE
					case 0x1001e40: ks = 0x1E40; break; // XK_Mabovedot / LATIN CAPITAL LETTER M WITH DOT ABOVE
					case 0x1001e41: ks = 0x1E41; break; // XK_mabovedot / LATIN SMALL LETTER M WITH DOT ABOVE
					case 0x1001e56: ks = 0x1E56; break; // XK_Pabovedot / LATIN CAPITAL LETTER P WITH DOT ABOVE
					case 0x1001e57: ks = 0x1E57; break; // XK_pabovedot / LATIN SMALL LETTER P WITH DOT ABOVE
					case 0x1001e60: ks = 0x1E60; break; // XK_Sabovedot / LATIN CAPITAL LETTER S WITH DOT ABOVE
					case 0x1001e61: ks = 0x1E61; break; // XK_sabovedot / LATIN SMALL LETTER S WITH DOT ABOVE
					case 0x1001e6a: ks = 0x1E6A; break; // XK_Tabovedot / LATIN CAPITAL LETTER T WITH DOT ABOVE
					case 0x1001e6b: ks = 0x1E6B; break; // XK_tabovedot / LATIN SMALL LETTER T WITH DOT ABOVE
					case 0x1001e80: ks = 0x1E80; break; // XK_Wgrave / LATIN CAPITAL LETTER W WITH GRAVE
					case 0x1001e81: ks = 0x1E81; break; // XK_wgrave / LATIN SMALL LETTER W WITH GRAVE
					case 0x1001e82: ks = 0x1E82; break; // XK_Wacute / LATIN CAPITAL LETTER W WITH ACUTE
					case 0x1001e83: ks = 0x1E83; break; // XK_wacute / LATIN SMALL LETTER W WITH ACUTE
					case 0x1001e84: ks = 0x1E84; break; // XK_Wdiaeresis / LATIN CAPITAL LETTER W WITH DIAERESIS
					case 0x1001e85: ks = 0x1E85; break; // XK_wdiaeresis / LATIN SMALL LETTER W WITH DIAERESIS
					case 0x1001ef2: ks = 0x1EF2; break; // XK_Ygrave / LATIN CAPITAL LETTER Y WITH GRAVE
					case 0x1001ef3: ks = 0x1EF3; break; // XK_ygrave / LATIN SMALL LETTER Y WITH GRAVE
					case 0x13bc: ks = 0x0152; break; // XK_OE / LATIN CAPITAL LIGATURE OE
					case 0x13bd: ks = 0x0153; break; // XK_oe / LATIN SMALL LIGATURE OE
					case 0x13be: ks = 0x0178; break; // XK_Ydiaeresis / LATIN CAPITAL LETTER Y WITH DIAERESIS
					case 0x47e: ks = 0x203E; break; // XK_overline / OVERLINE
					case 0x4a1: ks = 0x3002; break; // XK_kana_fullstop / IDEOGRAPHIC FULL STOP
					case 0x4a2: ks = 0x300C; break; // XK_kana_openingbracket / LEFT CORNER BRACKET
					case 0x4a3: ks = 0x300D; break; // XK_kana_closingbracket / RIGHT CORNER BRACKET
					case 0x4a4: ks = 0x3001; break; // XK_kana_comma / IDEOGRAPHIC COMMA
					case 0x4a5: ks = 0x30FB; break; // XK_kana_conjunctive / KATAKANA MIDDLE DOT
					case 0x4a6: ks = 0x30F2; break; // XK_kana_WO / KATAKANA LETTER WO
					case 0x4a7: ks = 0x30A1; break; // XK_kana_a / KATAKANA LETTER SMALL A
					case 0x4a8: ks = 0x30A3; break; // XK_kana_i / KATAKANA LETTER SMALL I
					case 0x4a9: ks = 0x30A5; break; // XK_kana_u / KATAKANA LETTER SMALL U
					case 0x4aa: ks = 0x30A7; break; // XK_kana_e / KATAKANA LETTER SMALL E
					case 0x4ab: ks = 0x30A9; break; // XK_kana_o / KATAKANA LETTER SMALL O
					case 0x4ac: ks = 0x30E3; break; // XK_kana_ya / KATAKANA LETTER SMALL YA
					case 0x4ad: ks = 0x30E5; break; // XK_kana_yu / KATAKANA LETTER SMALL YU
					case 0x4ae: ks = 0x30E7; break; // XK_kana_yo / KATAKANA LETTER SMALL YO
					case 0x4af: ks = 0x30C3; break; // XK_kana_tsu / KATAKANA LETTER SMALL TU
					case 0x4b0: ks = 0x30FC; break; // XK_prolongedsound / KATAKANA-HIRAGANA PROLONGED SOUND MARK
					case 0x4b1: ks = 0x30A2; break; // XK_kana_A / KATAKANA LETTER A
					case 0x4b2: ks = 0x30A4; break; // XK_kana_I / KATAKANA LETTER I
					case 0x4b3: ks = 0x30A6; break; // XK_kana_U / KATAKANA LETTER U
					case 0x4b4: ks = 0x30A8; break; // XK_kana_E / KATAKANA LETTER E
					case 0x4b5: ks = 0x30AA; break; // XK_kana_O / KATAKANA LETTER O
					case 0x4b6: ks = 0x30AB; break; // XK_kana_KA / KATAKANA LETTER KA
					case 0x4b7: ks = 0x30AD; break; // XK_kana_KI / KATAKANA LETTER KI
					case 0x4b8: ks = 0x30AF; break; // XK_kana_KU / KATAKANA LETTER KU
					case 0x4b9: ks = 0x30B1; break; // XK_kana_KE / KATAKANA LETTER KE
					case 0x4ba: ks = 0x30B3; break; // XK_kana_KO / KATAKANA LETTER KO
					case 0x4bb: ks = 0x30B5; break; // XK_kana_SA / KATAKANA LETTER SA
					case 0x4bc: ks = 0x30B7; break; // XK_kana_SHI / KATAKANA LETTER SI
					case 0x4bd: ks = 0x30B9; break; // XK_kana_SU / KATAKANA LETTER SU
					case 0x4be: ks = 0x30BB; break; // XK_kana_SE / KATAKANA LETTER SE
					case 0x4bf: ks = 0x30BD; break; // XK_kana_SO / KATAKANA LETTER SO
					case 0x4c0: ks = 0x30BF; break; // XK_kana_TA / KATAKANA LETTER TA
					case 0x4c1: ks = 0x30C1; break; // XK_kana_CHI / KATAKANA LETTER TI
					case 0x4c2: ks = 0x30C4; break; // XK_kana_TSU / KATAKANA LETTER TU
					case 0x4c3: ks = 0x30C6; break; // XK_kana_TE / KATAKANA LETTER TE
					case 0x4c4: ks = 0x30C8; break; // XK_kana_TO / KATAKANA LETTER TO
					case 0x4c5: ks = 0x30CA; break; // XK_kana_NA / KATAKANA LETTER NA
					case 0x4c6: ks = 0x30CB; break; // XK_kana_NI / KATAKANA LETTER NI
					case 0x4c7: ks = 0x30CC; break; // XK_kana_NU / KATAKANA LETTER NU
					case 0x4c8: ks = 0x30CD; break; // XK_kana_NE / KATAKANA LETTER NE
					case 0x4c9: ks = 0x30CE; break; // XK_kana_NO / KATAKANA LETTER NO
					case 0x4ca: ks = 0x30CF; break; // XK_kana_HA / KATAKANA LETTER HA
					case 0x4cb: ks = 0x30D2; break; // XK_kana_HI / KATAKANA LETTER HI
					case 0x4cc: ks = 0x30D5; break; // XK_kana_FU / KATAKANA LETTER HU
					case 0x4cd: ks = 0x30D8; break; // XK_kana_HE / KATAKANA LETTER HE
					case 0x4ce: ks = 0x30DB; break; // XK_kana_HO / KATAKANA LETTER HO
					case 0x4cf: ks = 0x30DE; break; // XK_kana_MA / KATAKANA LETTER MA
					case 0x4d0: ks = 0x30DF; break; // XK_kana_MI / KATAKANA LETTER MI
					case 0x4d1: ks = 0x30E0; break; // XK_kana_MU / KATAKANA LETTER MU
					case 0x4d2: ks = 0x30E1; break; // XK_kana_ME / KATAKANA LETTER ME
					case 0x4d3: ks = 0x30E2; break; // XK_kana_MO / KATAKANA LETTER MO
					case 0x4d4: ks = 0x30E4; break; // XK_kana_YA / KATAKANA LETTER YA
					case 0x4d5: ks = 0x30E6; break; // XK_kana_YU / KATAKANA LETTER YU
					case 0x4d6: ks = 0x30E8; break; // XK_kana_YO / KATAKANA LETTER YO
					case 0x4d7: ks = 0x30E9; break; // XK_kana_RA / KATAKANA LETTER RA
					case 0x4d8: ks = 0x30EA; break; // XK_kana_RI / KATAKANA LETTER RI
					case 0x4d9: ks = 0x30EB; break; // XK_kana_RU / KATAKANA LETTER RU
					case 0x4da: ks = 0x30EC; break; // XK_kana_RE / KATAKANA LETTER RE
					case 0x4db: ks = 0x30ED; break; // XK_kana_RO / KATAKANA LETTER RO
					case 0x4dc: ks = 0x30EF; break; // XK_kana_WA / KATAKANA LETTER WA
					case 0x4dd: ks = 0x30F3; break; // XK_kana_N / KATAKANA LETTER N
					case 0x4de: ks = 0x309B; break; // XK_voicedsound / KATAKANA-HIRAGANA VOICED SOUND MARK
					case 0x4df: ks = 0x309C; break; // XK_semivoicedsound / KATAKANA-HIRAGANA SEMI-VOICED SOUND MARK
					case 0x10006f0: ks = 0x06F0; break; // XK_Farsi_0 / EXTENDED ARABIC-INDIC DIGIT ZERO
					case 0x10006f1: ks = 0x06F1; break; // XK_Farsi_1 / EXTENDED ARABIC-INDIC DIGIT ONE
					case 0x10006f2: ks = 0x06F2; break; // XK_Farsi_2 / EXTENDED ARABIC-INDIC DIGIT TWO
					case 0x10006f3: ks = 0x06F3; break; // XK_Farsi_3 / EXTENDED ARABIC-INDIC DIGIT THREE
					case 0x10006f4: ks = 0x06F4; break; // XK_Farsi_4 / EXTENDED ARABIC-INDIC DIGIT FOUR
					case 0x10006f5: ks = 0x06F5; break; // XK_Farsi_5 / EXTENDED ARABIC-INDIC DIGIT FIVE
					case 0x10006f6: ks = 0x06F6; break; // XK_Farsi_6 / EXTENDED ARABIC-INDIC DIGIT SIX
					case 0x10006f7: ks = 0x06F7; break; // XK_Farsi_7 / EXTENDED ARABIC-INDIC DIGIT SEVEN
					case 0x10006f8: ks = 0x06F8; break; // XK_Farsi_8 / EXTENDED ARABIC-INDIC DIGIT EIGHT
					case 0x10006f9: ks = 0x06F9; break; // XK_Farsi_9 / EXTENDED ARABIC-INDIC DIGIT NINE
					case 0x100066a: ks = 0x066A; break; // XK_Arabic_percent / ARABIC PERCENT SIGN
					case 0x1000670: ks = 0x0670; break; // XK_Arabic_superscript_alef / ARABIC LETTER SUPERSCRIPT ALEF
					case 0x1000679: ks = 0x0679; break; // XK_Arabic_tteh / ARABIC LETTER TTEH
					case 0x100067e: ks = 0x067E; break; // XK_Arabic_peh / ARABIC LETTER PEH
					case 0x1000686: ks = 0x0686; break; // XK_Arabic_tcheh / ARABIC LETTER TCHEH
					case 0x1000688: ks = 0x0688; break; // XK_Arabic_ddal / ARABIC LETTER DDAL
					case 0x1000691: ks = 0x0691; break; // XK_Arabic_rreh / ARABIC LETTER RREH
					case 0x5ac: ks = 0x060C; break; // XK_Arabic_comma / ARABIC COMMA
					case 0x10006d4: ks = 0x06D4; break; // XK_Arabic_fullstop / ARABIC FULL STOP
					case 0x1000660: ks = 0x0660; break; // XK_Arabic_0 / ARABIC-INDIC DIGIT ZERO
					case 0x1000661: ks = 0x0661; break; // XK_Arabic_1 / ARABIC-INDIC DIGIT ONE
					case 0x1000662: ks = 0x0662; break; // XK_Arabic_2 / ARABIC-INDIC DIGIT TWO
					case 0x1000663: ks = 0x0663; break; // XK_Arabic_3 / ARABIC-INDIC DIGIT THREE
					case 0x1000664: ks = 0x0664; break; // XK_Arabic_4 / ARABIC-INDIC DIGIT FOUR
					case 0x1000665: ks = 0x0665; break; // XK_Arabic_5 / ARABIC-INDIC DIGIT FIVE
					case 0x1000666: ks = 0x0666; break; // XK_Arabic_6 / ARABIC-INDIC DIGIT SIX
					case 0x1000667: ks = 0x0667; break; // XK_Arabic_7 / ARABIC-INDIC DIGIT SEVEN
					case 0x1000668: ks = 0x0668; break; // XK_Arabic_8 / ARABIC-INDIC DIGIT EIGHT
					case 0x1000669: ks = 0x0669; break; // XK_Arabic_9 / ARABIC-INDIC DIGIT NINE
					case 0x5bb: ks = 0x061B; break; // XK_Arabic_semicolon / ARABIC SEMICOLON
					case 0x5bf: ks = 0x061F; break; // XK_Arabic_question_mark / ARABIC QUESTION MARK
					case 0x5c1: ks = 0x0621; break; // XK_Arabic_hamza / ARABIC LETTER HAMZA
					case 0x5c2: ks = 0x0622; break; // XK_Arabic_maddaonalef / ARABIC LETTER ALEF WITH MADDA ABOVE
					case 0x5c3: ks = 0x0623; break; // XK_Arabic_hamzaonalef / ARABIC LETTER ALEF WITH HAMZA ABOVE
					case 0x5c4: ks = 0x0624; break; // XK_Arabic_hamzaonwaw / ARABIC LETTER WAW WITH HAMZA ABOVE
					case 0x5c5: ks = 0x0625; break; // XK_Arabic_hamzaunderalef / ARABIC LETTER ALEF WITH HAMZA BELOW
					case 0x5c6: ks = 0x0626; break; // XK_Arabic_hamzaonyeh / ARABIC LETTER YEH WITH HAMZA ABOVE
					case 0x5c7: ks = 0x0627; break; // XK_Arabic_alef / ARABIC LETTER ALEF
					case 0x5c8: ks = 0x0628; break; // XK_Arabic_beh / ARABIC LETTER BEH
					case 0x5c9: ks = 0x0629; break; // XK_Arabic_tehmarbuta / ARABIC LETTER TEH MARBUTA
					case 0x5ca: ks = 0x062A; break; // XK_Arabic_teh / ARABIC LETTER TEH
					case 0x5cb: ks = 0x062B; break; // XK_Arabic_theh / ARABIC LETTER THEH
					case 0x5cc: ks = 0x062C; break; // XK_Arabic_jeem / ARABIC LETTER JEEM
					case 0x5cd: ks = 0x062D; break; // XK_Arabic_hah / ARABIC LETTER HAH
					case 0x5ce: ks = 0x062E; break; // XK_Arabic_khah / ARABIC LETTER KHAH
					case 0x5cf: ks = 0x062F; break; // XK_Arabic_dal / ARABIC LETTER DAL
					case 0x5d0: ks = 0x0630; break; // XK_Arabic_thal / ARABIC LETTER THAL
					case 0x5d1: ks = 0x0631; break; // XK_Arabic_ra / ARABIC LETTER REH
					case 0x5d2: ks = 0x0632; break; // XK_Arabic_zain / ARABIC LETTER ZAIN
					case 0x5d3: ks = 0x0633; break; // XK_Arabic_seen / ARABIC LETTER SEEN
					case 0x5d4: ks = 0x0634; break; // XK_Arabic_sheen / ARABIC LETTER SHEEN
					case 0x5d5: ks = 0x0635; break; // XK_Arabic_sad / ARABIC LETTER SAD
					case 0x5d6: ks = 0x0636; break; // XK_Arabic_dad / ARABIC LETTER DAD
					case 0x5d7: ks = 0x0637; break; // XK_Arabic_tah / ARABIC LETTER TAH
					case 0x5d8: ks = 0x0638; break; // XK_Arabic_zah / ARABIC LETTER ZAH
					case 0x5d9: ks = 0x0639; break; // XK_Arabic_ain / ARABIC LETTER AIN
					case 0x5da: ks = 0x063A; break; // XK_Arabic_ghain / ARABIC LETTER GHAIN
					case 0x5e0: ks = 0x0640; break; // XK_Arabic_tatweel / ARABIC TATWEEL
					case 0x5e1: ks = 0x0641; break; // XK_Arabic_feh / ARABIC LETTER FEH
					case 0x5e2: ks = 0x0642; break; // XK_Arabic_qaf / ARABIC LETTER QAF
					case 0x5e3: ks = 0x0643; break; // XK_Arabic_kaf / ARABIC LETTER KAF
					case 0x5e4: ks = 0x0644; break; // XK_Arabic_lam / ARABIC LETTER LAM
					case 0x5e5: ks = 0x0645; break; // XK_Arabic_meem / ARABIC LETTER MEEM
					case 0x5e6: ks = 0x0646; break; // XK_Arabic_noon / ARABIC LETTER NOON
					case 0x5e7: ks = 0x0647; break; // XK_Arabic_ha / ARABIC LETTER HEH
					case 0x5e8: ks = 0x0648; break; // XK_Arabic_waw / ARABIC LETTER WAW
					case 0x5e9: ks = 0x0649; break; // XK_Arabic_alefmaksura / ARABIC LETTER ALEF MAKSURA
					case 0x5ea: ks = 0x064A; break; // XK_Arabic_yeh / ARABIC LETTER YEH
					case 0x5eb: ks = 0x064B; break; // XK_Arabic_fathatan / ARABIC FATHATAN
					case 0x5ec: ks = 0x064C; break; // XK_Arabic_dammatan / ARABIC DAMMATAN
					case 0x5ed: ks = 0x064D; break; // XK_Arabic_kasratan / ARABIC KASRATAN
					case 0x5ee: ks = 0x064E; break; // XK_Arabic_fatha / ARABIC FATHA
					case 0x5ef: ks = 0x064F; break; // XK_Arabic_damma / ARABIC DAMMA
					case 0x5f0: ks = 0x0650; break; // XK_Arabic_kasra / ARABIC KASRA
					case 0x5f1: ks = 0x0651; break; // XK_Arabic_shadda / ARABIC SHADDA
					case 0x5f2: ks = 0x0652; break; // XK_Arabic_sukun / ARABIC SUKUN
					case 0x1000653: ks = 0x0653; break; // XK_Arabic_madda_above / ARABIC MADDAH ABOVE
					case 0x1000654: ks = 0x0654; break; // XK_Arabic_hamza_above / ARABIC HAMZA ABOVE
					case 0x1000655: ks = 0x0655; break; // XK_Arabic_hamza_below / ARABIC HAMZA BELOW
					case 0x1000698: ks = 0x0698; break; // XK_Arabic_jeh / ARABIC LETTER JEH
					case 0x10006a4: ks = 0x06A4; break; // XK_Arabic_veh / ARABIC LETTER VEH
					case 0x10006a9: ks = 0x06A9; break; // XK_Arabic_keheh / ARABIC LETTER KEHEH
					case 0x10006af: ks = 0x06AF; break; // XK_Arabic_gaf / ARABIC LETTER GAF
					case 0x10006ba: ks = 0x06BA; break; // XK_Arabic_noon_ghunna / ARABIC LETTER NOON GHUNNA
					case 0x10006be: ks = 0x06BE; break; // XK_Arabic_heh_doachashmee / ARABIC LETTER HEH DOACHASHMEE
					case 0x10006cc: ks = 0x06CC; break; // XK_Farsi_yeh / ARABIC LETTER FARSI YEH
					case 0x10006d2: ks = 0x06D2; break; // XK_Arabic_yeh_baree / ARABIC LETTER YEH BARREE
					case 0x10006c1: ks = 0x06C1; break; // XK_Arabic_heh_goal / ARABIC LETTER HEH GOAL
					case 0x1000492: ks = 0x0492; break; // XK_Cyrillic_GHE_bar / CYRILLIC CAPITAL LETTER GHE WITH STROKE
					case 0x1000493: ks = 0x0493; break; // XK_Cyrillic_ghe_bar / CYRILLIC SMALL LETTER GHE WITH STROKE
					case 0x1000496: ks = 0x0496; break; // XK_Cyrillic_ZHE_descender / CYRILLIC CAPITAL LETTER ZHE WITH DESCENDER
					case 0x1000497: ks = 0x0497; break; // XK_Cyrillic_zhe_descender / CYRILLIC SMALL LETTER ZHE WITH DESCENDER
					case 0x100049a: ks = 0x049A; break; // XK_Cyrillic_KA_descender / CYRILLIC CAPITAL LETTER KA WITH DESCENDER
					case 0x100049b: ks = 0x049B; break; // XK_Cyrillic_ka_descender / CYRILLIC SMALL LETTER KA WITH DESCENDER
					case 0x100049c: ks = 0x049C; break; // XK_Cyrillic_KA_vertstroke / CYRILLIC CAPITAL LETTER KA WITH VERTICAL STROKE
					case 0x100049d: ks = 0x049D; break; // XK_Cyrillic_ka_vertstroke / CYRILLIC SMALL LETTER KA WITH VERTICAL STROKE
					case 0x10004a2: ks = 0x04A2; break; // XK_Cyrillic_EN_descender / CYRILLIC CAPITAL LETTER EN WITH DESCENDER
					case 0x10004a3: ks = 0x04A3; break; // XK_Cyrillic_en_descender / CYRILLIC SMALL LETTER EN WITH DESCENDER
					case 0x10004ae: ks = 0x04AE; break; // XK_Cyrillic_U_straight / CYRILLIC CAPITAL LETTER STRAIGHT U
					case 0x10004af: ks = 0x04AF; break; // XK_Cyrillic_u_straight / CYRILLIC SMALL LETTER STRAIGHT U
					case 0x10004b0: ks = 0x04B0; break; // XK_Cyrillic_U_straight_bar / CYRILLIC CAPITAL LETTER STRAIGHT U WITH STROKE
					case 0x10004b1: ks = 0x04B1; break; // XK_Cyrillic_u_straight_bar / CYRILLIC SMALL LETTER STRAIGHT U WITH STROKE
					case 0x10004b2: ks = 0x04B2; break; // XK_Cyrillic_HA_descender / CYRILLIC CAPITAL LETTER HA WITH DESCENDER
					case 0x10004b3: ks = 0x04B3; break; // XK_Cyrillic_ha_descender / CYRILLIC SMALL LETTER HA WITH DESCENDER
					case 0x10004b6: ks = 0x04B6; break; // XK_Cyrillic_CHE_descender / CYRILLIC CAPITAL LETTER CHE WITH DESCENDER
					case 0x10004b7: ks = 0x04B7; break; // XK_Cyrillic_che_descender / CYRILLIC SMALL LETTER CHE WITH DESCENDER
					case 0x10004b8: ks = 0x04B8; break; // XK_Cyrillic_CHE_vertstroke / CYRILLIC CAPITAL LETTER CHE WITH VERTICAL STROKE
					case 0x10004b9: ks = 0x04B9; break; // XK_Cyrillic_che_vertstroke / CYRILLIC SMALL LETTER CHE WITH VERTICAL STROKE
					case 0x10004ba: ks = 0x04BA; break; // XK_Cyrillic_SHHA / CYRILLIC CAPITAL LETTER SHHA
					case 0x10004bb: ks = 0x04BB; break; // XK_Cyrillic_shha / CYRILLIC SMALL LETTER SHHA
					case 0x10004d8: ks = 0x04D8; break; // XK_Cyrillic_SCHWA / CYRILLIC CAPITAL LETTER SCHWA
					case 0x10004d9: ks = 0x04D9; break; // XK_Cyrillic_schwa / CYRILLIC SMALL LETTER SCHWA
					case 0x10004e2: ks = 0x04E2; break; // XK_Cyrillic_I_macron / CYRILLIC CAPITAL LETTER I WITH MACRON
					case 0x10004e3: ks = 0x04E3; break; // XK_Cyrillic_i_macron / CYRILLIC SMALL LETTER I WITH MACRON
					case 0x10004e8: ks = 0x04E8; break; // XK_Cyrillic_O_bar / CYRILLIC CAPITAL LETTER BARRED O
					case 0x10004e9: ks = 0x04E9; break; // XK_Cyrillic_o_bar / CYRILLIC SMALL LETTER BARRED O
					case 0x10004ee: ks = 0x04EE; break; // XK_Cyrillic_U_macron / CYRILLIC CAPITAL LETTER U WITH MACRON
					case 0x10004ef: ks = 0x04EF; break; // XK_Cyrillic_u_macron / CYRILLIC SMALL LETTER U WITH MACRON
					case 0x6a1: ks = 0x0452; break; // XK_Serbian_dje / CYRILLIC SMALL LETTER DJE
					case 0x6a2: ks = 0x0453; break; // XK_Macedonia_gje / CYRILLIC SMALL LETTER GJE
					case 0x6a3: ks = 0x0451; break; // XK_Cyrillic_io / CYRILLIC SMALL LETTER IO
					case 0x6a4: ks = 0x0454; break; // XK_Ukrainian_ie / CYRILLIC SMALL LETTER UKRAINIAN IE
					case 0x6a5: ks = 0x0455; break; // XK_Macedonia_dse / CYRILLIC SMALL LETTER DZE
					case 0x6a6: ks = 0x0456; break; // XK_Ukrainian_i / CYRILLIC SMALL LETTER BYELORUSSIAN-UKRAINIAN I
					case 0x6a7: ks = 0x0457; break; // XK_Ukrainian_yi / CYRILLIC SMALL LETTER YI
					case 0x6a8: ks = 0x0458; break; // XK_Cyrillic_je / CYRILLIC SMALL LETTER JE
					case 0x6a9: ks = 0x0459; break; // XK_Cyrillic_lje / CYRILLIC SMALL LETTER LJE
					case 0x6aa: ks = 0x045A; break; // XK_Cyrillic_nje / CYRILLIC SMALL LETTER NJE
					case 0x6ab: ks = 0x045B; break; // XK_Serbian_tshe / CYRILLIC SMALL LETTER TSHE
					case 0x6ac: ks = 0x045C; break; // XK_Macedonia_kje / CYRILLIC SMALL LETTER KJE
					case 0x6ad: ks = 0x0491; break; // XK_Ukrainian_ghe_with_upturn / CYRILLIC SMALL LETTER GHE WITH UPTURN
					case 0x6ae: ks = 0x045E; break; // XK_Byelorussian_shortu / CYRILLIC SMALL LETTER SHORT U
					case 0x6af: ks = 0x045F; break; // XK_Cyrillic_dzhe / CYRILLIC SMALL LETTER DZHE
					case 0x6b0: ks = 0x2116; break; // XK_numerosign / NUMERO SIGN
					case 0x6b1: ks = 0x0402; break; // XK_Serbian_DJE / CYRILLIC CAPITAL LETTER DJE
					case 0x6b2: ks = 0x0403; break; // XK_Macedonia_GJE / CYRILLIC CAPITAL LETTER GJE
					case 0x6b3: ks = 0x0401; break; // XK_Cyrillic_IO / CYRILLIC CAPITAL LETTER IO
					case 0x6b4: ks = 0x0404; break; // XK_Ukrainian_IE / CYRILLIC CAPITAL LETTER UKRAINIAN IE
					case 0x6b5: ks = 0x0405; break; // XK_Macedonia_DSE / CYRILLIC CAPITAL LETTER DZE
					case 0x6b6: ks = 0x0406; break; // XK_Ukrainian_I / CYRILLIC CAPITAL LETTER BYELORUSSIAN-UKRAINIAN I
					case 0x6b7: ks = 0x0407; break; // XK_Ukrainian_YI / CYRILLIC CAPITAL LETTER YI
					case 0x6b8: ks = 0x0408; break; // XK_Cyrillic_JE / CYRILLIC CAPITAL LETTER JE
					case 0x6b9: ks = 0x0409; break; // XK_Cyrillic_LJE / CYRILLIC CAPITAL LETTER LJE
					case 0x6ba: ks = 0x040A; break; // XK_Cyrillic_NJE / CYRILLIC CAPITAL LETTER NJE
					case 0x6bb: ks = 0x040B; break; // XK_Serbian_TSHE / CYRILLIC CAPITAL LETTER TSHE
					case 0x6bc: ks = 0x040C; break; // XK_Macedonia_KJE / CYRILLIC CAPITAL LETTER KJE
					case 0x6bd: ks = 0x0490; break; // XK_Ukrainian_GHE_WITH_UPTURN / CYRILLIC CAPITAL LETTER GHE WITH UPTURN
					case 0x6be: ks = 0x040E; break; // XK_Byelorussian_SHORTU / CYRILLIC CAPITAL LETTER SHORT U
					case 0x6bf: ks = 0x040F; break; // XK_Cyrillic_DZHE / CYRILLIC CAPITAL LETTER DZHE
					case 0x6c0: ks = 0x044E; break; // XK_Cyrillic_yu / CYRILLIC SMALL LETTER YU
					case 0x6c1: ks = 0x0430; break; // XK_Cyrillic_a / CYRILLIC SMALL LETTER A
					case 0x6c2: ks = 0x0431; break; // XK_Cyrillic_be / CYRILLIC SMALL LETTER BE
					case 0x6c3: ks = 0x0446; break; // XK_Cyrillic_tse / CYRILLIC SMALL LETTER TSE
					case 0x6c4: ks = 0x0434; break; // XK_Cyrillic_de / CYRILLIC SMALL LETTER DE
					case 0x6c5: ks = 0x0435; break; // XK_Cyrillic_ie / CYRILLIC SMALL LETTER IE
					case 0x6c6: ks = 0x0444; break; // XK_Cyrillic_ef / CYRILLIC SMALL LETTER EF
					case 0x6c7: ks = 0x0433; break; // XK_Cyrillic_ghe / CYRILLIC SMALL LETTER GHE
					case 0x6c8: ks = 0x0445; break; // XK_Cyrillic_ha / CYRILLIC SMALL LETTER HA
					case 0x6c9: ks = 0x0438; break; // XK_Cyrillic_i / CYRILLIC SMALL LETTER I
					case 0x6ca: ks = 0x0439; break; // XK_Cyrillic_shorti / CYRILLIC SMALL LETTER SHORT I
					case 0x6cb: ks = 0x043A; break; // XK_Cyrillic_ka / CYRILLIC SMALL LETTER KA
					case 0x6cc: ks = 0x043B; break; // XK_Cyrillic_el / CYRILLIC SMALL LETTER EL
					case 0x6cd: ks = 0x043C; break; // XK_Cyrillic_em / CYRILLIC SMALL LETTER EM
					case 0x6ce: ks = 0x043D; break; // XK_Cyrillic_en / CYRILLIC SMALL LETTER EN
					case 0x6cf: ks = 0x043E; break; // XK_Cyrillic_o / CYRILLIC SMALL LETTER O
					case 0x6d0: ks = 0x043F; break; // XK_Cyrillic_pe / CYRILLIC SMALL LETTER PE
					case 0x6d1: ks = 0x044F; break; // XK_Cyrillic_ya / CYRILLIC SMALL LETTER YA
					case 0x6d2: ks = 0x0440; break; // XK_Cyrillic_er / CYRILLIC SMALL LETTER ER
					case 0x6d3: ks = 0x0441; break; // XK_Cyrillic_es / CYRILLIC SMALL LETTER ES
					case 0x6d4: ks = 0x0442; break; // XK_Cyrillic_te / CYRILLIC SMALL LETTER TE
					case 0x6d5: ks = 0x0443; break; // XK_Cyrillic_u / CYRILLIC SMALL LETTER U
					case 0x6d6: ks = 0x0436; break; // XK_Cyrillic_zhe / CYRILLIC SMALL LETTER ZHE
					case 0x6d7: ks = 0x0432; break; // XK_Cyrillic_ve / CYRILLIC SMALL LETTER VE
					case 0x6d8: ks = 0x044C; break; // XK_Cyrillic_softsign / CYRILLIC SMALL LETTER SOFT SIGN
					case 0x6d9: ks = 0x044B; break; // XK_Cyrillic_yeru / CYRILLIC SMALL LETTER YERU
					case 0x6da: ks = 0x0437; break; // XK_Cyrillic_ze / CYRILLIC SMALL LETTER ZE
					case 0x6db: ks = 0x0448; break; // XK_Cyrillic_sha / CYRILLIC SMALL LETTER SHA
					case 0x6dc: ks = 0x044D; break; // XK_Cyrillic_e / CYRILLIC SMALL LETTER E
					case 0x6dd: ks = 0x0449; break; // XK_Cyrillic_shcha / CYRILLIC SMALL LETTER SHCHA
					case 0x6de: ks = 0x0447; break; // XK_Cyrillic_che / CYRILLIC SMALL LETTER CHE
					case 0x6df: ks = 0x044A; break; // XK_Cyrillic_hardsign / CYRILLIC SMALL LETTER HARD SIGN
					case 0x6e0: ks = 0x042E; break; // XK_Cyrillic_YU / CYRILLIC CAPITAL LETTER YU
					case 0x6e1: ks = 0x0410; break; // XK_Cyrillic_A / CYRILLIC CAPITAL LETTER A
					case 0x6e2: ks = 0x0411; break; // XK_Cyrillic_BE / CYRILLIC CAPITAL LETTER BE
					case 0x6e3: ks = 0x0426; break; // XK_Cyrillic_TSE / CYRILLIC CAPITAL LETTER TSE
					case 0x6e4: ks = 0x0414; break; // XK_Cyrillic_DE / CYRILLIC CAPITAL LETTER DE
					case 0x6e5: ks = 0x0415; break; // XK_Cyrillic_IE / CYRILLIC CAPITAL LETTER IE
					case 0x6e6: ks = 0x0424; break; // XK_Cyrillic_EF / CYRILLIC CAPITAL LETTER EF
					case 0x6e7: ks = 0x0413; break; // XK_Cyrillic_GHE / CYRILLIC CAPITAL LETTER GHE
					case 0x6e8: ks = 0x0425; break; // XK_Cyrillic_HA / CYRILLIC CAPITAL LETTER HA
					case 0x6e9: ks = 0x0418; break; // XK_Cyrillic_I / CYRILLIC CAPITAL LETTER I
					case 0x6ea: ks = 0x0419; break; // XK_Cyrillic_SHORTI / CYRILLIC CAPITAL LETTER SHORT I
					case 0x6eb: ks = 0x041A; break; // XK_Cyrillic_KA / CYRILLIC CAPITAL LETTER KA
					case 0x6ec: ks = 0x041B; break; // XK_Cyrillic_EL / CYRILLIC CAPITAL LETTER EL
					case 0x6ed: ks = 0x041C; break; // XK_Cyrillic_EM / CYRILLIC CAPITAL LETTER EM
					case 0x6ee: ks = 0x041D; break; // XK_Cyrillic_EN / CYRILLIC CAPITAL LETTER EN
					case 0x6ef: ks = 0x041E; break; // XK_Cyrillic_O / CYRILLIC CAPITAL LETTER O
					case 0x6f0: ks = 0x041F; break; // XK_Cyrillic_PE / CYRILLIC CAPITAL LETTER PE
					case 0x6f1: ks = 0x042F; break; // XK_Cyrillic_YA / CYRILLIC CAPITAL LETTER YA
					case 0x6f2: ks = 0x0420; break; // XK_Cyrillic_ER / CYRILLIC CAPITAL LETTER ER
					case 0x6f3: ks = 0x0421; break; // XK_Cyrillic_ES / CYRILLIC CAPITAL LETTER ES
					case 0x6f4: ks = 0x0422; break; // XK_Cyrillic_TE / CYRILLIC CAPITAL LETTER TE
					case 0x6f5: ks = 0x0423; break; // XK_Cyrillic_U / CYRILLIC CAPITAL LETTER U
					case 0x6f6: ks = 0x0416; break; // XK_Cyrillic_ZHE / CYRILLIC CAPITAL LETTER ZHE
					case 0x6f7: ks = 0x0412; break; // XK_Cyrillic_VE / CYRILLIC CAPITAL LETTER VE
					case 0x6f8: ks = 0x042C; break; // XK_Cyrillic_SOFTSIGN / CYRILLIC CAPITAL LETTER SOFT SIGN
					case 0x6f9: ks = 0x042B; break; // XK_Cyrillic_YERU / CYRILLIC CAPITAL LETTER YERU
					case 0x6fa: ks = 0x0417; break; // XK_Cyrillic_ZE / CYRILLIC CAPITAL LETTER ZE
					case 0x6fb: ks = 0x0428; break; // XK_Cyrillic_SHA / CYRILLIC CAPITAL LETTER SHA
					case 0x6fc: ks = 0x042D; break; // XK_Cyrillic_E / CYRILLIC CAPITAL LETTER E
					case 0x6fd: ks = 0x0429; break; // XK_Cyrillic_SHCHA / CYRILLIC CAPITAL LETTER SHCHA
					case 0x6fe: ks = 0x0427; break; // XK_Cyrillic_CHE / CYRILLIC CAPITAL LETTER CHE
					case 0x6ff: ks = 0x042A; break; // XK_Cyrillic_HARDSIGN / CYRILLIC CAPITAL LETTER HARD SIGN
					case 0x7a1: ks = 0x0386; break; // XK_Greek_ALPHAaccent / GREEK CAPITAL LETTER ALPHA WITH TONOS
					case 0x7a2: ks = 0x0388; break; // XK_Greek_EPSILONaccent / GREEK CAPITAL LETTER EPSILON WITH TONOS
					case 0x7a3: ks = 0x0389; break; // XK_Greek_ETAaccent / GREEK CAPITAL LETTER ETA WITH TONOS
					case 0x7a4: ks = 0x038A; break; // XK_Greek_IOTAaccent / GREEK CAPITAL LETTER IOTA WITH TONOS
					case 0x7a5: ks = 0x03AA; break; // XK_Greek_IOTAdieresis / GREEK CAPITAL LETTER IOTA WITH DIALYTIKA
					case 0x7a7: ks = 0x038C; break; // XK_Greek_OMICRONaccent / GREEK CAPITAL LETTER OMICRON WITH TONOS
					case 0x7a8: ks = 0x038E; break; // XK_Greek_UPSILONaccent / GREEK CAPITAL LETTER UPSILON WITH TONOS
					case 0x7a9: ks = 0x03AB; break; // XK_Greek_UPSILONdieresis / GREEK CAPITAL LETTER UPSILON WITH DIALYTIKA
					case 0x7ab: ks = 0x038F; break; // XK_Greek_OMEGAaccent / GREEK CAPITAL LETTER OMEGA WITH TONOS
					case 0x7ae: ks = 0x0385; break; // XK_Greek_accentdieresis / GREEK DIALYTIKA TONOS
					case 0x7af: ks = 0x2015; break; // XK_Greek_horizbar / HORIZONTAL BAR
					case 0x7b1: ks = 0x03AC; break; // XK_Greek_alphaaccent / GREEK SMALL LETTER ALPHA WITH TONOS
					case 0x7b2: ks = 0x03AD; break; // XK_Greek_epsilonaccent / GREEK SMALL LETTER EPSILON WITH TONOS
					case 0x7b3: ks = 0x03AE; break; // XK_Greek_etaaccent / GREEK SMALL LETTER ETA WITH TONOS
					case 0x7b4: ks = 0x03AF; break; // XK_Greek_iotaaccent / GREEK SMALL LETTER IOTA WITH TONOS
					case 0x7b5: ks = 0x03CA; break; // XK_Greek_iotadieresis / GREEK SMALL LETTER IOTA WITH DIALYTIKA
					case 0x7b6: ks = 0x0390; break; // XK_Greek_iotaaccentdieresis / GREEK SMALL LETTER IOTA WITH DIALYTIKA AND TONOS
					case 0x7b7: ks = 0x03CC; break; // XK_Greek_omicronaccent / GREEK SMALL LETTER OMICRON WITH TONOS
					case 0x7b8: ks = 0x03CD; break; // XK_Greek_upsilonaccent / GREEK SMALL LETTER UPSILON WITH TONOS
					case 0x7b9: ks = 0x03CB; break; // XK_Greek_upsilondieresis / GREEK SMALL LETTER UPSILON WITH DIALYTIKA
					case 0x7ba: ks = 0x03B0; break; // XK_Greek_upsilonaccentdieresis / GREEK SMALL LETTER UPSILON WITH DIALYTIKA AND TONOS
					case 0x7bb: ks = 0x03CE; break; // XK_Greek_omegaaccent / GREEK SMALL LETTER OMEGA WITH TONOS
					case 0x7c1: ks = 0x0391; break; // XK_Greek_ALPHA / GREEK CAPITAL LETTER ALPHA
					case 0x7c2: ks = 0x0392; break; // XK_Greek_BETA / GREEK CAPITAL LETTER BETA
					case 0x7c3: ks = 0x0393; break; // XK_Greek_GAMMA / GREEK CAPITAL LETTER GAMMA
					case 0x7c4: ks = 0x0394; break; // XK_Greek_DELTA / GREEK CAPITAL LETTER DELTA
					case 0x7c5: ks = 0x0395; break; // XK_Greek_EPSILON / GREEK CAPITAL LETTER EPSILON
					case 0x7c6: ks = 0x0396; break; // XK_Greek_ZETA / GREEK CAPITAL LETTER ZETA
					case 0x7c7: ks = 0x0397; break; // XK_Greek_ETA / GREEK CAPITAL LETTER ETA
					case 0x7c8: ks = 0x0398; break; // XK_Greek_THETA / GREEK CAPITAL LETTER THETA
					case 0x7c9: ks = 0x0399; break; // XK_Greek_IOTA / GREEK CAPITAL LETTER IOTA
					case 0x7ca: ks = 0x039A; break; // XK_Greek_KAPPA / GREEK CAPITAL LETTER KAPPA
					case 0x7cb: ks = 0x039B; break; // XK_Greek_LAMDA / GREEK CAPITAL LETTER LAMDA
					case 0x7cc: ks = 0x039C; break; // XK_Greek_MU / GREEK CAPITAL LETTER MU
					case 0x7cd: ks = 0x039D; break; // XK_Greek_NU / GREEK CAPITAL LETTER NU
					case 0x7ce: ks = 0x039E; break; // XK_Greek_XI / GREEK CAPITAL LETTER XI
					case 0x7cf: ks = 0x039F; break; // XK_Greek_OMICRON / GREEK CAPITAL LETTER OMICRON
					case 0x7d0: ks = 0x03A0; break; // XK_Greek_PI / GREEK CAPITAL LETTER PI
					case 0x7d1: ks = 0x03A1; break; // XK_Greek_RHO / GREEK CAPITAL LETTER RHO
					case 0x7d2: ks = 0x03A3; break; // XK_Greek_SIGMA / GREEK CAPITAL LETTER SIGMA
					case 0x7d4: ks = 0x03A4; break; // XK_Greek_TAU / GREEK CAPITAL LETTER TAU
					case 0x7d5: ks = 0x03A5; break; // XK_Greek_UPSILON / GREEK CAPITAL LETTER UPSILON
					case 0x7d6: ks = 0x03A6; break; // XK_Greek_PHI / GREEK CAPITAL LETTER PHI
					case 0x7d7: ks = 0x03A7; break; // XK_Greek_CHI / GREEK CAPITAL LETTER CHI
					case 0x7d8: ks = 0x03A8; break; // XK_Greek_PSI / GREEK CAPITAL LETTER PSI
					case 0x7d9: ks = 0x03A9; break; // XK_Greek_OMEGA / GREEK CAPITAL LETTER OMEGA
					case 0x7e1: ks = 0x03B1; break; // XK_Greek_alpha / GREEK SMALL LETTER ALPHA
					case 0x7e2: ks = 0x03B2; break; // XK_Greek_beta / GREEK SMALL LETTER BETA
					case 0x7e3: ks = 0x03B3; break; // XK_Greek_gamma / GREEK SMALL LETTER GAMMA
					case 0x7e4: ks = 0x03B4; break; // XK_Greek_delta / GREEK SMALL LETTER DELTA
					case 0x7e5: ks = 0x03B5; break; // XK_Greek_epsilon / GREEK SMALL LETTER EPSILON
					case 0x7e6: ks = 0x03B6; break; // XK_Greek_zeta / GREEK SMALL LETTER ZETA
					case 0x7e7: ks = 0x03B7; break; // XK_Greek_eta / GREEK SMALL LETTER ETA
					case 0x7e8: ks = 0x03B8; break; // XK_Greek_theta / GREEK SMALL LETTER THETA
					case 0x7e9: ks = 0x03B9; break; // XK_Greek_iota / GREEK SMALL LETTER IOTA
					case 0x7ea: ks = 0x03BA; break; // XK_Greek_kappa / GREEK SMALL LETTER KAPPA
					case 0x7eb: ks = 0x03BB; break; // XK_Greek_lamda / GREEK SMALL LETTER LAMDA
					case 0x7ec: ks = 0x03BC; break; // XK_Greek_mu / GREEK SMALL LETTER MU
					case 0x7ed: ks = 0x03BD; break; // XK_Greek_nu / GREEK SMALL LETTER NU
					case 0x7ee: ks = 0x03BE; break; // XK_Greek_xi / GREEK SMALL LETTER XI
					case 0x7ef: ks = 0x03BF; break; // XK_Greek_omicron / GREEK SMALL LETTER OMICRON
					case 0x7f0: ks = 0x03C0; break; // XK_Greek_pi / GREEK SMALL LETTER PI
					case 0x7f1: ks = 0x03C1; break; // XK_Greek_rho / GREEK SMALL LETTER RHO
					case 0x7f2: ks = 0x03C3; break; // XK_Greek_sigma / GREEK SMALL LETTER SIGMA
					case 0x7f3: ks = 0x03C2; break; // XK_Greek_finalsmallsigma / GREEK SMALL LETTER FINAL SIGMA
					case 0x7f4: ks = 0x03C4; break; // XK_Greek_tau / GREEK SMALL LETTER TAU
					case 0x7f5: ks = 0x03C5; break; // XK_Greek_upsilon / GREEK SMALL LETTER UPSILON
					case 0x7f6: ks = 0x03C6; break; // XK_Greek_phi / GREEK SMALL LETTER PHI
					case 0x7f7: ks = 0x03C7; break; // XK_Greek_chi / GREEK SMALL LETTER CHI
					case 0x7f8: ks = 0x03C8; break; // XK_Greek_psi / GREEK SMALL LETTER PSI
					case 0x7f9: ks = 0x03C9; break; // XK_Greek_omega / GREEK SMALL LETTER OMEGA
					case 0xcdf: ks = 0x2017; break; // XK_hebrew_doublelowline / DOUBLE LOW LINE
					case 0xce0: ks = 0x05D0; break; // XK_hebrew_aleph / HEBREW LETTER ALEF
					case 0xce1: ks = 0x05D1; break; // XK_hebrew_bet / HEBREW LETTER BET
					case 0xce2: ks = 0x05D2; break; // XK_hebrew_gimel / HEBREW LETTER GIMEL
					case 0xce3: ks = 0x05D3; break; // XK_hebrew_dalet / HEBREW LETTER DALET
					case 0xce4: ks = 0x05D4; break; // XK_hebrew_he / HEBREW LETTER HE
					case 0xce5: ks = 0x05D5; break; // XK_hebrew_waw / HEBREW LETTER VAV
					case 0xce6: ks = 0x05D6; break; // XK_hebrew_zain / HEBREW LETTER ZAYIN
					case 0xce7: ks = 0x05D7; break; // XK_hebrew_chet / HEBREW LETTER HET
					case 0xce8: ks = 0x05D8; break; // XK_hebrew_tet / HEBREW LETTER TET
					case 0xce9: ks = 0x05D9; break; // XK_hebrew_yod / HEBREW LETTER YOD
					case 0xcea: ks = 0x05DA; break; // XK_hebrew_finalkaph / HEBREW LETTER FINAL KAF
					case 0xceb: ks = 0x05DB; break; // XK_hebrew_kaph / HEBREW LETTER KAF
					case 0xcec: ks = 0x05DC; break; // XK_hebrew_lamed / HEBREW LETTER LAMED
					case 0xced: ks = 0x05DD; break; // XK_hebrew_finalmem / HEBREW LETTER FINAL MEM
					case 0xcee: ks = 0x05DE; break; // XK_hebrew_mem / HEBREW LETTER MEM
					case 0xcef: ks = 0x05DF; break; // XK_hebrew_finalnun / HEBREW LETTER FINAL NUN
					case 0xcf0: ks = 0x05E0; break; // XK_hebrew_nun / HEBREW LETTER NUN
					case 0xcf1: ks = 0x05E1; break; // XK_hebrew_samech / HEBREW LETTER SAMEKH
					case 0xcf2: ks = 0x05E2; break; // XK_hebrew_ayin / HEBREW LETTER AYIN
					case 0xcf3: ks = 0x05E3; break; // XK_hebrew_finalpe / HEBREW LETTER FINAL PE
					case 0xcf4: ks = 0x05E4; break; // XK_hebrew_pe / HEBREW LETTER PE
					case 0xcf5: ks = 0x05E5; break; // XK_hebrew_finalzade / HEBREW LETTER FINAL TSADI
					case 0xcf6: ks = 0x05E6; break; // XK_hebrew_zade / HEBREW LETTER TSADI
					case 0xcf7: ks = 0x05E7; break; // XK_hebrew_qoph / HEBREW LETTER QOF
					case 0xcf8: ks = 0x05E8; break; // XK_hebrew_resh / HEBREW LETTER RESH
					case 0xcf9: ks = 0x05E9; break; // XK_hebrew_shin / HEBREW LETTER SHIN
					case 0xcfa: ks = 0x05EA; break; // XK_hebrew_taw / HEBREW LETTER TAV
					case 0xda1: ks = 0x0E01; break; // XK_Thai_kokai / THAI CHARACTER KO KAI
					case 0xda2: ks = 0x0E02; break; // XK_Thai_khokhai / THAI CHARACTER KHO KHAI
					case 0xda3: ks = 0x0E03; break; // XK_Thai_khokhuat / THAI CHARACTER KHO KHUAT
					case 0xda4: ks = 0x0E04; break; // XK_Thai_khokhwai / THAI CHARACTER KHO KHWAI
					case 0xda5: ks = 0x0E05; break; // XK_Thai_khokhon / THAI CHARACTER KHO KHON
					case 0xda6: ks = 0x0E06; break; // XK_Thai_khorakhang / THAI CHARACTER KHO RAKHANG
					case 0xda7: ks = 0x0E07; break; // XK_Thai_ngongu / THAI CHARACTER NGO NGU
					case 0xda8: ks = 0x0E08; break; // XK_Thai_chochan / THAI CHARACTER CHO CHAN
					case 0xda9: ks = 0x0E09; break; // XK_Thai_choching / THAI CHARACTER CHO CHING
					case 0xdaa: ks = 0x0E0A; break; // XK_Thai_chochang / THAI CHARACTER CHO CHANG
					case 0xdab: ks = 0x0E0B; break; // XK_Thai_soso / THAI CHARACTER SO SO
					case 0xdac: ks = 0x0E0C; break; // XK_Thai_chochoe / THAI CHARACTER CHO CHOE
					case 0xdad: ks = 0x0E0D; break; // XK_Thai_yoying / THAI CHARACTER YO YING
					case 0xdae: ks = 0x0E0E; break; // XK_Thai_dochada / THAI CHARACTER DO CHADA
					case 0xdaf: ks = 0x0E0F; break; // XK_Thai_topatak / THAI CHARACTER TO PATAK
					case 0xdb0: ks = 0x0E10; break; // XK_Thai_thothan / THAI CHARACTER THO THAN
					case 0xdb1: ks = 0x0E11; break; // XK_Thai_thonangmontho / THAI CHARACTER THO NANGMONTHO
					case 0xdb2: ks = 0x0E12; break; // XK_Thai_thophuthao / THAI CHARACTER THO PHUTHAO
					case 0xdb3: ks = 0x0E13; break; // XK_Thai_nonen / THAI CHARACTER NO NEN
					case 0xdb4: ks = 0x0E14; break; // XK_Thai_dodek / THAI CHARACTER DO DEK
					case 0xdb5: ks = 0x0E15; break; // XK_Thai_totao / THAI CHARACTER TO TAO
					case 0xdb6: ks = 0x0E16; break; // XK_Thai_thothung / THAI CHARACTER THO THUNG
					case 0xdb7: ks = 0x0E17; break; // XK_Thai_thothahan / THAI CHARACTER THO THAHAN
					case 0xdb8: ks = 0x0E18; break; // XK_Thai_thothong / THAI CHARACTER THO THONG
					case 0xdb9: ks = 0x0E19; break; // XK_Thai_nonu / THAI CHARACTER NO NU
					case 0xdba: ks = 0x0E1A; break; // XK_Thai_bobaimai / THAI CHARACTER BO BAIMAI
					case 0xdbb: ks = 0x0E1B; break; // XK_Thai_popla / THAI CHARACTER PO PLA
					case 0xdbc: ks = 0x0E1C; break; // XK_Thai_phophung / THAI CHARACTER PHO PHUNG
					case 0xdbd: ks = 0x0E1D; break; // XK_Thai_fofa / THAI CHARACTER FO FA
					case 0xdbe: ks = 0x0E1E; break; // XK_Thai_phophan / THAI CHARACTER PHO PHAN
					case 0xdbf: ks = 0x0E1F; break; // XK_Thai_fofan / THAI CHARACTER FO FAN
					case 0xdc0: ks = 0x0E20; break; // XK_Thai_phosamphao / THAI CHARACTER PHO SAMPHAO
					case 0xdc1: ks = 0x0E21; break; // XK_Thai_moma / THAI CHARACTER MO MA
					case 0xdc2: ks = 0x0E22; break; // XK_Thai_yoyak / THAI CHARACTER YO YAK
					case 0xdc3: ks = 0x0E23; break; // XK_Thai_rorua / THAI CHARACTER RO RUA
					case 0xdc4: ks = 0x0E24; break; // XK_Thai_ru / THAI CHARACTER RU
					case 0xdc5: ks = 0x0E25; break; // XK_Thai_loling / THAI CHARACTER LO LING
					case 0xdc6: ks = 0x0E26; break; // XK_Thai_lu / THAI CHARACTER LU
					case 0xdc7: ks = 0x0E27; break; // XK_Thai_wowaen / THAI CHARACTER WO WAEN
					case 0xdc8: ks = 0x0E28; break; // XK_Thai_sosala / THAI CHARACTER SO SALA
					case 0xdc9: ks = 0x0E29; break; // XK_Thai_sorusi / THAI CHARACTER SO RUSI
					case 0xdca: ks = 0x0E2A; break; // XK_Thai_sosua / THAI CHARACTER SO SUA
					case 0xdcb: ks = 0x0E2B; break; // XK_Thai_hohip / THAI CHARACTER HO HIP
					case 0xdcc: ks = 0x0E2C; break; // XK_Thai_lochula / THAI CHARACTER LO CHULA
					case 0xdcd: ks = 0x0E2D; break; // XK_Thai_oang / THAI CHARACTER O ANG
					case 0xdce: ks = 0x0E2E; break; // XK_Thai_honokhuk / THAI CHARACTER HO NOKHUK
					case 0xdcf: ks = 0x0E2F; break; // XK_Thai_paiyannoi / THAI CHARACTER PAIYANNOI
					case 0xdd0: ks = 0x0E30; break; // XK_Thai_saraa / THAI CHARACTER SARA A
					case 0xdd1: ks = 0x0E31; break; // XK_Thai_maihanakat / THAI CHARACTER MAI HAN-AKAT
					case 0xdd2: ks = 0x0E32; break; // XK_Thai_saraaa / THAI CHARACTER SARA AA
					case 0xdd3: ks = 0x0E33; break; // XK_Thai_saraam / THAI CHARACTER SARA AM
					case 0xdd4: ks = 0x0E34; break; // XK_Thai_sarai / THAI CHARACTER SARA I
					case 0xdd5: ks = 0x0E35; break; // XK_Thai_saraii / THAI CHARACTER SARA II
					case 0xdd6: ks = 0x0E36; break; // XK_Thai_saraue / THAI CHARACTER SARA UE
					case 0xdd7: ks = 0x0E37; break; // XK_Thai_sarauee / THAI CHARACTER SARA UEE
					case 0xdd8: ks = 0x0E38; break; // XK_Thai_sarau / THAI CHARACTER SARA U
					case 0xdd9: ks = 0x0E39; break; // XK_Thai_sarauu / THAI CHARACTER SARA UU
					case 0xdda: ks = 0x0E3A; break; // XK_Thai_phinthu / THAI CHARACTER PHINTHU
					case 0xddf: ks = 0x0E3F; break; // XK_Thai_baht / THAI CURRENCY SYMBOL BAHT
					case 0xde0: ks = 0x0E40; break; // XK_Thai_sarae / THAI CHARACTER SARA E
					case 0xde1: ks = 0x0E41; break; // XK_Thai_saraae / THAI CHARACTER SARA AE
					case 0xde2: ks = 0x0E42; break; // XK_Thai_sarao / THAI CHARACTER SARA O
					case 0xde3: ks = 0x0E43; break; // XK_Thai_saraaimaimuan / THAI CHARACTER SARA AI MAIMUAN
					case 0xde4: ks = 0x0E44; break; // XK_Thai_saraaimaimalai / THAI CHARACTER SARA AI MAIMALAI
					case 0xde5: ks = 0x0E45; break; // XK_Thai_lakkhangyao / THAI CHARACTER LAKKHANGYAO
					case 0xde6: ks = 0x0E46; break; // XK_Thai_maiyamok / THAI CHARACTER MAIYAMOK
					case 0xde7: ks = 0x0E47; break; // XK_Thai_maitaikhu / THAI CHARACTER MAITAIKHU
					case 0xde8: ks = 0x0E48; break; // XK_Thai_maiek / THAI CHARACTER MAI EK
					case 0xde9: ks = 0x0E49; break; // XK_Thai_maitho / THAI CHARACTER MAI THO
					case 0xdea: ks = 0x0E4A; break; // XK_Thai_maitri / THAI CHARACTER MAI TRI
					case 0xdeb: ks = 0x0E4B; break; // XK_Thai_maichattawa / THAI CHARACTER MAI CHATTAWA
					case 0xdec: ks = 0x0E4C; break; // XK_Thai_thanthakhat / THAI CHARACTER THANTHAKHAT
					case 0xded: ks = 0x0E4D; break; // XK_Thai_nikhahit / THAI CHARACTER NIKHAHIT
					case 0xdf0: ks = 0x0E50; break; // XK_Thai_leksun / THAI DIGIT ZERO
					case 0xdf1: ks = 0x0E51; break; // XK_Thai_leknung / THAI DIGIT ONE
					case 0xdf2: ks = 0x0E52; break; // XK_Thai_leksong / THAI DIGIT TWO
					case 0xdf3: ks = 0x0E53; break; // XK_Thai_leksam / THAI DIGIT THREE
					case 0xdf4: ks = 0x0E54; break; // XK_Thai_leksi / THAI DIGIT FOUR
					case 0xdf5: ks = 0x0E55; break; // XK_Thai_lekha / THAI DIGIT FIVE
					case 0xdf6: ks = 0x0E56; break; // XK_Thai_lekhok / THAI DIGIT SIX
					case 0xdf7: ks = 0x0E57; break; // XK_Thai_lekchet / THAI DIGIT SEVEN
					case 0xdf8: ks = 0x0E58; break; // XK_Thai_lekpaet / THAI DIGIT EIGHT
					case 0xdf9: ks = 0x0E59; break; // XK_Thai_lekkao / THAI DIGIT NINE
					case 0xea1: ks = 0x3131; break; // XK_Hangul_Kiyeog / HANGUL LETTER KIYEOK
					case 0xea2: ks = 0x3132; break; // XK_Hangul_SsangKiyeog / HANGUL LETTER SSANGKIYEOK
					case 0xea3: ks = 0x3133; break; // XK_Hangul_KiyeogSios / HANGUL LETTER KIYEOK-SIOS
					case 0xea4: ks = 0x3134; break; // XK_Hangul_Nieun / HANGUL LETTER NIEUN
					case 0xea5: ks = 0x3135; break; // XK_Hangul_NieunJieuj / HANGUL LETTER NIEUN-CIEUC
					case 0xea6: ks = 0x3136; break; // XK_Hangul_NieunHieuh / HANGUL LETTER NIEUN-HIEUH
					case 0xea7: ks = 0x3137; break; // XK_Hangul_Dikeud / HANGUL LETTER TIKEUT
					case 0xea8: ks = 0x3138; break; // XK_Hangul_SsangDikeud / HANGUL LETTER SSANGTIKEUT
					case 0xea9: ks = 0x3139; break; // XK_Hangul_Rieul / HANGUL LETTER RIEUL
					case 0xeaa: ks = 0x313A; break; // XK_Hangul_RieulKiyeog / HANGUL LETTER RIEUL-KIYEOK
					case 0xeab: ks = 0x313B; break; // XK_Hangul_RieulMieum / HANGUL LETTER RIEUL-MIEUM
					case 0xeac: ks = 0x313C; break; // XK_Hangul_RieulPieub / HANGUL LETTER RIEUL-PIEUP
					case 0xead: ks = 0x313D; break; // XK_Hangul_RieulSios / HANGUL LETTER RIEUL-SIOS
					case 0xeae: ks = 0x313E; break; // XK_Hangul_RieulTieut / HANGUL LETTER RIEUL-THIEUTH
					case 0xeaf: ks = 0x313F; break; // XK_Hangul_RieulPhieuf / HANGUL LETTER RIEUL-PHIEUPH
					case 0xeb0: ks = 0x3140; break; // XK_Hangul_RieulHieuh / HANGUL LETTER RIEUL-HIEUH
					case 0xeb1: ks = 0x3141; break; // XK_Hangul_Mieum / HANGUL LETTER MIEUM
					case 0xeb2: ks = 0x3142; break; // XK_Hangul_Pieub / HANGUL LETTER PIEUP
					case 0xeb3: ks = 0x3143; break; // XK_Hangul_SsangPieub / HANGUL LETTER SSANGPIEUP
					case 0xeb4: ks = 0x3144; break; // XK_Hangul_PieubSios / HANGUL LETTER PIEUP-SIOS
					case 0xeb5: ks = 0x3145; break; // XK_Hangul_Sios / HANGUL LETTER SIOS
					case 0xeb6: ks = 0x3146; break; // XK_Hangul_SsangSios / HANGUL LETTER SSANGSIOS
					case 0xeb7: ks = 0x3147; break; // XK_Hangul_Ieung / HANGUL LETTER IEUNG
					case 0xeb8: ks = 0x3148; break; // XK_Hangul_Jieuj / HANGUL LETTER CIEUC
					case 0xeb9: ks = 0x3149; break; // XK_Hangul_SsangJieuj / HANGUL LETTER SSANGCIEUC
					case 0xeba: ks = 0x314A; break; // XK_Hangul_Cieuc / HANGUL LETTER CHIEUCH
					case 0xebb: ks = 0x314B; break; // XK_Hangul_Khieuq / HANGUL LETTER KHIEUKH
					case 0xebc: ks = 0x314C; break; // XK_Hangul_Tieut / HANGUL LETTER THIEUTH
					case 0xebd: ks = 0x314D; break; // XK_Hangul_Phieuf / HANGUL LETTER PHIEUPH
					case 0xebe: ks = 0x314E; break; // XK_Hangul_Hieuh / HANGUL LETTER HIEUH
					case 0xebf: ks = 0x314F; break; // XK_Hangul_A / HANGUL LETTER A
					case 0xec0: ks = 0x3150; break; // XK_Hangul_AE / HANGUL LETTER AE
					case 0xec1: ks = 0x3151; break; // XK_Hangul_YA / HANGUL LETTER YA
					case 0xec2: ks = 0x3152; break; // XK_Hangul_YAE / HANGUL LETTER YAE
					case 0xec3: ks = 0x3153; break; // XK_Hangul_EO / HANGUL LETTER EO
					case 0xec4: ks = 0x3154; break; // XK_Hangul_E / HANGUL LETTER E
					case 0xec5: ks = 0x3155; break; // XK_Hangul_YEO / HANGUL LETTER YEO
					case 0xec6: ks = 0x3156; break; // XK_Hangul_YE / HANGUL LETTER YE
					case 0xec7: ks = 0x3157; break; // XK_Hangul_O / HANGUL LETTER O
					case 0xec8: ks = 0x3158; break; // XK_Hangul_WA / HANGUL LETTER WA
					case 0xec9: ks = 0x3159; break; // XK_Hangul_WAE / HANGUL LETTER WAE
					case 0xeca: ks = 0x315A; break; // XK_Hangul_OE / HANGUL LETTER OE
					case 0xecb: ks = 0x315B; break; // XK_Hangul_YO / HANGUL LETTER YO
					case 0xecc: ks = 0x315C; break; // XK_Hangul_U / HANGUL LETTER U
					case 0xecd: ks = 0x315D; break; // XK_Hangul_WEO / HANGUL LETTER WEO
					case 0xece: ks = 0x315E; break; // XK_Hangul_WE / HANGUL LETTER WE
					case 0xecf: ks = 0x315F; break; // XK_Hangul_WI / HANGUL LETTER WI
					case 0xed0: ks = 0x3160; break; // XK_Hangul_YU / HANGUL LETTER YU
					case 0xed1: ks = 0x3161; break; // XK_Hangul_EU / HANGUL LETTER EU
					case 0xed2: ks = 0x3162; break; // XK_Hangul_YI / HANGUL LETTER YI
					case 0xed3: ks = 0x3163; break; // XK_Hangul_I / HANGUL LETTER I
					case 0xed4: ks = 0x11A8; break; // XK_Hangul_J_Kiyeog / HANGUL JONGSEONG KIYEOK
					case 0xed5: ks = 0x11A9; break; // XK_Hangul_J_SsangKiyeog / HANGUL JONGSEONG SSANGKIYEOK
					case 0xed6: ks = 0x11AA; break; // XK_Hangul_J_KiyeogSios / HANGUL JONGSEONG KIYEOK-SIOS
					case 0xed7: ks = 0x11AB; break; // XK_Hangul_J_Nieun / HANGUL JONGSEONG NIEUN
					case 0xed8: ks = 0x11AC; break; // XK_Hangul_J_NieunJieuj / HANGUL JONGSEONG NIEUN-CIEUC
					case 0xed9: ks = 0x11AD; break; // XK_Hangul_J_NieunHieuh / HANGUL JONGSEONG NIEUN-HIEUH
					case 0xeda: ks = 0x11AE; break; // XK_Hangul_J_Dikeud / HANGUL JONGSEONG TIKEUT
					case 0xedb: ks = 0x11AF; break; // XK_Hangul_J_Rieul / HANGUL JONGSEONG RIEUL
					case 0xedc: ks = 0x11B0; break; // XK_Hangul_J_RieulKiyeog / HANGUL JONGSEONG RIEUL-KIYEOK
					case 0xedd: ks = 0x11B1; break; // XK_Hangul_J_RieulMieum / HANGUL JONGSEONG RIEUL-MIEUM
					case 0xede: ks = 0x11B2; break; // XK_Hangul_J_RieulPieub / HANGUL JONGSEONG RIEUL-PIEUP
					case 0xedf: ks = 0x11B3; break; // XK_Hangul_J_RieulSios / HANGUL JONGSEONG RIEUL-SIOS
					case 0xee0: ks = 0x11B4; break; // XK_Hangul_J_RieulTieut / HANGUL JONGSEONG RIEUL-THIEUTH
					case 0xee1: ks = 0x11B5; break; // XK_Hangul_J_RieulPhieuf / HANGUL JONGSEONG RIEUL-PHIEUPH
					case 0xee2: ks = 0x11B6; break; // XK_Hangul_J_RieulHieuh / HANGUL JONGSEONG RIEUL-HIEUH
					case 0xee3: ks = 0x11B7; break; // XK_Hangul_J_Mieum / HANGUL JONGSEONG MIEUM
					case 0xee4: ks = 0x11B8; break; // XK_Hangul_J_Pieub / HANGUL JONGSEONG PIEUP
					case 0xee5: ks = 0x11B9; break; // XK_Hangul_J_PieubSios / HANGUL JONGSEONG PIEUP-SIOS
					case 0xee6: ks = 0x11BA; break; // XK_Hangul_J_Sios / HANGUL JONGSEONG SIOS
					case 0xee7: ks = 0x11BB; break; // XK_Hangul_J_SsangSios / HANGUL JONGSEONG SSANGSIOS
					case 0xee8: ks = 0x11BC; break; // XK_Hangul_J_Ieung / HANGUL JONGSEONG IEUNG
					case 0xee9: ks = 0x11BD; break; // XK_Hangul_J_Jieuj / HANGUL JONGSEONG CIEUC
					case 0xeea: ks = 0x11BE; break; // XK_Hangul_J_Cieuc / HANGUL JONGSEONG CHIEUCH
					case 0xeeb: ks = 0x11BF; break; // XK_Hangul_J_Khieuq / HANGUL JONGSEONG KHIEUKH
					case 0xeec: ks = 0x11C0; break; // XK_Hangul_J_Tieut / HANGUL JONGSEONG THIEUTH
					case 0xeed: ks = 0x11C1; break; // XK_Hangul_J_Phieuf / HANGUL JONGSEONG PHIEUPH
					case 0xeee: ks = 0x11C2; break; // XK_Hangul_J_Hieuh / HANGUL JONGSEONG HIEUH
					case 0xeef: ks = 0x316D; break; // XK_Hangul_RieulYeorinHieuh / HANGUL LETTER RIEUL-YEORINHIEUH
					case 0xef0: ks = 0x3171; break; // XK_Hangul_SunkyeongeumMieum / HANGUL LETTER KAPYEOUNMIEUM
					case 0xef1: ks = 0x3178; break; // XK_Hangul_SunkyeongeumPieub / HANGUL LETTER KAPYEOUNPIEUP
					case 0xef2: ks = 0x317F; break; // XK_Hangul_PanSios / HANGUL LETTER PANSIOS
					case 0xef3: ks = 0x3181; break; // XK_Hangul_KkogjiDalrinIeung / HANGUL LETTER YESIEUNG
					case 0xef4: ks = 0x3184; break; // XK_Hangul_SunkyeongeumPhieuf / HANGUL LETTER KAPYEOUNPHIEUPH
					case 0xef5: ks = 0x3186; break; // XK_Hangul_YeorinHieuh / HANGUL LETTER YEORINHIEUH
					case 0xef6: ks = 0x318D; break; // XK_Hangul_AraeA / HANGUL LETTER ARAEA
					case 0xef7: ks = 0x318E; break; // XK_Hangul_AraeAE / HANGUL LETTER ARAEAE
					case 0xef8: ks = 0x11EB; break; // XK_Hangul_J_PanSios / HANGUL JONGSEONG PANSIOS
					case 0xef9: ks = 0x11F0; break; // XK_Hangul_J_KkogjiDalrinIeung / HANGUL JONGSEONG YESIEUNG
					case 0xefa: ks = 0x11F9; break; // XK_Hangul_J_YeorinHieuh / HANGUL JONGSEONG YEORINHIEUH
					case 0xeff: ks = 0x20A9; break; // XK_Korean_Won / WON SIGN)
					case 0x1000587: ks = 0x0587; break; // XK_Armenian_ligature_ew / ARMENIAN SMALL LIGATURE ECH YIWN
					case 0x1000589: ks = 0x0589; break; // XK_Armenian_full_stop / ARMENIAN FULL STOP
					case 0x100055d: ks = 0x055D; break; // XK_Armenian_separation_mark / ARMENIAN COMMA
					case 0x100058a: ks = 0x058A; break; // XK_Armenian_hyphen / ARMENIAN HYPHEN
					case 0x100055c: ks = 0x055C; break; // XK_Armenian_exclam / ARMENIAN EXCLAMATION MARK
					case 0x100055b: ks = 0x055B; break; // XK_Armenian_accent / ARMENIAN EMPHASIS MARK
					case 0x100055e: ks = 0x055E; break; // XK_Armenian_question / ARMENIAN QUESTION MARK
					case 0x1000531: ks = 0x0531; break; // XK_Armenian_AYB / ARMENIAN CAPITAL LETTER AYB
					case 0x1000561: ks = 0x0561; break; // XK_Armenian_ayb / ARMENIAN SMALL LETTER AYB
					case 0x1000532: ks = 0x0532; break; // XK_Armenian_BEN / ARMENIAN CAPITAL LETTER BEN
					case 0x1000562: ks = 0x0562; break; // XK_Armenian_ben / ARMENIAN SMALL LETTER BEN
					case 0x1000533: ks = 0x0533; break; // XK_Armenian_GIM / ARMENIAN CAPITAL LETTER GIM
					case 0x1000563: ks = 0x0563; break; // XK_Armenian_gim / ARMENIAN SMALL LETTER GIM
					case 0x1000534: ks = 0x0534; break; // XK_Armenian_DA / ARMENIAN CAPITAL LETTER DA
					case 0x1000564: ks = 0x0564; break; // XK_Armenian_da / ARMENIAN SMALL LETTER DA
					case 0x1000535: ks = 0x0535; break; // XK_Armenian_YECH / ARMENIAN CAPITAL LETTER ECH
					case 0x1000565: ks = 0x0565; break; // XK_Armenian_yech / ARMENIAN SMALL LETTER ECH
					case 0x1000536: ks = 0x0536; break; // XK_Armenian_ZA / ARMENIAN CAPITAL LETTER ZA
					case 0x1000566: ks = 0x0566; break; // XK_Armenian_za / ARMENIAN SMALL LETTER ZA
					case 0x1000537: ks = 0x0537; break; // XK_Armenian_E / ARMENIAN CAPITAL LETTER EH
					case 0x1000567: ks = 0x0567; break; // XK_Armenian_e / ARMENIAN SMALL LETTER EH
					case 0x1000538: ks = 0x0538; break; // XK_Armenian_AT / ARMENIAN CAPITAL LETTER ET
					case 0x1000568: ks = 0x0568; break; // XK_Armenian_at / ARMENIAN SMALL LETTER ET
					case 0x1000539: ks = 0x0539; break; // XK_Armenian_TO / ARMENIAN CAPITAL LETTER TO
					case 0x1000569: ks = 0x0569; break; // XK_Armenian_to / ARMENIAN SMALL LETTER TO
					case 0x100053a: ks = 0x053A; break; // XK_Armenian_ZHE / ARMENIAN CAPITAL LETTER ZHE
					case 0x100056a: ks = 0x056A; break; // XK_Armenian_zhe / ARMENIAN SMALL LETTER ZHE
					case 0x100053b: ks = 0x053B; break; // XK_Armenian_INI / ARMENIAN CAPITAL LETTER INI
					case 0x100056b: ks = 0x056B; break; // XK_Armenian_ini / ARMENIAN SMALL LETTER INI
					case 0x100053c: ks = 0x053C; break; // XK_Armenian_LYUN / ARMENIAN CAPITAL LETTER LIWN
					case 0x100056c: ks = 0x056C; break; // XK_Armenian_lyun / ARMENIAN SMALL LETTER LIWN
					case 0x100053d: ks = 0x053D; break; // XK_Armenian_KHE / ARMENIAN CAPITAL LETTER XEH
					case 0x100056d: ks = 0x056D; break; // XK_Armenian_khe / ARMENIAN SMALL LETTER XEH
					case 0x100053e: ks = 0x053E; break; // XK_Armenian_TSA / ARMENIAN CAPITAL LETTER CA
					case 0x100056e: ks = 0x056E; break; // XK_Armenian_tsa / ARMENIAN SMALL LETTER CA
					case 0x100053f: ks = 0x053F; break; // XK_Armenian_KEN / ARMENIAN CAPITAL LETTER KEN
					case 0x100056f: ks = 0x056F; break; // XK_Armenian_ken / ARMENIAN SMALL LETTER KEN
					case 0x1000540: ks = 0x0540; break; // XK_Armenian_HO / ARMENIAN CAPITAL LETTER HO
					case 0x1000570: ks = 0x0570; break; // XK_Armenian_ho / ARMENIAN SMALL LETTER HO
					case 0x1000541: ks = 0x0541; break; // XK_Armenian_DZA / ARMENIAN CAPITAL LETTER JA
					case 0x1000571: ks = 0x0571; break; // XK_Armenian_dza / ARMENIAN SMALL LETTER JA
					case 0x1000542: ks = 0x0542; break; // XK_Armenian_GHAT / ARMENIAN CAPITAL LETTER GHAD
					case 0x1000572: ks = 0x0572; break; // XK_Armenian_ghat / ARMENIAN SMALL LETTER GHAD
					case 0x1000543: ks = 0x0543; break; // XK_Armenian_TCHE / ARMENIAN CAPITAL LETTER CHEH
					case 0x1000573: ks = 0x0573; break; // XK_Armenian_tche / ARMENIAN SMALL LETTER CHEH
					case 0x1000544: ks = 0x0544; break; // XK_Armenian_MEN / ARMENIAN CAPITAL LETTER MEN
					case 0x1000574: ks = 0x0574; break; // XK_Armenian_men / ARMENIAN SMALL LETTER MEN
					case 0x1000545: ks = 0x0545; break; // XK_Armenian_HI / ARMENIAN CAPITAL LETTER YI
					case 0x1000575: ks = 0x0575; break; // XK_Armenian_hi / ARMENIAN SMALL LETTER YI
					case 0x1000546: ks = 0x0546; break; // XK_Armenian_NU / ARMENIAN CAPITAL LETTER NOW
					case 0x1000576: ks = 0x0576; break; // XK_Armenian_nu / ARMENIAN SMALL LETTER NOW
					case 0x1000547: ks = 0x0547; break; // XK_Armenian_SHA / ARMENIAN CAPITAL LETTER SHA
					case 0x1000577: ks = 0x0577; break; // XK_Armenian_sha / ARMENIAN SMALL LETTER SHA
					case 0x1000548: ks = 0x0548; break; // XK_Armenian_VO / ARMENIAN CAPITAL LETTER VO
					case 0x1000578: ks = 0x0578; break; // XK_Armenian_vo / ARMENIAN SMALL LETTER VO
					case 0x1000549: ks = 0x0549; break; // XK_Armenian_CHA / ARMENIAN CAPITAL LETTER CHA
					case 0x1000579: ks = 0x0579; break; // XK_Armenian_cha / ARMENIAN SMALL LETTER CHA
					case 0x100054a: ks = 0x054A; break; // XK_Armenian_PE / ARMENIAN CAPITAL LETTER PEH
					case 0x100057a: ks = 0x057A; break; // XK_Armenian_pe / ARMENIAN SMALL LETTER PEH
					case 0x100054b: ks = 0x054B; break; // XK_Armenian_JE / ARMENIAN CAPITAL LETTER JHEH
					case 0x100057b: ks = 0x057B; break; // XK_Armenian_je / ARMENIAN SMALL LETTER JHEH
					case 0x100054c: ks = 0x054C; break; // XK_Armenian_RA / ARMENIAN CAPITAL LETTER RA
					case 0x100057c: ks = 0x057C; break; // XK_Armenian_ra / ARMENIAN SMALL LETTER RA
					case 0x100054d: ks = 0x054D; break; // XK_Armenian_SE / ARMENIAN CAPITAL LETTER SEH
					case 0x100057d: ks = 0x057D; break; // XK_Armenian_se / ARMENIAN SMALL LETTER SEH
					case 0x100054e: ks = 0x054E; break; // XK_Armenian_VEV / ARMENIAN CAPITAL LETTER VEW
					case 0x100057e: ks = 0x057E; break; // XK_Armenian_vev / ARMENIAN SMALL LETTER VEW
					case 0x100054f: ks = 0x054F; break; // XK_Armenian_TYUN / ARMENIAN CAPITAL LETTER TIWN
					case 0x100057f: ks = 0x057F; break; // XK_Armenian_tyun / ARMENIAN SMALL LETTER TIWN
					case 0x1000550: ks = 0x0550; break; // XK_Armenian_RE / ARMENIAN CAPITAL LETTER REH
					case 0x1000580: ks = 0x0580; break; // XK_Armenian_re / ARMENIAN SMALL LETTER REH
					case 0x1000551: ks = 0x0551; break; // XK_Armenian_TSO / ARMENIAN CAPITAL LETTER CO
					case 0x1000581: ks = 0x0581; break; // XK_Armenian_tso / ARMENIAN SMALL LETTER CO
					case 0x1000552: ks = 0x0552; break; // XK_Armenian_VYUN / ARMENIAN CAPITAL LETTER YIWN
					case 0x1000582: ks = 0x0582; break; // XK_Armenian_vyun / ARMENIAN SMALL LETTER YIWN
					case 0x1000553: ks = 0x0553; break; // XK_Armenian_PYUR / ARMENIAN CAPITAL LETTER PIWR
					case 0x1000583: ks = 0x0583; break; // XK_Armenian_pyur / ARMENIAN SMALL LETTER PIWR
					case 0x1000554: ks = 0x0554; break; // XK_Armenian_KE / ARMENIAN CAPITAL LETTER KEH
					case 0x1000584: ks = 0x0584; break; // XK_Armenian_ke / ARMENIAN SMALL LETTER KEH
					case 0x1000555: ks = 0x0555; break; // XK_Armenian_O / ARMENIAN CAPITAL LETTER OH
					case 0x1000585: ks = 0x0585; break; // XK_Armenian_o / ARMENIAN SMALL LETTER OH
					case 0x1000556: ks = 0x0556; break; // XK_Armenian_FE / ARMENIAN CAPITAL LETTER FEH
					case 0x1000586: ks = 0x0586; break; // XK_Armenian_fe / ARMENIAN SMALL LETTER FEH
					case 0x100055a: ks = 0x055A; break; // XK_Armenian_apostrophe / ARMENIAN APOSTROPHE
					case 0x10010d0: ks = 0x10D0; break; // XK_Georgian_an / GEORGIAN LETTER AN
					case 0x10010d1: ks = 0x10D1; break; // XK_Georgian_ban / GEORGIAN LETTER BAN
					case 0x10010d2: ks = 0x10D2; break; // XK_Georgian_gan / GEORGIAN LETTER GAN
					case 0x10010d3: ks = 0x10D3; break; // XK_Georgian_don / GEORGIAN LETTER DON
					case 0x10010d4: ks = 0x10D4; break; // XK_Georgian_en / GEORGIAN LETTER EN
					case 0x10010d5: ks = 0x10D5; break; // XK_Georgian_vin / GEORGIAN LETTER VIN
					case 0x10010d6: ks = 0x10D6; break; // XK_Georgian_zen / GEORGIAN LETTER ZEN
					case 0x10010d7: ks = 0x10D7; break; // XK_Georgian_tan / GEORGIAN LETTER TAN
					case 0x10010d8: ks = 0x10D8; break; // XK_Georgian_in / GEORGIAN LETTER IN
					case 0x10010d9: ks = 0x10D9; break; // XK_Georgian_kan / GEORGIAN LETTER KAN
					case 0x10010da: ks = 0x10DA; break; // XK_Georgian_las / GEORGIAN LETTER LAS
					case 0x10010db: ks = 0x10DB; break; // XK_Georgian_man / GEORGIAN LETTER MAN
					case 0x10010dc: ks = 0x10DC; break; // XK_Georgian_nar / GEORGIAN LETTER NAR
					case 0x10010dd: ks = 0x10DD; break; // XK_Georgian_on / GEORGIAN LETTER ON
					case 0x10010de: ks = 0x10DE; break; // XK_Georgian_par / GEORGIAN LETTER PAR
					case 0x10010df: ks = 0x10DF; break; // XK_Georgian_zhar / GEORGIAN LETTER ZHAR
					case 0x10010e0: ks = 0x10E0; break; // XK_Georgian_rae / GEORGIAN LETTER RAE
					case 0x10010e1: ks = 0x10E1; break; // XK_Georgian_san / GEORGIAN LETTER SAN
					case 0x10010e2: ks = 0x10E2; break; // XK_Georgian_tar / GEORGIAN LETTER TAR
					case 0x10010e3: ks = 0x10E3; break; // XK_Georgian_un / GEORGIAN LETTER UN
					case 0x10010e4: ks = 0x10E4; break; // XK_Georgian_phar / GEORGIAN LETTER PHAR
					case 0x10010e5: ks = 0x10E5; break; // XK_Georgian_khar / GEORGIAN LETTER KHAR
					case 0x10010e6: ks = 0x10E6; break; // XK_Georgian_ghan / GEORGIAN LETTER GHAN
					case 0x10010e7: ks = 0x10E7; break; // XK_Georgian_qar / GEORGIAN LETTER QAR
					case 0x10010e8: ks = 0x10E8; break; // XK_Georgian_shin / GEORGIAN LETTER SHIN
					case 0x10010e9: ks = 0x10E9; break; // XK_Georgian_chin / GEORGIAN LETTER CHIN
					case 0x10010ea: ks = 0x10EA; break; // XK_Georgian_can / GEORGIAN LETTER CAN
					case 0x10010eb: ks = 0x10EB; break; // XK_Georgian_jil / GEORGIAN LETTER JIL
					case 0x10010ec: ks = 0x10EC; break; // XK_Georgian_cil / GEORGIAN LETTER CIL
					case 0x10010ed: ks = 0x10ED; break; // XK_Georgian_char / GEORGIAN LETTER CHAR
					case 0x10010ee: ks = 0x10EE; break; // XK_Georgian_xan / GEORGIAN LETTER XAN
					case 0x10010ef: ks = 0x10EF; break; // XK_Georgian_jhan / GEORGIAN LETTER JHAN
					case 0x10010f0: ks = 0x10F0; break; // XK_Georgian_hae / GEORGIAN LETTER HAE
					case 0x10010f1: ks = 0x10F1; break; // XK_Georgian_he / GEORGIAN LETTER HE
					case 0x10010f2: ks = 0x10F2; break; // XK_Georgian_hie / GEORGIAN LETTER HIE
					case 0x10010f3: ks = 0x10F3; break; // XK_Georgian_we / GEORGIAN LETTER WE
					case 0x10010f4: ks = 0x10F4; break; // XK_Georgian_har / GEORGIAN LETTER HAR
					case 0x10010f5: ks = 0x10F5; break; // XK_Georgian_hoe / GEORGIAN LETTER HOE
					case 0x10010f6: ks = 0x10F6; break; // XK_Georgian_fi / GEORGIAN LETTER FI
					case 0x1001e8a: ks = 0x1E8A; break; // XK_Xabovedot / LATIN CAPITAL LETTER X WITH DOT ABOVE
					case 0x100012c: ks = 0x012C; break; // XK_Ibreve / LATIN CAPITAL LETTER I WITH BREVE
					case 0x10001b5: ks = 0x01B5; break; // XK_Zstroke / LATIN CAPITAL LETTER Z WITH STROKE
					case 0x10001e6: ks = 0x01E6; break; // XK_Gcaron / LATIN CAPITAL LETTER G WITH CARON
					case 0x10001d1: ks = 0x01D1; break; // XK_Ocaron / LATIN CAPITAL LETTER O WITH CARON
					case 0x100019f: ks = 0x019F; break; // XK_Obarred / LATIN CAPITAL LETTER O WITH MIDDLE TILDE
					case 0x1001e8b: ks = 0x1E8B; break; // XK_xabovedot / LATIN SMALL LETTER X WITH DOT ABOVE
					case 0x100012d: ks = 0x012D; break; // XK_ibreve / LATIN SMALL LETTER I WITH BREVE
					case 0x10001b6: ks = 0x01B6; break; // XK_zstroke / LATIN SMALL LETTER Z WITH STROKE
					case 0x10001e7: ks = 0x01E7; break; // XK_gcaron / LATIN SMALL LETTER G WITH CARON
					case 0x10001d2: ks = 0x01D2; break; // XK_ocaron / LATIN SMALL LETTER O WITH CARON
					case 0x1000275: ks = 0x0275; break; // XK_obarred / LATIN SMALL LETTER BARRED O
					case 0x100018f: ks = 0x018F; break; // XK_SCHWA / LATIN CAPITAL LETTER SCHWA
					case 0x1000259: ks = 0x0259; break; // XK_schwa / LATIN SMALL LETTER SCHWA
					case 0x10001b7: ks = 0x01B7; break; // XK_EZH / LATIN CAPITAL LETTER EZH
					case 0x1000292: ks = 0x0292; break; // XK_ezh / LATIN SMALL LETTER EZH
					case 0x1001e36: ks = 0x1E36; break; // XK_Lbelowdot / LATIN CAPITAL LETTER L WITH DOT BELOW
					case 0x1001e37: ks = 0x1E37; break; // XK_lbelowdot / LATIN SMALL LETTER L WITH DOT BELOW
					case 0x1001ea0: ks = 0x1EA0; break; // XK_Abelowdot / LATIN CAPITAL LETTER A WITH DOT BELOW
					case 0x1001ea1: ks = 0x1EA1; break; // XK_abelowdot / LATIN SMALL LETTER A WITH DOT BELOW
					case 0x1001ea2: ks = 0x1EA2; break; // XK_Ahook / LATIN CAPITAL LETTER A WITH HOOK ABOVE
					case 0x1001ea3: ks = 0x1EA3; break; // XK_ahook / LATIN SMALL LETTER A WITH HOOK ABOVE
					case 0x1001ea4: ks = 0x1EA4; break; // XK_Acircumflexacute / LATIN CAPITAL LETTER A WITH CIRCUMFLEX AND ACUTE
					case 0x1001ea5: ks = 0x1EA5; break; // XK_acircumflexacute / LATIN SMALL LETTER A WITH CIRCUMFLEX AND ACUTE
					case 0x1001ea6: ks = 0x1EA6; break; // XK_Acircumflexgrave / LATIN CAPITAL LETTER A WITH CIRCUMFLEX AND GRAVE
					case 0x1001ea7: ks = 0x1EA7; break; // XK_acircumflexgrave / LATIN SMALL LETTER A WITH CIRCUMFLEX AND GRAVE
					case 0x1001ea8: ks = 0x1EA8; break; // XK_Acircumflexhook / LATIN CAPITAL LETTER A WITH CIRCUMFLEX AND HOOK ABOVE
					case 0x1001ea9: ks = 0x1EA9; break; // XK_acircumflexhook / LATIN SMALL LETTER A WITH CIRCUMFLEX AND HOOK ABOVE
					case 0x1001eaa: ks = 0x1EAA; break; // XK_Acircumflextilde / LATIN CAPITAL LETTER A WITH CIRCUMFLEX AND TILDE
					case 0x1001eab: ks = 0x1EAB; break; // XK_acircumflextilde / LATIN SMALL LETTER A WITH CIRCUMFLEX AND TILDE
					case 0x1001eac: ks = 0x1EAC; break; // XK_Acircumflexbelowdot / LATIN CAPITAL LETTER A WITH CIRCUMFLEX AND DOT BELOW
					case 0x1001ead: ks = 0x1EAD; break; // XK_acircumflexbelowdot / LATIN SMALL LETTER A WITH CIRCUMFLEX AND DOT BELOW
					case 0x1001eae: ks = 0x1EAE; break; // XK_Abreveacute / LATIN CAPITAL LETTER A WITH BREVE AND ACUTE
					case 0x1001eaf: ks = 0x1EAF; break; // XK_abreveacute / LATIN SMALL LETTER A WITH BREVE AND ACUTE
					case 0x1001eb0: ks = 0x1EB0; break; // XK_Abrevegrave / LATIN CAPITAL LETTER A WITH BREVE AND GRAVE
					case 0x1001eb1: ks = 0x1EB1; break; // XK_abrevegrave / LATIN SMALL LETTER A WITH BREVE AND GRAVE
					case 0x1001eb2: ks = 0x1EB2; break; // XK_Abrevehook / LATIN CAPITAL LETTER A WITH BREVE AND HOOK ABOVE
					case 0x1001eb3: ks = 0x1EB3; break; // XK_abrevehook / LATIN SMALL LETTER A WITH BREVE AND HOOK ABOVE
					case 0x1001eb4: ks = 0x1EB4; break; // XK_Abrevetilde / LATIN CAPITAL LETTER A WITH BREVE AND TILDE
					case 0x1001eb5: ks = 0x1EB5; break; // XK_abrevetilde / LATIN SMALL LETTER A WITH BREVE AND TILDE
					case 0x1001eb6: ks = 0x1EB6; break; // XK_Abrevebelowdot / LATIN CAPITAL LETTER A WITH BREVE AND DOT BELOW
					case 0x1001eb7: ks = 0x1EB7; break; // XK_abrevebelowdot / LATIN SMALL LETTER A WITH BREVE AND DOT BELOW
					case 0x1001eb8: ks = 0x1EB8; break; // XK_Ebelowdot / LATIN CAPITAL LETTER E WITH DOT BELOW
					case 0x1001eb9: ks = 0x1EB9; break; // XK_ebelowdot / LATIN SMALL LETTER E WITH DOT BELOW
					case 0x1001eba: ks = 0x1EBA; break; // XK_Ehook / LATIN CAPITAL LETTER E WITH HOOK ABOVE
					case 0x1001ebb: ks = 0x1EBB; break; // XK_ehook / LATIN SMALL LETTER E WITH HOOK ABOVE
					case 0x1001ebc: ks = 0x1EBC; break; // XK_Etilde / LATIN CAPITAL LETTER E WITH TILDE
					case 0x1001ebd: ks = 0x1EBD; break; // XK_etilde / LATIN SMALL LETTER E WITH TILDE
					case 0x1001ebe: ks = 0x1EBE; break; // XK_Ecircumflexacute / LATIN CAPITAL LETTER E WITH CIRCUMFLEX AND ACUTE
					case 0x1001ebf: ks = 0x1EBF; break; // XK_ecircumflexacute / LATIN SMALL LETTER E WITH CIRCUMFLEX AND ACUTE
					case 0x1001ec0: ks = 0x1EC0; break; // XK_Ecircumflexgrave / LATIN CAPITAL LETTER E WITH CIRCUMFLEX AND GRAVE
					case 0x1001ec1: ks = 0x1EC1; break; // XK_ecircumflexgrave / LATIN SMALL LETTER E WITH CIRCUMFLEX AND GRAVE
					case 0x1001ec2: ks = 0x1EC2; break; // XK_Ecircumflexhook / LATIN CAPITAL LETTER E WITH CIRCUMFLEX AND HOOK ABOVE
					case 0x1001ec3: ks = 0x1EC3; break; // XK_ecircumflexhook / LATIN SMALL LETTER E WITH CIRCUMFLEX AND HOOK ABOVE
					case 0x1001ec4: ks = 0x1EC4; break; // XK_Ecircumflextilde / LATIN CAPITAL LETTER E WITH CIRCUMFLEX AND TILDE
					case 0x1001ec5: ks = 0x1EC5; break; // XK_ecircumflextilde / LATIN SMALL LETTER E WITH CIRCUMFLEX AND TILDE
					case 0x1001ec6: ks = 0x1EC6; break; // XK_Ecircumflexbelowdot / LATIN CAPITAL LETTER E WITH CIRCUMFLEX AND DOT BELOW
					case 0x1001ec7: ks = 0x1EC7; break; // XK_ecircumflexbelowdot / LATIN SMALL LETTER E WITH CIRCUMFLEX AND DOT BELOW
					case 0x1001ec8: ks = 0x1EC8; break; // XK_Ihook / LATIN CAPITAL LETTER I WITH HOOK ABOVE
					case 0x1001ec9: ks = 0x1EC9; break; // XK_ihook / LATIN SMALL LETTER I WITH HOOK ABOVE
					case 0x1001eca: ks = 0x1ECA; break; // XK_Ibelowdot / LATIN CAPITAL LETTER I WITH DOT BELOW
					case 0x1001ecb: ks = 0x1ECB; break; // XK_ibelowdot / LATIN SMALL LETTER I WITH DOT BELOW
					case 0x1001ecc: ks = 0x1ECC; break; // XK_Obelowdot / LATIN CAPITAL LETTER O WITH DOT BELOW
					case 0x1001ecd: ks = 0x1ECD; break; // XK_obelowdot / LATIN SMALL LETTER O WITH DOT BELOW
					case 0x1001ece: ks = 0x1ECE; break; // XK_Ohook / LATIN CAPITAL LETTER O WITH HOOK ABOVE
					case 0x1001ecf: ks = 0x1ECF; break; // XK_ohook / LATIN SMALL LETTER O WITH HOOK ABOVE
					case 0x1001ed0: ks = 0x1ED0; break; // XK_Ocircumflexacute / LATIN CAPITAL LETTER O WITH CIRCUMFLEX AND ACUTE
					case 0x1001ed1: ks = 0x1ED1; break; // XK_ocircumflexacute / LATIN SMALL LETTER O WITH CIRCUMFLEX AND ACUTE
					case 0x1001ed2: ks = 0x1ED2; break; // XK_Ocircumflexgrave / LATIN CAPITAL LETTER O WITH CIRCUMFLEX AND GRAVE
					case 0x1001ed3: ks = 0x1ED3; break; // XK_ocircumflexgrave / LATIN SMALL LETTER O WITH CIRCUMFLEX AND GRAVE
					case 0x1001ed4: ks = 0x1ED4; break; // XK_Ocircumflexhook / LATIN CAPITAL LETTER O WITH CIRCUMFLEX AND HOOK ABOVE
					case 0x1001ed5: ks = 0x1ED5; break; // XK_ocircumflexhook / LATIN SMALL LETTER O WITH CIRCUMFLEX AND HOOK ABOVE
					case 0x1001ed6: ks = 0x1ED6; break; // XK_Ocircumflextilde / LATIN CAPITAL LETTER O WITH CIRCUMFLEX AND TILDE
					case 0x1001ed7: ks = 0x1ED7; break; // XK_ocircumflextilde / LATIN SMALL LETTER O WITH CIRCUMFLEX AND TILDE
					case 0x1001ed8: ks = 0x1ED8; break; // XK_Ocircumflexbelowdot / LATIN CAPITAL LETTER O WITH CIRCUMFLEX AND DOT BELOW
					case 0x1001ed9: ks = 0x1ED9; break; // XK_ocircumflexbelowdot / LATIN SMALL LETTER O WITH CIRCUMFLEX AND DOT BELOW
					case 0x1001eda: ks = 0x1EDA; break; // XK_Ohornacute / LATIN CAPITAL LETTER O WITH HORN AND ACUTE
					case 0x1001edb: ks = 0x1EDB; break; // XK_ohornacute / LATIN SMALL LETTER O WITH HORN AND ACUTE
					case 0x1001edc: ks = 0x1EDC; break; // XK_Ohorngrave / LATIN CAPITAL LETTER O WITH HORN AND GRAVE
					case 0x1001edd: ks = 0x1EDD; break; // XK_ohorngrave / LATIN SMALL LETTER O WITH HORN AND GRAVE
					case 0x1001ede: ks = 0x1EDE; break; // XK_Ohornhook / LATIN CAPITAL LETTER O WITH HORN AND HOOK ABOVE
					case 0x1001edf: ks = 0x1EDF; break; // XK_ohornhook / LATIN SMALL LETTER O WITH HORN AND HOOK ABOVE
					case 0x1001ee0: ks = 0x1EE0; break; // XK_Ohorntilde / LATIN CAPITAL LETTER O WITH HORN AND TILDE
					case 0x1001ee1: ks = 0x1EE1; break; // XK_ohorntilde / LATIN SMALL LETTER O WITH HORN AND TILDE
					case 0x1001ee2: ks = 0x1EE2; break; // XK_Ohornbelowdot / LATIN CAPITAL LETTER O WITH HORN AND DOT BELOW
					case 0x1001ee3: ks = 0x1EE3; break; // XK_ohornbelowdot / LATIN SMALL LETTER O WITH HORN AND DOT BELOW
					case 0x1001ee4: ks = 0x1EE4; break; // XK_Ubelowdot / LATIN CAPITAL LETTER U WITH DOT BELOW
					case 0x1001ee5: ks = 0x1EE5; break; // XK_ubelowdot / LATIN SMALL LETTER U WITH DOT BELOW
					case 0x1001ee6: ks = 0x1EE6; break; // XK_Uhook / LATIN CAPITAL LETTER U WITH HOOK ABOVE
					case 0x1001ee7: ks = 0x1EE7; break; // XK_uhook / LATIN SMALL LETTER U WITH HOOK ABOVE
					case 0x1001ee8: ks = 0x1EE8; break; // XK_Uhornacute / LATIN CAPITAL LETTER U WITH HORN AND ACUTE
					case 0x1001ee9: ks = 0x1EE9; break; // XK_uhornacute / LATIN SMALL LETTER U WITH HORN AND ACUTE
					case 0x1001eea: ks = 0x1EEA; break; // XK_Uhorngrave / LATIN CAPITAL LETTER U WITH HORN AND GRAVE
					case 0x1001eeb: ks = 0x1EEB; break; // XK_uhorngrave / LATIN SMALL LETTER U WITH HORN AND GRAVE
					case 0x1001eec: ks = 0x1EEC; break; // XK_Uhornhook / LATIN CAPITAL LETTER U WITH HORN AND HOOK ABOVE
					case 0x1001eed: ks = 0x1EED; break; // XK_uhornhook / LATIN SMALL LETTER U WITH HORN AND HOOK ABOVE
					case 0x1001eee: ks = 0x1EEE; break; // XK_Uhorntilde / LATIN CAPITAL LETTER U WITH HORN AND TILDE
					case 0x1001eef: ks = 0x1EEF; break; // XK_uhorntilde / LATIN SMALL LETTER U WITH HORN AND TILDE
					case 0x1001ef0: ks = 0x1EF0; break; // XK_Uhornbelowdot / LATIN CAPITAL LETTER U WITH HORN AND DOT BELOW
					case 0x1001ef1: ks = 0x1EF1; break; // XK_uhornbelowdot / LATIN SMALL LETTER U WITH HORN AND DOT BELOW
					case 0x1001ef4: ks = 0x1EF4; break; // XK_Ybelowdot / LATIN CAPITAL LETTER Y WITH DOT BELOW
					case 0x1001ef5: ks = 0x1EF5; break; // XK_ybelowdot / LATIN SMALL LETTER Y WITH DOT BELOW
					case 0x1001ef6: ks = 0x1EF6; break; // XK_Yhook / LATIN CAPITAL LETTER Y WITH HOOK ABOVE
					case 0x1001ef7: ks = 0x1EF7; break; // XK_yhook / LATIN SMALL LETTER Y WITH HOOK ABOVE
					case 0x1001ef8: ks = 0x1EF8; break; // XK_Ytilde / LATIN CAPITAL LETTER Y WITH TILDE
					case 0x1001ef9: ks = 0x1EF9; break; // XK_ytilde / LATIN SMALL LETTER Y WITH TILDE
					case 0x10001a0: ks = 0x01A0; break; // XK_Ohorn / LATIN CAPITAL LETTER O WITH HORN
					case 0x10001a1: ks = 0x01A1; break; // XK_ohorn / LATIN SMALL LETTER O WITH HORN
					case 0x10001af: ks = 0x01AF; break; // XK_Uhorn / LATIN CAPITAL LETTER U WITH HORN
					case 0x10001b0: ks = 0x01B0; break; // XK_uhorn / LATIN SMALL LETTER U WITH HORN
					case 0x1000303: ks = 0x0303; break; // XK_combining_tilde / COMBINING TILDE
					case 0x1000300: ks = 0x0300; break; // XK_combining_grave / COMBINING GRAVE ACCENT
					case 0x1000301: ks = 0x0301; break; // XK_combining_acute / COMBINING ACUTE ACCENT
					case 0x1000309: ks = 0x0309; break; // XK_combining_hook / COMBINING HOOK ABOVE
					case 0x1000323: ks = 0x0323; break; // XK_combining_belowdot / COMBINING DOT BELOW
					case 0x10020a0: ks = 0x20A0; break; // XK_EcuSign / EURO-CURRENCY SIGN
					case 0x10020a1: ks = 0x20A1; break; // XK_ColonSign / COLON SIGN
					case 0x10020a2: ks = 0x20A2; break; // XK_CruzeiroSign / CRUZEIRO SIGN
					case 0x10020a3: ks = 0x20A3; break; // XK_FFrancSign / FRENCH FRANC SIGN
					case 0x10020a4: ks = 0x20A4; break; // XK_LiraSign / LIRA SIGN
					case 0x10020a5: ks = 0x20A5; break; // XK_MillSign / MILL SIGN
					case 0x10020a6: ks = 0x20A6; break; // XK_NairaSign / NAIRA SIGN
					case 0x10020a7: ks = 0x20A7; break; // XK_PesetaSign / PESETA SIGN
					case 0x10020a8: ks = 0x20A8; break; // XK_RupeeSign / RUPEE SIGN
					case 0x10020a9: ks = 0x20A9; break; // XK_WonSign / WON SIGN
					case 0x10020aa: ks = 0x20AA; break; // XK_NewSheqelSign / NEW SHEQEL SIGN
					case 0x10020ab: ks = 0x20AB; break; // XK_DongSign / DONG SIGN
					case 0x20ac: ks = 0x20AC; break; // XK_EuroSign / EURO SIGN
					case 0x1002070: ks = 0x2070; break; // XK_zerosuperior / SUPERSCRIPT ZERO
					case 0x1002074: ks = 0x2074; break; // XK_foursuperior / SUPERSCRIPT FOUR
					case 0x1002075: ks = 0x2075; break; // XK_fivesuperior / SUPERSCRIPT FIVE
					case 0x1002076: ks = 0x2076; break; // XK_sixsuperior / SUPERSCRIPT SIX
					case 0x1002077: ks = 0x2077; break; // XK_sevensuperior / SUPERSCRIPT SEVEN
					case 0x1002078: ks = 0x2078; break; // XK_eightsuperior / SUPERSCRIPT EIGHT
					case 0x1002079: ks = 0x2079; break; // XK_ninesuperior / SUPERSCRIPT NINE
					case 0x1002080: ks = 0x2080; break; // XK_zerosubscript / SUBSCRIPT ZERO
					case 0x1002081: ks = 0x2081; break; // XK_onesubscript / SUBSCRIPT ONE
					case 0x1002082: ks = 0x2082; break; // XK_twosubscript / SUBSCRIPT TWO
					case 0x1002083: ks = 0x2083; break; // XK_threesubscript / SUBSCRIPT THREE
					case 0x1002084: ks = 0x2084; break; // XK_foursubscript / SUBSCRIPT FOUR
					case 0x1002085: ks = 0x2085; break; // XK_fivesubscript / SUBSCRIPT FIVE
					case 0x1002086: ks = 0x2086; break; // XK_sixsubscript / SUBSCRIPT SIX
					case 0x1002087: ks = 0x2087; break; // XK_sevensubscript / SUBSCRIPT SEVEN
					case 0x1002088: ks = 0x2088; break; // XK_eightsubscript / SUBSCRIPT EIGHT
					case 0x1002089: ks = 0x2089; break; // XK_ninesubscript / SUBSCRIPT NINE
					case 0x1002202: ks = 0x2202; break; // XK_partdifferential / PARTIAL DIFFERENTIAL
					case 0x1002205: ks = 0x2205; break; // XK_emptyset / NULL SET
					case 0x1002208: ks = 0x2208; break; // XK_elementof / ELEMENT OF
					case 0x1002209: ks = 0x2209; break; // XK_notelementof / NOT AN ELEMENT OF
					case 0x100220b: ks = 0x220B; break; // XK_containsas / CONTAINS AS MEMBER
					case 0x100221a: ks = 0x221A; break; // XK_squareroot / SQUARE ROOT
					case 0x100221b: ks = 0x221B; break; // XK_cuberoot / CUBE ROOT
					case 0x100221c: ks = 0x221C; break; // XK_fourthroot / FOURTH ROOT
					case 0x100222c: ks = 0x222C; break; // XK_dintegral / DOUBLE INTEGRAL
					case 0x100222d: ks = 0x222D; break; // XK_tintegral / TRIPLE INTEGRAL
					case 0x1002235: ks = 0x2235; break; // XK_because / BECAUSE
					case 0x1002248: ks = 0x2248; break; // XK_approxeq / ALMOST EQUAL TO)
					case 0x1002247: ks = 0x2247; break; // XK_notapproxeq / NEITHER APPROXIMATELY NOR ACTUALLY EQUAL TO)
					case 0x1002262: ks = 0x2262; break; // XK_notidentical / NOT IDENTICAL TO
					case 0x1002263: ks = 0x2263; break; // XK_stricteq / STRICTLY EQUIVALENT TO
					case 0x1002800: ks = 0x2800; break; // XK_braille_blank / BRAILLE PATTERN BLANK
					case 0x1002801: ks = 0x2801; break; // XK_braille_dots_1 / BRAILLE PATTERN DOTS-1
					case 0x1002802: ks = 0x2802; break; // XK_braille_dots_2 / BRAILLE PATTERN DOTS-2
					case 0x1002803: ks = 0x2803; break; // XK_braille_dots_12 / BRAILLE PATTERN DOTS-12
					case 0x1002804: ks = 0x2804; break; // XK_braille_dots_3 / BRAILLE PATTERN DOTS-3
					case 0x1002805: ks = 0x2805; break; // XK_braille_dots_13 / BRAILLE PATTERN DOTS-13
					case 0x1002806: ks = 0x2806; break; // XK_braille_dots_23 / BRAILLE PATTERN DOTS-23
					case 0x1002807: ks = 0x2807; break; // XK_braille_dots_123 / BRAILLE PATTERN DOTS-123
					case 0x1002808: ks = 0x2808; break; // XK_braille_dots_4 / BRAILLE PATTERN DOTS-4
					case 0x1002809: ks = 0x2809; break; // XK_braille_dots_14 / BRAILLE PATTERN DOTS-14
					case 0x100280a: ks = 0x280a; break; // XK_braille_dots_24 / BRAILLE PATTERN DOTS-24
					case 0x100280b: ks = 0x280b; break; // XK_braille_dots_124 / BRAILLE PATTERN DOTS-124
					case 0x100280c: ks = 0x280c; break; // XK_braille_dots_34 / BRAILLE PATTERN DOTS-34
					case 0x100280d: ks = 0x280d; break; // XK_braille_dots_134 / BRAILLE PATTERN DOTS-134
					case 0x100280e: ks = 0x280e; break; // XK_braille_dots_234 / BRAILLE PATTERN DOTS-234
					case 0x100280f: ks = 0x280f; break; // XK_braille_dots_1234 / BRAILLE PATTERN DOTS-1234
					case 0x1002810: ks = 0x2810; break; // XK_braille_dots_5 / BRAILLE PATTERN DOTS-5
					case 0x1002811: ks = 0x2811; break; // XK_braille_dots_15 / BRAILLE PATTERN DOTS-15
					case 0x1002812: ks = 0x2812; break; // XK_braille_dots_25 / BRAILLE PATTERN DOTS-25
					case 0x1002813: ks = 0x2813; break; // XK_braille_dots_125 / BRAILLE PATTERN DOTS-125
					case 0x1002814: ks = 0x2814; break; // XK_braille_dots_35 / BRAILLE PATTERN DOTS-35
					case 0x1002815: ks = 0x2815; break; // XK_braille_dots_135 / BRAILLE PATTERN DOTS-135
					case 0x1002816: ks = 0x2816; break; // XK_braille_dots_235 / BRAILLE PATTERN DOTS-235
					case 0x1002817: ks = 0x2817; break; // XK_braille_dots_1235 / BRAILLE PATTERN DOTS-1235
					case 0x1002818: ks = 0x2818; break; // XK_braille_dots_45 / BRAILLE PATTERN DOTS-45
					case 0x1002819: ks = 0x2819; break; // XK_braille_dots_145 / BRAILLE PATTERN DOTS-145
					case 0x100281a: ks = 0x281a; break; // XK_braille_dots_245 / BRAILLE PATTERN DOTS-245
					case 0x100281b: ks = 0x281b; break; // XK_braille_dots_1245 / BRAILLE PATTERN DOTS-1245
					case 0x100281c: ks = 0x281c; break; // XK_braille_dots_345 / BRAILLE PATTERN DOTS-345
					case 0x100281d: ks = 0x281d; break; // XK_braille_dots_1345 / BRAILLE PATTERN DOTS-1345
					case 0x100281e: ks = 0x281e; break; // XK_braille_dots_2345 / BRAILLE PATTERN DOTS-2345
					case 0x100281f: ks = 0x281f; break; // XK_braille_dots_12345 / BRAILLE PATTERN DOTS-12345
					case 0x1002820: ks = 0x2820; break; // XK_braille_dots_6 / BRAILLE PATTERN DOTS-6
					case 0x1002821: ks = 0x2821; break; // XK_braille_dots_16 / BRAILLE PATTERN DOTS-16
					case 0x1002822: ks = 0x2822; break; // XK_braille_dots_26 / BRAILLE PATTERN DOTS-26
					case 0x1002823: ks = 0x2823; break; // XK_braille_dots_126 / BRAILLE PATTERN DOTS-126
					case 0x1002824: ks = 0x2824; break; // XK_braille_dots_36 / BRAILLE PATTERN DOTS-36
					case 0x1002825: ks = 0x2825; break; // XK_braille_dots_136 / BRAILLE PATTERN DOTS-136
					case 0x1002826: ks = 0x2826; break; // XK_braille_dots_236 / BRAILLE PATTERN DOTS-236
					case 0x1002827: ks = 0x2827; break; // XK_braille_dots_1236 / BRAILLE PATTERN DOTS-1236
					case 0x1002828: ks = 0x2828; break; // XK_braille_dots_46 / BRAILLE PATTERN DOTS-46
					case 0x1002829: ks = 0x2829; break; // XK_braille_dots_146 / BRAILLE PATTERN DOTS-146
					case 0x100282a: ks = 0x282a; break; // XK_braille_dots_246 / BRAILLE PATTERN DOTS-246
					case 0x100282b: ks = 0x282b; break; // XK_braille_dots_1246 / BRAILLE PATTERN DOTS-1246
					case 0x100282c: ks = 0x282c; break; // XK_braille_dots_346 / BRAILLE PATTERN DOTS-346
					case 0x100282d: ks = 0x282d; break; // XK_braille_dots_1346 / BRAILLE PATTERN DOTS-1346
					case 0x100282e: ks = 0x282e; break; // XK_braille_dots_2346 / BRAILLE PATTERN DOTS-2346
					case 0x100282f: ks = 0x282f; break; // XK_braille_dots_12346 / BRAILLE PATTERN DOTS-12346
					case 0x1002830: ks = 0x2830; break; // XK_braille_dots_56 / BRAILLE PATTERN DOTS-56
					case 0x1002831: ks = 0x2831; break; // XK_braille_dots_156 / BRAILLE PATTERN DOTS-156
					case 0x1002832: ks = 0x2832; break; // XK_braille_dots_256 / BRAILLE PATTERN DOTS-256
					case 0x1002833: ks = 0x2833; break; // XK_braille_dots_1256 / BRAILLE PATTERN DOTS-1256
					case 0x1002834: ks = 0x2834; break; // XK_braille_dots_356 / BRAILLE PATTERN DOTS-356
					case 0x1002835: ks = 0x2835; break; // XK_braille_dots_1356 / BRAILLE PATTERN DOTS-1356
					case 0x1002836: ks = 0x2836; break; // XK_braille_dots_2356 / BRAILLE PATTERN DOTS-2356
					case 0x1002837: ks = 0x2837; break; // XK_braille_dots_12356 / BRAILLE PATTERN DOTS-12356
					case 0x1002838: ks = 0x2838; break; // XK_braille_dots_456 / BRAILLE PATTERN DOTS-456
					case 0x1002839: ks = 0x2839; break; // XK_braille_dots_1456 / BRAILLE PATTERN DOTS-1456
					case 0x100283a: ks = 0x283a; break; // XK_braille_dots_2456 / BRAILLE PATTERN DOTS-2456
					case 0x100283b: ks = 0x283b; break; // XK_braille_dots_12456 / BRAILLE PATTERN DOTS-12456
					case 0x100283c: ks = 0x283c; break; // XK_braille_dots_3456 / BRAILLE PATTERN DOTS-3456
					case 0x100283d: ks = 0x283d; break; // XK_braille_dots_13456 / BRAILLE PATTERN DOTS-13456
					case 0x100283e: ks = 0x283e; break; // XK_braille_dots_23456 / BRAILLE PATTERN DOTS-23456
					case 0x100283f: ks = 0x283f; break; // XK_braille_dots_123456 / BRAILLE PATTERN DOTS-123456
					case 0x1002840: ks = 0x2840; break; // XK_braille_dots_7 / BRAILLE PATTERN DOTS-7
					case 0x1002841: ks = 0x2841; break; // XK_braille_dots_17 / BRAILLE PATTERN DOTS-17
					case 0x1002842: ks = 0x2842; break; // XK_braille_dots_27 / BRAILLE PATTERN DOTS-27
					case 0x1002843: ks = 0x2843; break; // XK_braille_dots_127 / BRAILLE PATTERN DOTS-127
					case 0x1002844: ks = 0x2844; break; // XK_braille_dots_37 / BRAILLE PATTERN DOTS-37
					case 0x1002845: ks = 0x2845; break; // XK_braille_dots_137 / BRAILLE PATTERN DOTS-137
					case 0x1002846: ks = 0x2846; break; // XK_braille_dots_237 / BRAILLE PATTERN DOTS-237
					case 0x1002847: ks = 0x2847; break; // XK_braille_dots_1237 / BRAILLE PATTERN DOTS-1237
					case 0x1002848: ks = 0x2848; break; // XK_braille_dots_47 / BRAILLE PATTERN DOTS-47
					case 0x1002849: ks = 0x2849; break; // XK_braille_dots_147 / BRAILLE PATTERN DOTS-147
					case 0x100284a: ks = 0x284a; break; // XK_braille_dots_247 / BRAILLE PATTERN DOTS-247
					case 0x100284b: ks = 0x284b; break; // XK_braille_dots_1247 / BRAILLE PATTERN DOTS-1247
					case 0x100284c: ks = 0x284c; break; // XK_braille_dots_347 / BRAILLE PATTERN DOTS-347
					case 0x100284d: ks = 0x284d; break; // XK_braille_dots_1347 / BRAILLE PATTERN DOTS-1347
					case 0x100284e: ks = 0x284e; break; // XK_braille_dots_2347 / BRAILLE PATTERN DOTS-2347
					case 0x100284f: ks = 0x284f; break; // XK_braille_dots_12347 / BRAILLE PATTERN DOTS-12347
					case 0x1002850: ks = 0x2850; break; // XK_braille_dots_57 / BRAILLE PATTERN DOTS-57
					case 0x1002851: ks = 0x2851; break; // XK_braille_dots_157 / BRAILLE PATTERN DOTS-157
					case 0x1002852: ks = 0x2852; break; // XK_braille_dots_257 / BRAILLE PATTERN DOTS-257
					case 0x1002853: ks = 0x2853; break; // XK_braille_dots_1257 / BRAILLE PATTERN DOTS-1257
					case 0x1002854: ks = 0x2854; break; // XK_braille_dots_357 / BRAILLE PATTERN DOTS-357
					case 0x1002855: ks = 0x2855; break; // XK_braille_dots_1357 / BRAILLE PATTERN DOTS-1357
					case 0x1002856: ks = 0x2856; break; // XK_braille_dots_2357 / BRAILLE PATTERN DOTS-2357
					case 0x1002857: ks = 0x2857; break; // XK_braille_dots_12357 / BRAILLE PATTERN DOTS-12357
					case 0x1002858: ks = 0x2858; break; // XK_braille_dots_457 / BRAILLE PATTERN DOTS-457
					case 0x1002859: ks = 0x2859; break; // XK_braille_dots_1457 / BRAILLE PATTERN DOTS-1457
					case 0x100285a: ks = 0x285a; break; // XK_braille_dots_2457 / BRAILLE PATTERN DOTS-2457
					case 0x100285b: ks = 0x285b; break; // XK_braille_dots_12457 / BRAILLE PATTERN DOTS-12457
					case 0x100285c: ks = 0x285c; break; // XK_braille_dots_3457 / BRAILLE PATTERN DOTS-3457
					case 0x100285d: ks = 0x285d; break; // XK_braille_dots_13457 / BRAILLE PATTERN DOTS-13457
					case 0x100285e: ks = 0x285e; break; // XK_braille_dots_23457 / BRAILLE PATTERN DOTS-23457
					case 0x100285f: ks = 0x285f; break; // XK_braille_dots_123457 / BRAILLE PATTERN DOTS-123457
					case 0x1002860: ks = 0x2860; break; // XK_braille_dots_67 / BRAILLE PATTERN DOTS-67
					case 0x1002861: ks = 0x2861; break; // XK_braille_dots_167 / BRAILLE PATTERN DOTS-167
					case 0x1002862: ks = 0x2862; break; // XK_braille_dots_267 / BRAILLE PATTERN DOTS-267
					case 0x1002863: ks = 0x2863; break; // XK_braille_dots_1267 / BRAILLE PATTERN DOTS-1267
					case 0x1002864: ks = 0x2864; break; // XK_braille_dots_367 / BRAILLE PATTERN DOTS-367
					case 0x1002865: ks = 0x2865; break; // XK_braille_dots_1367 / BRAILLE PATTERN DOTS-1367
					case 0x1002866: ks = 0x2866; break; // XK_braille_dots_2367 / BRAILLE PATTERN DOTS-2367
					case 0x1002867: ks = 0x2867; break; // XK_braille_dots_12367 / BRAILLE PATTERN DOTS-12367
					case 0x1002868: ks = 0x2868; break; // XK_braille_dots_467 / BRAILLE PATTERN DOTS-467
					case 0x1002869: ks = 0x2869; break; // XK_braille_dots_1467 / BRAILLE PATTERN DOTS-1467
					case 0x100286a: ks = 0x286a; break; // XK_braille_dots_2467 / BRAILLE PATTERN DOTS-2467
					case 0x100286b: ks = 0x286b; break; // XK_braille_dots_12467 / BRAILLE PATTERN DOTS-12467
					case 0x100286c: ks = 0x286c; break; // XK_braille_dots_3467 / BRAILLE PATTERN DOTS-3467
					case 0x100286d: ks = 0x286d; break; // XK_braille_dots_13467 / BRAILLE PATTERN DOTS-13467
					case 0x100286e: ks = 0x286e; break; // XK_braille_dots_23467 / BRAILLE PATTERN DOTS-23467
					case 0x100286f: ks = 0x286f; break; // XK_braille_dots_123467 / BRAILLE PATTERN DOTS-123467
					case 0x1002870: ks = 0x2870; break; // XK_braille_dots_567 / BRAILLE PATTERN DOTS-567
					case 0x1002871: ks = 0x2871; break; // XK_braille_dots_1567 / BRAILLE PATTERN DOTS-1567
					case 0x1002872: ks = 0x2872; break; // XK_braille_dots_2567 / BRAILLE PATTERN DOTS-2567
					case 0x1002873: ks = 0x2873; break; // XK_braille_dots_12567 / BRAILLE PATTERN DOTS-12567
					case 0x1002874: ks = 0x2874; break; // XK_braille_dots_3567 / BRAILLE PATTERN DOTS-3567
					case 0x1002875: ks = 0x2875; break; // XK_braille_dots_13567 / BRAILLE PATTERN DOTS-13567
					case 0x1002876: ks = 0x2876; break; // XK_braille_dots_23567 / BRAILLE PATTERN DOTS-23567
					case 0x1002877: ks = 0x2877; break; // XK_braille_dots_123567 / BRAILLE PATTERN DOTS-123567
					case 0x1002878: ks = 0x2878; break; // XK_braille_dots_4567 / BRAILLE PATTERN DOTS-4567
					case 0x1002879: ks = 0x2879; break; // XK_braille_dots_14567 / BRAILLE PATTERN DOTS-14567
					case 0x100287a: ks = 0x287a; break; // XK_braille_dots_24567 / BRAILLE PATTERN DOTS-24567
					case 0x100287b: ks = 0x287b; break; // XK_braille_dots_124567 / BRAILLE PATTERN DOTS-124567
					case 0x100287c: ks = 0x287c; break; // XK_braille_dots_34567 / BRAILLE PATTERN DOTS-34567
					case 0x100287d: ks = 0x287d; break; // XK_braille_dots_134567 / BRAILLE PATTERN DOTS-134567
					case 0x100287e: ks = 0x287e; break; // XK_braille_dots_234567 / BRAILLE PATTERN DOTS-234567
					case 0x100287f: ks = 0x287f; break; // XK_braille_dots_1234567 / BRAILLE PATTERN DOTS-1234567
					case 0x1002880: ks = 0x2880; break; // XK_braille_dots_8 / BRAILLE PATTERN DOTS-8
					case 0x1002881: ks = 0x2881; break; // XK_braille_dots_18 / BRAILLE PATTERN DOTS-18
					case 0x1002882: ks = 0x2882; break; // XK_braille_dots_28 / BRAILLE PATTERN DOTS-28
					case 0x1002883: ks = 0x2883; break; // XK_braille_dots_128 / BRAILLE PATTERN DOTS-128
					case 0x1002884: ks = 0x2884; break; // XK_braille_dots_38 / BRAILLE PATTERN DOTS-38
					case 0x1002885: ks = 0x2885; break; // XK_braille_dots_138 / BRAILLE PATTERN DOTS-138
					case 0x1002886: ks = 0x2886; break; // XK_braille_dots_238 / BRAILLE PATTERN DOTS-238
					case 0x1002887: ks = 0x2887; break; // XK_braille_dots_1238 / BRAILLE PATTERN DOTS-1238
					case 0x1002888: ks = 0x2888; break; // XK_braille_dots_48 / BRAILLE PATTERN DOTS-48
					case 0x1002889: ks = 0x2889; break; // XK_braille_dots_148 / BRAILLE PATTERN DOTS-148
					case 0x100288a: ks = 0x288a; break; // XK_braille_dots_248 / BRAILLE PATTERN DOTS-248
					case 0x100288b: ks = 0x288b; break; // XK_braille_dots_1248 / BRAILLE PATTERN DOTS-1248
					case 0x100288c: ks = 0x288c; break; // XK_braille_dots_348 / BRAILLE PATTERN DOTS-348
					case 0x100288d: ks = 0x288d; break; // XK_braille_dots_1348 / BRAILLE PATTERN DOTS-1348
					case 0x100288e: ks = 0x288e; break; // XK_braille_dots_2348 / BRAILLE PATTERN DOTS-2348
					case 0x100288f: ks = 0x288f; break; // XK_braille_dots_12348 / BRAILLE PATTERN DOTS-12348
					case 0x1002890: ks = 0x2890; break; // XK_braille_dots_58 / BRAILLE PATTERN DOTS-58
					case 0x1002891: ks = 0x2891; break; // XK_braille_dots_158 / BRAILLE PATTERN DOTS-158
					case 0x1002892: ks = 0x2892; break; // XK_braille_dots_258 / BRAILLE PATTERN DOTS-258
					case 0x1002893: ks = 0x2893; break; // XK_braille_dots_1258 / BRAILLE PATTERN DOTS-1258
					case 0x1002894: ks = 0x2894; break; // XK_braille_dots_358 / BRAILLE PATTERN DOTS-358
					case 0x1002895: ks = 0x2895; break; // XK_braille_dots_1358 / BRAILLE PATTERN DOTS-1358
					case 0x1002896: ks = 0x2896; break; // XK_braille_dots_2358 / BRAILLE PATTERN DOTS-2358
					case 0x1002897: ks = 0x2897; break; // XK_braille_dots_12358 / BRAILLE PATTERN DOTS-12358
					case 0x1002898: ks = 0x2898; break; // XK_braille_dots_458 / BRAILLE PATTERN DOTS-458
					case 0x1002899: ks = 0x2899; break; // XK_braille_dots_1458 / BRAILLE PATTERN DOTS-1458
					case 0x100289a: ks = 0x289a; break; // XK_braille_dots_2458 / BRAILLE PATTERN DOTS-2458
					case 0x100289b: ks = 0x289b; break; // XK_braille_dots_12458 / BRAILLE PATTERN DOTS-12458
					case 0x100289c: ks = 0x289c; break; // XK_braille_dots_3458 / BRAILLE PATTERN DOTS-3458
					case 0x100289d: ks = 0x289d; break; // XK_braille_dots_13458 / BRAILLE PATTERN DOTS-13458
					case 0x100289e: ks = 0x289e; break; // XK_braille_dots_23458 / BRAILLE PATTERN DOTS-23458
					case 0x100289f: ks = 0x289f; break; // XK_braille_dots_123458 / BRAILLE PATTERN DOTS-123458
					case 0x10028a0: ks = 0x28a0; break; // XK_braille_dots_68 / BRAILLE PATTERN DOTS-68
					case 0x10028a1: ks = 0x28a1; break; // XK_braille_dots_168 / BRAILLE PATTERN DOTS-168
					case 0x10028a2: ks = 0x28a2; break; // XK_braille_dots_268 / BRAILLE PATTERN DOTS-268
					case 0x10028a3: ks = 0x28a3; break; // XK_braille_dots_1268 / BRAILLE PATTERN DOTS-1268
					case 0x10028a4: ks = 0x28a4; break; // XK_braille_dots_368 / BRAILLE PATTERN DOTS-368
					case 0x10028a5: ks = 0x28a5; break; // XK_braille_dots_1368 / BRAILLE PATTERN DOTS-1368
					case 0x10028a6: ks = 0x28a6; break; // XK_braille_dots_2368 / BRAILLE PATTERN DOTS-2368
					case 0x10028a7: ks = 0x28a7; break; // XK_braille_dots_12368 / BRAILLE PATTERN DOTS-12368
					case 0x10028a8: ks = 0x28a8; break; // XK_braille_dots_468 / BRAILLE PATTERN DOTS-468
					case 0x10028a9: ks = 0x28a9; break; // XK_braille_dots_1468 / BRAILLE PATTERN DOTS-1468
					case 0x10028aa: ks = 0x28aa; break; // XK_braille_dots_2468 / BRAILLE PATTERN DOTS-2468
					case 0x10028ab: ks = 0x28ab; break; // XK_braille_dots_12468 / BRAILLE PATTERN DOTS-12468
					case 0x10028ac: ks = 0x28ac; break; // XK_braille_dots_3468 / BRAILLE PATTERN DOTS-3468
					case 0x10028ad: ks = 0x28ad; break; // XK_braille_dots_13468 / BRAILLE PATTERN DOTS-13468
					case 0x10028ae: ks = 0x28ae; break; // XK_braille_dots_23468 / BRAILLE PATTERN DOTS-23468
					case 0x10028af: ks = 0x28af; break; // XK_braille_dots_123468 / BRAILLE PATTERN DOTS-123468
					case 0x10028b0: ks = 0x28b0; break; // XK_braille_dots_568 / BRAILLE PATTERN DOTS-568
					case 0x10028b1: ks = 0x28b1; break; // XK_braille_dots_1568 / BRAILLE PATTERN DOTS-1568
					case 0x10028b2: ks = 0x28b2; break; // XK_braille_dots_2568 / BRAILLE PATTERN DOTS-2568
					case 0x10028b3: ks = 0x28b3; break; // XK_braille_dots_12568 / BRAILLE PATTERN DOTS-12568
					case 0x10028b4: ks = 0x28b4; break; // XK_braille_dots_3568 / BRAILLE PATTERN DOTS-3568
					case 0x10028b5: ks = 0x28b5; break; // XK_braille_dots_13568 / BRAILLE PATTERN DOTS-13568
					case 0x10028b6: ks = 0x28b6; break; // XK_braille_dots_23568 / BRAILLE PATTERN DOTS-23568
					case 0x10028b7: ks = 0x28b7; break; // XK_braille_dots_123568 / BRAILLE PATTERN DOTS-123568
					case 0x10028b8: ks = 0x28b8; break; // XK_braille_dots_4568 / BRAILLE PATTERN DOTS-4568
					case 0x10028b9: ks = 0x28b9; break; // XK_braille_dots_14568 / BRAILLE PATTERN DOTS-14568
					case 0x10028ba: ks = 0x28ba; break; // XK_braille_dots_24568 / BRAILLE PATTERN DOTS-24568
					case 0x10028bb: ks = 0x28bb; break; // XK_braille_dots_124568 / BRAILLE PATTERN DOTS-124568
					case 0x10028bc: ks = 0x28bc; break; // XK_braille_dots_34568 / BRAILLE PATTERN DOTS-34568
					case 0x10028bd: ks = 0x28bd; break; // XK_braille_dots_134568 / BRAILLE PATTERN DOTS-134568
					case 0x10028be: ks = 0x28be; break; // XK_braille_dots_234568 / BRAILLE PATTERN DOTS-234568
					case 0x10028bf: ks = 0x28bf; break; // XK_braille_dots_1234568 / BRAILLE PATTERN DOTS-1234568
					case 0x10028c0: ks = 0x28c0; break; // XK_braille_dots_78 / BRAILLE PATTERN DOTS-78
					case 0x10028c1: ks = 0x28c1; break; // XK_braille_dots_178 / BRAILLE PATTERN DOTS-178
					case 0x10028c2: ks = 0x28c2; break; // XK_braille_dots_278 / BRAILLE PATTERN DOTS-278
					case 0x10028c3: ks = 0x28c3; break; // XK_braille_dots_1278 / BRAILLE PATTERN DOTS-1278
					case 0x10028c4: ks = 0x28c4; break; // XK_braille_dots_378 / BRAILLE PATTERN DOTS-378
					case 0x10028c5: ks = 0x28c5; break; // XK_braille_dots_1378 / BRAILLE PATTERN DOTS-1378
					case 0x10028c6: ks = 0x28c6; break; // XK_braille_dots_2378 / BRAILLE PATTERN DOTS-2378
					case 0x10028c7: ks = 0x28c7; break; // XK_braille_dots_12378 / BRAILLE PATTERN DOTS-12378
					case 0x10028c8: ks = 0x28c8; break; // XK_braille_dots_478 / BRAILLE PATTERN DOTS-478
					case 0x10028c9: ks = 0x28c9; break; // XK_braille_dots_1478 / BRAILLE PATTERN DOTS-1478
					case 0x10028ca: ks = 0x28ca; break; // XK_braille_dots_2478 / BRAILLE PATTERN DOTS-2478
					case 0x10028cb: ks = 0x28cb; break; // XK_braille_dots_12478 / BRAILLE PATTERN DOTS-12478
					case 0x10028cc: ks = 0x28cc; break; // XK_braille_dots_3478 / BRAILLE PATTERN DOTS-3478
					case 0x10028cd: ks = 0x28cd; break; // XK_braille_dots_13478 / BRAILLE PATTERN DOTS-13478
					case 0x10028ce: ks = 0x28ce; break; // XK_braille_dots_23478 / BRAILLE PATTERN DOTS-23478
					case 0x10028cf: ks = 0x28cf; break; // XK_braille_dots_123478 / BRAILLE PATTERN DOTS-123478
					case 0x10028d0: ks = 0x28d0; break; // XK_braille_dots_578 / BRAILLE PATTERN DOTS-578
					case 0x10028d1: ks = 0x28d1; break; // XK_braille_dots_1578 / BRAILLE PATTERN DOTS-1578
					case 0x10028d2: ks = 0x28d2; break; // XK_braille_dots_2578 / BRAILLE PATTERN DOTS-2578
					case 0x10028d3: ks = 0x28d3; break; // XK_braille_dots_12578 / BRAILLE PATTERN DOTS-12578
					case 0x10028d4: ks = 0x28d4; break; // XK_braille_dots_3578 / BRAILLE PATTERN DOTS-3578
					case 0x10028d5: ks = 0x28d5; break; // XK_braille_dots_13578 / BRAILLE PATTERN DOTS-13578
					case 0x10028d6: ks = 0x28d6; break; // XK_braille_dots_23578 / BRAILLE PATTERN DOTS-23578
					case 0x10028d7: ks = 0x28d7; break; // XK_braille_dots_123578 / BRAILLE PATTERN DOTS-123578
					case 0x10028d8: ks = 0x28d8; break; // XK_braille_dots_4578 / BRAILLE PATTERN DOTS-4578
					case 0x10028d9: ks = 0x28d9; break; // XK_braille_dots_14578 / BRAILLE PATTERN DOTS-14578
					case 0x10028da: ks = 0x28da; break; // XK_braille_dots_24578 / BRAILLE PATTERN DOTS-24578
					case 0x10028db: ks = 0x28db; break; // XK_braille_dots_124578 / BRAILLE PATTERN DOTS-124578
					case 0x10028dc: ks = 0x28dc; break; // XK_braille_dots_34578 / BRAILLE PATTERN DOTS-34578
					case 0x10028dd: ks = 0x28dd; break; // XK_braille_dots_134578 / BRAILLE PATTERN DOTS-134578
					case 0x10028de: ks = 0x28de; break; // XK_braille_dots_234578 / BRAILLE PATTERN DOTS-234578
					case 0x10028df: ks = 0x28df; break; // XK_braille_dots_1234578 / BRAILLE PATTERN DOTS-1234578
					case 0x10028e0: ks = 0x28e0; break; // XK_braille_dots_678 / BRAILLE PATTERN DOTS-678
					case 0x10028e1: ks = 0x28e1; break; // XK_braille_dots_1678 / BRAILLE PATTERN DOTS-1678
					case 0x10028e2: ks = 0x28e2; break; // XK_braille_dots_2678 / BRAILLE PATTERN DOTS-2678
					case 0x10028e3: ks = 0x28e3; break; // XK_braille_dots_12678 / BRAILLE PATTERN DOTS-12678
					case 0x10028e4: ks = 0x28e4; break; // XK_braille_dots_3678 / BRAILLE PATTERN DOTS-3678
					case 0x10028e5: ks = 0x28e5; break; // XK_braille_dots_13678 / BRAILLE PATTERN DOTS-13678
					case 0x10028e6: ks = 0x28e6; break; // XK_braille_dots_23678 / BRAILLE PATTERN DOTS-23678
					case 0x10028e7: ks = 0x28e7; break; // XK_braille_dots_123678 / BRAILLE PATTERN DOTS-123678
					case 0x10028e8: ks = 0x28e8; break; // XK_braille_dots_4678 / BRAILLE PATTERN DOTS-4678
					case 0x10028e9: ks = 0x28e9; break; // XK_braille_dots_14678 / BRAILLE PATTERN DOTS-14678
					case 0x10028ea: ks = 0x28ea; break; // XK_braille_dots_24678 / BRAILLE PATTERN DOTS-24678
					case 0x10028eb: ks = 0x28eb; break; // XK_braille_dots_124678 / BRAILLE PATTERN DOTS-124678
					case 0x10028ec: ks = 0x28ec; break; // XK_braille_dots_34678 / BRAILLE PATTERN DOTS-34678
					case 0x10028ed: ks = 0x28ed; break; // XK_braille_dots_134678 / BRAILLE PATTERN DOTS-134678
					case 0x10028ee: ks = 0x28ee; break; // XK_braille_dots_234678 / BRAILLE PATTERN DOTS-234678
					case 0x10028ef: ks = 0x28ef; break; // XK_braille_dots_1234678 / BRAILLE PATTERN DOTS-1234678
					case 0x10028f0: ks = 0x28f0; break; // XK_braille_dots_5678 / BRAILLE PATTERN DOTS-5678
					case 0x10028f1: ks = 0x28f1; break; // XK_braille_dots_15678 / BRAILLE PATTERN DOTS-15678
					case 0x10028f2: ks = 0x28f2; break; // XK_braille_dots_25678 / BRAILLE PATTERN DOTS-25678
					case 0x10028f3: ks = 0x28f3; break; // XK_braille_dots_125678 / BRAILLE PATTERN DOTS-125678
					case 0x10028f4: ks = 0x28f4; break; // XK_braille_dots_35678 / BRAILLE PATTERN DOTS-35678
					case 0x10028f5: ks = 0x28f5; break; // XK_braille_dots_135678 / BRAILLE PATTERN DOTS-135678
					case 0x10028f6: ks = 0x28f6; break; // XK_braille_dots_235678 / BRAILLE PATTERN DOTS-235678
					case 0x10028f7: ks = 0x28f7; break; // XK_braille_dots_1235678 / BRAILLE PATTERN DOTS-1235678
					case 0x10028f8: ks = 0x28f8; break; // XK_braille_dots_45678 / BRAILLE PATTERN DOTS-45678
					case 0x10028f9: ks = 0x28f9; break; // XK_braille_dots_145678 / BRAILLE PATTERN DOTS-145678
					case 0x10028fa: ks = 0x28fa; break; // XK_braille_dots_245678 / BRAILLE PATTERN DOTS-245678
					case 0x10028fb: ks = 0x28fb; break; // XK_braille_dots_1245678 / BRAILLE PATTERN DOTS-1245678
					case 0x10028fc: ks = 0x28fc; break; // XK_braille_dots_345678 / BRAILLE PATTERN DOTS-345678
					case 0x10028fd: ks = 0x28fd; break; // XK_braille_dots_1345678 / BRAILLE PATTERN DOTS-1345678
					case 0x10028fe: ks = 0x28fe; break; // XK_braille_dots_2345678 / BRAILLE PATTERN DOTS-2345678
					case 0x10028ff: ks = 0x28ff; break; // XK_braille_dots_12345678 / BRAILLE PATTERN DOTS-12345678
					case 0x1000d82: ks = 0x0D82; break; // XK_Sinh_ng / SINHALA ANUSVARAYA
					case 0x1000d83: ks = 0x0D83; break; // XK_Sinh_h2 / SINHALA VISARGAYA
					case 0x1000d85: ks = 0x0D85; break; // XK_Sinh_a / SINHALA AYANNA
					case 0x1000d86: ks = 0x0D86; break; // XK_Sinh_aa / SINHALA AAYANNA
					case 0x1000d87: ks = 0x0D87; break; // XK_Sinh_ae / SINHALA AEYANNA
					case 0x1000d88: ks = 0x0D88; break; // XK_Sinh_aee / SINHALA AEEYANNA
					case 0x1000d89: ks = 0x0D89; break; // XK_Sinh_i / SINHALA IYANNA
					case 0x1000d8a: ks = 0x0D8A; break; // XK_Sinh_ii / SINHALA IIYANNA
					case 0x1000d8b: ks = 0x0D8B; break; // XK_Sinh_u / SINHALA UYANNA
					case 0x1000d8c: ks = 0x0D8C; break; // XK_Sinh_uu / SINHALA UUYANNA
					case 0x1000d8d: ks = 0x0D8D; break; // XK_Sinh_ri / SINHALA IRUYANNA
					case 0x1000d8e: ks = 0x0D8E; break; // XK_Sinh_rii / SINHALA IRUUYANNA
					case 0x1000d8f: ks = 0x0D8F; break; // XK_Sinh_lu / SINHALA ILUYANNA
					case 0x1000d90: ks = 0x0D90; break; // XK_Sinh_luu / SINHALA ILUUYANNA
					case 0x1000d91: ks = 0x0D91; break; // XK_Sinh_e / SINHALA EYANNA
					case 0x1000d92: ks = 0x0D92; break; // XK_Sinh_ee / SINHALA EEYANNA
					case 0x1000d93: ks = 0x0D93; break; // XK_Sinh_ai / SINHALA AIYANNA
					case 0x1000d94: ks = 0x0D94; break; // XK_Sinh_o / SINHALA OYANNA
					case 0x1000d95: ks = 0x0D95; break; // XK_Sinh_oo / SINHALA OOYANNA
					case 0x1000d96: ks = 0x0D96; break; // XK_Sinh_au / SINHALA AUYANNA
					case 0x1000d9a: ks = 0x0D9A; break; // XK_Sinh_ka / SINHALA KAYANNA
					case 0x1000d9b: ks = 0x0D9B; break; // XK_Sinh_kha / SINHALA MAHA. KAYANNA
					case 0x1000d9c: ks = 0x0D9C; break; // XK_Sinh_ga / SINHALA GAYANNA
					case 0x1000d9d: ks = 0x0D9D; break; // XK_Sinh_gha / SINHALA MAHA. GAYANNA
					case 0x1000d9e: ks = 0x0D9E; break; // XK_Sinh_ng2 / SINHALA KANTAJA NAASIKYAYA
					case 0x1000d9f: ks = 0x0D9F; break; // XK_Sinh_nga / SINHALA SANYAKA GAYANNA
					case 0x1000da0: ks = 0x0DA0; break; // XK_Sinh_ca / SINHALA CAYANNA
					case 0x1000da1: ks = 0x0DA1; break; // XK_Sinh_cha / SINHALA MAHA. CAYANNA
					case 0x1000da2: ks = 0x0DA2; break; // XK_Sinh_ja / SINHALA JAYANNA
					case 0x1000da3: ks = 0x0DA3; break; // XK_Sinh_jha / SINHALA MAHA. JAYANNA
					case 0x1000da4: ks = 0x0DA4; break; // XK_Sinh_nya / SINHALA TAALUJA NAASIKYAYA
					case 0x1000da5: ks = 0x0DA5; break; // XK_Sinh_jnya / SINHALA TAALUJA SANYOOGA NAASIKYAYA
					case 0x1000da6: ks = 0x0DA6; break; // XK_Sinh_nja / SINHALA SANYAKA JAYANNA
					case 0x1000da7: ks = 0x0DA7; break; // XK_Sinh_tta / SINHALA TTAYANNA
					case 0x1000da8: ks = 0x0DA8; break; // XK_Sinh_ttha / SINHALA MAHA. TTAYANNA
					case 0x1000da9: ks = 0x0DA9; break; // XK_Sinh_dda / SINHALA DDAYANNA
					case 0x1000daa: ks = 0x0DAA; break; // XK_Sinh_ddha / SINHALA MAHA. DDAYANNA
					case 0x1000dab: ks = 0x0DAB; break; // XK_Sinh_nna / SINHALA MUURDHAJA NAYANNA
					case 0x1000dac: ks = 0x0DAC; break; // XK_Sinh_ndda / SINHALA SANYAKA DDAYANNA
					case 0x1000dad: ks = 0x0DAD; break; // XK_Sinh_tha / SINHALA TAYANNA
					case 0x1000dae: ks = 0x0DAE; break; // XK_Sinh_thha / SINHALA MAHA. TAYANNA
					case 0x1000daf: ks = 0x0DAF; break; // XK_Sinh_dha / SINHALA DAYANNA
					case 0x1000db0: ks = 0x0DB0; break; // XK_Sinh_dhha / SINHALA MAHA. DAYANNA
					case 0x1000db1: ks = 0x0DB1; break; // XK_Sinh_na / SINHALA DANTAJA NAYANNA
					case 0x1000db3: ks = 0x0DB3; break; // XK_Sinh_ndha / SINHALA SANYAKA DAYANNA
					case 0x1000db4: ks = 0x0DB4; break; // XK_Sinh_pa / SINHALA PAYANNA
					case 0x1000db5: ks = 0x0DB5; break; // XK_Sinh_pha / SINHALA MAHA. PAYANNA
					case 0x1000db6: ks = 0x0DB6; break; // XK_Sinh_ba / SINHALA BAYANNA
					case 0x1000db7: ks = 0x0DB7; break; // XK_Sinh_bha / SINHALA MAHA. BAYANNA
					case 0x1000db8: ks = 0x0DB8; break; // XK_Sinh_ma / SINHALA MAYANNA
					case 0x1000db9: ks = 0x0DB9; break; // XK_Sinh_mba / SINHALA AMBA BAYANNA
					case 0x1000dba: ks = 0x0DBA; break; // XK_Sinh_ya / SINHALA YAYANNA
					case 0x1000dbb: ks = 0x0DBB; break; // XK_Sinh_ra / SINHALA RAYANNA
					case 0x1000dbd: ks = 0x0DBD; break; // XK_Sinh_la / SINHALA DANTAJA LAYANNA
					case 0x1000dc0: ks = 0x0DC0; break; // XK_Sinh_va / SINHALA VAYANNA
					case 0x1000dc1: ks = 0x0DC1; break; // XK_Sinh_sha / SINHALA TAALUJA SAYANNA
					case 0x1000dc2: ks = 0x0DC2; break; // XK_Sinh_ssha / SINHALA MUURDHAJA SAYANNA
					case 0x1000dc3: ks = 0x0DC3; break; // XK_Sinh_sa / SINHALA DANTAJA SAYANNA
					case 0x1000dc4: ks = 0x0DC4; break; // XK_Sinh_ha / SINHALA HAYANNA
					case 0x1000dc5: ks = 0x0DC5; break; // XK_Sinh_lla / SINHALA MUURDHAJA LAYANNA
					case 0x1000dc6: ks = 0x0DC6; break; // XK_Sinh_fa / SINHALA FAYANNA
					case 0x1000dca: ks = 0x0DCA; break; // XK_Sinh_al / SINHALA AL-LAKUNA
					case 0x1000dcf: ks = 0x0DCF; break; // XK_Sinh_aa2 / SINHALA AELA-PILLA
					case 0x1000dd0: ks = 0x0DD0; break; // XK_Sinh_ae2 / SINHALA AEDA-PILLA
					case 0x1000dd1: ks = 0x0DD1; break; // XK_Sinh_aee2 / SINHALA DIGA AEDA-PILLA
					case 0x1000dd2: ks = 0x0DD2; break; // XK_Sinh_i2 / SINHALA IS-PILLA
					case 0x1000dd3: ks = 0x0DD3; break; // XK_Sinh_ii2 / SINHALA DIGA IS-PILLA
					case 0x1000dd4: ks = 0x0DD4; break; // XK_Sinh_u2 / SINHALA PAA-PILLA
					case 0x1000dd6: ks = 0x0DD6; break; // XK_Sinh_uu2 / SINHALA DIGA PAA-PILLA
					case 0x1000dd8: ks = 0x0DD8; break; // XK_Sinh_ru2 / SINHALA GAETTA-PILLA
					case 0x1000dd9: ks = 0x0DD9; break; // XK_Sinh_e2 / SINHALA KOMBUVA
					case 0x1000dda: ks = 0x0DDA; break; // XK_Sinh_ee2 / SINHALA DIGA KOMBUVA
					case 0x1000ddb: ks = 0x0DDB; break; // XK_Sinh_ai2 / SINHALA KOMBU DEKA
					case 0x1000ddc: ks = 0x0DDC; break; // XK_Sinh_o2 / SINHALA KOMBUVA HAA AELA-PILLA
					case 0x1000ddd: ks = 0x0DDD; break; // XK_Sinh_oo2 / SINHALA KOMBUVA HAA DIGA AELA-PILLA
					case 0x1000dde: ks = 0x0DDE; break; // XK_Sinh_au2 / SINHALA KOMBUVA HAA GAYANUKITTA
					case 0x1000ddf: ks = 0x0DDF; break; // XK_Sinh_lu2 / SINHALA GAYANUKITTA
					case 0x1000df2: ks = 0x0DF2; break; // XK_Sinh_ruu2 / SINHALA DIGA GAETTA-PILLA
					case 0x1000df3: ks = 0x0DF3; break; // XK_Sinh_luu2 / SINHALA DIGA GAYANUKITTA
					case 0x1000df4: ks = 0x0DF4; break; // XK_Sinh_kunddaliya / SINHALA KUNDDALIYA

					default: ks = GK_UNKNOWN; break;
					}
				}

				ke->keysym = ks;
			}

			if (win && ke->pressed) {
				// XXX On some layouts, a single keypress can
				// output more than one codepoint. I'm not sure
				// what this even means for keysyms (none of
				// the keys in keysymdef.h appear to have more
				// than one codepoint in the comment?).
				// See: http://kbdlayout.info/features/ligatures
				// A solution could be to emit multiple events,
				// probably with .keysym=0 for all but one of
				// the events? (requires a minor bit of
				// refactoring, because we're already inside a
				// function that can only return one event)
				char buf[8];
				KeySym fallback_sym;
				int len = Xutf8LookupString(win->x11_ic, &xe.xkey, buf, sizeof buf, &fallback_sym, NULL);
				if (len > 0) {
					const char* p = &buf[0];
					int codepoint = gpudl_utf8_decode(&p, &len);
					if (codepoint >= 0) {
						// XXX this hack makes [ctrl]+[a] yield codepoint 'a' instead of 1
						// (1 as in "\x01"; a control code). Should this be configurable?
						// I've heard of long-bearded men from olden days, who will press
						// [ctrl]+[h] instead of [backspace] until the day they die(d). And
						// that's fair actually. I just don't personally see how any
						// application, other than a terminal emulator, could want this? Tell
						// me your stories!
						ke->codepoint =
							((0 <= codepoint && codepoint < ' ') || codepoint == 0x7f)
							? fallback_sym
							: codepoint;
						// NOTE the use of `fallback_sym`; because it comes from Xutf8LookupString()
						// (and NOT XLookupKeysym()) it's actually slightly closer to being "text input"
						// because [shift]+[a] gives fallback_sym='A' with Xutf8LookupString(), but
						// fallback_sym='a' with XLookupKeysym(). So this weird, crappy inconsistency
						// actually proves useful here, "thanks".
					}
				}
			}

			#if 0
			printf("[%c] keysym=%d codepoint=%d\n", ke->pressed ? '#' : ' ', ke->keysym, ke->codepoint);
			#endif
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

void gpudl_render_end(void)
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

void gpudl_set_cursor(int cursor)
{
	assert(0 <= cursor && cursor < GPUDL__MAX_CURSORS);
	XDefineCursor(gpudl__runtime.x11_display, RootWindow(gpudl__runtime.x11_display, gpudl__runtime.x11_screen), gpudl__runtime.cursors[cursor].cursor);
}

// bitmap height is defined by the number of lines in string; width is defined
// by string line length (each line must have same width). valid characters:
//   ' '  mask=0
//   '?'  mask=0, hotspot
//   '.'  mask=1, color=black
//   ':'  mask=1, color=black, hotspot
//   'x'  mask=1, color=white
//   'X'  mask=1, color=white, hotspot
// bitmap must define 0 or 1 hotspots
int gpudl_make_bitmap_cursor(const char* bitmap)
{
	int width = 0;
	int height = 0;

	{
		const char* p = bitmap;
		while (*p != 0) {
			const char* p0 = p;
			while (*p != 0 && *p != '\n') p++;
			const char* p1 = p++;
			const int row_width = p1-p0;
			if (width == 0) {
				width = row_width;
			} else {
				assert((width == row_width) && "inconsistent row width");
			}
			height++;
		}
	}
	assert((width > 0 && height > 0) && "empty bitmap?");

	const int width_in_bytes = (width+7) >> 3;
	const int bytes_in_bitmap = width_in_bytes * height;

	Display* dpy = gpudl__runtime.x11_display;
	Window drawable = DefaultRootWindow(dpy);

	char* source_data = calloc(1, bytes_in_bitmap);
	char* mask_data = calloc(1, bytes_in_bitmap);

	int hotspot_set = 0;
	int hotspot_x = 0;
	int hotspot_y = 0;
	{
		const char* p = bitmap;
		for (int y = 0; y < height; y++) {
			for (int x = 0; x < width; x++) {
				int is_mask = 0;
				int is_hotspot = 0;
				int color = 0;

				char c = *(p++);
				switch (c) {
				case ' ': break;
				case '?': is_hotspot = 1; break;
				case '.': is_mask = 1; color = 0; break;
				case ':': is_mask = 1; color = 0; is_hotspot = 1; break;
				case 'x': is_mask = 1; color = 1; break;
				case 'X': is_mask = 1; color = 1; is_hotspot = 1; break;
				default:
					fprintf(stderr, "invalid character '%c' at %d,%d\n", c, x, y);
					abort();
				}

				if (is_hotspot) {
					assert(!hotspot_set && "multiple hotspots in bitmap");
					hotspot_x = x;
					hotspot_y = y;
				}

				{
					const int i = (x>>3) + y*width_in_bytes;
					assert(0 <= i && i < bytes_in_bitmap);
					const int m = 1<<(x&7);
					if (is_mask) mask_data[i] |= m;
					if (color)   source_data[i] |= m;
				}
			}
			p++;
		}
	}

	Pixmap source = XCreateBitmapFromData(dpy, drawable, source_data, width, height);
	Pixmap mask = XCreateBitmapFromData(dpy, drawable, mask_data, width, height);

	free(source_data);
	free(mask_data);

	Cursor cursor = XCreatePixmapCursor(
		gpudl__runtime.x11_display,
		source,
		mask,
		&gpudl__runtime.x11_color_white,
		&gpudl__runtime.x11_color_black,
		hotspot_x,
		hotspot_y);

	XFreePixmap(dpy, source);
	XFreePixmap(dpy, mask);

	for (int i = GPUDL_CURSOR_END; i < GPUDL__MAX_CURSORS; i++) {
		struct gpudl__cursor* cc = &gpudl__runtime.cursors[i];
		if (cc->in_use) continue;
		cc->in_use = 1;
		cc->cursor = cursor;
		return i;
	}

	assert(!"too many cursors");
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
