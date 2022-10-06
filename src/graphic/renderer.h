#ifndef IRONENGINE_RENDERER_H
#define IRONENGINE_RENDERER_H
#include "PCH.h"

namespace gfx{

    class Renderer {
    public:
        explicit Renderer(MTL::Device* device);
        ~Renderer();

        void Draw(MTK::View* view);

    private:
        MTL::Device* device{nullptr};
        MTL::CommandQueue* commandQueue{nullptr};
    };

}


#endif //IRONENGINE_RENDERER_H
