#pragma once

#include <mono/jit/jit.h>
#include <mono/metadata/assembly.h>
#include <mono/metadata/object.h>
#include <mono/metadata/environment.h>

#include "Camera.h"

namespace sge {
	extern MonoArray* newMonoDoubleArray(int numberOfElems);
}

namespace sgewrap {
	inline MonoArray* newMonoArray3(float x, float y, float z);

	class Camera {
	public:
		static void reg() {
			mono_add_internal_call("ScapeInternal.Camera::create", create);
			mono_add_internal_call("ScapeInternal.Camera::destory", destroy);

			mono_add_internal_call("ScapeInternal.Camera::setPos", setPos);
			mono_add_internal_call("ScapeInternal.Camera::pos", pos);

			mono_add_internal_call("ScapeInternal.Camera::setRot", setRot);
			mono_add_internal_call("ScapeInternal.Camera::rot", rot);
		}

		static void* create() {
			return (void*)new sge::Camera;
		}

		static void destroy(Camera* cam) {
			if (cam) {
				delete cam;
			}
		}

		static void setPos(sge::Camera* cam, float x, float y, float z) {
			if (cam) {
				//For some reason, the coords are inverted, correct that
				cam->setPos(-x, -y, -z);
			}
		}

		static MonoArray* pos(sge::Camera* cam) {
			if (!cam) {
				return nullptr;
			}

			auto pos = cam->pos();
			return newMonoArray3(-pos.x, -pos.y, -pos.z);
		}

		//

		static void setRot(sge::Camera* cam, float x, float y, float z) {
			if (cam) {
				cam->setRot(x, y, z);
			}
		}

		static MonoArray* rot(sge::Camera* cam) {
			if (!cam) {
				return nullptr;
			}

			auto rot = cam->rot();
			return newMonoArray3(rot.x, rot.y, rot.z);
		}
	};
}