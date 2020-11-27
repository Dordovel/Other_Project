#ifndef SFMLPROJECT_REBUILD_NPC_DISPATCHER_HPP
#define SFMLPROJECT_REBUILD_NPC_DISPATCHER_HPP

#include "../graphicobject/text.hpp"
#include "../Interface/inpc.hpp"
#include "../headers/animation.hpp"
#include "../global.hpp"
#include "side_generator.hpp"

namespace PROJECT::DISPATCHER
{
	class NpcDispatcher
	{
		private:
			std::vector<std::shared_ptr<NPC::INpc>> _object;
			std::vector<ANIMATION::Anim> _objectAnimation;
			std::vector<NPC::SideGenerator> _sideGenerator;

		public:
			void delete_object(size_t index) noexcept;

			void add_object(std::unique_ptr<NPC::INpc> object) noexcept;

			std::shared_ptr<NPC::INpc> object(int index) const noexcept;

			ANIMATION::Anim& animation(int index) noexcept;

			MOVE::Side side(int index, float time) noexcept;

			size_t size() const noexcept;

			bool empty() const noexcept;
	};
};
#endif //SFMLPROJECT_REBUILD_NPC_DISPATCHER_HPP
