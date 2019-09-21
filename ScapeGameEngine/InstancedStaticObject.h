#pragma once
#include "stdheaders.h"
#include "Object.h"
#include "Mesh.h"
#include "TextureManager.h"
#include "Material.h"
#include "RigidPhysics.h"

namespace sge {
	class InstancedStaticObject;
	//Instances can only function inside of an InstancedObject
	class StaticObjectInstance : public Object {
	public:
		//Do not call
		void render() {
			throw std::runtime_error("Error: render was called on an object instance!");
		}
		//Do not call
		void setupVAO() {
			throw std::runtime_error("Error: setupVBOs was called on an object instance!");
		}

		//Rigid body from bounding box
		void setRigidBody(float mass);
		//Rigid body from custom shape
		void setRigidBody(float mass, BasicColliderType collider, glm::vec3 colliderDimensions);

		friend class InstancedStaticObject;
		InstancedStaticObject* parent;
	};

	//Stores instances of some object
	//Massively increases performance
	//Please construct only if the camera is set as this requires access
	//to the view matrix
	class InstancedStaticObject : public Object {
	public:
		InstancedStaticObject(fs::path filename, int numInstances, std::function<void(StaticObjectInstance&)> t, bool physics = false);
		InstancedStaticObject(Mesh& m, int numInstances, std::function<void(StaticObjectInstance&)> t, bool physics = false);
		InstancedStaticObject();

		~InstancedStaticObject();

		void setupVAO();
		void setMaterial(Material* tex) { mat_ = tex; }
		void setMesh(MeshInVBOs& mesh) { objectMesh_ = mesh; }

		//Used for physics, call this if you want to assign rigid bodies to instances
		void setMasterRigidBody() {
			physObj_ = new InstancedRigidPhysicsObject;
		}

		/////////////

		//Please allocate new instances on the heap
		void attachInstance(StaticObjectInstance& instance);
		void removeInstance(StaticObjectInstance& instance);
		
		/////////////

		//Renders all instances (use this if you can)
		void render();

		//void renderSpecificInstance(StaticObjectInstance& instance);
		//void renderSpecificInstance(int index);

		/////////////

		int getNumInstances() { return (int)instances_.size(); }
		StaticObjectInstance& getInstance(int index) { return *instances_[index]; }

		/////////////

		//Apply a function (transformation) to all instances
		void transformInstances(std::function<void(StaticObjectInstance&)> transformation);
		//Same as transformInstances but apply the transformation to only some instances
		void transformInstancesRange(
			int startIndex,
			int endIndex,
			std::function<void(StaticObjectInstance&)> transformation
		);

	private:
		void bindInstanceMVPs();
		//void renderSpecific(int index);
		void appendInstanceData(glm::mat4 MVP);

		std::vector<StaticObjectInstance*> instances_;

		Material* mat_;
		MeshInVBOs objectMesh_;

		friend class StaticObjectInstance;
		friend class InstancedRigidPhysicsObject;
	};
}