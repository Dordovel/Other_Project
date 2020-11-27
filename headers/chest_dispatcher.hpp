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

			void add_object(std::unique_ptr<PROJECT::CHEST::IChest> object) noexcept;

			std::shared_ptr<PROJECT::CHEST::IChest> object(int index) const noexcept;

			size_t size() const noexcept;

			bool empty() const noexcept;
	};
};
#endif //SFMLPROJECT_REBUILD_CHEST_DISPATCHER_HPP
