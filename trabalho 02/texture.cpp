#include "texture.h"

int findTexture(Imagem texture, int originX, int originY)
{

    const int textureTotal = 9, maxBorderSize = 4;

    texture.convertToGrayScale();
    texture.limiarize(texture.bestLimiar());


    Imagem textureCell;

    double comparison[textureTotal] = {0,0,0, 0,0,0, 0,0,0};
    int bestChoiceIndex = 0;

    for(int i = 1; i < textureTotal; ++i)
    {
        loadTextureCell(textureCell, i);

        textureCell.convertToGrayScale();
        textureCell.limiarize(textureCell.bestLimiar());

        std::cout << std::endl << std::endl;
        for(int k = 0; k <= maxBorderSize; ++k)
        {
            double compareK = compare(texture, textureCell, originX + k, originY + k, textureCell.getW(), textureCell.getH());

            std::cout << compareK << ' ';

            if(compareK >= comparison[i]) comparison[i] = compareK;
        }
        std::cout << " -> " << comparison[i] << std::endl;
        //comparison[i] = compare(texture, textureCell, originX, originY, textureCell.getW(), textureCell.getH());
        if(comparison[i] > comparison[bestChoiceIndex]) bestChoiceIndex = i;
    }

    std::cout << std::endl << std::endl << "Best: " << comparison[bestChoiceIndex] << std::endl << std::endl ;



    return bestChoiceIndex;
}


double compare(Imagem& first, Imagem& second, int originX, int originY, int width, int height)
{
    double total = 0, equals = 0;

    for(int i = 0; i < width; ++i)
        for(int j = 0; j < height; ++j)
        {
            ++total;
            if(first.getR(originX + i, originY + j) == second.getR(i,j)){ ++ equals; }
        }
    return (total != 0? equals/total : 1);
}

void loadTextureCell(Imagem& textureCell, int index)
{
    char indexString[5] = "0";
    if(index < 9999) itoa(index, indexString, 10);
    string texturePath = string("patterns/cell_") + indexString + string(".bmp") ;

    textureCell.load(texturePath.c_str());

}

void loadTexture(Imagem& textureCell, int index)
{
    char indexString[5] = "0";
    if(index < 9999) itoa(index, indexString, 10);
    string texturePath = string("patterns/pattern_") + string(indexString) + string(".bmp") ;

    textureCell.load(texturePath.c_str());
}
