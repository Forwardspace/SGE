#pragma once

#include <mono/jit/jit.h>
#include <mono/metadata/assembly.h>
#include <mono/metadata/object.h>
#include <mono/metadata/environment.h>

#include "StaticObject.h"
#include "Mesh.h"

namespace sgewrap {
	class StaticObject {
	public:
		static void reg() {
			mono_add_internal_call("ScapeInternal.StaticObject::create", create);
			mono_add_internal_call("ScapeInternal.StaticObject::createFromMesh", createFromMesh);
			mono_add_internal_call("ScapeInternal.StaticObject::destroy", destroy);

			mono_add_internal_call("ScapeInternal.StaticObject::setMaterial", setMaterial);

			mono_add_internal_call("ScapeInternal.StaticObject::getMeshInVBOs", getMeshInVBOs);
		}

		static sge::StaticObject* create(MonoString* filename) {
			return new sge::StaticObject(mono_string_to_utf8(filename));
		}

		static sge::StaticObject* createFromMesh(sge::Mesh* mesh) {
			return new sge::StaticObject(*mesh);
		}

		static void destroy(sge::StaticObject* object) {
			if (object) {
				delete object;
			}
		}

		static void setMaterial(sge::StaticObject* object, sge::Material* material) {
			object->setMaterial(material);
		}

		static sge::MeshInVBOs* getMeshInVBOs(sge::StaticObject* obj) {
			return new sge::MeshInVBOs(obj->mesh());
		}
	};
}