#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "../header/Vertex.h"

#ifdef __APPLE__
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <OpenGL/glu.h>
#elif WIN32
#include <GL\glew.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include <gl\GLU.h>
#endif

#ifdef _DEBUG
const std::string ASSET_PATH = "../assets";
#elif
const std::string ASSET_PATH = "assets";
#endif

const std::string SHADER_PATH = "/shaders";

//global values go here!
//VBO
GLuint triangleVBO;

ColourVertex triangleData[] = { { 0.0f, 1.0f, 0.0f,
1.0f, 1.0f, 1.0f, 1.0f },// Top

{ -1.0f, -1.0f, 0.0f,
1.0f, 1.0f, 1.0f, 1.0f },// Bottom Left

{ 1.0f, -1.0f, 0.0f,
1.0f, 1.0f, 1.0f, 1.0f } }; //Bottom Right

//basic 2d shader
GLuint shaderProgram;

//Loads a shader into a string
bool loadShaderFromFile(const std::string& filename, std::string& shaderData)
{
	std::ifstream file;
	file.open(filename.c_str(), std::ios::in);
	if (!file)
	{
		std::cout << "Can't load Shader file " << filename << std::endl;
		return false;
	}
	//calculate file size
	if (file.good())
	{
		file.seekg(0, std::ios::end);
		unsigned long len= file.tellg();
		file.seekg(std::ios::beg);

		if (len == 0)
		{
			std::cout << "File has no contents " << std::endl;
			return false;
		}

		shaderData.resize(len);
		file.read(&shaderData[0], len);
		file.close();
	}
	return true;
}

bool checkForLinkErrors(GLuint program)
{
	GLint isLinked = 0;
	glGetProgramiv(program, GL_LINK_STATUS, &isLinked);
	if (isLinked == GL_FALSE) {

		GLint maxLength = 0;
		glGetShaderiv(shaderProgram, GL_INFO_LOG_LENGTH, &maxLength);

		//The maxLength includes the NULL character
		std::string infoLog;
		glGetShaderInfoLog(shaderProgram, maxLength, &maxLength, &infoLog[0]);

		std::cout << "Shader not linked " << infoLog << std::endl;

		//We don't need the shader anymore.
		glDeleteProgram(program);
		return false;
	}

	return true;
}

bool checkForCompilerErrors(GLuint shaderProgram)
{
	GLint isCompiled = 0;
	glGetShaderiv(shaderProgram, GL_COMPILE_STATUS, &isCompiled);
	if (isCompiled == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetShaderiv(shaderProgram, GL_INFO_LOG_LENGTH, &maxLength);

		//The maxLength includes the NULL character
		std::string infoLog;
		glGetShaderInfoLog(shaderProgram, maxLength, &maxLength, &infoLog[0]);

		std::cout << "Shader not compiled " << infoLog << std::endl;

		//We don't need the shader anymore.
		glDeleteShader(shaderProgram);
		return false;

	}
	return true;
}

void initGame()
{
	//Create buffer
	glGenBuffers(1, &triangleVBO);
	// Make the new VBO active
	glBindBuffer(GL_ARRAY_BUFFER, triangleVBO);
	//Upload vertex data to the video device
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangleData), triangleData, GL_STATIC_DRAW);

	//Create shaders
	GLuint vertexShaderProgram;
	std::string vsSource;
	std::string vsPath = ASSET_PATH + SHADER_PATH+"/SimpleVS.glsl";


	loadShaderFromFile(vsPath, vsSource);
	vertexShaderProgram=glCreateShader(GL_VERTEX_SHADER);
	const GLchar *source = (const GLchar *)vsSource.c_str();
	glShaderSource(vertexShaderProgram, 1, &source, NULL);
	glCompileShader(vertexShaderProgram);
	checkForCompilerErrors(vertexShaderProgram);

	//bind locations
	glBindAttribLocation(vertexShaderProgram, 0, "vertexPosition");

	GLuint fragmentShaderProgram;
	std::string fsSource;
	std::string fsPath = ASSET_PATH + SHADER_PATH + "/SimpleFS.glsl";

	loadShaderFromFile(fsPath, fsSource);
	fragmentShaderProgram = glCreateShader(GL_FRAGMENT_SHADER);
	source = (const GLchar *)fsSource.c_str();
	glShaderSource(fragmentShaderProgram, 1, &source, NULL);
	glCompileShader(fragmentShaderProgram);
	checkForCompilerErrors(fragmentShaderProgram);

	
	//Now Create and link
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShaderProgram);
	glAttachShader(shaderProgram, fragmentShaderProgram);
	glLinkProgram(shaderProgram);
	checkForLinkErrors(shaderProgram);

	//now we can delete the VS & FS Programs
	glDeleteShader(vertexShaderProgram);
	glDeleteShader(fragmentShaderProgram);
}

//Function to update the game state
void update()
{
    
}

//Function to initialise OpenGL
void initOpenGL()
{
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		/* Problem: glewInit failed, something is seriously wrong. */
		std::cout << "Error: "<<glewGetErrorString(err) << std::endl;
	}
}

//Function to set/reset viewport
void setViewport(int width, int height)
{
	//screen ration
	GLfloat ratio;

	//make sure height is always above 1
	if (height == 0) {
		height = 1;
	}

	//calculate screen ration
	ratio = (GLfloat)width / (GLfloat)height;

	//Setup viewport
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);
}

//Function to render(aka draw)
void render()
{
    //old imediate mode!
    //Set the clear colour(background)
    glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
    //clear the colour and depth buffer
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	//Bind buffer containing our triangle
	glBindBuffer(GL_ARRAY_BUFFER, triangleVBO);

	//Use our shader program
	glUseProgram(shaderProgram);
	//Tell the shader that 0 is the position element
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(ColourVertex), NULL);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(ColourVertex), &triangleData[0].r);
	//Draw our traingle
	glDrawArrays(GL_TRIANGLES, 0, 3);
}

//Main Method
int main(int argc, char * arg[])
{
    //Controls the game loop
    bool run=true;
    bool pause=false;
	//Ask for version 4.2 of OpenGL
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

    // init everyting - SDL, if it is nonzero we have a problem
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        std::cout << "ERROR SDL_Init " <<SDL_GetError()<< std::endl;
        
        return -1;
    }

	std::cout << SDL_GetPlatform() << std::endl;
	std::cout << "Number of CPU Cores " << SDL_GetCPUCount()<< std::endl;
	std::cout << "RAM(in Mb) " << SDL_GetSystemRAM() << std::endl;
    
    //Create a window
    SDL_Window * window = SDL_CreateWindow(
                                           "SDL",             // window title
                                           SDL_WINDOWPOS_CENTERED,     // x position, centered
                                           SDL_WINDOWPOS_CENTERED,     // y position, centered
                                           640,                        // width, in pixels
                                           480,                        // height, in pixels
                                           SDL_WINDOW_OPENGL           // flags
                                           );
    // Create an OpenGL context associated with the window.
    SDL_GLContext glcontext = SDL_GL_CreateContext(window);
    
    //Call our InitOpenGL Function
    initOpenGL();
    //Set our viewport
    setViewport(640,480);
    
	initGame();

    //Value to hold the event generated by SDL
    SDL_Event event;
    //Game Loop
    while(run)
    {
        //While we still have events in the queue
        while (SDL_PollEvent(&event)) {
            //Get event type
            if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE) {
                //set our boolean which controls the loop to false
                run = false;
            }
            if (event.type==SDL_WINDOWEVENT)
            {
                switch (event.window.event) {
                    case SDL_WINDOWEVENT_MINIMIZED:
                            pause=true;
                        break;
                    default:
                        break;
                }
                
            }
        }
        if (!pause){
            //update
            update();
        }
        //render
        render();
        //Call swap so that our GL buffer is displayed
        SDL_GL_SwapWindow(window);
        
    }
    
    // clean up, reverse order!!!
	glDeleteProgram(shaderProgram);
	glDeleteBuffers(1, &triangleVBO);
    SDL_GL_DeleteContext(glcontext);
    SDL_DestroyWindow(window);
    SDL_Quit();
    
    return 0;
}