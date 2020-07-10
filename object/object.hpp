#ifndef SFMLPROJECT_REBUILD_OBJECT_OBJECT_HPP
#define SFMLPROJECT_REBUILD_OBJECT_OBJECT_HPP

#include "./identifiable.hpp"
#include "./movable.hpp"
#include "./drawable.hpp"
#include "./modifiable.hpp"
#include "./interaction.hpp"
#include "./dynamic.hpp"

class OBJECT : public MOVABLE, 
				public INTERACTION,
				public DYNAMIC,
				public IDENTIFIABLE, 
				public DRAWABLE, 
				public MODIFIABLE
{
    public:
		virtual std::shared_ptr<OBJECT> clone() noexcept = 0;
        virtual ~OBJECT() = default;
};
#endif //SFMLPROJECT_REBUILD_OBJECT_OBJECT_HPP
