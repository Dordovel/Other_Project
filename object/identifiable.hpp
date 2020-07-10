#ifndef SFMLPROJECT_REBUILD_OBJECT_IDENTIFIABLE_HPP
#define SFMLPROJECT_REBUILD_OBJECT_IDENTIFIABLE_HPP

#include <string>

class IDENTIFIABLE
{
    public:
        virtual std::string get_id() const noexcept = 0;
        virtual void set_id(std::string_view id) noexcept = 0;
        virtual ~IDENTIFIABLE() = default;
};
#endif //SFMLPROJECT_REBUILD_OBJECT_IDENTIFIABLE_HPP
