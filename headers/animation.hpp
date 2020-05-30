#pragma once
#include "../Interface/animation.hpp"
#include <vector>
#include <SFML/System/Time.hpp>

class Animation : public IAnimation
{
	private:
		std::vector<RectangleI> _frames;
		std::shared_ptr<ANIMATED> _object;

	public:
		void add_frame(const RectangleI& frame);
		void set_object(const std::shared_ptr<ANIMATED>& object);
		const RectangleI& get_frame(std::size_t index);
		std::shared_ptr<ANIMATED> get_object();
		std::size_t get_frame_count() const;

		Animation() = default;
};


class Anim : public IAnim
{
	private:
		IAnimation* _anim;
		std::shared_ptr<IClock> _clock;
		bool _loop, _stop, _play;
		std::size_t _currentFrame;
		sf::Time _currentTime;
		sf::Time _frameTime;

	public:

		void set_clock(const std::shared_ptr<IClock>& clock) override;
		void set_animation(IAnimation* anim) override;
		void run(unsigned int delta) override;
		void stop(bool stop) override;
		void loop(bool loop) override;

		Anim(float param);
};
