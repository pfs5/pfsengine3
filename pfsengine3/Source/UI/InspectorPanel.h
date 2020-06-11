#pragma once
#include "Panel.h"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/Text.hpp"
// ----------------------------------------------------------------------------
class OWorldObject;
// ----------------------------------------------------------------------------
/**
 * Generic UI panel with basic functionality.
 */
class PInspectorPanel : public PPanel
{
public:
	PInspectorPanel(PWindow* parentRenderWindow);

	void SetSelectedObject(OWorldObject* object);

// PPanel
public:
	virtual void Draw(PRenderTarget* renderTarget) override;
	virtual void InitSize(const PVector2& size) override;

private:
	sf::RectangleShape _headerRect;
	sf::Text _headerText;
	sf::RectangleShape _backgroundRect;

	OWorldObject* _selectedObject;

private:
	void DrawObjectData();
};
// ----------------------------------------------------------------------------