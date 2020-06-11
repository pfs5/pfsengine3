#pragma once
#include "Container/Array.h"
#include "Math/Vector2.h"
#include <SFML/Window.hpp>
// ----------------------------------------------------------------------------
class IMouseDownEventListener;
class IMouseUpEventListener;
class IMouseMovedEventListener;
class PWindow;
// ----------------------------------------------------------------------------
/**
 *	Class handles all out-of-game inputs. Provides static methods for accessing user inputs.
 */
class PInput 
{
public:
	static const int NUMBER_OF_KEYS = 256;

public:
	// ## Keys enum ##
	enum KeyCode : int 
	{
		A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
		Num0, Num1, Num2, Num3, Num4, Num5, Num6, Num7, Num8, Num9,
		Numpad0, Numpad1, Numpad2, Numpad3, Numpad4, Numpad5, Numpad6, Numpad7, Numpad8, Numpad9,
		LCTRL, RCTRL, LALT, RALT, SPACE, LSHIFT, RSHIFT, ENTER, ESCAPE,
		LARROW, RARROW, UARROW, DARROW,
		MOUSE_LEFT, MOUSE_RIGHT
	};

	// ## Static key methods ##
	/**
	 * Return true if the key is pressed in this frame, false otherwise.
	 */
	static bool GetKey(KeyCode key);

	/**
	 * Return true if the key has been pressed since the last frame.
	 */
	static bool GetKeyDown(KeyCode key);

	/**
	 * Return true if the key has been released since the last frame.
	 */
	static bool GetKeyUp(KeyCode key);

	/**
	 * Get current mouse position relative to window.
	 */
	static PVector2 GetMousePosition(const PWindow* window);

	// ## Methods called by the engine ##
	static void Update();

	static void RegisterMouseDownEventListener(IMouseDownEventListener* listener);
	static void UnregisterMouseDownEventListener(IMouseDownEventListener* listener);

	static void RegisterMouseUpEventListener(IMouseUpEventListener* listener);
	static void UnregisterMouseUpEventListener(IMouseUpEventListener* listener);

	static void RegisterMouseMovedEventListener(IMouseMovedEventListener* listener);
	static void UnregisterMouseMovedEventListener(IMouseMovedEventListener* listener);

private:
	static bool _key[NUMBER_OF_KEYS];
	static bool _keyDown[NUMBER_OF_KEYS];
	static bool _keyUp[NUMBER_OF_KEYS];

	static PArray <IMouseDownEventListener*> _mouseDownListeners;
	static PArray <IMouseUpEventListener*> _mouseUpListeners;
	static PArray <IMouseMovedEventListener*> _mouseMovedListeners;

private:
	static void UpdateKey(PInput::KeyCode key, sf::Keyboard::Key sfmlKeyCode);
	static void UpdateMouseButton(PInput::KeyCode key, sf::Mouse::Button sfmlKeyCode);
};
// ----------------------------------------------------------------------------