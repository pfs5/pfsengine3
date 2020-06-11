#pragma once
#include "Math/Vector2.h"
#include "Misc/PFSEngineString.h"
#include "RenderTarget.h"
#include "SFML/Graphics/RenderWindow.hpp"
// ----------------------------------------------------------------------------
struct PWindowParams
{
	PString Title;
	unsigned int AntiAliasingLevel = 0;
};
// ----------------------------------------------------------------------------
class PWindow : public PRenderTarget
{
public:
	static PWindow* MainWindow;

public:
	PWindow(unsigned int width, unsigned int height, const PWindowParams& params = PWindowParams());
	PWindow(unsigned int width, unsigned int height, PString title = PString());
	~PWindow();

	bool IsOpen() const;
	bool PollEvent(sf::Event& event);
	void Close();

	PVector2 GetSize() const;
	void SetPosition(const PVector2 pos);
	bool IsPointInWindow(const PVector2& point) const;

	// PRenderTarget
	virtual void Clear(const PColor& clearColor = PColor(0, 0, 0, 255)) override;
	virtual void Draw(const sf::Drawable& drawable, const sf::RenderStates& states = sf::RenderStates::Default) override;
	virtual void Display() override;

	const sf::RenderWindow* GetSFMLWindow() const;

public:
	inline operator sf::RenderWindow&() const;

private:
	sf::RenderWindow* _sfmlWindow;
};
// ----------------------------------------------------------------------------
PWindow::operator sf::RenderWindow&() const
{
	return *_sfmlWindow;
}
// ----------------------------------------------------------------------------