#include "PFSEngineWindow.h"
// ----------------------------------------------------------------------------
PWindow::PWindow(unsigned int width, unsigned int height, const PWindowParams& params/* = PWindowParams()*/)
{
	_sfmlWindow = new sf::RenderWindow(sf::VideoMode(width, height), params.Title);
}
// ----------------------------------------------------------------------------
PWindow::PWindow(unsigned int width, unsigned int height, PString title /*= PString()*/)
{
	_sfmlWindow = new sf::RenderWindow(sf::VideoMode(width, height), title);
}
// ----------------------------------------------------------------------------
PWindow::~PWindow()
{
	delete _sfmlWindow;
}
// ----------------------------------------------------------------------------
bool PWindow::IsOpen() const
{
	if (_sfmlWindow == nullptr)
	{
		return false;
	}

	return _sfmlWindow->isOpen();
}
// ----------------------------------------------------------------------------
bool PWindow::PollEvent(sf::Event& event)
{
	if (_sfmlWindow == nullptr)
	{
		return false;
	}

	return _sfmlWindow->pollEvent(event);
}
// ----------------------------------------------------------------------------
void PWindow::Close()
{
	if (_sfmlWindow == nullptr)
	{
		return;
	}

	_sfmlWindow->close();
}
// ----------------------------------------------------------------------------
PVector2 PWindow::GetSize()
{
	sf::Vector2u winSize = _sfmlWindow->getSize();
	return PVector2((float)winSize.x, (float)winSize.y);
}
// ----------------------------------------------------------------------------
void PWindow::SetPosition(const PVector2 pos)
{
	if (_sfmlWindow == nullptr)
	{
		return;
	}

	_sfmlWindow->setPosition(pos);
}
// ----------------------------------------------------------------------------
void PWindow::Clear(const PColor& clearColor/* = PColor(0, 0, 0, 255)*/)
{
	if (_sfmlWindow == nullptr)
	{
		return;
	}

	_sfmlWindow->clear(clearColor);
}
// ----------------------------------------------------------------------------
void PWindow::Draw(const sf::Drawable& drawable, const sf::RenderStates& states /*= sf::RenderStates::Default*/)
{
	if (_sfmlWindow == nullptr)
	{
		return;
	}

	_sfmlWindow->draw(drawable, states);
}
// ----------------------------------------------------------------------------
void PWindow::Display()
{
	if (_sfmlWindow == nullptr)
	{
		return;
	}

	_sfmlWindow->display();
}
// ----------------------------------------------------------------------------
const sf::RenderWindow* PWindow::GetSFMLWindow() const
{
	return _sfmlWindow;
}
// ----------------------------------------------------------------------------