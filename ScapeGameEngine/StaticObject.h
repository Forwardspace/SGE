#pragma once
#include "stdheaders.h"
#include "Object.h"
#include "Mesh.h"
#include "Material.h"
#include "TextureManager.h"
#include "Renderer.h"
#include "ShaderManager.h"
#include "RigidPhysics.h"

namespace sge {
	class StaticObject : public Object {
	public:
		StaticObject();
		StaticObject(Mesh& msh);
		//Object from a file: loads the first mesh from the
		//specified file.
		StaticObject(fs::path filename);
		~StaticObject();

		void setMesh(MeshInVBOs& mesh) { objectMesh_ = mesh; }
		void setMaterial(Material* tex) { mat_ = tex; }

		//Rigid body from bounding box
		void setRigidBody(float mass);
		//Rigid body from custom shape
		void setRigidBody(float mass, BasicColliderType collider, glm::vec3 colliderDimensions);

		MeshInVBOs mesh() { return objectMesh_; }

		void render();
		void setupVAO();

		//Used for physics, optional
		bool destructRigidBody_ = true;

		Material* mat_ = nullptr;;
		MeshInVBOs objectMesh_;
	};
}