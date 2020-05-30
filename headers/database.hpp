#pragma once
#include "../Interface/idatabase.hpp"
#include <map>
#include "../struct/side.hpp"
#include <array>

class RectangleI;

class DataBase final : public IDataBase
{
    private:
        std::map<PersonProfession , std::string> _rectList;
        std::string _pathToResourcesFile;
		std::map<SIDE, std::array<RectangleI, 3>> _animationSide;

    public:
        explicit DataBase(const std::string& pathToResourcesFile);
		DataBaseResult get_resources(PersonProfession person, SIDE side) const noexcept override;
		std::array<RectangleI, 3> get_animation(SIDE side) const noexcept override;
        ~DataBase() = default;
};

