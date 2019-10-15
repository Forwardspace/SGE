#pragma once

#include <mono/jit/jit.h>
#include <mono/metadata/assembly.h>
#include <mono/metadata/object.h>
#include <mono/metadata/environment.h>

#include "Texture.h"

namespace sgewrap {
	class Texture {
	public:
		static void reg() {
			mono_add_internal_call("ScapeInternal.Texture::createFromFilename", createFromFilename);
			mono_add_internal_call("ScapeInternal.Texture::destroy", destroy);
		}

		static sge::Texture* createFromFilename(MonoString* str) {
			return new sge::Texture(mono_string_to_utf8(str));
		}

		static void destroy(sge::Texture* tex) {
			if (tex) {
				delete tex;
			}
		}
	};
}