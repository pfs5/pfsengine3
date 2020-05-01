#pragma once
#include "Panel.h"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/Text.hpp"
// ----------------------------------------------------------------------------
class ITransformable;
// ----------------------------------------------------------------------------
struct PTreeNodeVisual
{
	sf::Text NodeTextObj;
	int Row;
	float RowSpacing;
	float LevelSpacing;

	void Draw(PRenderTarget* renderTarget, int level, const PString& text, const PVector2& position);
};
// ----------------------------------------------------------------------------
class PTreePanel : public PPanel
{
public:
	PTreePanel();

	void SetTreeRoot(const ITransformable* root);
	void SetTitle(const PString& title);

// PPanel
public:
	virtual void Draw(PRenderTarget* renderTarget);

	virtual void SetSize(const PVector2& size);
	virtual const PVector2& GetSize() const;

	virtual void SetPosition(const PVector2& pos);
	virtual const PVector2& GetPosition() const;

private:
	const ITransformable* _treeRoot;

	PVector2 _size;
	PVector2 _position;

	sf::RectangleShape _headerRect;
	sf::Text _headerText;
	sf::RectangleShape _backgroundRect;

	PTreeNodeVisual _treeNodeVisual;

private:
	void DrawTree(PRenderTarget* renderTarget);
	void DrawTreeLevel(PRenderTarget* renderTarget, const ITransformable* root, int level = 0);

};
// ----------------------------------------------------------------------------