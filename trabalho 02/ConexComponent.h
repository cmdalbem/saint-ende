#ifndef _CONEXCOMPONENT_H_
#define _CONEXCOMPONENT_H_


#include "bib/EasyBMP.h"
#include "Imagem.h"


class ConexComponent
{
    private:

        int area;
        int perimeter;
        int xo, yo; //um ponto qualquer pertencente à linha de borda do componente
        int x1, x2, y1, y2; //coordenadas da bounding box

        bool isMarkedPix(int x, int y, Imagem *image);
		bool known;

    public:
        ConexComponent(int x, int y, Imagem *image);
        ~ConexComponent();

		// pegadores
		
		int getX1() {return x1;}
		int getX2() {return x2;}
		int getY1() {return y1;}
		int getY2() {return y2;}

        // FUNÇÕES

        void findBoundingBox(int x, int y, Imagem *image);

        void drawBoundingBox(Imagem *image);

        void drawBoundingFillBox(Imagem *image);

        void findArea(int x, int y, Imagem *image);

        double getCompacity();
        
        
        // Funções Específicas de Componentes
        
		bool isKnown() {return known;}
		
        bool isClock(Imagem *image);
        const char* tellTimeOfClock(Imagem *image);


};





#endif

