#include "Texture.h"
#include <math.h>

void saveTextureToFile(const std::string filename, GLuint textureID)
{
	int width, height, internalFormat;
	int numBytes = 0;
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
		0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);

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

//Will clean up the surface as well;
GLuint convertSDLSurfaceToGLTexture(SDL_Surface * surface)
{
	GLuint textureID = 0;
    GLint  nOfColors = surface->format->BytesPerPixel;
	GLenum texture_format = GL_RGB;
    GLenum internalFormat=GL_RGB8;
	if (nOfColors == 4)     // contains an alpha channel
	{
		if (surface->format->Rmask == 0x000000ff){
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
		if (surface->format->Rmask == 0x000000ff){
			texture_format = GL_RGB;
            internalFormat=GL_RGB8;
        }
		else
        {
			texture_format = GL_BGR;
            internalFormat=GL_RGB8;
        }
	}
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, surface->w, surface->h, 0, texture_format,
		GL_UNSIGNED_BYTE, surface->pixels);

	SDL_FreeSurface(surface);

	return textureID;
}

GLuint loadTextureFromFile(const std::string& filename)
{
	GLuint textureID = 0;
	SDL_Surface *imageSurface = IMG_Load(filename.c_str());

	if (!imageSurface){
		std::cout << "Can' Load image " << filename << " " << IMG_GetError();
		return textureID;
	}

	textureID = convertSDLSurfaceToGLTexture(imageSurface);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glGenerateMipmap(GL_TEXTURE_2D);

	

	return textureID;
}

GLuint loadTextureFromFont(const std::string& fontFilename, int pointSize, const std::string& text)
{
	GLuint textureID = 0;
	TTF_Font * font = TTF_OpenFont(fontFilename.c_str(),pointSize);
	if (!font)
	{
		std::cout << "Unable to load font " << fontFilename << " " << TTF_GetError();
        return textureID;
	}

	SDL_Surface *textSurface = TTF_RenderText_Blended(font, text.c_str(), { 255, 255, 255 });
	textureID=convertSDLSurfaceToGLTexture(textSurface);

	TTF_CloseFont(font);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	return textureID;
}