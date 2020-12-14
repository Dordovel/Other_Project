#ifndef SFMLPROJECT_REBUILD_ANIMATION_HPP
#define SFMLPROJECT_REBUILD_ANIMATION_HPP

#include "../Interface/animation.hpp"
#include <vector>
#include <SFML/System/Time.hpp>

namespace PROJECT::ANIMATION
{
	class Animation : public PROJECT::ANIMATION::IAnimation
	{
		private:
			std::vector<PROJECT::BASE::DATA::RectangleI> _frames;
			TEXTURED* _object;

		public:
			void add_frame(PROJECT::BASE::DATA::RectangleI frame) override;
			PROJECT::BASE::DATA::RectangleI get_frame(std::size_t index) override;
			std::size_t get_frame_count() const override;
			void set_object(TEXTURED* object) noexcept override;
			TEXTURED* get_object() noexcept override;
			Animation() = default;
	};


	class Anim : public PROJECT::ANIMATION::IAnim
	{
		private:
			IAnimation* _anim;
			bool _loop, _stop;
			std::size_t _currentFrame;
			sf::Time _currentTime;
			sf::Time _frameTime;


		public:
			void set_animation(IAnimation* anim) noexcept override;
			void run(unsigned int delta) noexcept override;
			void stop(bool stop) noexcept override;
			void loop(bool loop) noexcept override;
			bool end() const noexcept override;
			void reset() noexcept override;

			Anim(float param);
	};
};
#endif //SFMLPROJECT_REBUILD_ANIMATION_HPP
