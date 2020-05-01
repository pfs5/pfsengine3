#include "MemoryManagement/ResourceManager.h"
#include "Rendering/RenderTarget.h"
#include "TreePanel.h"
#include "WorldObject/Nameable.h"
#include "WorldObject/Transformable.h"
// ----------------------------------------------------------------------------
void PTreeNodeVisual::Draw(PRenderTarget* renderTarget, int level, const PString& text, const PVector2& position)
{
	NodeTextObj.setString(text);
	NodeTextObj.setPosition(position + PVector2(level * LevelSpacing, Row * RowSpacing));
	renderTarget->Draw(NodeTextObj);
}
// ----------------------------------------------------------------------------
PTreePanel::PTreePanel()
{
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

	_treeNodeVisual.NodeTextObj.setFont(*PResourceManager::GetInstance().GetFont("Roboto-Regular"));
	_treeNodeVisual.NodeTextObj.setCharacterSize(12);
	_treeNodeVisual.NodeTextObj.setFillColor(PColor::FromHex(0x8f9396));
	_treeNodeVisual.RowSpacing = 20.f;
	_treeNodeVisual.LevelSpacing = 10.f;
}
// ----------------------------------------------------------------------------
void PTreePanel::SetTreeRoot(const ITransformable* root)
{
	_treeRoot = root;
}
// ----------------------------------------------------------------------------
void PTreePanel::SetTitle(const PString& title)
{
	_headerText.setString(title);
}
// ----------------------------------------------------------------------------
void PTreePanel::Draw(PRenderTarget* renderTarget)
{
	renderTarget->Draw(_headerRect);
	renderTarget->Draw(_backgroundRect);
	renderTarget->Draw(_headerText);

	DrawTree(renderTarget);
}
// ----------------------------------------------------------------------------
void PTreePanel::SetSize(const PVector2& size)
{
	_size = size;
	_headerRect.setSize(PVector2(size.X, _headerRect.getSize().y));
	_backgroundRect.setSize(size);
}
// ----------------------------------------------------------------------------
const PVector2& PTreePanel::GetSize() const
{
	return _size;
}
// ----------------------------------------------------------------------------
void PTreePanel::SetPosition(const PVector2& pos)
{
	_position = pos;

	_headerRect.setPosition(pos);
	_headerText.setPosition(pos);
	_backgroundRect.setPosition(pos);
}
// ----------------------------------------------------------------------------
const PVector2& PTreePanel::GetPosition() const
{
	return _position;
}
// ----------------------------------------------------------------------------
void PTreePanel::DrawTree(PRenderTarget* renderTarget)
{
	_treeNodeVisual.Row = 0;
	DrawTreeLevel(renderTarget, _treeRoot);
}
// ----------------------------------------------------------------------------
void PTreePanel::DrawTreeLevel(PRenderTarget* renderTarget, const ITransformable* root, int level /*= 0*/)
{
	if (root == nullptr)
	{
		return;
	}

	PString name("Error_Name_Not_Found");
	if (const INameable* nameable = dynamic_cast<const INameable*>(root))
	{
		name = nameable->GetName();
	}

	_treeNodeVisual.Draw(renderTarget, level, name, _position + PVector2(10.f, 10.f));
	_treeNodeVisual.Row++;

	for (const ITransformable* child : root->GetChildren())
	{
		DrawTreeLevel(renderTarget, child, level + 1);
	}
}
// ----------------------------------------------------------------------------