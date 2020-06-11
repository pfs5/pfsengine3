#include "Container/PFSEngineColor.h"
#include "InspectorPanel.h"
#include "MemoryManagement/ResourceManager.h"
#include "Math/Vector2.h"
#include "Rendering/RenderTarget.h"
#include "WorldObject/WorldObject.h"
// ----------------------------------------------------------------------------
PInspectorPanel::PInspectorPanel(PWindow* parentRenderWindow):
	PPanel(parentRenderWindow)
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
}
// ----------------------------------------------------------------------------
void PInspectorPanel::SetSelectedObject(OWorldObject* object)
{
	_selectedObject = object;
}
// ----------------------------------------------------------------------------
void PInspectorPanel::Draw(PRenderTarget* renderTarget)
{
	PVector2 position = GetPosition();

	_headerText.setString(_selectedObject != nullptr ? _selectedObject->GetName() : PString());

	_headerRect.setPosition(position);
	_backgroundRect.setPosition(position);
	_headerText.setPosition(position);

	renderTarget->Draw(_headerRect);
	renderTarget->Draw(_backgroundRect);
	renderTarget->Draw(_headerText);

	DrawObjectData();
}
// ----------------------------------------------------------------------------
void PInspectorPanel::InitSize(const PVector2& size)
{
	PPanel::InitSize(size);

	_headerRect.setSize(PVector2(size.X, _headerRect.getSize().y));
	_backgroundRect.setSize(size);
}
// ----------------------------------------------------------------------------
void PInspectorPanel::DrawObjectData()
{

}
// ----------------------------------------------------------------------------