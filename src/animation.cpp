#include "../headers/animation.hpp"
#include "../struct/rectobject.hpp"

void Animation::add_frame(const RectangleI& frame)
{
	this->_frames.push_back(frame);
}

void Animation::set_object(const std::shared_ptr<ANIMATED>& object)
{
	this->_object = object;
}

const RectangleI& Animation::get_frame(std::size_t index)
{
	return this->_frames.at(index);
}

std::shared_ptr<ANIMATED> Animation::get_object()
{
	return this->_object;
}

std::size_t Animation::get_frame_count() const
{
	return this->_frames.size();
}


void Anim::set_clock(const std::shared_ptr<IClock>& clock) 
{
	this->_clock = clock;
}

Anim::Anim(float param)
{
	this->_frameTime = sf::seconds(param);
}

void Anim::set_animation(IAnimation* anim) 
{
	this->_anim = anim;
}

void Anim::run(unsigned int delta) 
{
	if (!this->_stop && this->_anim)
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
			this->_anim->get_object()->set_texture_rect(this->_anim->get_frame(this->_currentFrame));
		}
	}
}

void Anim::stop(bool stop) 
{
	this->_stop = stop;
}

void Anim::loop(bool loop) 
{
	this->_loop = loop;
}
