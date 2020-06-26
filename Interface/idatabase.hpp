#pragma once
#include <string>
#include <array>

namespace PROJECT::MOVE
{
	enum class Side;
};

namespace PROJECT::BASE::DATA
{
	class RectangleI;
};

namespace PROJECT::DATABASE
{
	enum class PersonProfession
	{
		JEREMY_PINK,
		MARTHA_PINK,

		JEREMY_GREEN,
		MARTHA_GREEN,

		JEREMY_BLONDE,
		MARTHA_BLONDE,
	};

	struct DataBaseResult;

	class IDataBase
	{
		public:
			virtual PROJECT::DATABASE::DataBaseResult get_resources(PROJECT::DATABASE::PersonProfession person, PROJECT::MOVE::Side side) const noexcept = 0;
			virtual PROJECT::DATABASE::DataBaseResult get_resources(std::string_view file, const PROJECT::BASE::DATA::RectangleI& rect) const noexcept = 0;
			virtual std::array<PROJECT::BASE::DATA::RectangleI, 3> get_animation_walk(PROJECT::MOVE::Side side) const noexcept = 0;
			virtual std::array<PROJECT::BASE::DATA::RectangleI, 3> get_animation_attack(PROJECT::MOVE::Side side) const noexcept = 0;
			virtual  ~IDataBase() = default;
	};
};
