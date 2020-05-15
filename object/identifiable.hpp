#pragma once

#include <string>

class IDENTIFIABLE
{
    public:
        virtual std::string get_id() const = 0;
        virtual void set_id(const std::string& id) = 0;
        virtual ~IDENTIFIABLE() = default;
};
