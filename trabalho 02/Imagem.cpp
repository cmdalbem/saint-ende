#include<stdlib.h>
#include<iostream>
#include<conio2.h>

#include "Imagem.h"

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

    if( x>=0 && x<this->w && y>=0 && y<this->h )
        return image(x,y)->Red;
    else
        return -1;
}

int Imagem::getB(int x, int y) {

    if( x>=0 && x<this->w && y>0 && y<this->h )
        return image(x,y)->Blue;
    else
        return -1;
}

int Imagem::getG(int x, int y) {

    if( x>=0 && x<this->w && y>=0 && y<this->h )
        return image(x,y)->Green;
    else
        return -1;
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


int Imagem::load(char path[]) {

    if( image.ReadFromFile(path) ) {

            strcpy(imagePath,path);

			w = image.TellWidth();
			h = image.TellHeight();

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

        gotoxy(1,wherey()); cout<<"Limiarizing... "<<j*100/h +1<<"% ";
    }
    cout<<endl<<endl;
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

        gotoxy(1,wherey()); cout<<"Inverting... "<<j*100/h +1<<"% ";
    }
    cout<<endl<<endl;
}
    

void Imagem::fullDilate()
{
    int matrix[3][3] = { 1, 1, 1,
                       1, 1, 1,
                       1, 1, 1 };

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

        gotoxy(1,wherey()); cout<<"Dilating... "<<j*100/h +1<<"% ";
    }
    cout<<endl<<endl;
    

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

        gotoxy(1,wherey()); cout<<"Converting to GrayScale... "<<j*100/h +1<<"% ";
    }

    cout<<endl<<endl;
}
