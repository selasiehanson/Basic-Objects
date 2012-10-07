//Manages all scene nodes in currently in the scene

#ifndef __CSCENEMANAGER
#define __CSCENEMANAGER
#include <vector>
#include <stack>
#include "CSceneNode.h"
#include "CSkyBox.h"
//class CSkyBox;
namespace base
{
	namespace objects
	{
		class CSceneManager
		{
			public:
				CSceneManager();
				std::vector<SceneNode *> getNodes();
				void render();
				void addNode(SceneNode *node);
				void init();
				void exit();
				void setProjectionMatrix(glm::mat4 projectionMatrix);
				void setViewMatrix(glm::mat4 modeViewMatrix);
				//void addModelViewMatrix(glm::mat4 mvMatrix);
				std::stack<glm::mat4> getViewMatrix();
				glm::mat4 getProjectionMatrix();
				int getNumNodes();

				CSkyBox *getSkyBox();
				void setSkyBox(SkyBox *skyBox);
			private:
				std::vector<SceneNode *> nodes;
				glm::mat4 projectionMatrix;
				std::stack<glm::mat4> viewMatrix;
				CSkyBox *skybox;
		};

		typedef class CSceneManager SceneManager;
	}
}

#endif