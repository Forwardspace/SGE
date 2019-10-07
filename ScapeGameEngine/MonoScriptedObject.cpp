#ifdef SGE_MONO
#include "MonoScriptedObject.h"

#include "Renderer.h"
#include "MonoManager.h"

namespace sge {
	MonoScriptedObject::MonoScriptedObject() {
		type_ = ObjectType::MONO_SCRIPTED;

		Renderer::registerObject(this);
	}

	MonoScriptedObject::MonoScriptedObject(MonoObject* obj) {
		type_ = ObjectType::MONO_SCRIPTED;

		Renderer::registerObject(this);

		attachedObject_ = obj;
	}

	MonoScriptedObject::~MonoScriptedObject() {
		Renderer::removeObject(this);
	}

	void MonoScriptedObject::setPos(float x, float y, float z) {
		glm::vec3 delta(posX_ - x, posY_ - y, posZ_ - z);

		posX_ = x; posY_ = y; posZ_ = z; transformNeedsUpdating = true;

		for (auto child : children_) {
			child->setPos(child->pos() + delta);
		}
	}

	void MonoScriptedObject::setRot(float x, float y, float z) {
		glm::vec3 delta(posX_ - x, posY_ - y, posZ_ - z);

		rotX_ = x; rotY_ = y; rotZ_ = z; transformNeedsUpdating = true;

		for (auto child : children_) {
			child->setRot(child->rot() + delta);
		}
	}

	void MonoScriptedObject::setScl(float x, float y, float z) {
		glm::vec3 delta(posX_ - x, posY_ - y, posZ_ - z);

		scaleX_ = x; scaleY_ = y; scaleZ_ = z; transformNeedsUpdating = true;

		for (auto child : children_) {
			child->setScl(child->scl() + delta);
		}
	}

//	void MonoScriptedObject::attachScript(std::string objectManagerClass) {
//#ifdef DEBUG
//		if (attachedClass_) {
//			throw std::runtime_error("Warning: it's not really a good idea to change attached classes often!");
//		}
//#endif
//
//		attachedClass_ = mono_class_from_name(MonoManager::rootAssemblyImage(), "", objectManagerClass.c_str());
//		if (!attachedClass_) {
//			throw std::logic_error("ScapeMono: unable to find class: " + objectManagerClass);
//		}
//
//		//Allocate the required space for the instance of this Object,
//		//but initialize it later, after the constructor finishes
//		attachedClassInstance_ = mono_object_new(MonoManager::domain(), attachedClass_);
//	}

	void MonoScriptedObject::addChild(Object* obj) {
		children_.push_back(obj);
	}

	void MonoScriptedObject::removeChild(Object* obj) {
		children_.erase(std::find(children_.begin(), children_.end(), obj));
	}

	char* updateFName = "update";
	char* startupFName = "startup";
	char* cleanupFName = "cleanup";

	void MonoScriptedObject::render() {
		//Calls the update method in the attached class, and finds it if it's not yet found
		if (attachedObject_) {
			if (!updateMethod) {
				auto attachedClass = mono_object_get_class(attachedObject_);

				//Not yet inited, find the update() method in the class
				updateMethod = mono_class_get_method_from_name(attachedClass, updateFName, 0);
				if (!updateMethod) {
					throw std::logic_error(
						std::string("ScapeMono: unable to find update() in class: ") + mono_class_get_name(attachedClass)
					);
				}
			}

			MonoObject* exc = nullptr;
			mono_runtime_invoke(updateMethod, attachedObject_, nullptr, &exc);

			if (exc) {
				auto attachedClass = mono_object_get_class(attachedObject_);

				throw std::logic_error(
					std::string("ScapeMono: error when executing update() in class: ") + mono_class_get_name(attachedClass)
				);
			}
		}
	}
}
#endif