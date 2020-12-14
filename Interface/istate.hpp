#ifndef SFMLPROJECT_REBUILD_NPCSTATE_INTERFACE_HPP
#define SFMLPROJECT_REBUILD_NPCSTATE_INTERFACE_HPP

#include "./iarmor.hpp"
#include "./ipoints.hpp"
#include "./ihealth.hpp"
#include "./idamage.hpp"

namespace PROJECT::NPC
{
	class INpcState: public IDamage,
				public IHealth,
				public IPoints,
				public IArmor
	{
		public:
			virtual ~INpcState() = default;
	};
};
#endif //SFMLPROJECT_REBUILD_NPC_INTERFACE_HPP
