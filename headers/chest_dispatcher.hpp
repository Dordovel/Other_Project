#ifndef SFMLPROJECT_REBUILD_CHEST_DISPATCHER_HPP
#define SFMLPROJECT_REBUILD_CHEST_DISPATCHER_HPP

#include "../Interface/ichest.hpp"
#include <vector>

namespace PROJECT::DISPATCHER
{
	class ChestDispatcher
	{
		private:
			std::vector<std::shared_ptr<PROJECT::CHEST::IChest>> _object;

		public:
			void delete_object(size_t index) noexcept;

			void add_object(std::shared_ptr<PROJECT::CHEST::IChest>&& object) noexcept;

			std::shared_ptr<PROJECT::CHEST::IChest>& object(int index) noexcept;

			size_t size() const noexcept;
	};
};
#endif //SFMLPROJECT_REBUILD_CHEST_DISPATCHER_HPP
