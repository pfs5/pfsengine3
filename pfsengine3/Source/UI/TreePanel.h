#pragma once
#include "Input/MouseEventListener.h"
#include "Panel.h"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/Text.hpp"
#include "WorldObject/ObjectListeners.h"
// ----------------------------------------------------------------------------
class OWorldObject;
// ----------------------------------------------------------------------------
struct PTreeNodeVisual
{
	sf::Text NodeTextObj;
	sf::RectangleShape NodeSelectObj;

	int Row;
	float RowSpacing;
	float LevelSpacing;
	sf::Color SelectedColor;

	void Draw(PRenderTarget* renderTarget, int level, const PString& text, const PVector2& position, bool selected);
};
// ----------------------------------------------------------------------------
/**
 * UI panel for showing object trees.
 */
class PTreePanel : public PPanel, IWorldObjectEventListener
{
public:
	PTreePanel(PWindow* parentRenderWindow);

	void SetTreeRoot(OWorldObject* root);
	void SetTitle(const PString& title);

	OWorldObject* GetSelectedObject() const;

// PPanel
public:
	virtual void Draw(PRenderTarget* renderTarget) override;

	virtual void InitSize(const PVector2& size) override;
	virtual void SetPosition(const PVector2& pos) override;

protected:
	virtual void OnButtonClicked(int buttonId) override;
	virtual void OnPanelClicked() override;
	virtual void ClearButtons() override;

// IWorldObjectEventListener
public:
	virtual void OnWorldObjectCreated(OWorldObject* worldObject) override;
	virtual void OnWorldObjectDestroyed(OWorldObject* worldObject) override;
	virtual void OnWorldObjectParentChanged(OWorldObject* worldObject) override;

private:
	static const float PADDING_LEFT;
	static const float PADDING_RIGHT;
	static const float PADDING_TOP;

private:
	struct PTreePanelButtonNode
	{
		int ButtonRow;
		int ButtonTreeLevel;
		OWorldObject* WorldObject;

		bool Selected = false;
	};

private:
	OWorldObject* _treeRoot;

	sf::RectangleShape _headerRect;
	sf::Text _headerText;
	sf::RectangleShape _backgroundRect;

	PTreeNodeVisual _treeNodeVisual;

	PArray<PTreePanelButtonNode> _buttonNodes;

	OWorldObject* _selectedObject;

private:
	void DrawTree(PRenderTarget* renderTarget);

	void InitButtons(OWorldObject* root);
	void InitButtonsInternal(OWorldObject* root, int& row, int level = 0);
};
// ----------------------------------------------------------------------------