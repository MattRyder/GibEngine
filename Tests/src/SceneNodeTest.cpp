#include "SceneNodeTest.h"

TEST_F(SceneNodeTest, CanAddChild)
{
	Scene::Node* child = new Scene::Node(nullptr);
	root->AddChildNode(child);

	int count = root->GetChildNodeCount();

	ASSERT_EQ(count, 1);

	delete child;
}

TEST_F(SceneNodeTest, CanSetLocalTransform)
{
	glm::mat4 mat = glm::mat4();
	mat[3] = glm::vec4(2.0f, 2.0f, 2.0f, 1.0f);

	root->SetLocalTransform(mat);

	glm::mat4 trans = root->GetLocalTransform();

	ASSERT_EQ(trans, mat);
}

TEST_F(SceneNodeTest, CanSetRootWorldTransform)
{
	glm::mat4 mat = glm::mat4();
	mat[3] = glm::vec4(2.0f, 2.0f, 2.0f, 1.0f);

	root->SetLocalTransform(mat);

	glm::mat4 worldTrans = root->GetWorldTransform();

	ASSERT_EQ(worldTrans, mat);
}

TEST_F(SceneNodeTest, CanSetChildWorldTransform)
{
	glm::mat4 mat = glm::mat4();
	mat[3] = glm::vec4(2.0f, 2.0f, 2.0f, 1.0f);

	glm::mat4 expected = glm::mat4();
	expected[3] = glm::vec4(4.0f, 4.0f, 4.0f, 1.0f);

	root->SetLocalTransform(mat);

	Scene::Node* childNode = new Scene::Node(nullptr);
	childNode->SetLocalTransform(mat);
	root->AddChildNode(childNode);

	glm::mat4 worldTransChild = childNode->GetWorldTransform();

	ASSERT_EQ(worldTransChild, expected);

	delete childNode;
}