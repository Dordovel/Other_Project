#pragma once
#include <string>
#include <array>

enum class PersonProfession
{
	JEREMY_PINK,
	MARTHA_PINK,

	JEREMY_GREEN,
	MARTHA_GREEN,

	JEREMY_BLONDE,
	MARTHA_BLONDE,
};

enum class SIDE;
class RectangleI;
class DataBaseResult;

class IDataBase
{
    public:
        virtual DataBaseResult get_resources(PersonProfession person, SIDE side) const noexcept = 0;
		virtual std::array<RectangleI, 3> get_animation(SIDE side) const noexcept = 0;
        virtual  ~IDataBase() = default;
};
