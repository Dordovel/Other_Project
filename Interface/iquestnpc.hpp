#pragma once 

#include "./ipoints.hpp"

namespace PROJECT::NPC
{
	class IQuestNpc : public IPoints
	{
		public:

			virtual ~IQuestNpc() = default;
	};
};
