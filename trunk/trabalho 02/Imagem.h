#ifndef _IMAGEM_H_
#define _IMAGEM_H_

#include "bib/EasyBMP.h" // por favor usar essa barra --> / para separar diretorios
#include "kht/kht.h"
#include "definitions.h"
#include "linearAlgebra.h"
#include <vector>

using std::vector;

class ConexComponent;

class Imagem
{
    private:

		//atributos
        BMP image;
		int h, w; //height, widht
		char imagePath[MAX_URL];

		int internalFrameX1, internalFrameX2, internalFrameY1, internalFrameY2; //working frame (quadro que será considerado)


        Point findFirstPixel(int threshold);
		int truncaValor(int valor);
		void zeraBufalo(int* bufalo);
        void printMask(float *mask,int tam);
        void convolucao_nxn(float *mask, int n); //ImagemConvolution.cpp
        void copy(BMP im);


    public:
        Imagem(){};
        ~Imagem(){};

        vector<ConexComponent*> conexComponents;


        // GETTERS e setters ... dã
        int getR(int x, int y);
        int getB(int x, int y);
        int getG(int x, int y);
        bool isGreenPix(int x, int y);
        bool pixelIsEdge(int x, int y, int threshold);

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

		ConexComponent* getConexComponent(int index);
        // FUNÇÕES BÁSICAS

        bool isWhitePix(int x, int y);
        bool isBlackPix(int x, int y);

        // FUNÇÕES BÁSICAS

        char* getImagePath();

        int load(const char path[]);

        int save(const char path[]);

        void convertToGrayScale();

        void limiarize(double threshold);

        float bestLimiar();

        void fullDilate();

        void binaryInversion();

        void negative();

        void findInternalBox();

        void findConexComponents(int maxComponents);
        
        vector<int> unknownComponents();

        void spatialMapping(Point oldPos[4], Point newPos[4]);

        void findEdge();

        unsigned char* getArray();
        void readFromArray(unsigned char* array, int imWidth, int imHeight);

        // ImagemConvolution.cpp

        void laplaciano();
        void media();
        void gaussiano();
        void derivadaPrimeira();

        void customMask(int n);


        // ImagemOperators.cpp

		Imagem operator+=(Imagem aImage);

		Imagem operator-=(Imagem aImage);

		Imagem& operator=(Imagem aImage);

        //Hough

        void houghTransform();
};




#endif

