#include "Texture.h"

void saveTextureToFile(const std::string filename, GLuint textureID)
{
	int width, height, internalFormat;
	int pitch = 0;
	char * pixelData = NULL;
	SDL_Surface * saveSurface = NULL;
    
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D,textureID);
	glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &width);
	glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &height);
	glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_COMPONENTS, &internalFormat);
    
	if (internalFormat == GL_RGB)
	{
		pixelData = new char[width*height * 3];
		pitch = 3 * width;
	}
	else if (internalFormat == GL_RGBA || internalFormat == GL_BGRA)
	{
		pixelData = new char[width*height * 4];
		pitch = 4 * width;
	}
    
	glGetTexImage(GL_TEXTURE_2D, 0, internalFormat, GL_UNSIGNED_BYTE, pixelData);
    
	saveSurface=SDL_CreateRGBSurfaceFrom(pixelData, width, height, 32, pitch,
                                         0, 0, 0, 0x000000ff);
    
	if (saveSurface)
	{
		IMG_SavePNG(saveSurface, filename.c_str());
		SDL_FreeSurface(saveSurface);
	}
	if (pixelData)
	{
		delete[] pixelData;
		pixelData = NULL;
	}
}

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
    GLenum internalFormat=GL_RGB8;
	if (nOfColors == 4)     // contains an alpha channel
	{
		if (imageSurface->format->Rmask == 0x000000ff){
			texture_format = GL_RGBA;
            internalFormat=GL_RGBA8;
        }
		else{
			texture_format = GL_BGRA;
            internalFormat=GL_RGBA8;
        }
	}
	else if (nOfColors == 3)     // no alpha channel
	{
		if (imageSurface->format->Rmask == 0x000000ff){
			texture_format = GL_RGB;
            internalFormat=GL_RGB8;
        }
		else
        {
			texture_format = GL_BGR;
            internalFormat=GL_RGB8;
        }
	}
	else {
		std::cout << "warning: the image is not truecolor..  this will probably break";
		// this error should not go unhandled
	}
	glGenTextures(1, &textureID);
    glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, imageSurface->w, imageSurface->h, 0, texture_format,
		GL_UNSIGNED_BYTE, imageSurface->pixels);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glGenerateMipmap(GL_TEXTURE_2D);
    
	SDL_FreeSurface(imageSurface);
	return textureID;
}