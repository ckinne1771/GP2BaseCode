#include "Texture.h"

GLuint loadTextureFromFile(const std::string& filename)
{
	GLuint textureID = 0;
	SDL_Surface *imageSurface = IMG_Load(filename.c_str());

	if (!imageSurface){
		std::cout << "Can' Load image " << filename << " " << IMG_GetError();
		return textureID;
	}

	//Texture format may be weird, we use some SDL functions to convert to RGB
	SDL_Surface * myNewSurface = SDL_CreateRGBSurface(0, imageSurface->w, imageSurface->h, 32, 0xff000000, 0x00ff0000, 0x0000ff00, 0x000000ff);
	SDL_BlitSurface(imageSurface, 0, myNewSurface, 0); /* blit onto a purely RGB Surface*/
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, myNewSurface->w, myNewSurface->h, 0, GL_RGBA,
		GL_UNSIGNED_BYTE, myNewSurface->pixels);


	SDL_FreeSurface(myNewSurface);
	SDL_FreeSurface(imageSurface);

	return textureID;
}