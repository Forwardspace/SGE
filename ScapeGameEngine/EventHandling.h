#pragma once
#include <iostream>
#include <map>
#include <string>
#include <functional>

//Usage (example for RedrawEvent):
//inside a class:
//public:
//	LISTENER;
//	...
//	EVENT_HANDLER(Redraw, {
//		someDrawFunctionOrSomething(this, event);
//	})
//	...
//
//then, inside the constructor:
//	MyObject(...) : ..., LISTENER_INIT, ... {
//		HANDLES_EVENT(Redraw);
//		...
//	}
//
//and if you don't want to listen to an event anymore:
//	DOES_NOT_HANDLE_EVENT(Redraw);
//
//if you want to raise a normal event:
//	RAISE_EVENT(someObject, RedrawEvent(true, false));
//
//and raising an event to the whole parent system:
//	RAISE_MASTER_EVENT(RedrawEvent(true, false, this))
//
//Q:
//What is this ugly C-like sorcery?
//
//A:
//These macros ease the use of event handling; no need to keep track of handler names and
//registration; just use these macros! (and don't look what's under the hood, please)
//
/////////////////////////////////////////////////////////////////////////////////////////

#define PRE_CONCAT(x, y) x##y
#define PRE_STRINGIFY(x) #x
#define PRE_STRINGIFY_IND(x) PRE_STRINGIFY(x)

//Use this in all constructors of new events
#define REGISTER_EVENT(x) name = PRE_STRINGIFY(x);

#define LISTENER EventHandler EH
#define LISTENER_INIT(forwardToChildrenFunct) \
	EH(EventHandler::EventHandler(std::bind(&forwardToChildrenFunct, this, std::placeholders::_1)))

#define MASTER_LISTENER EventHandler masterEH(nullptr);

//Basically, define the handler itself and then a lambda capturing "this" to pass it to the EventHandler
//The lambda casts the Event* to a specific event and passes it along to the handler
#define EVENT_HANDLER(eventName, handlerBody) \
	bool PRE_CONCAT(eventName, PreLambdaFunctionForm)(PRE_CONCAT(eventName, Event)* event) { \
		handlerBody \
	} \
	std::function<EVENT_HANDLER_SIG> eventName = [this](Event* e) { \
		PRE_CONCAT(eventName, Event)* event = dynamic_cast<PRE_CONCAT(eventName, Event)*>(e); \
		return PRE_CONCAT(eventName, PreLambdaFunctionForm)(event); \
	}
#define MASTER_EVENT_HANDLER(eventName, handlerBody) \
	bool PRE_CONCAT(master, eventName)(Event* genericEvent) { \
		PRE_CONCAT(eventName, Event)* event = dynamic_cast<PRE_CONCAT(eventName, Event)*>(genericEvent); \
		handlerBody \
	}

#define HANDLES_EVENT(eventName) \
	EH.handles(PRE_STRINGIFY_IND(PRE_CONCAT(eventName, Event) ), eventName)
#define DOES_NOT_HANDLE(eventName) \
	EH.doesNotHandle(PRE_STRINGIFY_IND(PRE_CONCAT(eventName, Event)))

#define MASTER_HANDLES_EVENT(eventName) \
	masterEH.handles(PRE_STRINGIFY_IND(PRE_CONCAT(eventName, Event)), PRE_CONCAT(master, eventName))
#define MASTER_DOES_NOT_HANDLE(eventName) \
	masterEH.doesNotHandle(PRE_STRINGIFY_IND(PRE_CONCAT(eventName, Event)))

#define RAISE_EVENT(object, event) object->EH.handle(event)
#define RAISE_MASTER_EVENT(event) masterEH.handle(event)

#define EVENT_HANDLER_SIG bool(Event*)

struct Event {
	std::string name = "Event";

	virtual ~Event() = default;
};

class EventHandler {
public:
	EventHandler(std::function<bool(Event*)> ftc) : forwardToChildren(ftc) {}

	inline void handles(std::string e, std::function<EVENT_HANDLER_SIG> h) { handlers[e] = h; }
	inline void doesNotHandle(std::string e) { handlers[e] = nullptr; }

	//Look up the handler for the event and call it if it exists
	inline bool handle(Event* e) {
		auto& a = handlers[e->name];

		bool res = true;
		if (a) {
			//Yes, it exists; call it
			res = a(e);
		}

		//(forwardToChildren can also be nullptr)
		if (forwardToChildren && !forwardToChildren(e)) {
			return false;
		}

		delete e;
		return res;
	}

private:
	std::map<std::string, std::function<EVENT_HANDLER_SIG>> handlers;
	std::function<bool(Event*)> forwardToChildren;
};