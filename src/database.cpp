#include "../headers/database.hpp"
#include "../struct/rectobject.hpp"
#include "../struct/databaseresult.hpp"

DataBase::DataBase(const std::string& pathToResourcesFile):_pathToResourcesFile(pathToResourcesFile)
{
    this->_rectList.emplace(PersonProfession::Paladin , RectangleI{170 , 140 , 130 , 130 } );
    this->_rectList.emplace(PersonProfession::BerserkRed , RectangleI{170 , 0 , 130 , 130  } );
    this->_rectList.emplace(PersonProfession::PaladinRed , RectangleI{170 , 280 , 130 , 130 } );
    this->_rectList.emplace(PersonProfession::Warrior , RectangleI{340 , 140 , 130 , 130 } );
    this->_rectList.emplace(PersonProfession::WarriorRed , RectangleI{340 , 280 , 130 , 130 } );
    this->_rectList.emplace(PersonProfession::Magic , RectangleI{340 , 0 , 130 , 130 } );
    this->_rectList.emplace(PersonProfession::MagicRed , RectangleI{500 , 280 , 130 , 130 } );
    this->_rectList.emplace(PersonProfession::Thief , RectangleI{500 , 0 , 130 , 130 } );
    this->_rectList.emplace(PersonProfession::Berserk , RectangleI{170 , 410 , 130 , 130 } );
}

DataBaseResult DataBase::get_resources(PersonProfession person , const std::string& fileName) const
{
    DataBaseResult result { this->_rectList.at(person) , (this->_pathToResourcesFile + fileName) };

    return result;
}

DataBaseResult DataBase::get_resources(const std::string& fileName) const
{
    return { {}, this->_pathToResourcesFile + fileName};
}
