#include "MonoManager.h"

namespace sge {
	MonoDomain* MonoManager::domain_ = nullptr;
	MonoAssembly* MonoManager::rootAssembly_ = nullptr;
	MonoImage* MonoManager::rootAssemblyImage_ = nullptr;

	const std::string monoDomainName = "Scape";

	void MonoManager::init(std::string filename) {
		domain_ = mono_jit_init(monoDomainName.c_str());
		rootAssembly_ = mono_domain_assembly_open(domain_, filename.c_str());
		rootAssemblyImage_ = mono_assembly_get_image(rootAssembly_);

		if (!rootAssembly_) {
			throw std::runtime_error("Unable to open the main mono assembly: " + filename);
		}

		registerInternalCalls();

		//Let the games begin!
		callStaticVoidFunction(getFunction("MainInternal::Main"));
	}

	void MonoManager::terminate() {
		//Aaaand we're done.
		end();

		mono_jit_cleanup(domain_);
	}

	const std::string terminateFunct = "cleanup";

	void MonoManager::end() {
		callStaticVoidFunction(getFunction(terminateFunct));
	}

	///

	void MonoManager::registerInternalCalls() {
		sgewrap::Renderer::reg();
		sgewrap::Object::reg();
		sgewrap::StaticObject::reg();
		sgewrap::Camera::reg();
		sgewrap::Mesh::reg();
		sgewrap::InputManager::reg();
		sgewrap::ScriptedObject::reg();
	}

	///

	MonoMethod* MonoManager::getFunction(std::string function) {
		auto functDesc = mono_method_desc_new(function.c_str(), true);
		auto method = mono_method_desc_search_in_image(functDesc, mono_assembly_get_image(rootAssembly_));

		return method;
	}
	MonoMethod* MonoManager::callStaticVoidFunction(MonoMethod* function) {
		MonoObject* exception = nullptr;
		mono_runtime_invoke(function, nullptr, nullptr, &exception);

		if (exception) {
			throw std::runtime_error("Error: unhandled exception in Mono code!");
		}
	}

	MonoArray* newMonoDoubleArray(int numberOfElems) {
		return mono_array_new(MonoManager::domain(), mono_get_single_class(), numberOfElems);
	}
}