#pragma once

#include <mono/jit/jit.h>
#include <mono/metadata/assembly.h>
#include <mono/metadata/object.h>
#include <mono/metadata/environment.h>

#include "Object.h"

namespace sge {
	extern MonoArray* newMonoDoubleArray(int numberOfElems);
}

namespace sgewrap {
	inline MonoArray* newMonoArray3(float x, float y, float z) {
		auto arr = sge::newMonoDoubleArray(3);

		mono_array_set(arr, float, 0, x);
		mono_array_set(arr, float, 1, y);
		mono_array_set(arr, float, 2, z);

		return arr;
	}

	class Object {
	public:
		static void reg() {
			mono_add_internal_call("ScapeInternal.Object::setPos", setPos);
			mono_add_internal_call("ScapeInternal.StaticObject::pos", pos);

			mono_add_internal_call("ScapeInternal.Object::setRot", setRot);
			mono_add_internal_call("ScapeInternal.StaticObject::rot", rot);

			mono_add_internal_call("ScapeInternal.Object::setScl", setRot);
			mono_add_internal_call("ScapeInternal.StaticObject::scl", rot);
		}

		static void setPos(sge::Object* obj, float x, float y, float z) {
			if (obj) {
				obj->setPos(x, y, z);
			}
		}

		static MonoArray* pos(sge::Object* obj) {
			if (!obj) {
				return nullptr;
			}

			auto pos = obj->pos();
			return newMonoArray3(pos.x, pos.y, pos.z);
		}

		//

		static void setRot(sge::Object* obj, float x, float y, float z) {
			if (obj) {
				obj->setRot(x, y, z);
			}
		}

		static MonoArray* rot(sge::Object* obj) {
			if (!obj) {
				return nullptr;
			}

			auto rot = obj->rot();
			return newMonoArray3(rot.x, rot.y, rot.z);
		}

		//

		static void setScl(sge::Object* obj, float x, float y, float z) {
			if (obj) {
				obj->setScl(x, y, z);
			}
		}

		static MonoArray* scl(sge::Object* obj) {
			if (!obj) {
				return nullptr;
			}

			auto scl = obj->scl();
			return newMonoArray3(scl.x, scl.y, scl.z);
		}
	};
}