#include "CMesh.h"
#include "Globals.h"
#include "CTriangleMeshData.h"
#include "CPlaneMesh.h"
#include "CCubeMeshData.h"

namespace base
{

	namespace objects
	{
		CMesh::CMesh(EMESH_TYPE type, GLfloat length)
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
					new CPlaneMesh(this);
					break;
				case EMESH_TYPE::TRIANGLE:
					//passing in 'this' allows the appropriate mesh provider to provide the mesh data
					new CTriangleDataMesh(this,length);
					break;
				case EMESH_TYPE::CUBE:
					new  CCubeMeshData(this, length);
					break;
				case EMESH_TYPE::SPHERE:
					break;
			}

			//bufferData();
		}

		GLuint CMesh::getTextureId()
		{
			return textureId;
		}

		void CMesh::setTextureId(GLuint textureId)
		{
			this->textureId = textureId;
		}

		void CMesh::bufferData()
		{
			glGenVertexArrays(1,&vao);
			glBindVertexArray(vao);
			
			//populate vertex buffer
			glGenBuffers(1,&buffers[VERTEX_BUFFER]);
			glBindBuffer(GL_ARRAY_BUFFER,buffers[VERTEX_BUFFER]);
			glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3),&vertices[0],GL_STATIC_DRAW);
			glVertexAttribPointer(VERTEX_BUFFER,3,GL_FLOAT,GL_FALSE,0,(GLubyte *) NULL);
			glEnableVertexAttribArray(VERTEX_BUFFER); //vertex position

			if(textureCoordinates.size() > 0) {
				glGenBuffers(1, &buffers[TEXTURE_BUFFER]);
				glBindBuffer(GL_ARRAY_BUFFER, buffers[TEXTURE_BUFFER]);
				glBufferData(GL_ARRAY_BUFFER, textureCoordinates.size() * sizeof(glm::vec2), &textureCoordinates[0], GL_STATIC_DRAW);
				glVertexAttribPointer(TEXTURE_BUFFER,2, GL_FLOAT,GL_FALSE,0,(GLubyte *) NULL);
				glEnableVertexAttribArray(TEXTURE_BUFFER);
			}
	
			if(colors.size() > 0) {
				//populate color buffer
				glGenBuffers(1,&buffers[COLOUR_BUFFER]);
				glBindBuffer(GL_ARRAY_BUFFER,buffers[COLOUR_BUFFER]);
				glBufferData(GL_ARRAY_BUFFER,colors.size() * sizeof(glm::vec3),&colors[0],GL_STATIC_DRAW);		
				//map index 1 to colour buffer
				glVertexAttribPointer(COLOUR_BUFFER,3,GL_FLOAT,GL_FALSE,0,(GLubyte *) NULL);
				glEnableVertexAttribArray(COLOUR_BUFFER); 
			}
			
			//todo : normal stuff
			glBindVertexArray(0);
		}	

		void CMesh::draw(GLenum type)
		{
			glBindVertexArray(vao);
			if(textureCoordinates.size() > 0 && textureId != 0 ){
				glBindTexture(GL_TEXTURE_2D, textureId);
			}
			
			if(!type){
				type = GL_TRIANGLES;
			}
			glDrawArrays(type, 0, vertices.size());
			
			if(textureCoordinates.size()> 0 && textureId != 0 ) {
				glBindTexture(GL_TEXTURE_2D, 0);
			}	
			
			glBindVertexArray(0);
			
			glDisableVertexAttribArray(VERTEX_BUFFER);
			glDisableVertexAttribArray(COLOUR_BUFFER);
			glDisableVertexAttribArray(TEXTURE_BUFFER);
		}
	}
}