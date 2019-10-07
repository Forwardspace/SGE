#pragma once
#include "stdheaders.h"
#include <mono/jit/jit.h>
#include <mono/metadata/assembly.h>

#include "Object.h"

namespace sgewrap {
	class ScriptedObject;
}

namespace sge {
	//A script managing zero or more Objects from Mono C# code
	//Warning: when changing the transform of a MonoScriptedObject in C++,
	//you need to change the transform of each of its children objects
	class MonoScriptedObject : public Object {
	public:
		//Scripted object from the name of the class that manages it in Mono
		MonoScriptedObject();
		MonoScriptedObject(MonoObject* object);
		~MonoScriptedObject();

		//void attachScript(std::string objectManagerClass);

		//Override the transform functions as ScriptedObjects need to transform children Objects as well
		void setPos(float x, float y, float z);
		inline void setPos(glm::vec3 v) { setPos(v.x, v.y, v.z); }

		void setRot(float x, float y, float z);
		inline void setRot(glm::vec3 v) { setRot(v.x, v.y, v.z); }

		void setScl(float x, float y, float z);
		inline void setScl(glm::vec3 v) { setScl(v.x, v.y, v.z); }

		void addChild(Object* obj);
		void removeChild(Object* obj);

		void render();
		void setupVAO() {}

	private:
		/*MonoClass* attachedClass_ = nullptr;
		MonoObject* attachedClassInstance_ = nullptr;*/
		MonoObject* attachedObject_ = nullptr;

		//Cache the update method because it's called about
		//60 times/second
		MonoMethod* updateMethod = nullptr;

		//Scripted objects can spawn children - else they would be nearly pointless
		std::vector<Object*> children_;

		friend class sgewrap::ScriptedObject;
	};
}
