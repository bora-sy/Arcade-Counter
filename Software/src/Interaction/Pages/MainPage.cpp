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

    this->labelSession = Label(RelativePoint(0.5,0.05), "Session Ends In: 10m", 1, Color::White, RelativePoint(0.5, 0));
    this->labelTickets = Label(RelativePoint(0.5,0.5), "10", 3, Color::White, RelativePoint(0.5, 0.5));
    this->pbarSession = Progressbar(RelativePoint(0, 0.95), RelativeSize(1, 0.05), Color::White, 128, 128);
    
    this->AddComponent(&labelTickets);
    this->AddComponent(&labelSession);
    this->AddComponent(&pbarSession);
}