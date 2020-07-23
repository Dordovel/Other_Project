#ifndef SFMLPROJECT_REBUILD_NPC_INTERFACE_HPP
#define SFMLPROJECT_REBUILD_NPC_INTERFACE_HPP

#include "./iarmor.hpp"
#include "./ipoints.hpp"
#include "./ihealth.hpp"
#include "./idamage.hpp"
#include "./animation.hpp"
#include "../graphicobject/isprite.hpp"

namespace PROJECT::MOVE
{
	enum class Side;
}

namespace PROJECT::NPC
{

	enum class State
	{
		WALK,
		IDLE,
		ATTACK
	};

	class INpc : public IDamage,
				public IHealth,
				public IPoints,
				public IArmor,
				virtual public PROJECT::BASE::GRAPHIC::ISprite
	{
		public:

			virtual PROJECT::ANIMATION::IAnimation* get_animation_attack(PROJECT::MOVE::Side side) noexcept = 0;
			virtual PROJECT::ANIMATION::IAnimation* get_animation_walk(PROJECT::MOVE::Side side) noexcept = 0;
			virtual State get_state() noexcept = 0;
			virtual void set_state(State state) noexcept = 0;
			virtual ~INpc() = default;
	};
};
#endif //SFMLPROJECT_REBUILD_NPC_INTERFACE_HPP
