#define NS_PRIVATE_IMPLEMENTATION
#define MTL_PRIVATE_IMPLEMENTATION
#define MTK_PRIVATE_IMPLEMENTATION
#define CA_PRIVATE_IMPLEMENTATION
#include "PCH.h"
#include "core/application.h"


int main() {
    //initialize autoreleasePool pool
    NS::AutoreleasePool* poolAllocator = NS::AutoreleasePool::alloc()->init();

    core::Application game;

    /* every application uses a single instance of NSApplication, to control the main event loop,
     * keep track of app's windows and menus, distribute events to appropriate objects, set up
     * autorelease pools, and receive notification of app-level events. */
    NS::Application* appNS = NS::Application::sharedApplication();

    /* Every NSApplication has a delegate that is notified when app is start or terminated.
     * By setting the delegate and implementing the delegate methods,
     * you customize the behavior of your app without having to subclass NSApplication  */
    appNS->setDelegate(&game);

    appNS->run();

    poolAllocator->release();

    return 0;
}















