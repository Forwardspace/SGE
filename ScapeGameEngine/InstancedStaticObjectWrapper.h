#pragma once

#include <mono/jit/jit.h>
#include <mono/metadata/assembly.h>
#include <mono/metadata/object.h>
#include <mono/metadata/environment.h>

#include "InstancedStaticObject.h"

namespace sge {
	MonoArray* newMonoIntPtrArray(int numberOfElems);
}

namespace sgewrap {
	class InstancedStaticObject {
	public:
		static void reg() {
			mono_add_internal_call("ScapeInternal.InstancedStaticObject::create", create);
			mono_add_internal_call("ScapeInternal.InstancedStaticObject::createFromMesh", createFromMesh);
			mono_add_internal_call("ScapeInternal.InstancedStaticObject::destroy", destroy);

			mono_add_internal_call("ScapeInternal.InstancedStaticObject::attachInstance", attachInstance);
			mono_add_internal_call("ScapeInternal.InstancedStaticObject::removeInstance", removeInstance);
			mono_add_internal_call("ScapeInternal.InstancedStaticObject::removeInstanceAt", removeInstanceAt);

			mono_add_internal_call("ScapeInternal.InstancedStaticObject::setMaterial", setMaterial);

			mono_add_internal_call("ScapeInternal.InstancedStaticObject::getMeshInVBOs", getMeshInVBOs);
			mono_add_internal_call("ScapeInternal.InstancedStaticObject::getInstances", getInstances);
			///

			/*mono_add_internal_call("ScapeInternal.StaticObjectInstance::setPos", setPos);
			mono_add_internal_call("ScapeInternal.StaticObjectInstance::setRot", setRot);
			mono_add_internal_call("ScapeInternal.StaticObjectInstance::setScl", setScl);*/
		}

		static sge::InstancedStaticObject* create(MonoString* filename, int numInstances, bool physics) {
			return new sge::InstancedStaticObject(fs::path(mono_string_to_utf8(filename)), numInstances, physics);
		}

		static sge::InstancedStaticObject* createFromMesh(sge::Mesh* m, int numInstances, bool physics) {
			return new sge::InstancedStaticObject(*m, numInstances, physics);
		}

		static void destroy(sge::InstancedStaticObject* object) {
			if (object) {
				delete object;
			}
		}

		static void attachInstance(sge::InstancedStaticObject* object, sge::StaticObjectInstance* inst) {
			object->attachInstance(*inst);
		}

		static void removeInstance(sge::InstancedStaticObject* object, sge::StaticObjectInstance* inst) {
			object->removeInstance(*inst);
		}

		static void removeInstanceAt(sge::InstancedStaticObject* object, int index) {
			object->instances_.erase(object->instances_.begin() + index);
		}

		static void setMaterial(sge::InstancedStaticObject* object, sge::Material* mat) {
			object->setMaterial(mat);
		}

		static sge::MeshInVBOs* getMeshInVBOs(sge::InstancedStaticObject* obj) {
			return new sge::MeshInVBOs(obj->mesh());
		}

		static MonoArray* getInstances(sge::InstancedStaticObject* obj) {
			MonoArray* arr = sge::newMonoIntPtrArray((int)obj->instances_.size());

			for (int i = 0; i < obj->instances_.size(); i++) {
				mono_array_set(arr, sge::StaticObjectInstance*, i, obj->instances_[i]);
			}

			return arr;
		}
	};
}