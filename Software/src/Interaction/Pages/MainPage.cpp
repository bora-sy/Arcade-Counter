#include "Pages.h"




void MainPage::OnLoad()
{
    
}

void MainPage::OnExit()
{
    
}

void MainPage::OnInput(BtnInput input){}

void MainPage::Periodic()
{
    
}

void MainPage::ShowInfo(String info)
{
    this->ToggleAllVisible(false, false);

    this->labelInfo.UpdateText(info);
    this->labelInfo.SetVisible(true, false);
    this->DrawIfShown();
}

void MainPage::ClearInfo()
{
    this->ToggleAllVisible(true, false);

    this->labelInfo.SetVisible(false, false);
    
    this->DrawIfShown();
}


MainPage::MainPage()
{
    this->labelInfo = Label(RelativePoint(0, 0.5), "", 2, Color::White, RelativePoint(0, 0.5));
    labelInfo.SetVisible(false, false);

    this->labelTickets = Label(RelativePoint(0.21, 0.2), "0", 2, Color::White, RelativePoint(0.5, 0.5));
    this->labelSession = Label(RelativePoint(0.81, 0.2), "-", 2, Color::White, RelativePoint(0.5, 0.5));

    this->bmpTicket = Bitmap(RelativePoint(0.2,0.7), Bitmap_TICKET, Size_TICKET, Color::White, RelativePoint(0.5, 0.5));
    this->bmpSession = Bitmap(RelativePoint(0.8,0.7), Bitmap_CLOCK, Size_CLOCK, Color::White, RelativePoint(0.5, 0.5));
    
    this->AddComponent(&labelInfo);

    this->AddComponent(&labelTickets);
    this->AddComponent(&labelSession);

    this->AddComponent(&bmpTicket);
    this->AddComponent(&bmpSession);
}