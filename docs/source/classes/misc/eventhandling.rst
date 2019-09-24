EventHandling: .h
=================

Q:
What is this ugly C-like sorcery?

A:
This is a header-only implementation of an event library.
These macros and classes ease the use of event handling; no need to keep track of handler names and
registration; just use these macros! (and don't look at what's under the hood, please)

How to use it?
--------------

Well, if you don't have to, this is made just for GUI purposes. Else:

Defining new events
*******************

Events are structs inheriting from ``Event``.
To define a new one, simply inherit from it, add the required data and call the ``REGISTER_EVENT(x)`` like so:
::
	struct MouseDownEvent : public Event {
		MouseDownEvent(int x, int y) : mX(x), mY(y) { REGISTER_EVENT(MouseDownEvent) }

		int mX, mY;
	};

(note the placement of the ``REGISTER_EVENT(x)`` macro (it's in the constructor))

.. note:: Event names have to end with ``Event``; this is a technical limitation of the library.

Setting up listeners
********************

Every class that recieves events is a listener. To set up one, use the ``LISTENER`` and ``LISTENER_INIT(x)`` macros:
::
	class MyClass {
		LISTENER;
		...
		MyClass() : ..., LISTENER_INIT(forwardEventToChilldren), ... {}
	}

where ``forwardEventToChildren`` is a function with the signature of:
::
	bool forwardEventToChildren(Event* e);

which raises the event to all or some of the children of your listener class.

.. note:: Pass ``nullptr`` if you are a bad ``parent`` and don't want to pass events to children.

Setting up handlers
*******************

Simply use the ``EVENT_HANDLER(x, y)`` macros in your class' body:
::
	...
	EVENT_HANDLER(MouseDown, {
		event->something = Something();
		if (doSomethingWith(event)) {
			return true;
		}
		return false
	});

You can see that the name of the handler consists of the name of the event it handles without the ``Event`` part at the end.
For example, a handler that handles ``SomethingHappensEvent`` will pass the name ``SomethingHappens`` to ``EVENT_HANDLER(x, y)``.

The handler itself returns a bool. Return true if you were able to handle the event (or if you ignored it). The return value will
be forwarded back up as the return value of the ``RAISE_EVENT`` macro.

Inside the macro's block, you now have access to a pointer pre-casted to the required derived Event class named ``event``;
no need to ``dynamic_cast`` anything!

.. note::	To enable event handling for any specific event, in your constructor do:
		::
			...
			HANDLES_EVENT(MouseDown);
			...
			//To stop (temporarily or permanently):
			DOES_NOT_HANDLE_EVENT(MouseDown);

Raising Events
**************

Use the ``RAISE_EVENT(x, y)`` macro like so:
::
	RAISE_EVENT(someObjectInstancePointer, new MouseDown(132, 168));

The first argument is the object instance you wish to send the event to, and the second is the event itself.

Notes
-----

There is also a MASTER_* set of macros that allow whole parent systems to operate as listeners outside of any class.
Its usage is similar to the normal set of macros, so check the macros for details if you want to know more.