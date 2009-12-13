#include "ConexComponent.h"
#include <iostream>

using namespace std;


ConexComponent::ConexComponent(int x, int y, Imagem *image)
{
    this->x1 = image->getW();
    this->x2 = 0;
    this->y1 = image->getH();
    this->y2 = 0;

    xo = x;
    yo = y;

    area = 0;
    perimeter = 0;


    this->findBoundingBox(xo,yo,image);

    //this->findArea(xo+2,yo+2,image);

//    this->drawBoundingFillBox(image); //usar isso na an�lise de componentes conexos far� com que ignoremos os "buracos" dos componentes
}

ConexComponent::~ConexComponent() {}


void ConexComponent::findBoundingBox(int x, int y, Imagem *image)
{
    if( x < this->x1 )
        this->x1 = x;
    else if( x > this->x2 )
           this->x2 = x;
    if( y < this->y1 )
        this->y1 = y;
    else if(y>this->y2)
           this->y2=y;


    image->setGreenPix(x,y);


    for(int i=-1; i<2; i++)
        for(int j=-1; j<2; j++)
            if( image->isWhitePix(x+i,y+j) ) {
                perimeter++;
                findBoundingBox(x+i,y+j,image);
            }
}

void ConexComponent::drawBoundingBox(Imagem *image)
{
    for(int i=x1; i<=x2; i++) //linha horizontal superior
        image->setRedPix(i,y1);
    for(int i=x1; i<=x2; i++) //linha horizontal inferior
        image->setRedPix(i,y2);
    for(int i=y1; i<=y2; i++) //linha vertical esquerda
        image->setRedPix(x1,i);
    for(int i=y1; i<=y2; i++) //linha vertical direita
        image->setRedPix(x2,i);
}

void ConexComponent::drawBoundingFillBox(Imagem *image)
{
    for(int i=x1; i<=x2; i++)
        for(int j=y1; j<=y2; j++) {
            image->setRedPix(i,j);
        }
}

bool ConexComponent::isMarkedPix(int x, int y, Imagem *image)
{
    return (image->getR(x,y)==0) && (image->getG(x,y)==255) && (image->getB(x,y)==0);
}


void ConexComponent::findArea(int x, int y, Imagem *image)
{
    image->setGreenPix(x,y);

    for(int i=-1; i<2; i++)
        for(int j=-1; j<2; j++)
            if( !isMarkedPix(x+i,y+j,image) ) {
                area++;
                findArea(x+i,y+j,image);
            }
}

double ConexComponent::getCompacity()
{
    return (perimeter*perimeter) / area;
}

