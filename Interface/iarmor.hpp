#ifndef SFMLPROJECT_REBUILD_ARMOR_INTERFACE_HPP
#define SFMLPROJECT_REBUILD_ARMOR_INTERFACE_HPP

namespace PROJECT::NPC
{
	class IArmor
	{
		public:

			virtual float get_armor() const noexcept = 0;
			virtual void set_armor(float damage) noexcept = 0;
	};
};
#endif //SFMLPROJECT_REBUILD_ARMOR_INTERFACE_HPP
