//#include<stdlib.h>
//#define GLEW_STATIC
#include <GL/glew.h>
#define FREEGLUT_STATIC
#include <GL/glut.h>
#include <iostream>
#include <sstream>
#include "../glm/gtc/matrix_transform.hpp"

#include "Cube.h"
#include "CImage.h"
#include "CShader.h"
#include "Globals.h"
#include "CPlane.h"
#include "CCamera.h"
#include "CSceneManager.h"
#include "CComplexModelSceneNode.h"
#include "CMatrix4.h"
#include "CSkyBox.h"
#include "CTGAHandler.h"
#include "CJPEGHandler.h"
#include "CLightSceneNode.h"
#include "CTriangleSceneNode.h"
#include "CText.h"
#include "CMesh2.h"
#include "EMeshBuffer.h"
#include "EMeshType.h"
#include "EModelType.h"

