#pragma once

#include <iostream>
#include <string>

#include <mono/jit/jit.h>
#include <mono/metadata/assembly.h>
#include <mono/metadata/debug-helpers.h>

#pragma comment(lib, "mono-2.0-sgen.lib")

#include "RendererWrapper.h"
#include "ObjectWrapper.h"
#include "StaticObjectWrapper.h"
#include "CameraWrapper.h"
#include "MeshWrapper.h"
#include "UserInputWrapper.h"
#include "ScriptedObjectWrapper.h"
#include "TextureWrapper.h"
#include "MaterialWrapper.h"
#include "InstancedStaticObjectWrapper.h"

namespace sge {
	class MonoManager {
	public:
		MonoManager() = delete;		//Singleton
		~MonoManager() = delete;

		//Inits Mono and loads the compiled program from "filename"
		//It then calls the static function "void startup()"
		static void init(std::string filename = "InternalMain.dll");
		//Calls the static function "void cleanup()" and terminates Mono
		static void terminate();

		static inline void preFrame() { callStaticVoidFunction(getFunction("MainInternal::preFrame()")); }
		static inline void postFrame() { callStaticVoidFunction(getFunction("MainInternal::postFrame()")); }

		static inline MonoDomain* domain() { return domain_; }
		static inline MonoAssembly* rootAssembly() { return rootAssembly_; }
		static inline MonoImage* rootAssemblyImage() { return rootAssemblyImage_; }

	private:
		static void end();

		//Actually does the "wrapping" part
		//Registers the functions in C++ to be available in Mono
		//Add any wrappers' reg() functions here
		//It's not especially pretty, but it works
		static void registerInternalCalls();

		static MonoMethod* MonoManager::getFunction(std::string function);
		static void MonoManager::callStaticVoidFunction(MonoMethod* function);

		static MonoDomain* domain_;
		static MonoAssembly* rootAssembly_;
		static MonoImage* rootAssemblyImage_;
	};
}