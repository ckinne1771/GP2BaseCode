#include "Texture.h"

GLuint loadTextureFromFile(const std::string& filename)
{
	GLuint textureID = 0;
	SDL_Surface *imageSurface = IMG_Load(filename.c_str());

	if (!imageSurface){
		std::cout << "Can' Load image " << filename << " " << IMG_GetError();
		return textureID;
	}

	// get the number of channels in the SDL surface
	GLint  nOfColors = imageSurface->format->BytesPerPixel;
	GLenum texture_format = GL_RGB;
	if (nOfColors == 4)     // contains an alpha channel
	{
		if (imageSurface->format->Rmask == 0x000000ff)
			texture_format = GL_RGBA;
		else
			texture_format = GL_BGRA;
	}
	else if (nOfColors == 3)     // no alpha channel
	{
		if (imageSurface->format->Rmask == 0x000000ff)
			texture_format = GL_RGBA;
		else
			texture_format = GL_BGR;
	}
	else {
		std::cout << "warning: the image is not truecolor..  this will probably break";
		// this error should not go unhandled
	}
	
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, texture_format, imageSurface->w, imageSurface->h, 0, texture_format,
		GL_UNSIGNED_BYTE, imageSurface->pixels);
	glGenerateMipmap(GL_TEXTURE_2D);
	SDL_FreeSurface(imageSurface);

	return textureID;
}