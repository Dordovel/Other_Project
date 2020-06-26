#pragma once

namespace PROJECT::DATABASE
{
	struct DataBaseResult;
};
	class TEXTURED
	{
		public:
			virtual void set_texture(const PROJECT::DATABASE::DataBaseResult& resources) = 0;

			virtual ~TEXTURED() = default;
	};
