#ifdef __APPLE__
#include <CoreFoundation/CoreFoundation.h>
#endif

#include "Game.h"

//Main Method
int main(int argc, char * arg[])
{
    // Setup asset path, no real work required for Windows. Mac needs to load assets from a bundle
    // ----------------------------------------------------------------------------
    // http://stackoverflow.com/questions/516200/relative-paths-not-working-in-xcode-c
    // This makes relative paths work in C++ in Xcode by changing directory to the Resources folder inside the .app bundle
#ifdef __APPLE__
    CFBundleRef mainBundle = CFBundleGetMainBundle();
    CFURLRef resourcesURL = CFBundleCopyResourcesDirectoryURL(mainBundle);
    char path[PATH_MAX];
    if (!CFURLGetFileSystemRepresentation(resourcesURL, TRUE, (UInt8 *)path, PATH_MAX))
    {
        // error!
    }
    CFRelease(resourcesURL);
    
    chdir(path);
    std::cout << "Current Path: " << path << std::endl;
#endif
    
    GameApplication * app=new GameApplication();
    if (!app->init(argc, arg))
    {
        if(app)
        {
            delete app;
            app=NULL;
        }
        
        return -1;
    }
    
    while(app->isRunning())
    {
        app->update();
        app->render();
    }
    
    
    if (app)
    {
        delete app;
        app=NULL;
    }
    return 0;
}