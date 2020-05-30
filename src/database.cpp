#include "../headers/database.hpp"
#include "../struct/rectobject.hpp"
#include "../struct/databaseresult.hpp"

DataBase::DataBase(const std::string& pathToResourcesFile):_pathToResourcesFile(pathToResourcesFile)
{
	int titleHeight = 32;
	int titleWidth = 32;
	std::array<RectangleI, 3> arr = {};

	arr[0] = {titleWidth, 0, titleWidth, titleHeight};
	arr[1] = {0, 0, titleWidth, titleHeight};
	arr[2] = {titleWidth * 2, 0, titleWidth, titleHeight};
	this->_animationSide.emplace(SIDE::DOWN, arr);

	arr[0] = {titleWidth, titleHeight, titleWidth, titleHeight};
	arr[1] = {0, titleHeight, titleWidth, titleHeight};
	arr[2] = {titleWidth * 2, titleHeight, titleWidth, titleHeight};
	this->_animationSide.emplace(SIDE::RIGHT, arr);

	arr[0] = {titleWidth, titleHeight * 2, titleWidth, titleHeight};
	arr[1] = {0, titleHeight * 2, titleWidth, titleHeight};
	arr[2] = {titleWidth * 2, titleHeight * 2, titleWidth, titleHeight};
	this->_animationSide.emplace(SIDE::LEFT, arr);

	arr[0] = {titleWidth, titleHeight * 3, titleWidth, titleHeight};
	arr[1] = {0, titleHeight * 3, titleWidth, titleHeight};
	arr[2] = {titleWidth * 2, titleHeight * 3, titleWidth, titleHeight};
	this->_animationSide.emplace(SIDE::UP, arr);

    this->_rectList.emplace(PersonProfession::JEREMY_BLONDE, "/hero/Jeremy/Jeremy_Blonde.png" );
    this->_rectList.emplace(PersonProfession::MARTHA_BLONDE, "/hero/Martha/Martha_Blonde.png" );
    this->_rectList.emplace(PersonProfession::JEREMY_GREEN, "/hero/Jeremy/Jeremy_Green.png" );
    this->_rectList.emplace(PersonProfession::MARTHA_GREEN, "/hero/Martha/Martha_Green.png" );
    this->_rectList.emplace(PersonProfession::JEREMY_PINK, "/hero/Jeremy/Jeremy Pink.png" );
    this->_rectList.emplace(PersonProfession::MARTHA_PINK, "/hero/Jeremy/Jeremy Pink.png" );
}

DataBaseResult DataBase::get_resources(PersonProfession person, SIDE side) const noexcept
{ 
	return {this->_pathToResourcesFile + this->_rectList.at(person), this->get_animation(side)[0]};
}

std::array<RectangleI, 3> DataBase::get_animation(SIDE side) const noexcept
{
	return this->_animationSide.at(side);
}
