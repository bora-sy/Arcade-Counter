#include "Pages.h"

namespace Pages
{
    MainPage* mainPage;
    StartupPage* startupPage;

    void Initialize()
    {
        mainPage = new MainPage();
        startupPage = new StartupPage();
    }
}