#include "Containers/QuadTree.h"
#include "Input/InputManager.h"
#include "Logging/DebugLog.h"
#include "MemoryManagement/ResourceManager.h"
#include "Rendering/RenderTarget.h"
#include "TreePanel.h"
#include "WorldObject/Nameable.h"
#include "WorldObject/Transformable.h"
#include "WorldObject/WorldObject.h"
#include "WorldObject/WorldObjectManager.h"
// ----------------------------------------------------------------------------
const float PTreePanel::PADDING_LEFT = 10.f;
const float PTreePanel::PADDING_RIGHT = 10.f;
const float PTreePanel::PADDING_TOP = 10.f;
// ----------------------------------------------------------------------------
void PTreeNodeVisual::Draw(PRenderTarget* renderTarget, int level, const PString& text, const PVector2& position, bool selected)
{
	NodeSelectObj.setFillColor(selected ? SelectedColor : sf::Color::Transparent);
	NodeSelectObj.setPosition(position + PVector2(0.f, Row * RowSpacing));
	renderTarget->Draw(NodeSelectObj);

	NodeTextObj.setString(text);
	NodeTextObj.setOrigin(0.f, NodeTextObj.getCharacterSize() * 0.5f);
	NodeTextObj.setPosition(position + PVector2(level * LevelSpacing, (Row + 0.5f) * RowSpacing));
	NodeTextObj.setStyle(selected ? sf::Text::Bold : sf::Text::Regular);
	renderTarget->Draw(NodeTextObj);
}
// ----------------------------------------------------------------------------
PTreePanel::PTreePanel(PWindow* parentRenderWindow):
	PPanel(parentRenderWindow)
{
	PInput::RegisterMouseDownEventListener(this);
	PInput::RegisterMouseUpEventListener(this);
	PWorldObjectManager::GetInstance().RegisterWorldObjectCreationListener(this);

	_headerRect.setFillColor(PColor::FromHex(0x33373a));
	_headerRect.setOutlineColor(PColor::FromHex(0x4a4b4f));
	_headerRect.setOutlineThickness(2.f);

	_headerRect.setSize(PVector2(0.f, 30.f));
	_headerRect.setOrigin(PVector2(0.f, _headerRect.getSize().y));

	_headerText.setFont(*PResourceManager::GetInstance().GetFont("Roboto-Bold"));
	_headerText.setCharacterSize(14);
	_headerText.setFillColor(PColor::FromHex(0xeff3f6));
	_headerText.setOrigin(PVector2(-10.f, _headerText.getCharacterSize() + 10.f));

	_backgroundRect.setFillColor(PColor::FromHex(0x292d30));
	_backgroundRect.setOutlineColor(PColor::FromHex(0x4a4b4f));
	_backgroundRect.setOutlineThickness(2.f);

	// Tree node visual
	_treeNodeVisual.SelectedColor = PColor::FromHex(0x383e42);

	_treeNodeVisual.NodeTextObj.setFont(*PResourceManager::GetInstance().GetFont("Roboto-Regular"));
	_treeNodeVisual.NodeTextObj.setCharacterSize(12);
	_treeNodeVisual.NodeTextObj.setFillColor(PColor::FromHex(0x8f9396));
	_treeNodeVisual.RowSpacing = 25.f;
	_treeNodeVisual.LevelSpacing = 10.f;
}
// ----------------------------------------------------------------------------
void PTreePanel::SetTreeRoot(OWorldObject* root)
{
	_treeRoot = root;

	// Init buttons
	ClearButtons();
	InitButtons(_treeRoot);
}
// ----------------------------------------------------------------------------
void PTreePanel::SetTitle(const PString& title)
{
	_headerText.setString(title);
}
// ----------------------------------------------------------------------------
OWorldObject* PTreePanel::GetSelectedObject() const
{
	return _selectedObject;
}
// ----------------------------------------------------------------------------
/*override*/
void PTreePanel::Draw(PRenderTarget* renderTarget)
{
	renderTarget->Draw(_headerRect);
	renderTarget->Draw(_backgroundRect);
	renderTarget->Draw(_headerText);

	DrawTree(renderTarget);
}
// ----------------------------------------------------------------------------
/*override*/
void PTreePanel::InitSize(const PVector2& size)
{
	PPanel::InitSize(size);

	_headerRect.setSize(PVector2(size.X, _headerRect.getSize().y));
	_backgroundRect.setSize(size);
	_treeNodeVisual.NodeSelectObj.setSize(PVector2(size.X - PADDING_LEFT - PADDING_RIGHT, _treeNodeVisual.RowSpacing));
}
// ----------------------------------------------------------------------------
/*override*/
void PTreePanel::SetPosition(const PVector2& pos)
{
	PPanel::SetPosition(pos);

	_headerRect.setPosition(pos);
	_headerText.setPosition(pos);
	_backgroundRect.setPosition(pos);
}
// ----------------------------------------------------------------------------
/*override*/
void PTreePanel::OnButtonClicked(int buttonId)
{
	PPanel::OnButtonClicked(buttonId);

	_selectedObject = nullptr;

	// Ignore root
	for (psize i = 1; i < _buttonNodes.Size(); ++i)
	{
		_buttonNodes[i].Selected = false;

		if (i == buttonId)
		{
			_buttonNodes[i].Selected = true;
			_selectedObject = _buttonNodes[i].WorldObject;
		}
	}
}
// ----------------------------------------------------------------------------
/*override*/
void PTreePanel::OnWorldObjectCreated(OWorldObject* worldObject)
{
}
// ----------------------------------------------------------------------------
/*override*/
void PTreePanel::OnWorldObjectDestroyed(OWorldObject* worldObject)
{
}
// ----------------------------------------------------------------------------
/*override*/
void PTreePanel::OnWorldObjectParentChanged(OWorldObject* worldObject)
{
	ClearButtons();
	InitButtons(_treeRoot);
}
// ----------------------------------------------------------------------------
/*override*/
void PTreePanel::OnPanelClicked()
{
	PPanel::OnPanelClicked();

	for (PTreePanelButtonNode& btn : _buttonNodes)
	{
		btn.Selected = false;
	}

	_selectedObject = nullptr;
}
// ----------------------------------------------------------------------------
void PTreePanel::ClearButtons()
{
	PPanel::ClearButtons();

	_buttonNodes.Clear(_buttonNodes.Size());
}
// ----------------------------------------------------------------------------
void PTreePanel::DrawTree(PRenderTarget* renderTarget)
{
	_treeNodeVisual.Row = 0;
	for (const PTreePanelButtonNode& node : _buttonNodes)
	{
		PString name("Error_Object_Null");
		if (node.WorldObject != nullptr)
		{
			name = node.WorldObject->GetName();
		}

		_treeNodeVisual.Row = node.ButtonRow;
		_treeNodeVisual.Draw(renderTarget, node.ButtonTreeLevel, name, GetPosition() + PVector2(PADDING_LEFT, PADDING_TOP), node.Selected);
	}
}
// ----------------------------------------------------------------------------
void PTreePanel::InitButtons(OWorldObject* root)
{
	int row = 0;
	InitButtonsInternal(root, row);
}
// ----------------------------------------------------------------------------
void PTreePanel::InitButtonsInternal(OWorldObject* root, int& row, int level/* = 0*/)
{
	if (root == nullptr)
	{
		return;
	}

	int buttonId = row;

	_buttonNodes.Add(PTreePanelButtonNode{ buttonId, level, root});

	PVector2 panelSize = GetPanelBounds().GetSize();

	PVector2 buttonMin = PVector2(PADDING_LEFT, PADDING_TOP + row * _treeNodeVisual.RowSpacing) +
		GetPosition();
	PVector2 buttonMax = buttonMin + PVector2(panelSize.X - PADDING_LEFT, _treeNodeVisual.RowSpacing);
	PBox buttonBounds(buttonMin, buttonMax);

	AddButton(buttonId, buttonBounds);

	for (OWorldObject* child : root->GetChildren())
	{
		row++;
		InitButtonsInternal(child, row, level + 1);
	}
}
// ----------------------------------------------------------------------------