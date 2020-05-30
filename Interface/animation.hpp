#pragma once 

#include "../object/animated.hpp"
#include <memory>
#include "./iclock.hpp"

class RectangleI;

class IAnimation
{
	public:
		virtual void add_frame(const RectangleI& frame) = 0;
		virtual void set_object(const std::shared_ptr<ANIMATED>& object) = 0;
		virtual const RectangleI& get_frame(std::size_t index) = 0;
		virtual std::shared_ptr<ANIMATED> get_object() = 0;
		virtual std::size_t get_frame_count() const = 0;

		virtual ~IAnimation() = default;
};

class IAnim
{
	public:
		virtual void set_animation(IAnimation* anim) = 0;
		virtual void set_clock(const std::shared_ptr<IClock>& clock) = 0;
		virtual void run(unsigned int delta) = 0;
		virtual void stop(bool stop) = 0;
		virtual void loop(bool loop) = 0;

		virtual ~IAnim() = default;
};
