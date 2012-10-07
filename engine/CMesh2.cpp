#include "CMesh2.h"
#include "Globals.h"
#include "CTriangleMeshData.h"
namespace base
{

	namespace objects
	{
		CMesh2::CMesh2(EMESH_TYPE type)
		{
			for (int i = 0 ;i < EMESH_BUFFER_COUNT; i++ )
			{
				buffers[i] = 0;		
			}

			switch(type)
			{
				case EMESH_TYPE::POINT:
					break;
				case EMESH_TYPE::LINE:
					break;
				case EMESH_TYPE::PLANE:
					break;
				case EMESH_TYPE::TRIANGLE:
					new CTriangleDataMesh(this,0.8f);
					break;
				case EMESH_TYPE::CUBE:
					break;
				case EMESH_TYPE::SPHERE:
					break;
			}

			//populate vertex buffer
			
			glGenBuffers(1,&buffers[VERTEX_BUFFER]);
			glBindBuffer(GL_ARRAY_BUFFER,buffers[VERTEX_BUFFER]);
			glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3),&vertices[0],GL_STATIC_DRAW);

			//populate color buffer
			glGenBuffers(1,&buffers[COLOUR_BUFFER]);
			glBindBuffer(GL_ARRAY_BUFFER,buffers[COLOUR_BUFFER]);
			glBufferData(GL_ARRAY_BUFFER,colors.size() * sizeof(glm::vec3),&colors[0],GL_STATIC_DRAW);

			//bufferData();
		}

		void CMesh2::bufferData()
		{
			glGenVertexArrays(1,&vao);
			glBindVertexArray(vao);

			//move this to the scene node
			auto basicVs = ASSETS::SHADER("basic.vp");
			auto basicFs = ASSETS::SHADER("basic.fp");
			shader =  new base::objects::Shader(basicVs.c_str(),basicFs.c_str());
			shader->enableLocations();

			//mapindex 0 to vertex buffer
			glBindBuffer(GL_ARRAY_BUFFER,buffers[VERTEX_BUFFER]);
			glVertexAttribPointer(VERTEX_BUFFER,3,GL_FLOAT,GL_FALSE,0,(GLubyte *) NULL);

			//map index 1 to colour buffer
			glBindBuffer(GL_ARRAY_BUFFER,buffers[COLOUR_BUFFER]);
			glVertexAttribPointer(COLOUR_BUFFER,3,GL_FLOAT,GL_FALSE,0,(GLubyte *) NULL);
			
			//bind indices to shader inputs
			shader->bindLocations();
			shader->link();
		}	

		void CMesh2::draw()
		{
			glEnable(GL_CULL_FACE);
			glUseProgram(shader->getProgram());

			auto rotationMatrix = glm::rotate(glm::mat4(1.0f),45.0f,glm::vec3(0.0f,0.0f,1.0f));

			auto location =  glGetUniformLocation(shader->getProgram(),"rotationMatrix");

			if(location >= 0)
			{
				glUniformMatrix4fv(location,1,GL_FALSE	,&rotationMatrix[0][0]);
			}

			glBindVertexArray(vao);
			glDrawArrays(GL_TRIANGLES,0,3);
			glUseProgram(0);
			glDisable(GL_CULL_FACE);
		}
	}
}