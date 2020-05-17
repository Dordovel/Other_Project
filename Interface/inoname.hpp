#pragma once

#include "../object/object.hpp"

class INoname : public OBJECT
{
	public:
		virtual int get_health() const = 0;
		virtual void set_health(int health) = 0;

		virtual ~INoname() = default;
};
