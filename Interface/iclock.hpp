#pragma once

namespace PROJECT::CLOCK
{
    class IClock
    {
        public:
            virtual unsigned int get_elapsed_time() const noexcept = 0;
            virtual unsigned int get_work_time() const noexcept = 0;
            virtual void restart() noexcept = 0;
            virtual ~IClock() = default;;
    };
};
