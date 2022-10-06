
#ifndef IRONENGINE_VIEW_H
#define IRONENGINE_VIEW_H
#include "renderer.h"

namespace gfx{
    //view delegate
    class View : public MTK::ViewDelegate {
    public:
        explicit View(MTL::Device* device) : renderer{new gfx::Renderer(device)} {}
        ~View() override { delete renderer;};

        void drawInMTKView(MTK::View *pView) override {
            renderer->Draw(pView);
        };

    private:
        Renderer* renderer{nullptr};
    };

}



#endif //IRONENGINE_VIEW_H
