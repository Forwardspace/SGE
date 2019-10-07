#pragma once

#include <mono/jit/jit.h>
#include <mono/metadata/assembly.h>
#include <mono/metadata/object.h>
#include <mono/metadata/environment.h>

#include "Renderer.h"

namespace sgewrap {
	class Renderer {
	public:
		Renderer() = delete;

		static void reg() {
			mono_add_internal_call("ScapeInternal.Renderer::init", init);
			mono_add_internal_call("ScapeInternal.Renderer::terminate", terminate);

			mono_add_internal_call("ScapeInternal.Renderer::deltaTime", deltaTime);

			mono_add_internal_call("ScapeInternal.Renderer::currentCamera", currentCamera);
		}

		static void init(uint32_t w, uint32_t h, MonoString* name, MonoBoolean fullscreen) {
			sge::Renderer::init(w, h, mono_string_to_utf8(name), fullscreen);
		}

		static void terminate() {
			sge::Renderer::terminate();
		}

		//This is not exactly a Renderer function, but for the sake of avoiding
		//global variables, it's here anyway
		static double deltaTime() {
			return sge::deltaTime;
		}

		static void* currentCamera() {
			return (void*)sge::Renderer::currentCamera();
		}
	};
}