#include "Pages.h"




void StartupPage::OnLoad()
{
    
}

void StartupPage::OnExit()
{
    
}

void StartupPage::OnInput(BtnInput input){}

void StartupPage::Periodic()
{
    
}

void StartupPage::ShowInfo(String info)
{
    this->ToggleAllVisible(false, false);

    this->labelInfo.UpdateText(info);
    this->labelInfo.SetVisible(true, false);
    this->DrawIfShown();
}

void StartupPage::ClearInfo()
{
    this->ToggleAllVisible(true, false);

    this->labelInfo.SetVisible(false, false);
    
    this->DrawIfShown();
}


StartupPage::StartupPage()
{
    this->labelInfo = Label(RelativePoint(0, 0.5), "", 2, Color::White, RelativePoint(0, 0.5));
    labelInfo.SetVisible(false, false);
    
    this->AddComponent(&labelInfo);
}