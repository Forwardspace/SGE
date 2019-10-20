#pragma once

#include <mono/jit/jit.h>
#include <mono/metadata/assembly.h>
#include <mono/metadata/object.h>
#include <mono/metadata/environment.h>

#include "Mesh.h"

namespace sgewrap {
	class Mesh {
	public:
		static void reg() {
			mono_add_internal_call("ScapeInternal.Mesh::create", create);
			mono_add_internal_call("ScapeInternal.Mesh::destroy", destroy);

			mono_add_internal_call("ScapeInternal.MeshInVBOs::destroy", destroyMeshInVBOs);
		}

		static sge::Mesh* create(MonoString* filename) {
			return new sge::Mesh(fs::path(mono_string_to_utf8(filename)));
		}

		static void destroy(sge::Mesh* mesh) {
			if (mesh) {
				delete mesh;
			}
		}

		static void destroyMeshInVBOs(sge::MeshInVBOs* mesh) {
			if (mesh) {
				delete mesh;
			}
		}
	};
}