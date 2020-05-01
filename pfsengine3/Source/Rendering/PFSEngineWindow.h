#pragma once
#include "Math/Vector2.h"
#include "Misc/PFSEngineString.h"
#include "RenderTarget.h"
#include "SFML/Graphics/RenderWindow.hpp"
// ----------------------------------------------------------------------------
struct PWindowParams
{
	PString Title;
};
// ----------------------------------------------------------------------------
class PWindow : public PRenderTarget
{
public:
	PWindow(unsigned int width, unsigned int height, const PWindowParams& params = PWindowParams());
	PWindow(unsigned int width, unsigned int height, PString title = PString());
	~PWindow();

	bool IsOpen() const;
	bool PollEvent(sf::Event& event);
	void Close();

	PVector2 GetSize();
	void SetPosition(const PVector2 pos);

	// PRenderTarget
	virtual void Clear(const PColor& clearColor = PColor(0, 0, 0, 255)) override;
	virtual void Draw(const sf::Drawable& drawable, const sf::RenderStates& states = sf::RenderStates::Default) override;
	virtual void Display() override;

private:
	sf::RenderWindow *_sfmlWindow;
};
// ----------------------------------------------------------------------------