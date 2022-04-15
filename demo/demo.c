#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>

#include "gpudl.h"

#define STB_DS_IMPLEMENTATION
#include "stb_ds.h"

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

struct window {
	int id;
	int mx;
	int my;
};

int main(int argc, char** argv)
{
	gpudl_init();
	//wgpuCreateInstance(NULL);

	struct window* windows = NULL;
	arrput(windows, ((struct window) {
		.id = gpudl_window_open("gpudl/0"),
	}));

	WGPUAdapter adapter;
	WGPUDevice device;
	WGPUQueue queue;
	gpudl_get_wgpu(NULL, &adapter, &device, &queue);

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
		.usage = WGPUBufferUsage_Vertex /*| WGPUBufferUsage_MapWrite*/ | WGPUBufferUsage_CopyDst,
		.size = vtxbuf_sz,
	});
	assert(vtxbuf);

	WGPUBuffer unibuf = wgpuDeviceCreateBuffer(device, &(WGPUBufferDescriptor){
		.usage = WGPUBufferUsage_Uniform /*| WGPUBufferUsage_MapWrite*/ | WGPUBufferUsage_CopyDst,
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

	WGPUShaderModuleDescriptor shader_source = load_wgsl(my_shader2);
	WGPUShaderModule shader = wgpuDeviceCreateShaderModule(device, &shader_source);
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

	WGPUTextureFormat swapChainFormat = wgpuSurfaceGetPreferredFormat(gpudl_window_get_surface(windows[0].id), adapter);

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

	int iteration = 0;
	int exiting = 0;

	while (!exiting) {
		struct gpudl_event e;
		while (gpudl_poll_event(&e)) {
			switch (e.type) {
			case GPUDL_MOTION:
				for (int i = 0; i < arrlen(windows); i++) {
					struct window* window = &windows[i];
					if (window->id == e.window_id) {
						window->mx = e.motion.x;
						window->my = e.motion.y;
					}
				}
				break;
			case GPUDL_BUTTON:
				printf("btn %d %d\n", e.button.which, e.button.pressed);
				if (e.button.pressed) {
					if (e.button.which == 1) {
						arrput(windows, ((struct window) {
							.id = gpudl_window_open("gpudl/n"),
						}));
					} else if (e.button.which == 3) {
						for (int i = 0; i < arrlen(windows); i++) {
							if (windows[i].id == e.window_id) {
								gpudl_window_close(e.window_id);
								arrdel(windows, i);
								break;
							}
						}
					}
				}
				break;
			}
		}

		for (int i = 0; i < arrlen(windows); i++) {
			struct window* window = &windows[i];

			WGPUTextureView next_texture = gpudl_render_begin(window->id);
			if (!next_texture) {
				fprintf(stderr, "WARNING: no swap chain texture view\n");
				continue;
			}


			struct Vertex vs[n_vertices];
			write_vertices(iteration, n_triangles, vs);
			wgpuQueueWriteBuffer(queue, vtxbuf, 0, vs, vtxbuf_sz);

			int width, height;
			gpudl_window_get_size(window->id, &width, &height);

			struct Uniforms u = {
				.frame = iteration,
				.distort = (((float)window->my / (float)height) - 0.5f) * 2.5f,
				.alpha = ((float)window->mx / (float)width) * 5.0f,
			};
			wgpuQueueWriteBuffer(queue, unibuf, 0, &u, sizeof u);

			WGPUCommandEncoder encoder = wgpuDeviceCreateCommandEncoder(
				device,
				&(WGPUCommandEncoderDescriptor){.label = "Command Encoder"}
			);

			WGPURenderPassEncoder renderPass = wgpuCommandEncoderBeginRenderPass(
				encoder,
				&(WGPURenderPassDescriptor){
					.colorAttachmentCount = 1,
					.colorAttachments = &(WGPURenderPassColorAttachment){
						.view = next_texture,
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

			gpudl_render_end();
		}

		iteration++;
	}

	return EXIT_SUCCESS;
}


