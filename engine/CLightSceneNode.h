#ifndef __CLIGHTSCENENODE
#define __CLIGHTSCENENODE

#include "CSceneNode.h"

namespace base 
{
	namespace objects 
	{
		class CLightSceneNode : public CSceneNode
		{
			public:
				CLightSceneNode(glm::vec3 position, glm::vec4 diffuseColor = glm::vec4(1.0f));
				void init();
				void render();
				void exit();

			private : 
				glm::vec4 diffuseColor;

		};

		typedef class CLightSceneNode Light;
	}
}

#endif