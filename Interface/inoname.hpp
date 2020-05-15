#pragma once

#include "./iobject.hpp"
#include "../object/drawable.hpp"

class INoname : public IOBJECT, public DRAWABLE
{
	public:
		virtual int get_health() const = 0;
		virtual void set_health(int health) = 0;

		virtual ~INoname() = default;
};
