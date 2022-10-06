
#include "application.h"

core::Application::~Application() {
    m_view->release();
    m_window->release();
    m_device->release();
    delete m_appView;
}

void core::Application::applicationDidFinishLaunching(NS::Notification* pNotification) {
    //Returns the device instance Metal selects as the default
    m_device = MTL::CreateSystemDefaultDevice();

    //window frame dimensions
    CGRect frame{{0, 0}, {width, height}};

    //create window object with properties
    m_window = NS::Window::alloc()->init(frame,
                                         NS::WindowStyleMaskClosable | NS::WindowStyleMaskTitled,
                                         NS::BackingStoreBuffered,
                                         false);

    //specialized view that creates, configures, and display Metal objects
    m_view = MTK::View::alloc()->init(frame, m_device);
    //specify color format & clear window color
    m_view->setColorPixelFormat(MTL::PixelFormat::PixelFormatBGRA8Unorm_sRGB);
    m_view->setClearColor(MTL::ClearColor::Make(0.0, 1.0, 0.0, 1.0));

    //construct a view delegate and set it
    m_appView = new gfx::View(m_device);
    m_view->setDelegate(m_appView);

    //the window retains the new content view and owns it thereafter, view obj is resized to fit precisely within the content area of the window
    m_window->setContentView(m_view);
    m_window->setTitle(NS::String::string(title.c_str(), NS::StringEncoding::UTF8StringEncoding));

    //moves the window
    m_window->makeKeyAndOrderFront(nullptr);

    //get global shared application state and activate it
    auto* appNS = reinterpret_cast<NS::Application*>(pNotification->object());
    appNS->activateIgnoringOtherApps(true);

}

void core::Application::applicationWillFinishLaunching(NS::Notification *pNotification) {
    NS::Menu* menu = createMenuBar();

    //get global shared application state
    auto* appNS = reinterpret_cast<NS::Application*>(pNotification->object());
    //assign a new menu bar
    appNS->setMainMenu(menu);
    //controls whether and how an app may be activated
    appNS->setActivationPolicy(NS::ActivationPolicy::ActivationPolicyRegular);

}

bool core::Application::applicationShouldTerminateAfterLastWindowClosed(NS::Application *pSender) {
    return true;
}

NS::Menu* core::Application::createMenuBar() {
    using NS::StringEncoding::UTF8StringEncoding;

    //create a main menu instance
    auto* mainMenu = NS::Menu::alloc()->init();

    //create an app menu instance
    auto* appMenu = NS::Menu::alloc()->init(NS::String::string( "Appname", UTF8StringEncoding ));
    //create a menuItem instance for
    auto* appMenuItem = NS::MenuItem::alloc()->init();


    //ptr to application title name
    auto* appName = NS::RunningApplication::currentApplication()->localizedName();
    //create a string and append a string to it
    NS::String* quitItemName = NS::String::string( "Quit ", UTF8StringEncoding )->stringByAppendingString( appName );

    //callback object pointer that closes application
    SEL quitCallBackFunc = NS::MenuItem::registerActionCallback("appQuit", [](void*,SEL,const NS::Object* pSender){
        auto* appInstance = NS::Application::sharedApplication();
        appInstance->terminate( pSender );
    });

    //add a menu item that invokes a callback when pressing q while command key is pressed
    NS::MenuItem* appQuitItem = appMenu->addItem( quitItemName, quitCallBackFunc, NS::String::string( "q", UTF8StringEncoding ) );
    appQuitItem->setKeyEquivalentModifierMask( NS::EventModifierFlagCommand );
    //add ass submenu option for menu
    appMenuItem->setSubmenu( appMenu );


    //create a menu instance
    auto* windowMenu = NS::Menu::alloc()->init( NS::String::string( "Window", UTF8StringEncoding ) );
    //create a menu item instance
    auto* windowMenuItem = NS::MenuItem::alloc()->init();

    //callback object pointer that closes application
    SEL closeWindowCallback = NS::MenuItem::registerActionCallback( "windowClose", [](void*, SEL, const NS::Object*){
        auto* appInstance = NS::Application::sharedApplication();
        appInstance->windows()->object<NS::Window>(0)->close();
    });

    //add a menu item that invokes a callback when pressing w while command key is pressed
    auto* closeWindowItem = windowMenu->addItem( NS::String::string( "Close Window", UTF8StringEncoding ), closeWindowCallback, NS::String::string( "w", UTF8StringEncoding ) );
    closeWindowItem->setKeyEquivalentModifierMask( NS::EventModifierFlagCommand );
    //add as sub menu option for window menu
    windowMenuItem->setSubmenu( windowMenu );

    //add menu items to main menu
    mainMenu->addItem( appMenuItem );
    mainMenu->addItem( windowMenuItem );

    //release memory
    appMenuItem->release();
    windowMenuItem->release();
    appMenu->release();
    windowMenu->release();

    //return ptr holding main menu
    return mainMenu->autorelease();
}

