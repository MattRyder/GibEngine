#pragma once

#include <glm/gtx/quaternion.hpp>

#include "Mesh.h"
#include "EnumFlags.h"
#include "world/DatabaseRecord.h"

namespace GibEngine
{
	namespace Scene
	{
		const glm::vec3 X_AXIS = glm::vec3(1, 0, 0);
		const glm::vec3 Y_AXIS = glm::vec3(0, 1, 0);
		const glm::vec3 Z_AXIS = glm::vec3(0, 0, 1);

		class Node
		{
		public:
			enum class Flags : int
			{
				// Nothing special
				DEFAULT = 1 << 1,

				// Defines this node as the root of a mesh
				MESH_ROOT = 1 << 2
			};

			Node(const char* name);
			Node(const char* name, World::DatabaseRecord* dbRecord);

			World::DatabaseRecord* GetDatabaseRecord() const;
			Entity* GetEntity() const;
			glm::mat4 GetWorldTransform() const;
			glm::mat4 GetLocalTransform() const;

			Flags GetFlags() const { return flags; }
			const char* GetName() const;
			const glm::quat GetRotation() const;
			size_t GetChildNodeCount() const;
			std::vector<Node*>::const_iterator GetChildNodesBegin() const { return childNodes.begin(); }
			std::vector<Node*>::const_iterator GetChildNodesEnd() const { return childNodes.end(); }

			bool IsRootNode() const;

			void AddChildNode(Node* child);

			void SetFlags(Flags flags) { this->flags = flags; }
			void SetParentNode(Node* parent);
			void SetEntity(Entity* entity);
			void SetLocalTransform(glm::mat4 transformMatrix);
			void SetRotation(glm::quat rotationQuaternion);

			Entity* ModifyEntity();

			void SetNodeDirty();
			void SetEntityDirty();

			void Translate(const glm::vec3& translation);
			void Rotate(const float angle, const glm::vec3& axis);
			void RotateX(const float angle);
			void RotateY(const float angle);
			void RotateZ(const float angle);
			void Scale(const glm::vec3& scale);

			void RecalculateWorldTransform();

			static bool FlagMask(const Flags x) { return static_cast<char>(x) != 0; };

		private:
			Node* parentNode;
			std::vector<Node*> childNodes;

			Flags flags;
			Entity* entity;
			World::DatabaseRecord* dbRecord;

			const char* name;
			glm::mat4 worldTransform;

			glm::mat4 localTransform;
			glm::quat rotationQuaternion;
		};
		
		GIB_FLAGS(Node::Flags)
	}
}