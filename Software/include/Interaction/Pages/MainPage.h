#pragma once

#include <PagedView.h>
#include "Interaction/Components/Label.h"
#include "Interaction/Components/Progressbar.h"

class MainPage : public Page
{
private:
Label labelTickets;
Label labelSession;
Progressbar pbarSession;

public:
    void OnLoad() override;
    void OnExit() override;
    void OnInput(BtnInput input) override;
    void Periodic() override;

    MainPage();
};