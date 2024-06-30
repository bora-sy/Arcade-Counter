#pragma once

#include <PagedView.h>
#include "Interaction/Pages/MainPage.h"
#include "Interaction/Pages/StartupPage.h"

namespace Pages
{
    extern MainPage* mainPage;
    extern StartupPage* startupPage;

    void Initialize();
}