#pragma once

#include <string>

class IDENTIFIABLE
{
    public:
        virtual std::string get_id() const noexcept = 0;
        virtual ~IDENTIFIABLE() = default;
};
