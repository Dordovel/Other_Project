#pragma once
#include "../Interface/animation.hpp"
#include <vector>
#include <SFML/System/Time.hpp>

namespace PROJECT::ANIMATION
{
	class Animation : public PROJECT::ANIMATION::IAnimation
	{
		private:
			std::vector<PROJECT::BASE::DATA::RectangleI> _frames;

		public:
			void add_frame(const PROJECT::BASE::DATA::RectangleI& frame);
			const PROJECT::BASE::DATA::RectangleI& get_frame(std::size_t index);
			std::size_t get_frame_count() const;

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

			std::shared_ptr<ANIMATED> _object;

		public:
			void set_object(const std::shared_ptr<ANIMATED>& object) noexcept override;
			void set_animation(IAnimation* anim) noexcept override;
			void run(unsigned int delta) noexcept override;
			void stop(bool stop) noexcept override;
			void loop(bool loop) noexcept override;
			bool end() const noexcept override;
			void reset() noexcept override;

			Anim(float param);
	};
};
