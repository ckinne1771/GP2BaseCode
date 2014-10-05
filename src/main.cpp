#include <iostream>
#include <GL/glew.h>
//maths headers
#include <glm/glm.hpp>
using glm::mat4;
using glm::vec3;

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#ifdef __APPLE__
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <OpenGL/glu.h>
#include <CoreFoundation/CoreFoundation.h>
#elif WIN32
#include <SDL.h>
#include <SDL_opengl.h>
#include <gl/GLU.h>
#endif

#ifdef _DEBUG && WIN32
const std::string ASSET_PATH = "../assets";
const std::string SHADER_PATH = "/shaders";
#elif __APPLE__
const std::string ASSET_PATH;
const std::string SHADER_PATH;
#else
const std::string ASSET_PATH="/assets";
const std::string SHADER_PATH="/shaders";
#endif



//Our headers
#include "Vertex.h"
#include "Shader.h"

//global values go here!
GLuint triangleVBO;
GLuint triangleEBO;
GLuint VAO;

//Shader Program
GLuint shaderProgram=0;

//matrices
mat4 viewMatrix;
mat4 projMatrix;
mat4 worldMatrix;

float triangleData[]={
//Front
 -0.5f, 0.5f, 0.5f ,// Top Left

 -0.5f, -0.5f, 0.5f,// Bottom Left

0.5f, -0.5f, 0.5f, //Bottom Right

0.5f, 0.5f, 0.5f ,// Top Right


//back
 -0.5f, 0.5f, -0.5f,// Top Left

 -0.5f, -0.5f, -0.5f ,// Bottom Left

 0.5f, -0.5f, -0.5f, //Bottom Right

 0.5f, 0.5f, -0.5f ,// Top Right

};


GLuint indices[]={
    //front
    0,1,2,
    0,3,2,
    
    //left
    4,5,1,
    4,1,0,
    
    //right
    3,7,2,
    7,6,2,
    
    //bottom
    1,5,2,
    6,2,1,
    
    //top
    5,0,7,
    5,7,3,
    
    //back
    4,5,6,
    4,7,6
};

//SDL Window
SDL_Window * window = NULL;
//SDL GL Context
SDL_GLContext glcontext = NULL;

//Window Width
const int WINDOW_WIDTH = 640;
//Window Height
const int WINDOW_HEIGHT = 480;

bool running = true;

//Global functions
void InitWindow(int width, int height, bool fullscreen)
{
	//Create a window
	window = SDL_CreateWindow(
		"Lab 3",             // window title
		SDL_WINDOWPOS_CENTERED,     // x position, centered
		SDL_WINDOWPOS_CENTERED,     // y position, centered
		width,                        // width, in pixels
		height,                        // height, in pixels
		SDL_WINDOW_OPENGL           // flags
		);
}

void CleanUp()
{
	// clean up, reverse order!!!
    glDeleteProgram(shaderProgram);
	glDeleteBuffers(1, &triangleVBO);
    glDeleteBuffers(1, &triangleEBO);
    glDeleteVertexArrays(1,&VAO);
	SDL_GL_DeleteContext(glcontext);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void createShader()
{
    GLuint vertexShaderProgram=0;
	std::string vsPath = ASSET_PATH + SHADER_PATH+"/simpleVS.glsl";
	vertexShaderProgram = loadShaderFromFile(vsPath, VERTEX_SHADER);
    
    glBindAttribLocation(vertexShaderProgram, 0, "vertexPosition");
    
    GLuint fragmentShaderProgram=0;
	std::string fsPath = ASSET_PATH + SHADER_PATH + "/simpleFS.glsl";
	fragmentShaderProgram = loadShaderFromFile(fsPath, FRAGMENT_SHADER);
    
    shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShaderProgram);
	glAttachShader(shaderProgram, fragmentShaderProgram);
	glLinkProgram(shaderProgram);
	checkForLinkErrors(shaderProgram);
    
	//now we can delete the VS & FS Programs
	glDeleteShader(vertexShaderProgram);
	glDeleteShader(fragmentShaderProgram);
    

}

void initGeometry()
{
    glGenVertexArrays( 1, &VAO );
    glBindVertexArray( VAO );
    
	//Create buffer
	glGenBuffers(1, &triangleVBO);
	// Make the new VBO active
	glBindBuffer(GL_ARRAY_BUFFER, triangleVBO);
	//Copy Vertex Data to VBO
	glBufferData(GL_ARRAY_BUFFER, 24*sizeof(float), triangleData, GL_STATIC_DRAW);
    
    //create buffer
    glGenBuffers(1, &triangleEBO);
    //Make the EBO active
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, triangleEBO);
    //Copy Index data to the EBO
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 36*sizeof(int), indices, GL_STATIC_DRAW);
    

}

//Function to update the game state
void update()
{
	projMatrix = glm::perspective(45.0f, (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.1f, 100.0f);
	viewMatrix = glm::lookAt(vec3(0.0f, 0.0f, 10.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));
    worldMatrix= glm::translate(mat4(1.0f), vec3(0.0f,0.0f,0.0f));
}

//Function to initialise OpenGL
void initOpenGL()
{
	//Create OpenGL Context
	glcontext = SDL_GL_CreateContext(window);

    glewExperimental = GL_TRUE;
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		/* Problem: glewInit failed, something is seriously wrong. */
		std::cout << "Error: " << glewGetErrorString(err) << std::endl;
	}
    
	glEnable(GL_DEPTH_TEST);
}

//Function to set/reset viewport
void setViewport( int width, int height )
{
    
    //make sure height is always above 1
    if ( height == 0 ) {
        height = 1;
    }

    
    //Setup viewport
    glViewport( 0, 0, ( GLsizei )width, ( GLsizei )height );
}

//Function to render(aka draw)
void render()
{
    //old imediate mode!
    //Set the clear colour(background)
    glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
    //clear the colour and depth buffer
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    
    //Make the new VBO active. Repeat here as a sanity check( may have changed since initialisation)
	glBindBuffer(GL_ARRAY_BUFFER, triangleVBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, triangleEBO);
    glBindVertexArray( VAO );
    
    glUseProgram(shaderProgram);
	GLint MVPLocation = glGetUniformLocation(shaderProgram, "MVP");
	if (MVPLocation != -1)
	{
		mat4 MVP = projMatrix*viewMatrix*worldMatrix;
		glUniformMatrix4fv(MVPLocation, 1, GL_FALSE, glm::value_ptr(MVP));
	}
    
    //Tell the shader that 0 is the position element
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

    //Actually draw the triangle, giving the number of vertices provided
	glDrawElements(GL_TRIANGLES,36,GL_UNSIGNED_INT,0);
    
    SDL_GL_SwapWindow(window);
}

//Main Method
int main(int argc, char * arg[])
{
    // Setup asset path, no real work required for Windows. Mac needs to load assets from a bundle
    // ----------------------------------------------------------------------------
    // http://stackoverflow.com/questions/516200/relative-paths-not-working-in-xcode-c
    // This makes relative paths work in C++ in Xcode by changing directory to the Resources folder inside the .app bundle
#ifdef __APPLE__
    CFBundleRef mainBundle = CFBundleGetMainBundle();
    CFURLRef resourcesURL = CFBundleCopyResourcesDirectoryURL(mainBundle);
    char path[PATH_MAX];
    if (!CFURLGetFileSystemRepresentation(resourcesURL, TRUE, (UInt8 *)path, PATH_MAX))
    {
        // error!
    }
    CFRelease(resourcesURL);
    
    chdir(path);
    std::cout << "Current Path: " << path << std::endl;
#endif
    

    
    // init everyting - SDL, if it is nonzero we have a problem
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        std::cout << "ERROR SDL_Init " <<SDL_GetError()<< std::endl;
        
        return -1;
    }
    
    //Ask for version 4.2 of OpenGL
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    
	InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, false);
    //Call our InitOpenGL Function
    initOpenGL();
    //Set our viewport
	setViewport(WINDOW_WIDTH, WINDOW_HEIGHT);
    
	initGeometry();
    createShader();

    //Value to hold the event generated by SDL
    SDL_Event event;
    //Game Loop
	while (running)
    {
        //While we still have events in the queue
        while (SDL_PollEvent(&event)) {
            //Get event type
            if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE) {
                //set our boolean which controls the loop to false
                running = false;
            }
        }
		update();
        //render
		render();
       
        
    }
    

	CleanUp();
    
    return 0;
}