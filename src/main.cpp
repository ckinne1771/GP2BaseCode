#include <iostream>
#include <fstream>
#include <string>

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
const std::string ASSET_PATH = "../../assets";
#elif
const std::string ASSET_PATH = "assets";
#endif

const std::string SHADER_PATH = "/shaders";

//global values go here!
//VBO
GLuint triangleVBO;

float triangleData[] = { 0.0f, 1.0f, 0.0f, // Top
						-1.0f, -1.0f, 0.0f, // Bottom Left
						1.0f, -1.0f, 0.0f }; //Bottom Right

//Shader
GLuint shaderProgram;

//
bool loadShader(const std::string& filename, char ** shaderData, unsigned long *shaderSize)
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

		if (*shaderSize == 0)
		{
			std::cout << "File has no contents " << std::endl;
			return false;
		}
		*shaderData = new char[len + 1];
		*shaderData[len] = 0;
		unsigned int i = 0;
		while (file.good())
		{
			*shaderData[i] = file.get();       // get character from file.
			if (!file.eof())
				i++;
		}

		*shaderData[i] = 0;  // 0-terminate it at the correct position
		*shaderSize = (unsigned long)i;
		file.close();
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

	//Create and link shaders
	char * vsSource=NULL;
	unsigned long vsLen;
	std::string vsPath = ASSET_PATH + SHADER_PATH + "/SimpleVS.vert";
	loadShader(vsPath, &vsSource, &vsLen);

	if (vsSource)
	{
		delete[] vsSource;
	}
}

//Function to update the game state
void update()
{
    
}

//Function to initialise OpenGL
void initOpenGL()
{
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

	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		/* Problem: glewInit failed, something is seriously wrong. */
		std::cout << "Error: "<<glewGetErrorString(err) << std::endl;
	}
}

//Function to set/reset viewport
void setViewport( int width, int height )
{
    //screen ration
    GLfloat ratio;
    
    //make sure height is always above 1
    if ( height == 0 ) {
        height = 1;
    }
    
    //calculate screen ration
    ratio = ( GLfloat )width / ( GLfloat )height;
    
    //Setup viewport
    glViewport( 0, 0, ( GLsizei )width, ( GLsizei )height );
    
    //Change to poject matrix mode
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity( );
    
    //Calculate perspective matrix, using glu library functions
    gluPerspective( 45.0f, ratio, 0.1f, 100.0f );
    
    //Swith to ModelView
    glMatrixMode( GL_MODELVIEW );
    
    //Reset using the Indentity Matrix
    glLoadIdentity( );
}

//Function to render(aka draw)
void render()
{
    //old imediate mode!
    //Set the clear colour(background)
    glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
    //clear the colour and depth buffer
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    
    //Swith to ModelView
    glMatrixMode( GL_MODELVIEW );
    //Reset using the Indentity Matrix
    glLoadIdentity( );
    //translate
    glTranslatef( -2.0f, 0.0f, -6.0f );
    
    //Begin drawing triangles
    glBegin( GL_TRIANGLES );
        glVertex3f(  0.0f,  1.0f, 0.0f ); // Top
        glVertex3f( -1.0f, -1.0f, 0.0f ); // Bottom Left
        glVertex3f(  1.0f, -1.0f, 0.0f ); // Bottom Right
    glEnd( );

	//move four units from previous position
	glTranslatef(4.0f, 0.0f, 0.0f);
	//Make the new VBO active. Repeat here incase changed since initialisation
	glBindBuffer(GL_ARRAY_BUFFER, triangleVBO);

	//Draw Triangle from VBO - do each time window, view point or data changes
	//Establish its 3 coordinates per vertex with zero stride in this array; necessary here
	glVertexPointer(3, GL_FLOAT, 0, NULL);

	//Establish array contains vertices (not normals, colours, texture coords etc)
	glEnableClientState(GL_VERTEX_ARRAY);

	//Actually draw the triangle, giving the number of vertices provided
	glDrawArrays(GL_TRIANGLES, 0, sizeof(triangleData) / sizeof(float) / 3);
}

//Main Method
int main(int argc, char * arg[])
{
    //Controls the game loop
    bool run=true;
    bool pause=false;
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
	glDeleteBuffers(1, &triangleVBO);
    SDL_GL_DeleteContext(glcontext);
    SDL_DestroyWindow(window);
    SDL_Quit();
    
    return 0;
}