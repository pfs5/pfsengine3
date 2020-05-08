#pragma once
#include "InputManager.h"
#include "Math/Vector2.h"
// ----------------------------------------------------------------------------
struct PMouseEvent
{
	bool WasConsumed;
};
// ----------------------------------------------------------------------------
struct PMouseDownEvent : public PMouseEvent
{
	PInput::KeyCode Key;
};
// ----------------------------------------------------------------------------
struct PMouseUpEvent : public PMouseEvent
{
	PInput::KeyCode Key;
};
// ----------------------------------------------------------------------------
struct PMouseMovedEvent
{

};
// ----------------------------------------------------------------------------
class IMouseEventListener
{

};
// ----------------------------------------------------------------------------
class IMouseDownEventListener : IMouseEventListener
{
public:
	/**
	 * Return true if event consumed.
	 */
	virtual bool OnMouseDownEvent(const PMouseDownEvent& eventData) = 0;
};
// ----------------------------------------------------------------------------
class IMouseUpEventListener : IMouseEventListener
{
public:
	/**
	 * Return true if event consumed.
	 */
	virtual bool OnMouseUpEvent(const PMouseUpEvent& eventData) = 0;
};
// ----------------------------------------------------------------------------
class IMouseMovedEventListener : IMouseEventListener
{
public:
	/**
	 * Return true if event consumed.
	 */
	virtual bool OnMouseMovedEvent(const PMouseMovedEvent& eventData) = 0;
};
// ----------------------------------------------------------------------------