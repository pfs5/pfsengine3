#pragma once
#include "Containers/QuadTree.h"
#include "Input/MouseEventListener.h"
#include "Math/Box.h"
#include "Math/Vector2.h"
// ----------------------------------------------------------------------------
class PRenderTarget;
class PWindow;
// ----------------------------------------------------------------------------
/**
 * Generic UI panel with basic functionality.
 */
class PPanel : public IMouseDownEventListener, public IMouseUpEventListener
{
public:
	PPanel(PWindow* parentRenderWindow);
	void Initialize(const PVector2& size);

	virtual void Draw(PRenderTarget* renderTarget) = 0;

	virtual void InitSize(const PVector2& size);
	const PVector2& GetSize() const;

	virtual void SetPosition(const PVector2& pos);
	const PVector2& GetPosition() const;

// MouseEventListener
public:
	virtual bool OnMouseDownEvent(const PMouseDownEvent& eventData) override;
	virtual bool OnMouseUpEvent(const PMouseUpEvent& eventData) override;

protected:
	const PWindow* GetParentWindow() const;
	const PBox& GetPanelBounds() const;

	void ClearButtons();
	void AddButton(int buttonId, const PBox& buttonBounds);
	virtual void OnButtonClicked(int buttonId);
	virtual void OnPanelClicked();

private:
	/**
	 * Update bounds. Assumed origin is top left corner.
	 */
	void UpdatePanelBounds();

private:
	struct PButtonDescription
	{
		int ButtonId;
	};

private:
	PWindow* _parentWindow = nullptr;
	PBox _panelBounds;

	PVector2 _size;
	PVector2 _position;

	PQuadTree<PButtonDescription> _buttonQuadTree;
};
// ----------------------------------------------------------------------------