#ifndef DBR_GL_KEYBOARD_HPP
#define DBR_GL_KEYBOARD_HPP

#include "util/Flags.hpp"

namespace dbr
{
	namespace gl
	{
		enum class Keyboard
		{

		};

		enum class Modifiers : int
		{
			None = 0,
			Shift = 1 << 0,
			Control = 1 << 1,
			Alt = 1 << 2,
			Super = 1 << 3,
		};

		using ModifersFlags = util::Flags<Modifiers>;
	}
}

#endif
