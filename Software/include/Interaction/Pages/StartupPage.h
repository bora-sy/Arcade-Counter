#pragma once

#include <PagedView.h>
#include "Interaction/Components/Label.h"
#include "Interaction/Components/Progressbar.h"
#include "Interaction/Components/Bitmap.h"
#include "Interaction/Bitmaps/Ticket.h"

class StartupPage : public Page
{
private:
Label labelInfo;

public:
    void OnLoad() override;
    void OnExit() override;
    void OnInput(BtnInput input) override;
    void Periodic() override;

    void ShowInfo(String info, uint8_t textSize = 2);
    void ClearInfo();

    StartupPage();
};