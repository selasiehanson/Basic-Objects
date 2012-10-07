#include "CLightSceneNode.h"

namespace base 
{
	namespace objects 
	{
		
		CLightSceneNode ::CLightSceneNode(glm::vec3 position, glm::vec4 diffuseColor)
		{
			this->setPosition(position.x,position.y,position.z);
			this->diffuseColor = diffuseColor;
		}

		void CLightSceneNode ::init()
		{
			
		}

		void CLightSceneNode :: render()
		{
		
		}

		void CLightSceneNode :: exit()
		{
		
		}
	}
}