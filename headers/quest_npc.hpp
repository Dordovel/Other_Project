#ifndef SFMLPROJECT_REBUILD_QUEST_NPC_HPP
#define SFMLPROJECT_REBUILD_QUEST_NPC_HPP

#include "../Interface/iquestnpc.hpp"
#include "../graphicobject/sprite.hpp"

namespace PROJECT::NPC
{
	class QuestNpc : public PROJECT::BASE::GRAPHIC::Sprite, public IQuestNpc
	{
		private:
			int _points = {0};

		public:
			explicit QuestNpc(const PROJECT::DATABASE::DataBaseResult& data);

			int get_points() const noexcept override;
			void set_points(int points) noexcept override;

			~QuestNpc() = default;
	};
};
#endif //SFMLPROJECT_REBUILD_QUEST_NPC_HPP
