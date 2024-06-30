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


MainPage::MainPage()
{
    this->labelTickets = Label(RelativePoint(0.21, 0.2), "0", 2, Color::White, RelativePoint(0.5, 0.5));
    this->labelSession = Label(RelativePoint(0.81, 0.2), "-", 2, Color::White, RelativePoint(0.5, 0.5));

    this->bmpTicket = Bitmap(RelativePoint(0.2,0.7), Bitmap_TICKET, Size_TICKET, Color::White, RelativePoint(0.5, 0.5));
    this->bmpSession = Bitmap(RelativePoint(0.8,0.7), Bitmap_CLOCK, Size_CLOCK, Color::White, RelativePoint(0.5, 0.5));

    this->AddComponent(&labelTickets);
    this->AddComponent(&labelSession);

    this->AddComponent(&bmpTicket);
    this->AddComponent(&bmpSession);
}