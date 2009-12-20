#include<stdlib.h>
#include<iostream>

#include "Imagem.h"

using namespace std;




Imagem Imagem::operator+=(Imagem aImage)
//buffer + original
{
    for(int x=0; x < w; x++){

        for(int y=0; y < h; y++) {

            image(x,y)->Red = truncaValor( image(x,y)->Red + aImage.image(x,y)->Red );
			image(x,y)->Blue = truncaValor( image(x,y)->Blue + aImage.image(x,y)->Blue );
			image(x,y)->Green = truncaValor( image(x,y)->Green + aImage.image(x,y)->Green );
	    }

	    //gotoxy(1,wherey()); cout<<"Operando soma... "<<x*100/w +1<<"% ";
    }

    cout<<endl;

    return *this;
}


Imagem Imagem::operator-=(Imagem aImage)
//buffer + original
{
    for(int x=0; x < w; x++){

        for(int y=0; y < h; y++) {

            image(x,y)->Red = truncaValor( image(x,y)->Red - aImage.image(x,y)->Red );
			image(x,y)->Blue = truncaValor( image(x,y)->Blue - aImage.image(x,y)->Blue );
			image(x,y)->Green = truncaValor( image(x,y)->Green - aImage.image(x,y)->Green );
	    }

	    //gotoxy(1,wherey()); cout<<"Operando subtracao... "<<x*100/w +1<<"% ";
    }

    cout<<endl;

    return *this;
}


Imagem& Imagem::operator=(Imagem aImage)
{
    this->load( aImage.getImagePath() );

    this->internalFrameX1 = aImage.internalFrameX1;
    this->internalFrameX2 = aImage.internalFrameX2;
    this->internalFrameY1 = aImage.internalFrameY1;
    this->internalFrameY2 = aImage.internalFrameY2;


    for(int x=0; x < w; x++)

        for(int y=0; y < h; y++) {

            this->image(x,y)->Red = aImage.image(x,y)->Red;
            this->image(x,y)->Blue = aImage.image(x,y)->Blue;
            this->image(x,y)->Green = aImage.image(x,y)->Green;
	    }


    return *this;
}

