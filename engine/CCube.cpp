#include "CCube.h"
#include "CSceneManager.h"

#include "CJPEGHandler.h"
#include "CTGAHandler.h"
#include "CShader.h"
#include "iostream"
#include "helpers\Helpers.h"

namespace base
{
	namespace objects
	{
		

		CCube :: CCube(){
			
		}
		CCube::CCube(CSceneManager *sceneManager)
		{
			//default length
			this->length = 1.0f;
			this->sceneManager = sceneManager;
		}

		CCube::CCube(CSceneManager *sceneManager, CMesh *mesh, GLfloat length,string texture ,bool useTexCoords, GLenum drawType )
		{
			this->length = length;
			this->sceneManager = sceneManager;
			this->useTexCoords = useTexCoords;
			this->texture = texture;
			this->drawType = drawType;
			this->mesh = mesh;
		}

		CCube::~CCube()
		{
		
		}

		void CCube::setLength(GLfloat length)
		{
			this->length = length;
		}

		GLfloat CCube::getLength()
		{
			return length;
		}

		
		void CCube::init()
		{


			//load textures
			auto jpgHandler = new base::io::JPEGHandler();
			auto tgaHandler = new base::io::TGAHandler();
		
			auto path =  ASSETS::IMAGE(this->texture);
			auto image = jpgHandler->readFile(path.c_str(),textureId);

			HELPERS::setTexture(image, textureId[0]);
			
			delete image->data;
			mesh->bufferData();
			mesh->setTextureId(textureId[0]);

			auto cubeVXF = ASSETS::SHADER("texture.vp");
			auto cubeFGF = ASSETS::SHADER("texture.fp");
			shader =  new base::objects::Shader(cubeVXF.c_str(),cubeFGF.c_str());		 
			shader->bindLocations();
			
			shader->link();
		}

		void CCube::render()
		{
			//glEnable(GL_CULL_FACE);
			glUseProgram(shader->getProgram());

			auto pos = this->getPosition();
			mat4 model = translate(mat4 (1.0f),vec3(pos.x,pos.y,pos.z));
			
			glm::mat4 view = sceneManager->getViewMatrix().top();
			glm::mat4 mv = view * model;

			auto MVP =  sceneManager->getProjectionMatrix() * mv;
			locMVP = glGetUniformLocation(shader->getProgram(),"locMVP");
			glUniformMatrix4fv(locMVP,1,GL_FALSE,glm::value_ptr(MVP));

			glUniform1i( glGetUniformLocation(shader->getProgram(), "textureUnit0"),0);
			
			mesh->draw(drawType);
			glUseProgram(0);
			//glDisable(GL_CULL_FACE);
		}

		void CCube::exit()
		{
		
		}
	}

}

