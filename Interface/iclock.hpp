#pragma once

class IClock
{
    public:
        virtual float get_time() const = 0;
        virtual void restart() = 0;
        virtual ~IClock() = default;;
};
