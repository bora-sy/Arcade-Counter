#include "PagedView.h"

// --- PAGED VIEW  ---

namespace PagedView
{

  Page *currentPage = nullptr;

  bool Begin()
  {
    return Display::Begin();
  }

  void HandleInput(BtnInput input)
  {
    if (currentPage != nullptr)
      currentPage->OnInput(input);
  }

  void Periodic()
  {
    if (currentPage != nullptr)
      currentPage->Periodic();
  }

  void SwitchToPage(Page *page)
  {
    if (currentPage == page)
    {
      return;
    }

    if (currentPage != nullptr)
      currentPage->OnExit();

    if (page == nullptr)
      currentPage = nullptr;
    else
    {
      currentPage = page;
      page->OnLoad();
      page->DrawIfShown();
    }
  }

  Page *GetCurrentPage()
  {
    return currentPage;
  }
}

// --- PAGE  ---

void Page::ToggleAllVisible(bool v, bool update)
{
  for (int i = 0; i < this->componentsCount; i++)
  {
    PageComponent *comp = this->components[i];
    comp->SetVisible(v, false);
  }

  if (update) this->DrawIfShown();
}

void Page::Close()
{
  if (PagedView::GetCurrentPage() == this)
    PagedView::SwitchToPage(nullptr);
}

void Page::Show()
{
  if (PagedView::GetCurrentPage() == nullptr)
    PagedView::SwitchToPage(this);
  else
  {
    PagedView::GetCurrentPage()->Close();
    PagedView::SwitchToPage(this);
  }
}

bool Page::IsShown()
{
  return PagedView::GetCurrentPage() == this;
}

void Page::DrawIfShown()
{
  if (!this->IsShown())
  {
    return;
  }

  Display::Clear(false);

  for (int i = 0; i < this->componentsCount; i++)
  {
    PageComponent *comp = this->components[i];

    if (comp->IsVisible())
      comp->Draw();
  }

  Display::Update();
}

void Page::AddComponent(PageComponent *component)
{
  component->SetParentPage(this);
  this->components[componentsCount++] = component;
}

// --- PAGE COMPONENT ---

void PageComponent::SetVisible(bool v, bool update)
{
  this->visible = v;
  
  if(update && this->parentPage != nullptr)
  this->parentPage->DrawIfShown();
}

bool PageComponent::IsVisible()
{
  return this->visible;
}

void PageComponent::SetParentPage(Page *_page)
{
  if (this->parentPage == nullptr)
    this->parentPage = _page;
}

// --- BTNINPUT ---

BtnInput::BtnInput(BtnKey key, BtnInputMode mode)
{
  this->key = key;
  this->mode = mode;
}