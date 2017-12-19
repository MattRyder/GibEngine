#pragma once

namespace GibEngine
{
    namespace World
    {
		enum class DatabaseEntityState
		{
			/* No State changes have been recorded */
			CLEAN,

			/* The entity state has changed */
			DIRTY,

			/* The entity is untracked, and requires saving to the DB */
			NEW,

			/* The entity is marked for deletion */
			DELETED,
		};

		template<class T>
        class DatabaseEntity
        {
		public:

			DatabaseEntity(unsigned int id) : id(id), entity(nullptr)
			{
				if (id == 0)
				{
					SetState(DatabaseEntityState::NEW);
				}
			}

			DatabaseEntity(unsigned int id, T* entityObject) : DatabaseEntity(id) { entity = entityObject; }

			unsigned int GetId() { return id; }

			T* GetEntity() { return entity; }

			T* Modify()
			{
				SetState(DatabaseEntityState::DIRTY);
				return GetEntity();
			}

			DatabaseEntityState GetState() { return entityState; }

			void SetState(DatabaseEntityState entityState)
			{
				if (this->entityState == DatabaseEntityState::NEW
					&& entityState == DatabaseEntityState::DIRTY)
				{
					// Prevent a NEW flag being overwritten by DIRTY
					return;
				}
				this->entityState = entityState;
			}

			void SetId(unsigned int id) { this->id = id; }

		protected:
			DatabaseEntityState entityState = DatabaseEntityState::CLEAN;

			// GibEngine entity referenced by the ID
			T* entity;

			// ID as given in the GWO database
			unsigned int id;
		};
	}
}