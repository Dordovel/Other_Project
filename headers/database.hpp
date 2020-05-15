#pragma once
#include "../Interface/idatabase.hpp"
#include <map>

class RectangleI;

class DataBase : public IDataBase
{
    private:
        std::map<PersonProfession , RectangleI> _rectList;
        std::string _pathToResourcesFile;

    public:
        explicit DataBase(const std::string& pathToResourcesFile);
        DataBaseResult get_resources(PersonProfession person , const std::string& fileName) const override;
        DataBaseResult get_resources(const std::string& fileName) const override;
        ~DataBase() = default;
};

