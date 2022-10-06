
#include "renderer.h"

gfx::Renderer::Renderer(MTL::Device* device) : device{device->retain()}{
    commandQueue = device->newCommandQueue();
}


gfx::Renderer::~Renderer() {
    commandQueue->release();
    device->release();
}

void gfx::Renderer::Draw(MTK::View *view) {

    NS::AutoreleasePool* pool = NS::AutoreleasePool::alloc()->init();

    //get the current command buffer object to encode commands for execution in the GPU
    auto* commandBuffer = commandQueue->commandBuffer();
    //get the current render pass descriptor that will be populated with different render targets and their information
    auto* renderPassDescriptor = view->currentRenderPassDescriptor();
    //encodes the renderPass descriptor into actually commands
    auto* renderCommandEncoder = commandBuffer->renderCommandEncoder(renderPassDescriptor);
    //YOU SHALL NOT ENCODE ANYMORE - end encoding
    renderCommandEncoder->endEncoding();
    //tell gpu we got something to draw
    commandBuffer->presentDrawable(view->currentDrawable());
    //this ain't a marriage, commit to the damn draw
    commandBuffer->commit();

    pool->release();

}
