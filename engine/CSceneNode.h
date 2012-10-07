#ifndef __CSCENENODE
#define __CSCENENODE
#include "CBase.h"

#include "../glm/glm.hpp"
#include "../glm/gtc/matrix_transform.hpp"
#include "../glm/gtc/type_ptr.hpp"
#include "Globals.h"
#include "CAttribLocationsTypes.h"
using namespace glm;
namespace base
{
	namespace objects
	{
		class CSceneManager;
		class CSceneNode
		{
			public : 
				CSceneNode(){};
				CSceneNode(CSceneManager *sceneManager){ 
					this->sceneManager = sceneManager;
					this->setScale(1.0f,1.0f,1.0f);
				};
				virtual void init()  {} ;
				virtual void render(){} ;
				virtual void exit()  {} ;
				virtual void setPosition(float x, float y, float z)
				{
					position.x = x;
					position.y = y;
					position.z = z;
				}
				virtual void setPosition(base::Vertexf position)
				{
					this->position = position;
				}
				virtual base::Vertexf getPosition()
				{
					return position;
				}

				virtual void setScale(float x, float y, float z)
				{
					this->scale,x = x;
					this->scale.y = y;
					this->scale.z = z;
				}

				virtual void setScale(float value)
				{
					this->scale.x = value;
					this->scale.y =  value;
					this->scale.z = value;
				}
				virtual void setScale(base::Vertexf scale)
				{
					this->scale = scale;
				}

				virtual base::Vertexf getScale()
				{
						return scale;
				}
				base::objects::CSceneManager *sceneManager;
		protected:
			base::Vertexf position;
			base::Vertexf scale;
			GLint locMVP;
			//ASSETS directory;
			
		};

		typedef class CSceneNode SceneNode;
	}
}


#endif
