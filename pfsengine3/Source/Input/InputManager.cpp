#include "InputManager.h"
#include "MouseEventListener.h"
#include "Rendering/PFSEngineWindow.h"
// ----------------------------------------------------------------------------
bool PInput::_key[PInput::NUMBER_OF_KEYS];
bool PInput::_keyDown[PInput::NUMBER_OF_KEYS];
bool PInput::_keyUp[PInput::NUMBER_OF_KEYS];

PArray <IMouseDownEventListener*> PInput::_mouseDownListeners;
PArray <IMouseUpEventListener*> PInput::_mouseUpListeners;
PArray <IMouseMovedEventListener*> PInput::_mouseMovedListeners;
// ----------------------------------------------------------------------------
bool PInput::GetKey(KeyCode key) 
{
	return _key[static_cast<int>(key)];
}
// ----------------------------------------------------------------------------
bool PInput::GetKeyDown(KeyCode key) 
{
	return _keyDown[static_cast<int>(key)];
}
// ----------------------------------------------------------------------------
bool PInput::GetKeyUp(KeyCode key) 
{
	return _keyUp[static_cast<int>(key)];
}
// ----------------------------------------------------------------------------
PVector2 PInput::GetMousePosition(const PWindow* window)
{
	return PVector2(sf::Mouse::getPosition(*window->GetSFMLWindow()));
}
// ----------------------------------------------------------------------------
void PInput::Update() 
{
	UpdateKey(KeyCode::A, sf::Keyboard::A);
	UpdateKey(KeyCode::B, sf::Keyboard::B);
	UpdateKey(KeyCode::C, sf::Keyboard::C);
	UpdateKey(KeyCode::D, sf::Keyboard::D);
	UpdateKey(KeyCode::E, sf::Keyboard::E);
	UpdateKey(KeyCode::F, sf::Keyboard::F);
	UpdateKey(KeyCode::G, sf::Keyboard::G);
	UpdateKey(KeyCode::H, sf::Keyboard::H);
	UpdateKey(KeyCode::I, sf::Keyboard::I);
	UpdateKey(KeyCode::J, sf::Keyboard::J);
	UpdateKey(KeyCode::K, sf::Keyboard::K);
	UpdateKey(KeyCode::L, sf::Keyboard::L);
	UpdateKey(KeyCode::M, sf::Keyboard::M);
	UpdateKey(KeyCode::N, sf::Keyboard::N);
	UpdateKey(KeyCode::O, sf::Keyboard::O);
	UpdateKey(KeyCode::P, sf::Keyboard::P);
	UpdateKey(KeyCode::R, sf::Keyboard::R);
	UpdateKey(KeyCode::S, sf::Keyboard::S);
	UpdateKey(KeyCode::T, sf::Keyboard::T);
	UpdateKey(KeyCode::U, sf::Keyboard::U);
	UpdateKey(KeyCode::V, sf::Keyboard::V);
	UpdateKey(KeyCode::W, sf::Keyboard::W);
	UpdateKey(KeyCode::X, sf::Keyboard::X);
	UpdateKey(KeyCode::Y, sf::Keyboard::Y);
	UpdateKey(KeyCode::Z, sf::Keyboard::Z);

	UpdateKey(KeyCode::Num0, sf::Keyboard::Num0);
	UpdateKey(KeyCode::Num1, sf::Keyboard::Num1);
	UpdateKey(KeyCode::Num2, sf::Keyboard::Num2);
	UpdateKey(KeyCode::Num3, sf::Keyboard::Num3);
	UpdateKey(KeyCode::Num4, sf::Keyboard::Num4);
	UpdateKey(KeyCode::Num5, sf::Keyboard::Num5);
	UpdateKey(KeyCode::Num6, sf::Keyboard::Num6);
	UpdateKey(KeyCode::Num7, sf::Keyboard::Num7);
	UpdateKey(KeyCode::Num8, sf::Keyboard::Num8);
	UpdateKey(KeyCode::Num9, sf::Keyboard::Num9);

	UpdateKey(KeyCode::Numpad0, sf::Keyboard::Numpad0);
	UpdateKey(KeyCode::Numpad1, sf::Keyboard::Numpad1);
	UpdateKey(KeyCode::Numpad2, sf::Keyboard::Numpad2);
	UpdateKey(KeyCode::Numpad3, sf::Keyboard::Numpad3);
	UpdateKey(KeyCode::Numpad4, sf::Keyboard::Numpad4);
	UpdateKey(KeyCode::Numpad5, sf::Keyboard::Numpad5);
	UpdateKey(KeyCode::Numpad6, sf::Keyboard::Numpad6);
	UpdateKey(KeyCode::Numpad7, sf::Keyboard::Numpad7);
	UpdateKey(KeyCode::Numpad8, sf::Keyboard::Numpad8);
	UpdateKey(KeyCode::Numpad9, sf::Keyboard::Numpad9);

	UpdateKey(KeyCode::LCTRL, sf::Keyboard::LControl);
	UpdateKey(KeyCode::RCTRL, sf::Keyboard::RControl);
	UpdateKey(KeyCode::LALT, sf::Keyboard::LAlt);
	UpdateKey(KeyCode::RALT, sf::Keyboard::RAlt);
	UpdateKey(KeyCode::SPACE, sf::Keyboard::Space);
	UpdateKey(KeyCode::LSHIFT, sf::Keyboard::LShift);
	UpdateKey(KeyCode::RSHIFT, sf::Keyboard::RShift);
	UpdateKey(KeyCode::ENTER, sf::Keyboard::Return);
	UpdateKey(KeyCode::ESCAPE, sf::Keyboard::Escape);

	UpdateKey(KeyCode::LARROW, sf::Keyboard::Left);
	UpdateKey(KeyCode::RARROW, sf::Keyboard::Right);
	UpdateKey(KeyCode::UARROW, sf::Keyboard::Up);
	UpdateKey(KeyCode::DARROW, sf::Keyboard::Down);

	UpdateMouseButton(KeyCode::MOUSE_LEFT, sf::Mouse::Button::Left);
	UpdateMouseButton(KeyCode::MOUSE_RIGHT, sf::Mouse::Button::Right);
}
// ----------------------------------------------------------------------------
void PInput::RegisterMouseDownEventListener(IMouseDownEventListener* listener)
{
	if (listener == nullptr)
	{
		return;
	}

	_mouseDownListeners.Add(listener);
}
// ----------------------------------------------------------------------------
void PInput::UnregisterMouseDownEventListener(IMouseDownEventListener* listener)
{
	if (listener == nullptr)
	{
		return;
	}

	_mouseDownListeners.RemoveSwap(listener);
}
// ----------------------------------------------------------------------------
void PInput::RegisterMouseUpEventListener(IMouseUpEventListener* listener)
{
	if (listener == nullptr)
	{
		return;
	}

	_mouseUpListeners.Add(listener);
}
// ----------------------------------------------------------------------------
void PInput::UnregisterMouseUpEventListener(IMouseUpEventListener* listener)
{
	if (listener == nullptr)
	{
		return;
	}

	_mouseUpListeners.RemoveSwap(listener);
}
// ----------------------------------------------------------------------------
void PInput::RegisterMouseMovedEventListener(IMouseMovedEventListener* listener)
{
	if (listener == nullptr)
	{
		return;
	}

	_mouseMovedListeners.Add(listener);
}
// ----------------------------------------------------------------------------
void PInput::UnregisterMouseMovedEventListener(IMouseMovedEventListener* listener)
{
	if (listener == nullptr)
	{
		return;
	}

	_mouseMovedListeners.RemoveSwap(listener);
}
// ----------------------------------------------------------------------------
void PInput::UpdateKey(PInput::KeyCode key, sf::Keyboard::Key sfmlKeyCode) 
{
	bool newKeyValue = sf::Keyboard::isKeyPressed(sfmlKeyCode);
	int keyIndex = static_cast<int>(key);

	// check key down and key up
	bool frameDifference = _key[keyIndex] != newKeyValue;
	_keyDown[keyIndex] = (newKeyValue) ? frameDifference : false;
	_keyUp[keyIndex] = (!newKeyValue) ? frameDifference : false;

	// update key value
	_key[keyIndex] = newKeyValue;
}
// ----------------------------------------------------------------------------
void PInput::UpdateMouseButton(KeyCode key, sf::Mouse::Button sfmlKeyCode)
{
	bool newKeyValue = sf::Mouse::isButtonPressed(sfmlKeyCode);
	int keyIndex = static_cast<int>(key);

	// check key down and key up
	bool frameDifference = _key[keyIndex] != newKeyValue;
	bool keyUp = (newKeyValue) ? frameDifference : false;
	bool keyDown = (!newKeyValue) ? frameDifference : false;

	_keyDown[keyIndex] = keyUp;
	_keyUp[keyIndex] = keyDown;

	// update key value
	_key[keyIndex] = newKeyValue;

	// update mouse event listeners
	if (keyDown)
	{
		PMouseDownEvent eventData;
		eventData.WasConsumed = false;
		eventData.Key = key;
		for (IMouseDownEventListener* listener : _mouseDownListeners)
		{
			eventData.WasConsumed |= listener->OnMouseDownEvent(eventData);
		}
	}

	if (keyUp)
	{
		PMouseUpEvent eventData;
		eventData.WasConsumed = false;
		eventData.Key = key;
		for (IMouseUpEventListener* listener : _mouseUpListeners)
		{
			eventData.WasConsumed |= listener->OnMouseUpEvent(eventData);
		}
	}
}
// ----------------------------------------------------------------------------