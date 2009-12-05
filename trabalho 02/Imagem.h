#ifndef _IMAGEM_H_
#define _IMAGEM_H_



#include "bib\EasyBMP.h"
#include "definitions.h"

class Imagem
{
    private:

		//atributos
        BMP image;
		int h, w; //height, widht
		char imagePath[MAX_URL];
		
		
		int truncaValor(int valor);
		void zeraBufalo(int* bufalo);
        void printMask(float *mask,int tam);
        void convolucao_nxn(float *mask, int n); //ImagemConvolution.cpp
        
    public:
        Imagem(){};
        ~Imagem(){};
        
        // GETTERS
        int getR(int x, int y);
        int getB(int x, int y);
        int getG(int x, int y);
        
        int getH();
        int getW();
        
        
        // FUNÇÕES BÁSCIAS

        char* getImagePath();

        int load(char path[]);

        int save(char path[]);
        
        void convertToGrayScale();
        
        void limiarize(double treshold);
        
        void fullDilate();
        
        void binaryInversion();
    
        
        // ImagemConvolution.cpp
        
        void laplaciano();
        void media();       
        void gaussiano();
        void derivadaPrimeira();
        
        void customMask(int n);
        
        
        // ImagemOperators.cpp
         	
		Imagem operator+=(Imagem aImage);
		
		Imagem operator-=(Imagem aImage);
		
		Imagem operator=(Imagem aImage);
     
};




#endif
