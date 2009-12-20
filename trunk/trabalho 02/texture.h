#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include <string>

#include "Imagem.h"

using std::string;

int findTexture(Imagem texture, int originX, int originY);

double compare(Imagem& first, Imagem& second, int originX, int originY, int width, int height); //result in [0,1] where 1 means "totally equal".
void loadTextureCell(Imagem& textureCell, int index);
void loadTexture(Imagem& textureCell, int index);

#endif //_TEXTURE_H_
