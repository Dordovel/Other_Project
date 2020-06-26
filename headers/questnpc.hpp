#pragma once 

#include "../Interface/iquestnpc.hpp"
#include "../graphicobject/sprite.hpp"

namespace PROJECT::NPC
{
	class QuestNpc : public PROJECT::BASE::GRAPHIC::Sprite, public IQuestNpc
	{
		private:
			int _points = {0};

		public:
			explicit QuestNpc(const PROJECT::DATABASE::DataBaseResult& data, std::string_view id);

			int get_points() const noexcept override;
			void set_points(int points) noexcept override;

			~QuestNpc() = default;
	};
};