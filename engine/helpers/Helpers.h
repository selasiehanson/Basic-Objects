#ifndef __HELPERS
#define __HELPERS

#include <iostream>
#include "CImage.h"
using std::string;

class HELPERS 
{
	public:
		static void setTexture(base::io::CImage* image, GLuint &textureId)
		{
			glEnable(GL_TEXTURE_2D);
			//glActiveTexture(GL_TEXTURE0);
			glGenTextures(1, &textureId);
			glBindTexture(GL_TEXTURE_2D, textureId);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
			//glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR_MIPMAP_LINEAR);
			//gluBuild2DMipmaps(GL_TEXTURE_2D, 3,image->width, image->height, GL_RGB, GL_UNSIGNED_BYTE, image->data);
			glTexImage2D(GL_TEXTURE_2D,0,GL_COMPRESSED_RGB,image->width,image->height,0,GL_RGB,GL_UNSIGNED_BYTE,image->data);
			//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
			/*glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR_MIPMAP_LINEAR);*/
		}
};



#endif
