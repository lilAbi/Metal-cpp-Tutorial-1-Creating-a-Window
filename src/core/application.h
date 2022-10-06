
#ifndef IRONENGINE_APPLICATION_H
#define IRONENGINE_APPLICATION_H
#include "graphic/view.h"
#include "PCH.h"

namespace core{

    //object that manages an NS::Application object’s life cycle and its interaction with common system services
    class Application : public NS::ApplicationDelegate {
    public:
        Application() = default;
        Application(std::string winTitle, CGFloat winWidth, CGFloat winHeight) : title(std::move(winTitle)), width{winWidth}, height{winHeight} {}
        ~Application() override;

        //This method is called after the application’s main run loop has been started, but before it has processed any events
        void applicationDidFinishLaunching(NS::Notification* pNotification) override;
        //Tells the delegate that the app’s initialization is about to complete.
        void applicationWillFinishLaunching(NS::Notification* pNotification) override;
        //The application sends this message to your delegate when the application’s last window is closed
        bool applicationShouldTerminateAfterLastWindowClosed(NS::Application* pSender) override;

        NS::Menu* createMenuBar();

    private:
        std::string title{"Metal Window"};

        CGFloat width{1280};
        CGFloat height{720};

        NS::Window* m_window{nullptr};
        MTK::View* m_view{nullptr};
        MTL::Device* m_device{nullptr};
        gfx::View* m_appView{nullptr};
    };
}



#endif //IRONENGINE_APPLICATION_H
