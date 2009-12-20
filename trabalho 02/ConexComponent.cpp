#include "ConexComponent.h"
#include <iostream>
#include <cmath>

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

    this->drawBoundingFillBox(image); //usar isso na análise de componentes conexos fará com que ignoremos os "buracos" dos componentes
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
// Não consegui fazer essa função funcionar (Cristiano)
// Há casos em que o preenchimento "vasa" do componente conexo. Por exemplo, isso funciona para Letras mas não para Símbolos
{
//    image->setGreenPix(x,y);
//
//    for(int i=-1; i<2; i++)
//        for(int j=-1; j<2; j++)
//            if( !isMarkedPix(x+i,y+j,image) ) {
//                area++;
//                findArea(x+i,y+j,image);
//            }
}

double ConexComponent::getCompacity()
{
    return (perimeter*perimeter) / area;
}


int ConexComponent::tellTimeOfClock(Imagem *image)
//retorna -1 se não conseguir ler as horas
{
    double PI = 3.141592653589793238462643383279502884197169399375;
    
    int midx = (x1+x2)/2;
    int midy = (y1+y2)/2;
    int pointerSize = ((x2 - midx)*3)/4;
    int hour, minute;

    // MINUTE
    int pointerWidth =0;
    double pointerAngle =0;
    for(double i=0; i<2*PI; i+=0.01) { //iteração circular
        
        double itx = pointerSize*sin(i) + midx;
        double ity = pointerSize*cos(i) + midy;

        if( image->isWhitePix(itx, ity) ) {
            pointerWidth++;
            pointerAngle += i;
        }
    }
    pointerAngle = pointerAngle/pointerWidth;
    image->setRedPix( pointerSize*sin(pointerAngle) + midx , pointerSize*cos(pointerAngle) + midy);
    minute = (60*pointerAngle) / (2*PI);
    
    // HOUR
    pointerWidth =0;
    pointerAngle =0;
    pointerSize = pointerSize/2;
    for(double i=0; i<2*PI; i+=0.01) {

        double itx = pointerSize*sin(i) + midx;
        double ity = pointerSize*cos(i) + midy;

        if( image->isWhitePix(itx, ity) ) {
            pointerWidth++;
            pointerAngle +=i;
        }
    }
    pointerAngle = pointerAngle/pointerWidth;
    image->setRedPix( pointerSize*sin(pointerAngle) + midx , pointerSize*cos(pointerAngle) + midy);
    hour = (12*pointerAngle) / (2*PI);
    
    
    cout<< hour << "h " << minute << "min." << endl;

        
    return 1;
}
    
