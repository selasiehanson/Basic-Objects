#include  "engine/Engine.h"
#include  <ft2build.h>


//libraries to be loaded
#pragma comment(lib,"glew32d.lib")
#pragma comment(lib,"freetype249_D.lib")

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


base::objects::CMesh *mesh;
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






void renderScene()
{	
	glClearColor(0, 0, 0.2f, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	sceneManager->setViewMatrix(camera->getMatrix());
	//glEnable(GL_CULL_FACE);

	//do light stuff here
	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	sceneManager->render();	
	
	//glDisable(GL_CULL_FACE);
	
	
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
	
	glm::mat4 src(0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15);
	
	auto srcValue = glm::value_ptr(src);
	
	float dst[9];
	memcpy(dst,srcValue, sizeof(float ) * 3 );
	memcpy(dst + 3 , srcValue + 4, sizeof(float) * 3);
	memcpy(dst + 6 , srcValue + 8 , sizeof(float) * 3 );
	 
	sceneManager = new SceneManager;
	skybox =  new SkyBox(skyImages,sceneManager,1000.0f);
	auto s = reinterpret_cast<CSkyBox * >(skybox);
	//sceneManager->setSkyBox(skybox);

	//create a single triangle
	//mesh = new base::objects::CMesh(EMESH_TYPE::TRIANGLE);
	//triangle = new TriangleSceneNode(sceneManager,mesh);
	//sceneManager->addNode(triangle);

	auto planeMesh = new base::objects::CMesh(EMESH_TYPE::PLANE);
	ground = new Plane(sceneManager,planeMesh, GL_LINES);
	if(ground){
		ground->setPosition(20.0f, -0.1f, 10.0f);
		sceneManager->addNode(ground);
	}

	//creating lights
	//light =  new Light(vec3(-100.0f, 100.0f, 100.0f),vec4(0.0f, 0.0f, 1.0f, 1.0f));

	//sceneManager->addNode(light);

	//draw a colletion of cubes
	const auto size = 1;
	Cube *cubes[size];
	const char * texture  = "3_store.jpg";
	auto cubeMesh = new base::objects::CMesh(EMESH_TYPE::CUBE,0.7f);
	

	for(int i=0; i < size; i++)
	{
		auto z = rand() % 40;
		auto x = rand() % 40;
		//std::cout<<"adding cube " << i +1<<endl;
		//cubes[i] = new Cube(sceneManager,0.7f,texture);
		cubes[i] = new Cube(sceneManager,cubeMesh,0.7f,texture,true, GL_POLYGON);
		cubes[i]->setPosition(x , 0, z);
		sceneManager->addNode(cubes[i]);
	}

	fighter1 = new ModelSceneNode(sceneManager,"Hover01_Body.obj","FB_hover01_uv01.jpg");
	if(fighter1)
	{
		fighter1->setPosition(20,0,10);
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

	Vertexf position(20.0f, 1.0f, 20.0f);
	Vertexf target( 0.0f, 0.0f,-50.0f);
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
	text.setCurrentColor(CCOLORS::YELLOW);
	//initFont();
	//rect init
	//initRect2d(500,155,300,155);
}

void main(int argc, char **argv)
{	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(550,0);
	glutInitWindowSize(windowWidth,windowHeight);
	glutCreateWindow("IN-gine");
	
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
	std::cout<<"Running on GLEW Version : "<<glewGetString(GLEW_VERSION)<<std::endl;

	init(); ///a lot of things should move to this function
	glutMainLoop();
}