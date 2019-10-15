#pragma once

#include <mono/jit/jit.h>
#include <mono/metadata/assembly.h>
#include <mono/metadata/object.h>
#include <mono/metadata/environment.h>

#include "Material.h"

namespace sgewrap {
	class Material {
	public:
		static void reg() {
			mono_add_internal_call("ScapeInternal.Material::createEmpty", createEmpty);
			mono_add_internal_call("ScapeInternal.Material::createFromTextures", createFromTextures);
			mono_add_internal_call("ScapeInternal.Material::destroy", destroy);
		}

		static sge::Material* createEmpty() {
			return new sge::Material;
		}

		static sge::Material* createFromTextures(MonoArray* types, MonoArray* textures) {
			std::vector<std::pair<sge::Texture*, std::string>> pairs;

			auto size = mono_array_length(types);
			//Assume the textures array is of the same length - should be checked in Mono

			for (int i = 0; i < size; i++) {
				std::string type = std::string(mono_string_to_utf8(mono_array_get(types, MonoString*, i)));
				sge::Texture* texture = mono_array_get(textures, sge::Texture*, i);

				pairs.push_back(std::pair<sge::Texture*, std::string>(texture, type));
			}

			return new sge::Material(pairs);
		}

		static void destroy(sge::Material* mat) {
			if (mat) {
				delete mat;
			}
		}
	};
}