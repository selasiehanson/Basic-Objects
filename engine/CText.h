#ifndef __CTEXT
#define __CTEXT 

#include  <ft2build.h>
//#include  <freetype2>
#include FT_FREETYPE_H
#include "CShader.h"
#include <map>
#include "CColors.h"

namespace base 
{
	namespace objects2D 
	{
		struct point {
			GLfloat x;
			GLfloat y;
			GLfloat s;
			GLfloat t;
		};
		class CText
		{

			public: 
				CText();
				void registerFont(const char * fileName, const char * path);
				void displayText(const char *text,float x, float y, int size = 20);
				void setCurrentColor(base::objects::CCOLORS color);
				void setActiveFont(const char * font);
			private:
				
				int init();
				void render(const char *text,float x, float y, float w, float h);
				base::objects::CShader *fontShader;
				GLint attribute_coord;
				GLint uniform_tex;
				GLint uniform_color;
				GLuint vbo;
				std::map<const char * , const char *> fonts;
				FT_Library ft;
				FT_Face face;
				GLfloat currentColor[4];
				const char *fontfilename;
		};
	}
}

#endif