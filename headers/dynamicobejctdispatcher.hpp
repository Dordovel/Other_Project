#pragma once
#include "../graphicobject/text.hpp"
#include "./npc.hpp"
#include "../global.hpp"
#include "./generatside.hpp"

namespace PROJECT::DISPATCHER
{
	class DynamicObjectDispatcher
	{
		private:
			std::vector<std::shared_ptr<NPC::Npc>> _object;
			std::vector<std::shared_ptr<BASE::GRAPHIC::IText>> _objectStatus;
			std::vector<ANIMATION::Anim> _objectAnimation;
			std::vector<NPC::SideGenerator> _sideGenerator;

		public:
			void delete_object(size_t index) noexcept;

			void add_object(std::shared_ptr<NPC::Npc>&& object) noexcept;

			std::shared_ptr<NPC::Npc>& object(int index) noexcept;

			std::shared_ptr<BASE::GRAPHIC::IText>& status(int index) noexcept;

			ANIMATION::Anim& animation(int index) noexcept;

			MOVE::Side side(int index, float time) noexcept;

			size_t size() const noexcept;
	};
};
