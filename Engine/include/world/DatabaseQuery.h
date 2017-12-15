#pragma once

namespace GibEngine
{
    namespace World
    {
        static const char* CREATE_DATABASE_QUERY = R"(
            BEGIN TRANSACTION;
            CREATE TABLE `ModelsInstances` (
                `Id`	INTEGER NOT NULL,
                `ModelId`	INTEGER NOT NULL,
                `Position`	TEXT NOT NULL,
                `RotationAxis` TEXT,
                `RotationAngle` TEXT,
                `Scale` TEXT,
                PRIMARY KEY(`Id`),
                FOREIGN KEY(`ModelId`) REFERENCES `Models`(`Id`)
            );
			CREATE TABLE `Skyboxes` (
				`Id`	INTEGER NOT NULL,
                `AssetName`	TEXT NOT NULL,
                `Extension` TEXT NOT NULL,
				PRIMARY KEY(`Id`)
			);
			CREATE TABLE `Levels` (
                `Id`	INTEGER NOT NULL,
                `SkyboxId`  INTEGER,
                `Name`	INTEGER NOT NULL,
                PRIMARY KEY(`Id`),
				FOREIGN KEY(`SkyboxId`) REFERENCES `Skyboxes`(`Id`)
            );
            CREATE TABLE `Models` (
                `Id`	INTEGER NOT NULL,
                `LevelId`	INTEGER NOT NULL,
                `AssetName`	INTEGER NOT NULL,
                PRIMARY KEY(`Id`),
                FOREIGN KEY(`LevelId`) REFERENCES `Levels`(`Id`)
            );

            CREATE UNIQUE INDEX `ModelsInstancesId_Idx` ON `ModelsInstances` (`Id` );
            CREATE UNIQUE INDEX `ModelsId_Idx` ON `Models` (`Id` );
            CREATE UNIQUE INDEX `LevelsId_Idx` ON `Levels` (`Id` );
            COMMIT;
            )";

        static const char* SELECT_LAST_AUTOINCREMENT_ID = R"(
            SELECT last_insert_rowid();
        )";

        static const char* CREATE_LEVEL_QUERY = R"(
            INSERT INTO Levels (Name) VALUES (:levelName);
        )";

        static const char* CREATE_MODEL_QUERY = R"(
            INSERT INTO Models (LevelId, AssetName) VALUES (:levelId, :assetName);
        )";

        static const char* CREATE_SKYBOX_QUERY = R"(
            INSERT INTO Skyboxes (AssetName, Extension) VALUES (:assetName, :extension);
        )";

        static const char* SET_LEVEL_SKYBOX_QUERY = R"(
            UPDATE Levels SET SkyboxId = :skyboxId WHERE Id = :levelId;
        )";

        static const char* CREATE_INSTANCE_QUERY = R"(
            INSERT INTO ModelsInstances (ModelId, Position, RotationAxis, RotationAngle, Scale)
            VALUES (:modelId, :position, :rotationAxis, :rotationAngle, :scale);
        )";

        static const char* SELECT_LEVEL_QUERY = R"(
            SELECT Levels.Id, Levels.Name, Skyboxes.AssetName, Skyboxes.Extension
            FROM Levels
            INNER JOIN Skyboxes
            ON Skyboxes.Id = Levels.SkyboxId
            WHERE Levels.Id = ?;
        )";

        static const char* SELECT_LEVEL_MODELS_QUERY = R"(
            SELECT Id, AssetName FROM Models WHERE LevelId = ?;
        )";

        static const char* SELECT_MODEL_INSTANCES_QUERY = R"(
            SELECT Id, Position, RotationAxis, RotationAngle, Scale FROM ModelsInstances WHERE ModelId = ?;
        )";

        static const char* SELECT_LEVEL_SKYBOX_QUERY = R"(
            SELECT AssetName FROM Skyboxes WHERE Id = ?;
        )";

		static const char* UPDATE_SKYBOX_QUERY = R"(
			UPDATE Skyboxes
			SET AssetName = :assetName, Extension = :extension
			WHERE Id = ?;
		)";

		static const char* UPDATE_MODEL_INSTANCES_QUERY = R"(
			UPDATE ModelsInstances
			SET Position = :position, RotationAxis = :rotationAxis, RotationAngle = :rotationAngle, Scale = :scale
			WHERE Id = :id;
		)";

		static const char* MODEL_INSTANCE_DELETE_QUERY = "DELETE FROM ModelsInstances WHERE Id = :id;";
    }
}