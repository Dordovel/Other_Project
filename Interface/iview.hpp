#ifndef SFMLPROJECT_REBUILD_VIEW_INTERFACE_HPP
#define SFMLPROJECT_REBUILD_VIEW_INTERFACE_HPP

#include "../object/movable.hpp"
#include "../object/dynamic.hpp"
#include "../object/static.hpp"
#include "../object/interaction.hpp"
#include "../object/modifiable.hpp"

namespace PROJECT::APPLICATION
{
    class IView: public MOVABLE, public DYNAMIC, public INTERACTION, public MODIFIABLE
    {
        public:
            virtual void zoom(float zoom) noexcept = 0;
            virtual PROJECT::BASE::DATA::Vector2F get_size() const noexcept = 0;
            virtual void set_size(const PROJECT::BASE::DATA::Vector2F& size) noexcept = 0;
            virtual void set_size(float x, float y) noexcept = 0;
            virtual ~IView() = default;
    };
};
#endif //SFMLPROJECT_REBUILD_VIEW_INTERFACE_HPP