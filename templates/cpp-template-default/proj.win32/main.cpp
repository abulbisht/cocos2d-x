#include "main.h"
#include "AppDelegate.h"
#include "cocos2d.h"
#pragma comment(lib, "libxreaderp.lib")
#pragma comment(lib, "libxreader.lib")

USING_NS_CC;

int WINAPI _tWinMain(HINSTANCE hInstance,
                       HINSTANCE hPrevInstance,
                       LPTSTR    lpCmdLine,
                       int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // create the application instance
    AppDelegate app;
    return Application::getInstance()->run();
}
