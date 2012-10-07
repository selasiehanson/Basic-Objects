/*
*THIS FILE IS USED FOR TURNING ON/OFF PROPERTIES
*e.g 
*	if(USE_GL)
*		std::cout<<"Using GL"<<std::endl;
*/

#ifndef __GLOBALS
#define __GLOBALS


#include <iostream>
#define USE_GL 0


using std::string;

class ASSETS {

	public:
		static string ROOT;
		static string MODELS ;
		static string SHADERS ;
		static string IMAGES;
		static string FONTS;
		
		static string MODEL(string str)
		{
			return resolvePath(MODELS,str);
		}

		static string SHADER (string str)
		{
			return resolvePath(SHADERS, str);	
		}
		
		static string IMAGE (string str)
		{
			return resolvePath(IMAGES, str);	
		}

		static string FONT (string str)
		{
			return resolvePath(FONTS,str);
		}

	private :
		static string resolvePath (string path, string filename)
		{
			auto _path = ROOT;
			_path.append(path);
			_path.append(filename);
			return _path;
		}
};


#endif