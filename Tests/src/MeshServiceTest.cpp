#include "MeshServiceTest.h"

TEST_F(MeshServiceTest, GeneratePlane)
{
	json11::Json planeGenerationData = json11::Json::object
	{
		{ "MeshType", "Plane" },
		{ "Length", 250 },
		{ "Width", 250 },
		{ "IntervalSize", 5 }
	};

	GibEngine::Mesh::Flags expectedFlags =
		GibEngine::Mesh::Flags::RENDER_ENABLED ^
		GibEngine::Mesh::Flags::RENDER_ARRAYS ^
		GibEngine::Mesh::Flags::RENDER_FORWARD ^
		GibEngine::Mesh::Flags::RENDER_WIREFRAME;

	auto ptr = std::shared_ptr<MeshUploadTicket>(new MeshUploadTicket());

	NiceMock<MockGraphicsApi>* mock = new NiceMock<MockGraphicsApi>();
	std::shared_ptr<NiceMock<MockGraphicsApi>> graphicsApi = std::shared_ptr<NiceMock<MockGraphicsApi>>(mock);

	EXPECT_CALL(*mock, UploadMesh(_, _))
		.Times(AtLeast(1))
		.WillOnce(Return(ptr));

	auto planeMesh = GibEngine::MeshService::Generate(graphicsApi, planeGenerationData);

	ASSERT_NE(planeMesh, nullptr);
	ASSERT_TRUE(planeMesh->GetFlags() == expectedFlags);
}