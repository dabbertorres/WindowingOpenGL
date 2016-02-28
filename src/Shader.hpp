#ifndef DBR_GL_SHADER_HPP
#define DBR_GL_SHADER_HPP

#include "Core.hpp"

#include <istream>

namespace dbr
{
	namespace gl
	{
		class Shader
		{
			public:
				enum class Type
				{
					Vertex,
					Fragment,
					Geometry,
				};

				Shader(Type t);
				~Shader();

				void load(std::istream& in);

				glHandle handle() const;
				Type type() const;

			private:
				glHandle handleVal;
				Type typeVal;
		};
	}
}

#endif