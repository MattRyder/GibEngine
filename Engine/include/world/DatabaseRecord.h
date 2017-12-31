#pragma once

namespace GibEngine
{
	namespace World
	{
		class DatabaseRecord
		{
		public:
			enum class State
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

			DatabaseRecord() : id(0), attachedEntityId(0), state(State::NEW) { }
			DatabaseRecord(int id) : id(id), attachedEntityId(0), state(State::CLEAN) { }

			int GetId() const { return id; }
			int GetEntityId() const { return attachedEntityId; }
			State GetState() const { return state; }

			void SetState(State state)
			{
				if (this->state == State::NEW && state == State::DIRTY)
				{
					// Prevent a NEW flag being overwritten by DIRTY
					return;
				}
				this->state = state;
			}

			void SetId(unsigned int id) { this->id = id; }

			void SetAttachedEntityId(unsigned int id) { this->attachedEntityId = id; }

		protected:
			// ID as given in the GWO database
			unsigned int id;

			// ID of the Entity attached to the DatabaseRecord
			unsigned int attachedEntityId;

			// Tracks the state of the record
			State state;
		};
	}
}