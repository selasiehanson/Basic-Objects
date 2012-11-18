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

		CCube::CCube(CSceneManager *sceneManager,GLfloat length,string texture ,bool useTexCoords )
		{
			this->length = length;
			this->sceneManager = sceneManager;
			this->useTexCoords = useTexCoords;
			this->texture = texture;
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


			float i[] = {3};
			float n[normalSize]  = { 
				0.0f, 0.0f, 1.0f,
				0.0f, 0.0f,-1.0f,
				0.0f, 1.0f, 0.0f,
				0.0f,-1.0f, 0.0f,
				1.0f, 0.0f, 0.0f,
				-1.0f, 0.0f, 0.0f 
			};
			

			float v[] = {

						//Front face
						-length, -length,  length,
						 length, -length,  length,
						 length,  length,  length,
						-length,  length, length,

						 // Top Face
						-length,  length, -length,
						-length,  length,  length,
						 length,  length,  length,
						 length,  length, -length,

						// Back Face
						-length, -length, -length,
						-length,  length, -length,
						 length,  length, -length,
						 length, -length, -length,
						
						
						// Bottom Face
						-length, -length, -length,
						 length, -length, -length,
						 length, -length,  length,
						-length, -length,  length,

						// Left Face
						-length, -length, -length,
						-length, -length,  length,
						-length,  length,  length,
						-length,  length, -length,

						// Right face
						length, -length, -length,
						length,  length, -length,
						length,  length,  length,
						length, -length,  length
			};

			//verts = &v[0];
			normals = &n[0];
			
			glGenBuffers(1, &vertexId);
			glBindBuffer(GL_ARRAY_BUFFER,vertexId);
			glBufferData(GL_ARRAY_BUFFER, sizeof(v),v,GL_STATIC_DRAW);
			
			if(this->useTexCoords) {
				float t[texcoordSize] = {
						0.0f, 0.0f,  
						1.0f, 0.0f, 
						1.0f, 1.0f, 
						0.0f, 1.0f
				};
				//texCoords = &t[0];
			
				for(int i=1;  i < 6; i++){
					memcpy(&t[i*2*4], &t[0], 2 * 4 * sizeof(float));
				}
			
				//texcoords
				glGenBuffers(1,&texCoordId);
				glBindBuffer(GL_ARRAY_BUFFER,texCoordId);
				glBufferData(GL_ARRAY_BUFFER, sizeof(t),t ,GL_STATIC_DRAW);															
			}
			
			
			  GLushort indices[] = {
					// front
					0,  1,  2,
					2,  3,  0,
					// top
					4,  5,  6,
					6,  7,  4,
					// back
					8,  9, 10,
					10, 11,  8,
					// bottom
					12, 13, 14,
					14, 15, 12,
					// left
					16, 17, 18,
					18, 19, 16,
					// right
					20, 21, 22,
					22, 23, 20
			  };

			glGenBuffers(1, &indexBufferId);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferId);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices),indices,GL_STATIC_DRAW);

			auto cubeVXF = ASSETS::SHADER( "texture.vp");
			auto cubeFGF = ASSETS::SHADER("texture.fp");
			shader =  new base::objects::Shader(cubeVXF.c_str(),cubeFGF.c_str());		 

			//load textures
			auto jpgHandler = new base::io::JPEGHandler();
			auto tgaHandler = new base::io::TGAHandler();
		
			auto path =  ASSETS::IMAGE(this->texture);
			auto image = jpgHandler->readFile(path.c_str(),textureId);

			HELPERS::setTexture(image, textureId);
			
			delete image->data;
			vVertex = glGetAttribLocation(shader->getProgram(),"vVertex");
			vTexCoords = glGetAttribLocation(shader->getProgram(),"vTexCoords");
			
			shader->link();
		}

		void CCube::render()
		{
			glEnable(GL_CULL_FACE);
			glUseProgram(shader->getProgram());

			auto pos = this->getPosition();
			mat4 model = translate(mat4 (1.0f),vec3(pos.x,pos.y,pos.z));
			
			glm::mat4 view = sceneManager->getViewMatrix().top();
			glm::mat4 mv = view * model;

			auto MVP =  sceneManager->getProjectionMatrix() * mv;
			locMVP = glGetUniformLocation(shader->getProgram(),"locMVP");
			textureUnit = glGetUniformLocation(shader->getProgram(), "textureUnit0");
			glUniformMatrix4fv(locMVP, 1, GL_FALSE, glm::value_ptr(MVP));
			
			glUniform1i(textureUnit,0);
			
			// Describe our vertices array to OpenGL (it can't guess its format automatically)
			glBindBuffer(GL_ARRAY_BUFFER, vertexId);
			glVertexAttribPointer(vVertex,3,GL_FLOAT, GL_FALSE,0,0);
			glEnableVertexAttribArray(vVertex);

			glBindBuffer(GL_ARRAY_BUFFER,texCoordId);
			glVertexAttribPointer(vTexCoords,2,GL_FLOAT,GL_FALSE,0,0);
			glEnableVertexAttribArray(vTexCoords);

			glBindTexture(GL_TEXTURE_2D,textureId[0]);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferId);
			int size;
			glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER,GL_BUFFER_SIZE, &size);
			glDrawElements(GL_TRIANGLES,size / sizeof(GLushort), GL_UNSIGNED_SHORT,0);

			glDisableVertexAttribArray(vVertex);
			glDisableVertexAttribArray(vTexCoords);

			glUseProgram(0);
			glDisable(GL_CULL_FACE);
		}

		void CCube::exit()
		{
		
		}
	}

}

