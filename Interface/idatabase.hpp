#pragma once
#include <string>

enum class PersonProfession
{
    Berserk,
    BerserkRed ,

    Paladin ,
    PaladinRed ,

    Magic ,
    MagicRed ,

    Thief ,

    Warrior ,
    WarriorRed
};

struct DataBaseResult;

class IDataBase
{
    public:
        virtual DataBaseResult get_resources(PersonProfession person , const std::string& fileName) const = 0;
        virtual DataBaseResult get_resources(const std::string& fileName) const = 0;
        virtual  ~IDataBase() = default;
};
