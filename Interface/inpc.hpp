#ifndef SFMLPROJECT_REBUILD_NPC_INTERFACE_HPP
#define SFMLPROJECT_REBUILD_NPC_INTERFACE_HPP

#include "./istate.hpp"
#include "./ianimated.hpp"
#include "../graphicobject/isprite.hpp"

namespace PROJECT::NPC
{
	enum class State
	{
		WALK,
		IDLE,
		ATTACK
	};

	class INpc : public INpcState,
				public PROJECT::ANIMATION::IAnimated,
				virtual public PROJECT::BASE::GRAPHIC::ISprite
	{
		public:

			virtual State get_state() const noexcept = 0;
			virtual void set_state(State state) noexcept = 0;
			virtual float get_view_radius() const noexcept = 0;
			virtual void set_view_radius(float radius) noexcept = 0;
			virtual ~INpc() = default;
	};
};
#endif //SFMLPROJECT_REBUILD_NPC_INTERFACE_HPP
