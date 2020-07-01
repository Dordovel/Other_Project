#include "../headers/database.hpp"
#include "../struct/rectobject.hpp"
#include "../struct/databaseresult.hpp"

namespace PROJECT::DATABASE
{
	DataBase::DataBase(const std::string& pathToResourcesFile):_pathToResourcesFile(pathToResourcesFile)
	{
		const int titleHeight = 32;
		const int titleWidth = 32;
		std::array<PROJECT::BASE::DATA::RectangleI, 3> walk = {};
		std::array<PROJECT::BASE::DATA::RectangleI, 3> attack = {};

		walk[0] = {titleWidth, 0, titleWidth, titleHeight};
		walk[1] = {0, 0, titleWidth, titleHeight};
		walk[2] = {titleWidth * 2, 0, titleWidth, titleHeight};
		this->_animationSide.emplace(PROJECT::MOVE::Side::DOWN, walk);

		walk[0] = {titleWidth, titleHeight, titleWidth, titleHeight};
		walk[1] = {0, titleHeight, titleWidth, titleHeight};
		walk[2] = {titleWidth * 2, titleHeight, titleWidth, titleHeight};
		this->_animationSide.emplace(PROJECT::MOVE::Side::RIGHT, walk);

		walk[0] = {titleWidth, titleHeight * 2, titleWidth, titleHeight};
		walk[1] = {0, titleHeight * 2, titleWidth, titleHeight};
		walk[2] = {titleWidth * 2, titleHeight * 2, titleWidth, titleHeight};
		this->_animationSide.emplace(PROJECT::MOVE::Side::LEFT, walk);

		walk[0] = {titleWidth, titleHeight * 3, titleWidth, titleHeight};
		walk[1] = {0, titleHeight * 3, titleWidth, titleHeight};
		walk[2] = {titleWidth * 2, titleHeight * 3, titleWidth, titleHeight};
		this->_animationSide.emplace(PROJECT::MOVE::Side::UP, walk);


		attack[0] = {titleWidth * 2, 0, titleWidth, titleHeight};
		attack[1] = {titleWidth * 3, 0, titleWidth, titleHeight};
		attack[2] = {titleWidth * 4, 0, titleWidth, titleHeight};
		this->_animationAttack.emplace(PROJECT::MOVE::Side::DOWN, attack);

		attack[0] = {titleWidth * 2, titleHeight, titleWidth, titleHeight};
		attack[1] = {titleWidth * 3, titleHeight, titleWidth, titleHeight};
		attack[2] = {titleWidth * 4, titleHeight, titleWidth, titleHeight};
		this->_animationAttack.emplace(PROJECT::MOVE::Side::RIGHT, attack);

		attack[0] = {titleWidth * 2, titleHeight * 2, titleWidth, titleHeight};
		attack[1] = {titleWidth * 3, titleHeight * 2, titleWidth, titleHeight};
		attack[2] = {titleWidth * 4, titleHeight * 2, titleWidth, titleHeight};
		this->_animationAttack.emplace(PROJECT::MOVE::Side::LEFT, attack);

		attack[0] = {titleWidth * 2, titleHeight * 3, titleWidth, titleHeight};
		attack[1] = {titleWidth * 3, titleHeight * 3, titleWidth, titleHeight};
		attack[2] = {titleWidth * 4, titleHeight * 3, titleWidth, titleHeight};
		this->_animationAttack.emplace(PROJECT::MOVE::Side::UP, attack);

		this->_rectList.emplace(PersonProfession::JEREMY_BLONDE, "/hero/Jeremy/Jeremy_Blonde.png" );
		this->_rectList.emplace(PersonProfession::MARTHA_BLONDE, "/hero/Martha/Martha_Blonde.png" );
		this->_rectList.emplace(PersonProfession::JEREMY_GREEN, "/hero/Jeremy/Jeremy_Green.png" );
		this->_rectList.emplace(PersonProfession::MARTHA_GREEN, "/hero/Martha/Martha_Green.png" );
		this->_rectList.emplace(PersonProfession::JEREMY_PINK, "/hero/Jeremy/Jeremy_Pink.png" );
		this->_rectList.emplace(PersonProfession::MARTHA_PINK, "/hero/Martha/Martha_Pink.png" );
	}

	DataBaseResult DataBase::get_resources(PersonProfession person, PROJECT::MOVE::Side side) const noexcept
	{ 
		return {this->_pathToResourcesFile + this->_rectList.at(person), this->get_animation_walk(side)[0]};
	}

	PROJECT::DATABASE::DataBaseResult DataBase::get_resources(std::string_view file, const PROJECT::BASE::DATA::RectangleI& rect) const noexcept
	{
		return {this->_pathToResourcesFile + std::string(file), rect};
	}

	std::array<PROJECT::BASE::DATA::RectangleI, 3> DataBase::get_animation_walk(PROJECT::MOVE::Side side) const noexcept
	{
		return this->_animationSide.at(side);
	}

	std::array<PROJECT::BASE::DATA::RectangleI, 3> DataBase::get_animation_attack(PROJECT::MOVE::Side side) const noexcept
	{
		return this->_animationAttack.at(side);
	}
};
