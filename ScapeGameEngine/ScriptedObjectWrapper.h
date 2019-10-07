#pragma once

#include <mono/jit/jit.h>
#include <mono/metadata/assembly.h>
#include <mono/metadata/object.h>
#include <mono/metadata/environment.h>

#include "MonoScriptedObject.h"

namespace sgewrap {
	class ScriptedObject {
	public:
		static void reg() {
			mono_add_internal_call("ScapeInternal.ScriptedObject::createEmpty", createEmpty);
			mono_add_internal_call("ScapeInternal.ScriptedObject::createFromObject", createFromObject);

			mono_add_internal_call("ScapeInternal.ScriptedObject::destroy", destroy);

			mono_add_internal_call("ScapeInternal.ScriptedObject::setPos", setPos);
			mono_add_internal_call("ScapeInternal.ScriptedObject::setRot", setRot);
			mono_add_internal_call("ScapeInternal.ScriptedObject::setScl", setScl);

			mono_add_internal_call("ScapeInternal.ScriptedObject::addChild", addChild);
			mono_add_internal_call("ScapeInternal.ScriptedObject::removeChild", removeChild);
		}

		static sge::MonoScriptedObject* createFromObject(MonoObject* obj) {
			return new sge::MonoScriptedObject(obj);
		}

		static sge::MonoScriptedObject* createEmpty() {
			return new sge::MonoScriptedObject;
		}

		static void destroy(sge::MonoScriptedObject* object) {
			if (object) {
				delete object;
			}
		}

		static void addChild(sge::MonoScriptedObject* object, sge::Object* child) {
			object->addChild(child);
		}

		static void removeChild(sge::MonoScriptedObject* object, sge::Object* child) {
			object->removeChild(child);
		}

		static void setPos(sge::MonoScriptedObject* object, float x, float y, float z) {
			object->setPos(x, y, z);
		}

		static void setRot(sge::MonoScriptedObject* object, float x, float y, float z) {
			object->setRot(x, y, z);
		}

		static void setScl(sge::MonoScriptedObject* object, float x, float y, float z) {
			object->setScl(x, y, z);
		}
	};
}