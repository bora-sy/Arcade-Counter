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

void ShowInfo(String info);
void ClearInfo();

public:
    void OnLoad() override;
    void OnExit() override;
    void OnInput(BtnInput input) override;
    void Periodic() override;

    StartupPage();
};