#pragma once

#include <mono/jit/jit.h>
#include <mono/metadata/assembly.h>
#include <mono/metadata/object.h>
#include <mono/metadata/environment.h>

#include "StaticObject.h"

namespace sgewrap {
	class StaticObject {
	public:
		static void reg() {
			mono_add_internal_call("ScapeInternal.StaticObject::create", create);
			mono_add_internal_call("ScapeInternal.StaticObject::destroy", destroy);

			mono_add_internal_call("ScapeInternal.StaticObject::setMaterial", setMaterial);
		}

		static sge::StaticObject* create(MonoString* filename) {
			return new sge::StaticObject(mono_string_to_utf8(filename));
		}

		static void destroy(sge::StaticObject* object) {
			if (object) {
				delete object;
			}
		}

		static void setMaterial(sge::StaticObject* object, sge::Material* material) {
			object->setMaterial(material);
		}
	};
}