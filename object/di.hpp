#pragma once
#include "./interaction.hpp"
#include "./dynamic.hpp"

class DI : public INTERACTION, public DYNAMIC
{
	public:
		virtual ~DI() = default;
};
