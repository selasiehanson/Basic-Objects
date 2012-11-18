#include "CShader.h"
#include "EMeshBuffer.h"
#include <iostream>
using std::ios;
namespace base
{
	namespace objects
	{
		CShader::CShader()
		{
			reset();
		}

		CShader::CShader(const char *vertexShaderFile, const char*fragmentShaderFile)
		{
			reset();
			vertexSrcProgram = loadShader(vertexShaderFile);
			 fragmentSrcProgram = loadShader (fragmentShaderFile);

			 if(vertexSrcProgram != NULL && fragmentSrcProgram != NULL)
				 loadShadersVF();
		}
			

		CShader::~CShader()
		{
			
		}

		/*
		*vertexShaderSrc   contains the memory representation of the vertex shader
		*fragmentShaderSrc contains the memory representation of the fragment shader
		*/
		void CShader::loadShadersVF()
		{

			GLint compiled;
			GLint blen = 0;
			GLsizei slen = 0;
			
			
			vertexShader = glCreateShaderObjectARB(GL_VERTEX_SHADER_ARB);
			glShaderSourceARB(vertexShader,1,(const char **)(&vertexSrcProgram),NULL);
			
			//COMPILATION OF SHADERS
			glCompileShaderARB(vertexShader);
			glGetShaderiv(vertexShader,GL_COMPILE_STATUS,&compiled);
			if(compiled == GL_FALSE)
			{
				std::cout<<"Vertex shader compiled Unsuccesfully"<<std::endl;
				glGetShaderiv(vertexShader,GL_INFO_LOG_LENGTH,&blen);
				if(blen > 1)
				{
					GLchar* compiler_log = new GLchar[blen];
					glGetInfoLogARB(vertexShader,blen,&slen,compiler_log);
					std::cout<<"Compiler log: "<<compiler_log<<std::endl;
					delete compiler_log;
				}
				glDeleteShader(vertexShader);
				glDeleteShader(fragmentShader);
				return;
			}
			
			std::cout<<"Vertex shader compiled succesfully"<<std::endl;
			fragmentShader  = glCreateShaderObjectARB(GL_FRAGMENT_SHADER);
			glShaderSourceARB(fragmentShader,1 ,(const char **)(&fragmentSrcProgram),NULL);
			glCompileShaderARB(fragmentShader);
			glGetShaderiv(fragmentShader,GL_COMPILE_STATUS,&compiled);
			if(compiled == GL_FALSE)
			{
				std::cout<<"Fragment shader compiled Unsuccesfully"<<std::endl;
				glGetShaderiv(fragmentShader,GL_INFO_LOG_LENGTH,&blen);
				if(blen > 1)
				{
					GLchar* compiler_log = new GLchar[blen];
					glGetInfoLogARB(fragmentShader,blen,&slen,compiler_log);
					std::cout<<"Compiler log: "<<compiler_log<<std::endl;
					delete compiler_log;
				}
				glDeleteShader(vertexShader);
				glDeleteShader(fragmentShader);
				return;
			}
			std::cout<<"FragmentShader Conpiled Successfully"<<std::endl;
			
			//if everything compiled well, link the program
			shaderProgram = glCreateProgramObjectARB();
			glAttachShader(shaderProgram, vertexShader);
			glAttachShader(shaderProgram,fragmentShader);

			//binding of attributes should be done here
			glLinkProgram(shaderProgram);
			//we do not need these any more
			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);
			
			
			
		}

		void CShader::link(){
			GLint linked;
			glGetProgramiv(shaderProgram,GL_LINK_STATUS,&linked);
			
			
			if(linked == GL_FALSE)
			{
				char link_log[1024]; //please change this
				std::cout<<"Linking UNsuccessfull"<<std::endl;
				glGetProgramInfoLog(shaderProgram,1024,NULL,link_log);
				std::cout<<"Linker Error: "<<link_log<<std::endl;
			}
			std::cout<<"Linking successful"<<std::endl;
		}

		unsigned long CShader::getFileLength(ifstream &file)
		{
				if(!file.good())
					return 0;
				file.seekg(0,ios::end);
				unsigned long length = file.tellg();
				file.seekg(0,ios::beg);
				return length;
		}

		char * CShader::loadShader(const char * filename)
		{
			char * shaderSrc = NULL;
			ifstream file;
			file.open(filename,ios::in); //opens as ascii
			if(!file)
			{
				std::cout<<"File "<<filename<<" could not be opened"<<std::endl;
				return NULL;
			}
			unsigned long length = 0;
			length  = getFileLength(file);
			if(length == 0) //error: empty file
			{
				std::cout<<"File "<<filename<<" is empty"<<std::endl;
				return NULL;
			}
				
			shaderSrc = (char *) new char[length+1];
			if(shaderSrc == 0)
				return NULL;
			shaderSrc[length] = 0;
			 
			unsigned int i = 0;
			while(file.good())
			{
				shaderSrc[i] = file.get();
				if(!file.eof())
					i++;
			}

			shaderSrc[i] = 0; //zero/null terminator
			file.close();
			
			std::cout<<"Shader file:" << filename <<" loaded succesfully "<<std::endl;
			return shaderSrc;
		}

		void CShader::unloadShaderSrc(GLubyte * shaderSrc)
		{
			if(shaderSrc != 0)
				delete shaderSrc;
			shaderSrc = 0;
		}

		void CShader::reset()
		{
			vertexSrcProgram = NULL;
			fragmentSrcProgram = NULL;

			vertexShader = 0 ;
			fragmentShader = 0;
			shaderProgram = 0;
		}

		GLuint CShader::getProgram()
		{
			return shaderProgram;
		}

		void CShader::bindLocations()
		{
			glBindAttribLocation(getProgram(),VERTEX_BUFFER,"vVertex");
			glBindAttribLocation(getProgram(),COLOUR_BUFFER,"vColor");
			glBindAttribLocation(getProgram(),TEXTURE_BUFFER,"texCoord");
		}

		void CShader::enableLocations()
		{
			glEnableVertexAttribArray(VERTEX_BUFFER); //vertex position
			glEnableVertexAttribArray(COLOUR_BUFFER); //color position
			glEnableVertexAttribArray(TEXTURE_BUFFER);
		}

		void CShader::reflectLocations()
		{
		
		}
		/*void CShader::loadShader(io::FilReader file)
		{
			
		}*/
	}
}