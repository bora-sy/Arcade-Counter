#pragma once

#include <PagedView.h>
#include "Interaction/Components/Label.h"
#include "Interaction/Components/Progressbar.h"
#include "Interaction/Components/Bitmap.h"
#include "Interaction/Bitmaps/Ticket.h"

class MainPage : public Page
{
private:
Label labelTickets;
Label labelSession;
Progressbar pbarSession;
Bitmap bmpTicket;
Bitmap bmpSession;

uint16_t ticketCount = 10;

public:
    void OnLoad() override;
    void OnExit() override;
    void OnInput(BtnInput input) override;
    void Periodic() override;

    MainPage();
};