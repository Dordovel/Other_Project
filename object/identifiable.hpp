#pragma once

#include <string>

class IDENTIFIABLE
{
    public:
        virtual std::string get_id() const noexcept = 0;
        virtual void set_id(const std::string& id) noexcept = 0;
        virtual ~IDENTIFIABLE() = default;
};
