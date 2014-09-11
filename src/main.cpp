//Header files
#include <iostream>

//If we are on APPLE
#ifdef __APPLE__
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <OpenGL/glu.h>
//IF we are on WIN32
#elif WIN32
#include <SDL.h>
#endif

//global values go here!
SDL_Window * window;

const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;

//Global functions
void InitWindows(int width, int height, bool fullscreen)
{
	//Create a window
	window = SDL_CreateWindow(
		"Lab 1",             // window title
		SDL_WINDOWPOS_CENTERED,     // x position, centered
		SDL_WINDOWPOS_CENTERED,     // y position, centered
		width,                        // width, in pixels
		height,                        // height, in pixels
		SDL_WINDOW_OPENGL           // flags
		);
}

void CleanUp()
{
	SDL_DestroyWindow(window);
	SDL_Quit();
}

//Main Method - Entry Point
int main(int argc, char * arg[])
{
	// init everything - SDL, if it returns nonzero we have a problem
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		std::cout << "ERROR SDL_Init " << SDL_GetError() << std::endl;

		return -1;
	}

	InitWindows(WINDOW_WIDTH, WINDOW_HEIGHT, false);
	CleanUp();
    return 0;
}