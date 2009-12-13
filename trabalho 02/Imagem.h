#ifndef _IMAGEM_H_
#define _IMAGEM_H_



#include "bib/EasyBMP.h" // por favor usar essa barra --> / para separar diretorios
#include "definitions.h"





class Imagem
{
    private:

		//atributos
        BMP image;
		int h, w; //height, widht
		char imagePath[MAX_URL];

		int internalFrameX1, internalFrameX2, internalFrameY1, internalFrameY2; //working frame (quadro que ser� considerado)


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
        bool isWhitePix(int x, int y);
        bool isBlackPix(int x, int y);
        void setR(int x, int y, int value);
        void setB(int x, int y, int value);
        void setG(int x, int y, int value);
        void setGreenPix(int x, int y);
        void setRedPix(int x, int y);

        int getH();
        int getW();

        int getInternalFrameX1();
        int getInternalFrameX2();
        int getInternalFrameY1();
        int getInternalFrameY2();
        void setInternalFrameX1(int x1);
        void setInternalFrameX2(int x2);
        void setInternalFrameY1(int y1);
        void setInternalFrameY2(int y2);


        // FUN��ES B�SCIAS

        char* getImagePath();

        int load(char path[]);

        int save(char path[]);

        void convertToGrayScale();

        void limiarize(double treshold);

        float bestLimiar();

        void fullDilate();

        void binaryInversion();

        void findInternalBox();

        void findConexComponents();


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

