#ifndef SFMLPROJECT_REBUILD_DATABASE_HPP
#define SFMLPROJECT_REBUILD_DATABASE_HPP

#include "../Interface/idatabase.hpp"
#include <map>
#include "../struct/side.hpp"
#include <array>

namespace PROJECT::BASE::DATA
{
    class RectangleI;
};

namespace PROJECT::DATABASE
{
    class DataBase final : public PROJECT::DATABASE::IDataBase
    {
        private:
            std::map<PersonProfession , std::string> _rectList;
            std::string _pathToResourcesFile;
            std::map<PROJECT::MOVE::Side, std::array<PROJECT::BASE::DATA::RectangleI, 3>> _animationSide;
            std::map<PROJECT::MOVE::Side, std::array<PROJECT::BASE::DATA::RectangleI, 3>> _animationAttack;

        public:
            explicit DataBase(const std::string& pathToResourcesFile);
            DataBaseResult get_resources(PersonProfession person, PROJECT::MOVE::Side side) const noexcept override;
			PROJECT::DATABASE::DataBaseResult get_resources(std::string_view file, const PROJECT::BASE::DATA::RectangleI& rect) const noexcept override;
            std::array<PROJECT::BASE::DATA::RectangleI, 3> get_animation_walk(PROJECT::MOVE::Side side) const noexcept override;
            std::array<PROJECT::BASE::DATA::RectangleI, 3> get_animation_attack(PROJECT::MOVE::Side side) const noexcept override;
            ~DataBase() = default;
    };
};
#endif //SFMLPROJECT_REBUILD_DATABASE_HPP
