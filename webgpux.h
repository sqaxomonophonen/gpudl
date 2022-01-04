#ifndef WEBGPUX_H

#include <assert.h>

#include "wgpu.h"
#include "webgpu.h"

struct WgpuxBufferMapResult {
	WGPUBufferMapAsyncStatus status;
};

static void wgpuxBufferMapCallback(WGPUBufferMapAsyncStatus status, void* userdata)
{
	struct WgpuxBufferMapResult* result = userdata;
	result->status = status;
}

// synchronous buffer mapping; this goes against the WebGPU standard which is
// asynchronous in nature, but I'm putting my money on this eventually being
// "fixed in the substrate", e.g. see:
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

#define WEBGPUX_H
#endif
