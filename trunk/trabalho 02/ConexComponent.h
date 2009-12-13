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

    public:
        ConexComponent(int x, int y, Imagem *image);
        ~ConexComponent();


        // FUNÇÕES

        void findBoundingBox(int x, int y, Imagem *image);

        void drawBoundingBox(Imagem *image);

        void drawBoundingFillBox(Imagem *image);

        void findArea(int x, int y, Imagem *image);

        double getCompacity();


};





#endif

