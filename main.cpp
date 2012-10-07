//#include "Engine.h"
//#define GLEW_STATIC
#include  "engine/Engine.h"
#include  <ft2build.h>
//#include  <freetype2>
#include FT_FREETYPE_H


#pragma comment(lib,"glew32d.lib")
#pragma comment(lib,"freetype.lib")

using namespace base;
using namespace base::io;
using namespace base::objects;
using namespace base::math;

const char *skyImages[]  = { "pos_x.tga", "neg_x.tga", "pos_y.tga","neg_y.tga","pos_z.tga", "neg_z.tga" };
SkyBox *skybox;
SceneManager *sceneManager;
TriangleSceneNode * triangle;
Cube *cube;
Plane *ground;
ModelSceneNode *fighter1, *fighter2, *fighter3;
glm::mat4 projection;
glm::mat4 modelView;
int windowHeight = 600;
int windowWidth = 800; 
char *logo = "assets/images/op_logo.tga";

GLuint rectVertId, rectUvId, rectTextureId;
GLint rectMVP, rectTexture;

GLint vVertex;
GLint vTexCoords;
Shader *rectShader;
vector<vec3> rectVertices;
vector<vec2> rectUVs;
GLuint rectBuffers[2];

//lights
Light * light;

//glm::mat4 MVP;


//camera stuff
Camera *camera;
float angle = 0.0f;
float moveAmount = 0.5f;


base::objects::CMesh2 *mesh;
///font stuff

GLuint program;
GLint attribute_coord;
GLint uniform_tex;
GLint uniform_color;

struct point {
	GLfloat x;
	GLfloat y;
	GLfloat s;
	GLfloat t;
};

GLuint vbo;

FT_Library ft;
FT_Face face;

const char *fontfilename;

base::objects2D::CText text;

///end of font stuff


void processNormalKeys(unsigned char key, int x, int y)
{
	
}

void print (glm::mat4 mat)
{
	std::cout<<"printing matrix\n";
	float *mt = glm::value_ptr(mat);
	for (int i =0 ; i < 16; ++i)
	{
		std::cout<< "mat["<<i + 1<<"] is " << mt[i] <<std::endl;
		//std::cout << mt [i];
	}
}

void processSpecialKeys(int key, int x , int y)
{	
	switch(key)
	{
	case GLUT_KEY_F1:
		angle += 0.05f;
		camera->rotateYZ(angle);
		break;
	case GLUT_KEY_F2:
		
		break;
	case GLUT_KEY_F3:
		
		break;

	case GLUT_KEY_LEFT:
		angle -= 0.05f;
		camera->rotateXZ(angle);
		break;

	case GLUT_KEY_RIGHT:
		angle += 0.05f;
		camera->rotateXZ(angle);
		break;
		
	case GLUT_KEY_UP:
		camera->move(1,moveAmount);
		//print(camera->getMatrix());
		break;
	case GLUT_KEY_DOWN:
		camera->move(-1,moveAmount);
		//print(camera->getMatrix());
		break;
	
	}
}

/* vectors that makes the rotation and translation of the cube */
float eye[3] = {0.0f, 0.0f, 7.0f};
float rot[3] = {45.0f, 45.0f, 0.0f};

void createProjectionMatrix (){
	
}


void changeSize(int width, int height)
{
	height = (height == 0) ? 1: height;
	float aspectRatio = (float)width / (float)height;
	
	glViewport(0,0,width,height);
	
	sceneManager->setProjectionMatrix( glm::perspective(45.0f, aspectRatio, 0.1f, 100000.0f));
	camera->setMatrix(glm::mat4(1.0f));
	camera->view();
	//cout<<"printed";
}

void initOGL()
{
	glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);

	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);
	
}

void load2dRect(Image *image, GLenum minFilter = GL_NEAREST, GLenum magFilter = GL_NEAREST,GLenum wrapMode = GL_CLAMP_TO_EDGE)
{
	if(image && image->data)
	{
		glTexParameteri(GL_TEXTURE_RECTANGLE,GL_TEXTURE_WRAP_S, wrapMode);
		glTexParameteri(GL_TEXTURE_RECTANGLE,GL_TEXTURE_WRAP_T,wrapMode);
		glTexParameteri(GL_TEXTURE_RECTANGLE,GL_TEXTURE_MIN_FILTER,minFilter);
		glTexParameteri(GL_TEXTURE_RECTANGLE, GL_TEXTURE_MAG_FILTER, magFilter);
		glPixelStorei(GL_UNPACK_ALIGNMENT,1);
		glTexImage2D(GL_TEXTURE_RECTANGLE,0,image->component,image->width,
			image->height,0,image->format,GL_UNSIGNED_BYTE,image->data);
		delete image->data;
		//delete image;
	}
	else
	{
		cout<<"image has no data"<<endl;
	}
}

void initRect2d(int x,int y,int width,int height)
{
	/*vec3 rectVertices [] = {
					vec3(x,y,0.0f),
					vec3(x, y - height,0.0f),
					vec3(x + width, y - height , 0.0f),
					vec3(x + width, y , 0.0f)
	};*/
									
	rectVertices.push_back(vec3(x,y,0.0f));
	rectVertices.push_back(vec3(x,y- height,0.0f));
	rectVertices.push_back(vec3(x + width, y - height , 0.0f));
	rectVertices.push_back(vec3(x + width, y , 0.0f));

	rectUVs.push_back(vec2(0.0f,height));
	rectUVs.push_back(vec2(0.0f,0.0f));
	rectUVs.push_back(vec2(width,0.0f));
	rectUVs.push_back(vec2(width,height));
	
	/*vec2 rectUVs[] = {
		vec2(0.0f,height),
		vec2(0.0f,0.0f),
		vec2(width,0.0f),
		vec2(width,height)
	};*/

	
	//do shader stuff here
	auto vsh = "assets/shaders/rect.vp";
	auto fsh = "assets/shaders/rect.fp";
	rectShader =  new Shader(vsh,fsh);
	//rectShader->bindLocations();
	rectShader->link();
	//vVertex = glGetAttribLocation(rectShader->getProgram(),"vVertex");
	//vTexCoords = glGetAttribLocation(rectShader->getProgram(),"vTexCoord");
	
	
	
	glGenBuffers(1,&rectVertId);
	glBindBuffer(GL_ARRAY_BUFFER,rectVertId);
	glBufferData(GL_ARRAY_BUFFER,sizeof(rectVertices),&rectVertices[0],GL_STATIC_DRAW);

	glGenBuffers(1,&rectUvId);
	glBindBuffer(GL_ARRAY_BUFFER,rectUvId);
	glBufferData(GL_ARRAY_BUFFER,sizeof(rectUVs),&rectUVs[0],GL_STATIC_DRAW);

	
	//bind the texture
	glGenTextures(1,&rectTextureId);
	glBindTexture(GL_TEXTURE_RECTANGLE,rectTextureId);
	unsigned int rectId;
	TGAHandler  * tgaHandler=  new TGAHandler();
	auto image = tgaHandler->readFile (logo,&rectId);
	load2dRect(image);


	
}


void renderRect()
{
	auto projection = glm::ortho(0.0f, (float)windowWidth,0.0f,(float)windowHeight,-1.0f,1.0f);
	glEnable(GL_BLEND);
	glDisable(GL_DEPTH_TEST);
	glUseProgram(rectShader->getProgram());
		
	
	glBindTexture(GL_TEXTURE_RECTANGLE,rectTextureId);

	//rectShader->enableLocations();
	//glEnableVertexAttribArray(vVertex);
	glBindBuffer(GL_ARRAY_BUFFER,rectVertId);
	glVertexAttribPointer(vVertex, 3, GL_FLOAT,GL_FALSE,0,0);

	//glEnableVertexAttribArray(vTexCoords);
	glBindBuffer(GL_ARRAY_BUFFER,rectUvId);
	glVertexAttribPointer(vTexCoords, 2, GL_FLOAT,GL_FALSE,0,0);
	
	rectMVP = glGetUniformLocation(rectShader->getProgram(), "mvpMatrix");
	rectTexture = glGetUniformLocation(rectShader->getProgram(), "rectangleImage");
	
	glUniform1i(rectTexture,0);
	//auto value = glm::value_ptr( projection);
	glUniformMatrix4fv(rectMVP,1,GL_FALSE,glm::value_ptr(projection));



	//do the drawing here
	glDrawArrays(GL_TRIANGLE_STRIP,0,4);
	glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
}


void renderScene()
{	
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	sceneManager->setViewMatrix(camera->getMatrix());
	glEnable(GL_CULL_FACE);

	//do light stuff here
	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	sceneManager->render();	
	
	glDisable(GL_CULL_FACE);
	
	
	camera->view();
	text.displayText("Engine : version 1.0 ", 10  ,  26,14);
	std::ostringstream c;
	c << "Number of objects : ";
	c << sceneManager->getNumNodes();

	text.displayText(c.str().c_str() ,10,50,16);
	
	//renderRect();
	glutSwapBuffers();
	glFlush();
}

void beforeInit(){
	
	std::cout<<ASSETS::ROOT <<std::endl;
	std::cout<<ASSETS::IMAGES<<std::endl;
	
	fontfilename = "FreeSans.ttf";

	glm::mat4 src(0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15);
	
	auto srcValue = glm::value_ptr(src);
	
	float dst[9];
	memcpy(dst,srcValue, sizeof(float ) * 3 );
	memcpy(dst + 3 , srcValue + 4, sizeof(float) * 3);
	memcpy(dst + 6 , srcValue + 8 , sizeof(float) * 3 );
	 
	sceneManager = new SceneManager;
	skybox =  new SkyBox(skyImages,sceneManager,1000.0f);
	//auto s = reinterpret_cast<CSkyBox * >(skybox);
	//sceneManager->setSkyBox(skybox);

	//create a single triangle
	mesh = new base::objects::CMesh2(EMESH_TYPE::TRIANGLE);
	triangle = new TriangleSceneNode(sceneManager,mesh);
	//sceneManager->addNode(triangle);

	//creating lights
	light =  new Light(vec3(-100.0f, 100.0f, 100.0f),vec4(0.0f, 0.0f, 1.0f, 1.0f));

	//sceneManager->addNode(light);

	//creating cubes
	const char * texture  = "3_store.jpg";
	cube  = new Cube(sceneManager,0.6f,texture);
	cube->setPosition(Vertexf(-2,0,2));
	
	//the ground plane
	ground  = new Plane(sceneManager);
	ground->setPosition(0.0f,-1.0f,-15.0f);
	
	sceneManager->addNode(ground);

	//draw a colletion of cubes
	const auto size = 2;
	Cube *cubes[size];
	
	for(int i=0; i < size; i++)
	{
		std::cout<<"adding cube " << i +1<<endl;
		cubes[i] = new Cube(sceneManager,0.7f,texture);
		if(i % 2 == 0)
			cubes[i]->setPosition((i * -2) , 0, 3 * i);
		else 
			cubes[i]->setPosition((i * 2) , 0, -3 * i);
		sceneManager->addNode(cubes[i]);
	}

	fighter1 = new ModelSceneNode(sceneManager,"Hover01_Body.obj","FB_hover01_uv01.jpg");
	if(fighter1)
	{
		fighter1->setPosition(0,1.5f,0);
		fighter1->setScale(0.1f);
		sceneManager->addNode(fighter1);
	}

	//fighter2 = new ModelSceneNode(sceneManager,"Hover02_Body.obj","FB_hover02_uv01.jpg");
	if(fighter2)
	{
		fighter2->setPosition(-15,1.5f,0);
		fighter2->setScale(0.1f);
		sceneManager->addNode(fighter2);
	}

	//fighter3 = new ModelSceneNode(sceneManager,"Hover03_Body.obj","FB_hover03_uv01.jpg");
	if(fighter3)
	{
		fighter3->setPosition(15,1.5f,0);
		fighter3->setScale(0.1f);
		sceneManager->addNode(fighter3);
	}

	Vertexf position(0.0f, 2.0f, 10.0f);
	Vertexf target( 0.0f, 0.0f,-5.0f);
	//Vertexf position(75,75,75);
	//Vertexf target( 0,1.5f,0);
	camera = new Camera(position , target);
}

void init()
{
	
	////glClearDepth(1);
	//glDepthFunc(GL_LEQUAL);
	//glEnable(GL_DEPTH_TEST);

	glCullFace(GL_BACK);
    glFrontFace(GL_CCW);
    glEnable(GL_DEPTH_TEST);

	beforeInit();
	sceneManager->init(); 
	
	//init_resources();

	text.registerFont("FreeSans","FreeSans.ttf"); 
	text.setActiveFont("FreeSans");
	text.setCurrentColor(CCOLORS::COLOR_YELLOW);
	//initFont();
	//rect init
	initRect2d(500,155,300,155);
}

void main(int argc, char **argv)
{	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(windowWidth,windowHeight);
	glutCreateWindow("Testing Engine");
	
	glutIdleFunc(renderScene);
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	glutKeyboardFunc(processNormalKeys);
	glutSpecialFunc(processSpecialKeys);
	
	
	//glew stuff
	GLenum err = glewInit();
	if(GLEW_OK != err)
	{
		std::cout<<glewGetErrorString(err);
	}
	std::cout<<glewGetString(GLEW_VERSION)<<std::endl;

	init(); ///a lot of thing should move to this function
	glutMainLoop();
}