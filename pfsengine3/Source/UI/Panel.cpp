#include "Logging/DebugLog.h"
#include "Panel.h"
// ----------------------------------------------------------------------------
PPanel::PPanel(PWindow* parentRenderWindow):
	_parentWindow(parentRenderWindow)
{
}
// ----------------------------------------------------------------------------
void PPanel::Initialize(const PVector2& size)
{
	InitSize(size);
}
// ----------------------------------------------------------------------------
void PPanel::InitSize(const PVector2& size)
{
	_size = size;
	UpdatePanelBounds();
	_buttonQuadTree.Clear(_panelBounds);
}
// ----------------------------------------------------------------------------
const PVector2& PPanel::GetSize() const
{
	return _size;
}
// ----------------------------------------------------------------------------
void PPanel::SetPosition(const PVector2& pos)
{
	_position = pos;
	UpdatePanelBounds();
}
// ----------------------------------------------------------------------------
const PVector2& PPanel::GetPosition() const
{
	return _position;
}
// ----------------------------------------------------------------------------
bool PPanel::OnMouseDownEvent(const PMouseDownEvent& eventData)
{
	PVector2 mousePos = PInput::GetMousePosition(GetParentWindow());
	PArray<PButtonDescription> buttons = _buttonQuadTree.FindData(mousePos);
	if (buttons.Size() == 0)
	{
		if (_panelBounds.DoesContain(mousePos))
		{
			OnPanelClicked();
			return true;
		}
		else
		{
			return false;
		}
	}

	for (PButtonDescription& btn : buttons)
	{
		OnButtonClicked(btn.ButtonId);
	}

	return true;
}
// ----------------------------------------------------------------------------
bool PPanel::OnMouseUpEvent(const PMouseUpEvent& eventData)
{
	PVector2 mousePos = PInput::GetMousePosition(GetParentWindow());
	/*for (PButtonDescription& btn : _buttonQuadTree.FindData(mousePos))
	{
		if (btn.OnClicked != nullptr)
		{
			btn.OnClicked();
		}
	}*/

	return false;
}
// ----------------------------------------------------------------------------
const PWindow* PPanel::GetParentWindow() const
{
	return _parentWindow;
}
// ----------------------------------------------------------------------------
const PBox& PPanel::GetPanelBounds() const
{
	return _panelBounds;
}
// ----------------------------------------------------------------------------
void PPanel::ClearButtons()
{
	_buttonQuadTree.Clear(_panelBounds);
}
// ----------------------------------------------------------------------------
void PPanel::AddButton(int buttonId, const PBox& buttonBounds)
{
	PButtonDescription btn;
	btn.ButtonId = buttonId;
	_buttonQuadTree.Add(btn, buttonBounds);
}
// ----------------------------------------------------------------------------
void PPanel::OnButtonClicked(int buttonId)
{

}
// ----------------------------------------------------------------------------
void PPanel::OnPanelClicked()
{

}
// ----------------------------------------------------------------------------
void PPanel::UpdatePanelBounds()
{
	_panelBounds.Min = GetPosition();
	_panelBounds.Max = _panelBounds.Min + GetSize();
}
// ----------------------------------------------------------------------------