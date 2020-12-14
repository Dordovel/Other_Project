#ifndef SFMLPROJECT_REBUILD_ANIMATION_INTERFACE_HPP
#define SFMLPROJECT_REBUILD_ANIMATION_INTERFACE_HPP

#include "../object/textured.hpp"
#include <memory>

namespace PROJECT::BASE::DATA
{
	class RectangleI;
};

namespace PROJECT::ANIMATION
{
	class IAnimation
	{
		public:
			virtual void add_frame(PROJECT::BASE::DATA::RectangleI frame) = 0;
			virtual PROJECT::BASE::DATA::RectangleI get_frame(std::size_t index) = 0;
			virtual std::size_t get_frame_count() const = 0;
			virtual void set_object(TEXTURED* object) noexcept = 0;
			virtual TEXTURED* get_object() noexcept = 0;
			virtual ~IAnimation() = default;
	};

	class IAnim
	{
		public:
			virtual void set_animation(IAnimation* anim) noexcept = 0;
			virtual void run(unsigned int delta) noexcept = 0;
			virtual void stop(bool stop) noexcept = 0;
			virtual bool end() const noexcept = 0;
			virtual void reset() noexcept = 0;
			virtual void loop(bool loop) noexcept = 0;

			virtual ~IAnim() = default;
	};
};
#endif //SFMLPROJECT_REBUILD_ANIMATION_INTERFACE_HPP
