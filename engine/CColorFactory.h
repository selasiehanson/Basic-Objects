#ifndef __COLOR_FACTORY
#define __COLOR_FACTORY
#include "CColors.h"
#include "../glm/glm.hpp"
#include "../glm/gtc/matrix_transform.hpp"
#include "../glm/gtc/type_ptr.hpp"

namespace  base
{ 
	namespace objects 
	{
		class CColorFactory
		{
			public:
				static glm::vec4	Color(CCOLORS color)
				{
					glm::vec4 out;
					switch (color)
					{
						case CCOLORS::COLOR_BLACK:
							out = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
							break;
						case CCOLORS::COLOR_BLUE:
							out = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);
							break;
						case CCOLORS::COLOR_RED:
							out = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
							break;
						case CCOLORS::COLOR_YELLOW:
							out = glm::vec4(1.0f, 1.0f, 0.0f, 1.0f);
							break;
						case CCOLORS::COLOR_GREEN:
							out = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
							break;
						default :
							out = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
							break;
					
					}
					return out;
				}


		};		
	}
	
}



#endif