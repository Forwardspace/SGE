#pragma once

#include <mono/jit/jit.h>
#include <mono/metadata/assembly.h>
#include <mono/metadata/object.h>
#include <mono/metadata/environment.h>

#include "UserInputManager.h"

namespace sgewrap {
	class InputManager {
	public:
		static void reg() {
			mono_add_internal_call("ScapeInternal.InputManager::isPressed", isPressed);
		}

		static MonoBoolean isPressed(int key) {
			return sge::UserInputManager::pressed(key);
		}
	};
}