#pragma once

#include "Mesh.h"
#include "world/DatabaseRecord.h"

namespace GibEngine
{
	namespace Scene
	{
		class Node
		{
			Node* parentNode;
			std::vector<Node*> childNodes;

			Entity* entity;
			World::DatabaseRecord* dbRecord;

			glm::mat4 worldTransform;
			glm::mat4 localTransform;

		public:
			Node();
			Node(World::DatabaseRecord* dbRecord);

			World::DatabaseRecord* GetDatabaseRecord() const;
			Entity* GetEntity() const;
			glm::mat4 GetWorldTransform() const;
			glm::mat4 GetLocalTransform() const;

			size_t GetChildNodeCount() const;
			std::vector<Node*>::const_iterator GetChildNodesBegin() const { return childNodes.begin(); }
			std::vector<Node*>::const_iterator GetChildNodesEnd() const { return childNodes.end(); }

			bool IsRootNode() const;

			void AddChildNode(Node* child);

			void SetParentNode(Node* parent);
			void SetEntity(Entity* entity);
			void SetLocalTransform(glm::mat4 transformMatrix);

			void RecalculateWorldTransform();
		};
	}
}