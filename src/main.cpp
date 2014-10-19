//Properties -> Debugging -> Environment -> "PATH=F:\MATLAB R2010b\bin\win32"

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
#include <SDL2_ttf/SDL_ttf.h>
#include <SDL2_image/SDL_image.h>
#elif WIN32
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <gl/GLU.h>
#endif

#ifdef _DEBUG && WIN32
const std::string ASSET_PATH = "../assets/";
const std::string SHADER_PATH = "shaders/";
const std::string TEXTURE_PATH = "textures/";
const std::string FONT_PATH = "fonts/";
#elif __APPLE__
const std::string ASSET_PATH;
const std::string SHADER_PATH;
const std::string TEXTURE_PATH;
const std::string FONT_PATH;
#else
const std::string ASSET_PATH="/assets/";
const std::string SHADER_PATH="shaders/";
#endif

//Our headers
#include "Vertex.h"
#include "Shader.h"
#include "Texture.h"

//global values go here!
//UI
GLuint UIVBO;
GLuint UIEBO;
GLuint UIVAO;

//3D World
GLuint gameVBO;
GLuint gameEBO;
GLuint gameVAO;

//Shader Program
GLuint shaderProgramUI=0;
GLuint shaderProgramGame=0;

//matrices
mat4 viewMatrix;

//UI
mat4 projMatrixUI;
mat4 worldMatrixUI;

mat4 projMatrixGame;
mat4 worldMatrixGame;

//Texture
GLuint texture=0;
GLuint nameTexture = 0;


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
		"Lab 4",             // window title
		SDL_WINDOWPOS_CENTERED,     // x position, centered
		SDL_WINDOWPOS_CENTERED,     // y position, centered
		width,                        // width, in pixels
		height,                        // height, in pixels
		SDL_WINDOW_OPENGL           // flags
		);
}

void CleanUp2DScene()
{
	glDeleteTextures(1, &nameTexture);
    glDeleteProgram(shaderProgramUI);
	glDeleteBuffers(1, &UIVBO);
    glDeleteBuffers(1, &UIEBO);
    glDeleteVertexArrays(1,&UIVAO);
}

void CleanUp3DScene()
{
	glDeleteTextures(1, &texture);
    glDeleteProgram(shaderProgramUI);
    glDeleteProgram(shaderProgramGame);
	glDeleteBuffers(1, &gameVBO);
    glDeleteBuffers(1, &gameEBO);
    glDeleteVertexArrays(1,&gameVAO);
}

void CleanUp()
{
	// clean up, reverse order!!!
    CleanUp2DScene();
    CleanUp3DScene();
	SDL_GL_DeleteContext(glcontext);
	SDL_DestroyWindow(window);
	IMG_Quit();
	TTF_Quit();
	SDL_Quit();
}


void create2DScene()
{
    std::string fontPath = ASSET_PATH + FONT_PATH + "OratorStd.otf";
	nameTexture = loadTextureFromFont(fontPath, 28, "Test");
    
    GLuint vertexShaderProgram=0;
	std::string vsPath = ASSET_PATH + SHADER_PATH+"vertexColourTextureVS.glsl";
	vertexShaderProgram = loadShaderFromFile(vsPath, VERTEX_SHADER);
    
    GLuint fragmentShaderProgram=0;
	std::string fsPath = ASSET_PATH + SHADER_PATH + "vertexColourTextureFS.glsl";
	fragmentShaderProgram = loadShaderFromFile(fsPath, FRAGMENT_SHADER);
    
    shaderProgramUI = glCreateProgram();
	glAttachShader(shaderProgramUI, vertexShaderProgram);
	glAttachShader(shaderProgramUI, fragmentShaderProgram);
	glLinkProgram(shaderProgramUI);
	checkForLinkErrors(shaderProgramUI);
    
	//now we can delete the VS & FS Programs
	glDeleteShader(vertexShaderProgram);
	glDeleteShader(fragmentShaderProgram);
    
    glBindAttribLocation(shaderProgramUI, 0, "vertexPosition");
	glBindAttribLocation(shaderProgramUI,1, "vertexTexCoords");
	glBindAttribLocation(shaderProgramUI, 2, "vertexColour");
    
    int width, height;
    
	glBindTexture(GL_TEXTURE_2D, nameTexture);
	glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &width);
	glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &height);
    
	Vertex spriteData[] = {
		//Front
        { vec3(0.0, 0.0f, 0.0f), vec2(0.0f, 0.0f), vec4(1.0f, 1.0f, 1.0f, 1.0f) },// Top Left
        
        { vec3(0.0f, height, 0.0f), vec2(0.0f, 1.0f), vec4(1.0f, 1.0f, 1.0f, 1.0f) },// Bottom Left
        
        { vec3(width, height, 0.0f), vec2(1.0f, 1.0f), vec4(1.0f, 1.0f, 1.0f, 1.0f) }, //Bottom Right
        
        { vec3(width, 0.0f, 0.0f), vec2(1.0f, 0.0f), vec4(1.0f, 1.0f, 1.0f, 1.0f) }// Top Right
        
	};
    
    GLuint spriteIndices[]={
        //front
        0,1,2,
        0,3,2,
    };
    
	glGenVertexArrays(1, &UIVAO);
	glBindVertexArray(UIVAO);
	//Create buffer
	glGenBuffers(1, &UIVBO);
	// Make the new VBO active
	glBindBuffer(GL_ARRAY_BUFFER, UIVBO);
	//Copy Vertex Data to VBO
	glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(Vertex), spriteData, GL_STATIC_DRAW);
    
	//create buffer
	glGenBuffers(1, &UIEBO);
	//Make the EBO active
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, UIEBO);
	//Copy Index data to the EBO
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(int), spriteIndices, GL_STATIC_DRAW);
    
	//Tell the shader that 0 is the position element
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), NULL);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void**)sizeof(vec3));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void**)(sizeof(vec3) + sizeof(vec2)));
}


void create3DScene()
{
    std::string texturePath = ASSET_PATH + TEXTURE_PATH + "test.png";
	texture = loadTextureFromFile(texturePath);
    
    GLuint vertexShaderProgram=0;
	std::string vsPath = ASSET_PATH + SHADER_PATH+"textureVS.glsl";
	vertexShaderProgram = loadShaderFromFile(vsPath, VERTEX_SHADER);
    
    GLuint fragmentShaderProgram=0;
	std::string fsPath = ASSET_PATH + SHADER_PATH + "textureFS.glsl";
	fragmentShaderProgram = loadShaderFromFile(fsPath, FRAGMENT_SHADER);
    
    shaderProgramGame = glCreateProgram();
	glAttachShader(shaderProgramGame, vertexShaderProgram);
	glAttachShader(shaderProgramGame, fragmentShaderProgram);
	glLinkProgram(shaderProgramGame);
	checkForLinkErrors(shaderProgramGame);
    
	//now we can delete the VS & FS Programs
	glDeleteShader(vertexShaderProgram);
	glDeleteShader(fragmentShaderProgram);
    
    glBindAttribLocation(shaderProgramGame, 0, "vertexPosition");
	glBindAttribLocation(shaderProgramGame,1, "vertexTexCoords");
	glBindAttribLocation(shaderProgramGame, 2, "vertexColour");
    
    Vertex triangleData[] = {
        //Front
		{ vec3(-0.5, 0.5f, 0.0f), vec2(0.0f, 0.0f), vec4(1.0f, 0.0f, 0.0f, 1.0f) },// Top Left
        
		{ vec3 (- 0.5f, -0.5f, 0.0f), vec2(0.0f,1.0f), vec4(0.0f, 1.0f, 0.0f, 1.0f) },// Bottom Left
        
		{ vec3(0.5f, -0.5f, 0.0f), vec2(1.0f, 1.0f), vec4(0.0f, 0.0f, 1.0f, 1.0f) }, //Bottom Right
        
		{ vec3(0.5f, 0.5f, 0.0f), vec2(1.0f, 0.0f), vec4(1.0f, 0.0f, 0.0f, 1.0f) }// Top Right
        
    };
    
    
    GLuint indices[]={
        //front
        0,1,2,
        0,3,2,
    };
    
    glGenVertexArrays( 1, &gameVAO );
    glBindVertexArray( gameVAO );
	//Create buffer
	glGenBuffers(1, &gameVBO);
	// Make the new VBO active
	glBindBuffer(GL_ARRAY_BUFFER, gameVBO);
	//Copy Vertex Data to VBO
	glBufferData(GL_ARRAY_BUFFER, 4*sizeof(Vertex), triangleData, GL_STATIC_DRAW);
    
    //create buffer
    glGenBuffers(1, &gameEBO);
    //Make the EBO active
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gameEBO);
    //Copy Index data to the EBO
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6*sizeof(int), indices, GL_STATIC_DRAW);
    
	//Tell the shader that 0 is the position element
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), NULL);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void**)sizeof(vec3));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void**)(sizeof(vec3) + sizeof(vec2)));
}

void update2DScene()
{
	viewMatrix = glm::lookAt(vec3(0.0f, 0.0f, 2.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));
	projMatrixUI = glm::ortho(0.0f, (float)WINDOW_WIDTH, (float)WINDOW_HEIGHT,0.0f,0.1f, 100.0f);
    worldMatrixUI= glm::translate(mat4(1.0f), vec3(10.0f,10.0f,-10.0f));
}

void update3DScene()
{
    projMatrixGame = glm::perspective(45.0f, (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.1f, 100.0f);
    viewMatrix = glm::lookAt(vec3(0.0f, 0.0f, 2.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));
    worldMatrixGame= glm::translate(mat4(1.0f), vec3(0.0f,0.0f,-10.0f));
}

//Function to update the game state
void update()
{
    update3DScene();
    update2DScene();
}

//Function to initialise OpenGL
void initOpenGL()
{
    //Ask for version 3.2 of OpenGL
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    
	//Create OpenGL Context
	glcontext = SDL_GL_CreateContext(window);

    glewExperimental = GL_TRUE;
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		/* Problem: glewInit failed, something is seriously wrong. */
		std::cout << "Error: " << glewGetErrorString(err) << std::endl;
	}
    
    //Smooth shading
    glShadeModel( GL_SMOOTH );
    
    //clear the background to black
    glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
    
    //Clear the depth buffer
    glClearDepth( 1.0f );
    
    //Enable depth testing
    glEnable( GL_DEPTH_TEST );
    
    //The depth test to go
    glDepthFunc( GL_LEQUAL );
    
    //Turn on best perspective correction
    glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );

	

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

void render2D()
{
    //Turn on Alpha Blending
    glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    glBindVertexArray( UIVAO );
    
    glUseProgram(shaderProgramUI);
	GLint MVPLocation = glGetUniformLocation(shaderProgramUI, "MVP");
	mat4 MVP = projMatrixUI*viewMatrix*worldMatrixUI;
	glUniformMatrix4fv(MVPLocation, 1, GL_FALSE, glm::value_ptr(MVP));
	
	GLint texture0Location = glGetUniformLocation(shaderProgramUI, "texture0");
    
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, nameTexture);
	glUniform1i(texture0Location, 0);
    
    //Actually draw the triangle, giving the number of vertices provided
	glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);

}

void render3D()
{
    glBindVertexArray( gameVAO );
    
    glUseProgram(shaderProgramGame);
	GLint MVPLocation = glGetUniformLocation(shaderProgramGame, "MVP");
	mat4 MVP = projMatrixGame*viewMatrix*worldMatrixGame;
	glUniformMatrix4fv(MVPLocation, 1, GL_FALSE, glm::value_ptr(MVP));
	
	GLint texture0Location = glGetUniformLocation(shaderProgramGame, "texture0");
    
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glUniform1i(texture0Location, 0);
    
    //Actually draw the triangle, giving the number of vertices provided
	glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);
}

//Function to render(aka draw)
void render()
{
    //old imediate mode!
    //Set the clear colour(background)
    glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
    //clear the colour and depth buffer
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    
    render2D();
    render3D();
    
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
    
	int imageInitFlags = IMG_INIT_JPG | IMG_INIT_PNG;
	int returnInitFlags = IMG_Init(imageInitFlags);
	if (((returnInitFlags) & (imageInitFlags)) != imageInitFlags) {
		std::cout << "ERROR SDL_Image Init " << IMG_GetError() << std::endl;
		// handle error
	}

	if (TTF_Init() == -1) {
		std::cout << "TTF_Init: " << TTF_GetError();
	}
    
	InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, false);
    //Call our InitOpenGL Function
    initOpenGL();
    //Set our viewport
	setViewport(WINDOW_WIDTH, WINDOW_HEIGHT);

    create2DScene();
    create3DScene();
    GLenum error;
    do{
        error=glGetError();
    }while(error!=GL_NO_ERROR);
    
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