#pragma once

namespace GibEngine
{
	namespace World
	{
		namespace DatabaseQuery
		{
			static std::string CREATE_DATABASE_COMMAND = R"(
				BEGIN TRANSACTION;
				DROP TABLE IF EXISTS `Skyboxes`;
				CREATE TABLE IF NOT EXISTS `Skyboxes` (
					`Id`	INTEGER NOT NULL,
					`AssetName`	TEXT NOT NULL,
					`Extension`	TEXT NOT NULL,
					PRIMARY KEY(`Id`)
				);
				DROP TABLE IF EXISTS `Nodes`;
				CREATE TABLE IF NOT EXISTS `Nodes` (
					`Id`	INTEGER NOT NULL,
					`ParentId`	INTEGER,
					`EntityType`	INTEGER,
					`EntityId`	INTEGER,
					`Position`	TEXT,
					`RotationAxis`	TEXT,
					`RotationAngle`	REAL,
					`Scale`	TEXT,
					PRIMARY KEY(`Id`)
				);
				DROP TABLE IF EXISTS `Meshes`;
				CREATE TABLE IF NOT EXISTS `Meshes` (
					`Id`	INTEGER NOT NULL,
					`AssetName`	TEXT NOT NULL,
					`GenInfo` TEXT, 
					PRIMARY KEY(`Id`)
				);
				DROP TABLE IF EXISTS `Lights`;
				CREATE TABLE IF NOT EXISTS `Lights` (
					`Id`	INTEGER NOT NULL,
					`LightType`	TEXT NOT NULL,
					`AmbientColor`	TEXT NOT NULL,
					`DiffuseColor`	TEXT NOT NULL,
					`SpecularColor`	TEXT NOT NULL,
					`LinearAttenuation`	REAL NOT NULL,
					`QuadraticAttenuation`	REAL NOT NULL,
					PRIMARY KEY(`Id`)
				);
				DROP TABLE IF EXISTS `Levels`;
				CREATE TABLE IF NOT EXISTS `Levels` (
					`Id`	INTEGER NOT NULL,
					`NodeId`	INTEGER NOT NULL,
					`Name`	TEXT NOT NULL,
					PRIMARY KEY(`Id`)
					FOREIGN KEY(`NodeId`) REFERENCES `Nodes`(`Id`)
				);
				DROP INDEX IF EXISTS `NodesId`;
				CREATE UNIQUE INDEX IF NOT EXISTS `NodesId` ON `Nodes` (
					`Id`
				);
				DROP INDEX IF EXISTS `MeshesId`;
				CREATE UNIQUE INDEX IF NOT EXISTS `MeshesId` ON `Meshes` (
					`Id`
				);
				DROP INDEX IF EXISTS `LightsId`;
				CREATE UNIQUE INDEX IF NOT EXISTS `LightsId` ON `Lights` (
					`Id`
				);
				DROP INDEX IF EXISTS `LevelsId`;
				CREATE UNIQUE INDEX IF NOT EXISTS `LevelsId` ON `Levels` (
					`Id`
				);
				COMMIT;
			)";

			static std::string SELECT_LAST_AUTOINCREMENT_ID = R"(
				SELECT last_insert_rowid();
			)";

			static std::string CREATE_LEVEL_COMMAND = R"(
				INSERT INTO Levels (NodeId, Name) VALUES (:nodeId, :name);
			)";

			static std::string CREATE_NODE_COMMAND = R"(
				INSERT INTO Nodes (ParentId, EntityType, EntityId, Position, Scale)
				VALUES (:parentId, :entityType, :entityId, :position, :scale);
			)";

			static std::string CREATE_MESH_COMMAND = R"(
				INSERT INTO Meshes (AssetName, GenInfo) VALUES (:assetName, :genInfo);
			)";

			static std::string CREATE_SKYBOX_COMMAND = R"(
				INSERT INTO Skyboxes (AssetName, Extension) VALUES (:assetName, :extension);
			)";

			static std::string CREATE_LIGHT_COMMAND = R"(
				INSERT INTO Lights (LightType, AmbientColor, DiffuseColor, SpecularColor, LinearAttenuation, QuadraticAttenuation)
				VALUES (:lightType, :ambientColor, :diffuseColor, :specularColor, :linearAttenuation, :quadraticAttenuation); 
			)";

			static std::string SELECT_NODE_QUERY = R"(
				SELECT ParentId, EntityType, EntityId, Position, Scale
				FROM Nodes
				WHERE Id = :id;
			)";

			static std::string SELECT_CHILD_NODES_QUERY = R"(
				SELECT Id FROM Nodes WHERE ParentId = :parentId; 
			)";

			static std::string SELECT_SKYBOX_QUERY = R"(
				SELECT AssetName, Extension FROM Skyboxes WHERE Id = :id;
			)";

			static std::string SELECT_LIGHT_QUERY = R"(
				SELECT LightType, AmbientColor, DiffuseColor, SpecularColor, LinearAttenuation, QuadraticAttenuation
				FROM Lights
				WHERE Id = :id;
			)";

			static std::string SELECT_MESH_QUERY = R"(
				SELECT AssetName, GenInfo FROM Meshes WHERE Id = :id;
			)";

			static std::string UPDATE_SKYBOX_COMMAND = R"(
				UPDATE Skyboxes
				SET AssetName = :assetName, Extension = :extension
				WHERE Id = :id;
			)";

			static std::string UPDATE_NODE_COMMAND = R"(
				UPDATE Nodes
				SET ParentId = :parentId, EntityType = :entityType, EntityId = :entityId, Position = :position, Scale = :scale
				WHERE Id = :id;
			)";

			static std::string UPDATE_LIGHT_COMMAND = R"(
				UPDATE Lights
				SET LightType = :lightType, AmbientColor = :ambientColor, DiffuseColor = :diffuseColor, SpecularColor = :specularColor,
					LinearAttenuation = :linearAttenuation, QuadraticAttenuation = :quadraticAttenuation
				WHERE Id = :id
			)";

			static std::string DELETE_NODE_COMMAND = R"(
				DELETE FROM Nodes WHERE Id = :id;
			)";
		}
	}
}