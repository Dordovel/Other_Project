#include "../headers/animation.hpp"
#include "../struct/rectobject.hpp"
#include <iostream>

namespace PROJECT::ANIMATION
{
	void Animation::add_frame(const PROJECT::BASE::DATA::RectangleI& frame)
	{
		this->_frames.push_back(frame);
	}

	const PROJECT::BASE::DATA::RectangleI& Animation::get_frame(std::size_t index)
	{
		return this->_frames.at(index);
	}

	std::size_t Animation::get_frame_count() const
	{
		return this->_frames.size();
	}



	Anim::Anim(float param):_anim(nullptr)
	{
		this->_frameTime = sf::seconds(param);
	}

	void Anim::set_object(const std::shared_ptr<ANIMATED>& object) noexcept
	{
		this->_object = object;
	}

	void Anim::set_animation(IAnimation* anim) noexcept 
	{
		this->_anim = anim;
	}

	void Anim::run(unsigned int delta) noexcept 
	{
		if (!this->_stop && this->_anim != nullptr)
		{
			this->_currentTime += sf::milliseconds(delta);

			if (this->_currentTime >= this->_frameTime)
			{
				this->_currentTime = sf::microseconds(this->_currentTime.asMicroseconds() % this->_frameTime.asMicroseconds());

				if (this->_currentFrame + 1 < this->_anim->get_frame_count())
					this->_currentFrame++;
				else
				{
					if (!this->_loop)
					{
						this->_stop = true;
					}
					else
					{
						this->_currentFrame = 0;
					}
				}
				this->_object->set_texture_rect(this->_anim->get_frame(this->_currentFrame));
			}
		}
	}

	void Anim::stop(bool stop) noexcept 
	{
		this->_stop = stop;

		if(stop)
		{
			this->reset();
		}
	}

	bool Anim::end() const noexcept
	{
		if(this->_anim)
		{
			std::cout<<"SIZE"<<this->_currentFrame<<":"<<this->_anim->get_frame_count()<<"\n";
			return this->_currentFrame != (this->_anim->get_frame_count() - 1);
		}

		return true;
	}

	void Anim::loop(bool loop) noexcept 
	{
		this->_loop = loop;
	}

	void Anim::reset() noexcept
	{
		if (this->_anim != nullptr)
		{
			if(this->_anim->get_frame_count() > 0)
			{
				this->_object->set_texture_rect(this->_anim->get_frame(0));
			}
		}
	}
};
