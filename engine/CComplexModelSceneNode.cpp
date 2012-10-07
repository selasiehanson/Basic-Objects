#include "CComplexModelSceneNode.h"
#include "CMeshLoader.h"
#include "CSceneManager.h"
#include "CJPEGHandler.h"
namespace base
{
	namespace objects
	{
		/*CComplexModelSceneNode::CComplexModelSceneNode()
		{ 
			reset();
		}*/


		CComplexModelSceneNode::CComplexModelSceneNode( SceneManager *sceneManager)
		{
			this->sceneManager = sceneManager;	
			reset();
		}

		CComplexModelSceneNode::CComplexModelSceneNode(CSceneManager *sceneManager, string filename, string texture)
		{
			//mesh =  new CMesh(filename);
			MeshLoader *msl = new MeshLoader;
			mesh = msl->loadMesh(ASSETS::MODEL(filename));
			this->sceneManager = sceneManager;
			this->texture =  texture;
			reset();
		}


		void CComplexModelSceneNode::reset()
		{
			position.x = 0;
			position.y = 0;
			position.z = 0;
		}
		void CComplexModelSceneNode::init()
		{
			//bind model and textures
			//vertices
			glGenBuffers(1, &vertexId);
			glBindBuffer(GL_ARRAY_BUFFER,vertexId);
			//float *vPtr  = static_cast<float *>(&mesh->vertices[0]);
			std::cout<<"size of vertices is "<< mesh->vertices.size() * sizeof(vec3 )<< std::endl;
			glBufferData(GL_ARRAY_BUFFER, mesh->vertices.size() * sizeof(vec3),&mesh->vertices[0],GL_STATIC_DRAW);
			
			//texcoords
			glGenBuffers(1,&texCoordId);
			//float *tPtr  = static_cast<float *>(&mesh->textcureCoordinates[0]);
			glBindBuffer(GL_ARRAY_BUFFER,texCoordId);
			glBufferData(GL_ARRAY_BUFFER,mesh->textureCoordinates.size() * sizeof(vec2),&mesh->textureCoordinates[0] ,GL_STATIC_DRAW_ARB);

			//indices
			//GLushort *iPtr = static_cast<GLushort *>(&mesh->indices[0]);
			glGenBuffers(1, &indexBufferId);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferId);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER,mesh->indices.size() * sizeof(GLushort),&mesh->indices[0],GL_STATIC_DRAW);


			//setup shaders
			/*const char *groundVXF = "assets/shaders/vertex_shader.glvs";
			const char *groundFGF = "assets/shaders/fragment_shader.glfs";*/
			const char *shv = "assets/shaders/texture.vp";
			const char *shf = "assets/shaders/texture.fp";
			shader=  new base::objects::Shader(shv,shf);


			//set up textures must me moved from here
			base::io::JPEGHandler *tgaHandler;
			tgaHandler = new base::io::JPEGHandler ();
			auto path  = ASSETS::IMAGE(texture);
			base::io::Image *image = tgaHandler->readFile(path.c_str(),textureId);
			setUpTexturing(image);
			delete image->data;
			 
			shader->link();

			vVertex = glGetAttribLocation(shader->getProgram(),"vVertex");
			vTexCoords = glGetAttribLocation(shader->getProgram(),"vTexCoords");
			locMVP = glGetUniformLocation(shader->getProgram(),"locMVP");
			textureUnit = glGetUniformLocation(shader->getProgram(), "textureUnit0");
		}

		void CComplexModelSceneNode::setUpTexturing(base::io::CImage* image)
		{
			glEnable(GL_TEXTURE_2D);
			glGenTextures(1, &textureId[0]);
			glBindTexture(GL_TEXTURE_2D, textureId[0]);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
			glTexImage2D(GL_TEXTURE_2D,0,GL_COMPRESSED_RGB,image->width,image->height,0,GL_RGB,GL_UNSIGNED_BYTE,image->data);
		}
		
		void CComplexModelSceneNode::render()
		{
			glEnable(GL_CULL_FACE);
						
			auto pos = this->getPosition();
			mat4 model = translate(mat4 (1.0f),vec3(pos.x,pos.y,pos.z));
			auto scale = this->getScale();
			model = glm::scale(model,glm::vec3(scale.x,scale.y,scale.z));
			
			glm::mat4 view = sceneManager->getViewMatrix().top();
			auto mv =  view * model;
			glm::mat4 MVP = sceneManager->getProjectionMatrix() * mv;
			glUseProgram(shader->getProgram());
			
			glUniformMatrix4fv(locMVP,1,GL_FALSE,glm::value_ptr(MVP));

			glUniform1i(textureUnit,0);
			
			//enable and bind our vertices
			glEnableVertexAttribArray(vVertex);
			glBindBuffer(GL_ARRAY_BUFFER,vertexId);
			glVertexAttribPointer(vVertex,3,GL_FLOAT,GL_FALSE,0,0);

			glEnableVertexAttribArray(vTexCoords);
			glBindBuffer(GL_ARRAY_BUFFER,texCoordId);
			glVertexAttribPointer(vTexCoords,2,GL_FLOAT,GL_FALSE,0,0);

			glBindTexture(GL_TEXTURE_2D,textureId[0]);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,indexBufferId);
			int size;
			glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER,GL_BUFFER_SIZE,&size);
			
			glDrawArrays(GL_TRIANGLES, 0, mesh->vertices.size());
			//glDrawElements(GL_TRIANGLES,mesh->indices.size(), GL_UNSIGNED_SHORT,0);
			glDisableVertexAttribArray(vVertex);
			glDisableVertexAttribArray(vTexCoords);
			glUseProgram(0);
			
			glDisable(GL_CULL_FACE);
		}
		
		void CComplexModelSceneNode::exit()
		{
		
		}
		
	}
}