#ifndef SFMLPROJECT_REBUILD_QUEST_NPC_INTERFACE_HPP
#define SFMLPROJECT_REBUILD_QUEST_NPC_INTERFACE_HPP

#include "./ipoints.hpp"

namespace PROJECT::NPC
{
	class IQuestNpc : public IPoints
	{
		public:

			virtual ~IQuestNpc() = default;
	};
};
#endif //SFMLPROJECT_REBUILD_QUEST_NPC_INTERFACE_HPP
