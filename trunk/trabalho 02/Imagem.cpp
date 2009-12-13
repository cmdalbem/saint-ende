#include<stdlib.h>
#include<iostream>
//#include<conio2.h>

#include "Imagem.h"
#include "ConexComponent.h"

#include <vector>

using namespace std;




///////////////////////
// PRIVATE FUNCTIONS //
///////////////////////

int Imagem::truncaValor(int valor)
{
	    if( valor < 0 )

					return 0;

			else if( valor > 255 )

							return 255;

						else

								return valor;
}


void Imagem::zeraBufalo(int* bufalo)
{
    for(int x=0; x<w; x++)
        for(int y=0; y<h; y++)
            bufalo[x+w*y] = 0;
}


void Imagem::printMask(float *mask, int tam)
{
    cout<<"-> Matriz de Convolucao"<<endl<<endl;
    for(int i=0; i<tam; i++){
        for( int k=0; k<tam; k++)
            cout << "\t" << mask[i + k*tam] << " ";
        cout << endl;
    }
    cout<<endl<<endl;
}




//////////////////////
// PUBLIC FUNCTIONS //
//////////////////////

int Imagem::getR(int x, int y) {

    return image(x,y)->Red;
}

int Imagem::getB(int x, int y) {

    return image(x,y)->Blue;
}

int Imagem::getG(int x, int y) {

    return image(x,y)->Green;
}

bool Imagem::isWhitePix(int x, int y) {

    return (image(x,y)->Green == 255) && (image(x,y)->Red == 255) && (image(x,y)->Blue == 255);
}
bool Imagem::isBlackPix(int x, int y) {

    return (image(x,y)->Green == 0) && (image(x,y)->Red == 0) && (image(x,y)->Blue == 0);
}

void Imagem::setR(int x, int y, int value) {

    image(x,y)->Red = (ebmpBYTE) value;
}

void Imagem::setB(int x, int y, int value) {

    image(x,y)->Blue = (ebmpBYTE) value;
}

void Imagem::setG(int x, int y, int value) {

    image(x,y)->Green = (ebmpBYTE) value;
}
void Imagem::setGreenPix(int x, int y)
{
    this->setR(x,y,0);
    this->setG(x,y,255);
    this->setB(x,y,0);
}
void Imagem::setRedPix(int x, int y)
{
    this->setR(x,y,255);
    this->setG(x,y,0);
    this->setB(x,y,0);
}

int Imagem::getH() {
    return this->h;
}

int Imagem::getW() {
    return this->w;
}

char* Imagem::getImagePath() {

    return imagePath;
}

int Imagem::getInternalFrameX1() {

    return internalFrameX1;
}

int Imagem::getInternalFrameX2() {

    return internalFrameX2;
}

int Imagem::getInternalFrameY1() {

    return internalFrameY1;
}

int Imagem::getInternalFrameY2() {

    return internalFrameY2;
}
void Imagem::setInternalFrameX1(int x1) {

    internalFrameX1 = x1;
}

void Imagem::setInternalFrameX2(int x2) {

    internalFrameX2 = x2;
}

void Imagem::setInternalFrameY1(int y1) {

    internalFrameY1 = y1;
}

void Imagem::setInternalFrameY2(int y2) {

    internalFrameY2 = y2;
}



int Imagem::load(char path[]) {

    if( image.ReadFromFile(path) ) {

            strcpy(imagePath,path);

			w = image.TellWidth();
			h = image.TellHeight();

			internalFrameX1 = internalFrameY1 = 0;
			internalFrameX2 = w-1;
			internalFrameY2 = h-1;

			image.ReadFromFile(path);

			return 1;
    }
	else return 0;
}


int Imagem::save(char path[]) {

    return image.WriteToFile( path );
}


void Imagem::limiarize(double treshold)
{

    for(  int  j=0  ;  j  <  h  ;  j++) {

        for(  int  i=0  ;  i  <  w  ;  i++) {

            if( image(i,j)->Red > treshold ) {
                image(i,j)->Red = 255;
                image(i,j)->Green = 255;
                image(i,j)->Blue = 255;
            }
            else {
                image(i,j)->Red = 0;
                image(i,j)->Green = 0;
                image(i,j)->Blue = 0;
            }
        }

    }
}

float Imagem::bestLimiar()
{
    float m1 = 0;

    //média dos elementos nos cantos
    for (int i=0; i < h; ++i)
    {
        m1 += image(0,i)->Red;
        m1 += image(w,i)->Red;
    }

    for (int i=1; i < w-1; ++i)
    {
        m1 += image(i,0)->Red;
        m1 += image(i,h)->Red;
    }

    m1 /= 2*h + 2*(w-1);
    //end média

    float m2 = 0;

    //média dos elementos restantes
    for (int i=1; i < w-1; ++i)
        for (int j=1; j < h-1; ++j)
            m2 += image(i,j)->Red;

    m2 /= w + h - 4;
    //end média

    float lanterior = 0;
    float latual = (m1 + m2)/2;

    while (lanterior != latual)
    {
        m1 = 0; m2 = 0;
        int quantos = 0;

        for (int i=0; i < w; ++i)
            for (int j=0; j < h; ++j)
            {
                if (image(i,j)->Red < latual)
                {
                    ++quantos;
                    m1 += image(i,j)->Red;
                }
            }

        m1 /= quantos;

        quantos = 0;

        for (int i=0; i < w; ++i)
            for (int j=0; j < h; ++j)
            {
                if (image(i,j)->Red >= latual)
                {
                    ++quantos;
                    m2 += image(i,j)->Red;
                }
            }

        m2 /= quantos;

        lanterior = latual;
        latual = (m1+m2)/2;
    }

    return latual;
}

void Imagem::binaryInversion()
{
    for(  int  j=0  ;  j  <  h  ;  j++) {

        for(  int  i=0  ;  i  <  w  ;  i++) {

            if( image(i,j)->Red == 255 ) {
                image(i,j)->Red = 0;
                image(i,j)->Green = 0;
                image(i,j)->Blue = 0;
            }
            else {
                image(i,j)->Red = 255;
                image(i,j)->Green = 255;
                image(i,j)->Blue = 255;
            }
        }

    }
}


void Imagem::fullDilate()
{
    int matrix[3][3] = { { 1, 1, 1 } ,
                         { 1, 1, 1 },
                         { 1, 1, 1 }

    };

    //bufalo é uma matriz que representa uma imagem temporária
    int* bufalo = (int*) malloc(sizeof(int)*w*h);
    zeraBufalo(bufalo);


    //algoritmo
    for(  int  j=1  ;  j  <  h-1  ;  j++) {

        for(  int  i=1  ;  i  <  w-1  ;  i++) {

            int paintThis = 0;

            for(  int  x=-1  ;  x  <  2  ;  x++)
                for(  int  y=-1  ;  y  <  2  ;  y++)
                    if( image(i+x,j+y)->Red && matrix[x+1][y+1] )
                        paintThis = 255;

            bufalo[i+w*j] = paintThis;
        }

    }

    //passamos os valores da imagem temporária para a original
    for(int x=0; x < w; x++)
			for(int y=0; y < h; y++) {

			    image(x,y)->Red = (ebmpBYTE) bufalo[x+w*y];
				image(x,y)->Blue = (ebmpBYTE) bufalo[x+w*y];
				image(x,y)->Green = (ebmpBYTE) bufalo[x+w*y];
			}
}


void Imagem::convertToGrayScale()
//função retirada do manual da biblioteca EasyBMP
{
    for(  int  j=0  ;  j  <  h  ;  j++){

        for(  int  i=0  ;  i  <  w  ;  i++){

            int temp = (int) floor(   0.299*image(i,j)->Red
                                    + 0.587*image(i,j)->Green
                                    + 0.114*image(i,j)->Blue );

            image(i,j)->Red = (ebmpBYTE) temp;
            image(i,j)->Green = (ebmpBYTE) temp;
            image(i,j)->Blue =  (ebmpBYTE) temp;
        }

    }
}

void Imagem::findInternalBox()
{
    internalFrameX1 = 0;
    while( this->isWhitePix(internalFrameX1,this->getH()/2) ) //encontra lado esquerdo da margem
        internalFrameX1++;
    while( this->isBlackPix(internalFrameX1,this->getH()/2) ) //pula a margem esquerda
        internalFrameX1++;

    internalFrameX2 = this->getW()-1;
    while( this->isWhitePix(internalFrameX2,this->getH()/2) ) //encontra lado direito da margem
        internalFrameX2--;
    while( this->isBlackPix(internalFrameX2,this->getH()/2) ) //pula a margem direita
        internalFrameX2--;

    internalFrameY1 = 0;
    while( this->isWhitePix(this->getW()/2, internalFrameY1) ) //encontra lado esquerdo da margem
        internalFrameY1++;
    while( this->isBlackPix(this->getW()/2, internalFrameY1) ) //pula a margem esquerda
        internalFrameY1++;

    internalFrameY2 = this->getH()-1;
    while( this->isWhitePix(this->getW()/2, internalFrameY2) ) //encontra lado direito da margem
        internalFrameY2--;
    while( this->isBlackPix(this->getW()/2, internalFrameY2) ) //pula a margem direita
        internalFrameY2--;

}

void Imagem::findConexComponents()
{
    int x, y;
    x = internalFrameX1+1;
    y = internalFrameY1+1;

    vector<ConexComponent> components;

    Imagem drawingBuffer = *this;

    while( y < internalFrameY2 /*&& components.size()!=1*/) {

        while( x < internalFrameX2-1 /*&& components.size()!=1*/) {

            if( drawingBuffer.isWhitePix(x,y) )
                components.push_back(ConexComponent(x,y,&drawingBuffer)); //dá um ponto qualquer do contorno do componente e
            x++;
        }

        y++;
        x=internalFrameX1+1;
    }

    cout<<components.size()<<" components found."<<endl;

    vector<ConexComponent>::iterator it;
    for(it = components.begin(); it!=components.end(); it++)
        it->drawBoundingBox(this);

    *this = drawingBuffer;
}

