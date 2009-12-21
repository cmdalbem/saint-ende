#include<stdlib.h>
#include<iostream>

#include "Imagem.h"
#include "ConexComponent.h"

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


bool Imagem::isWhitePix(int x, int y) {

    return (image(x,y)->Green == 255) && (image(x,y)->Red == 255) && (image(x,y)->Blue == 255);
}
bool Imagem::isBlackPix(int x, int y) {

    return (image(x,y)->Green == 0) && (image(x,y)->Red == 0) && (image(x,y)->Blue == 0);
}


int Imagem::load(const char path[]) {

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

int Imagem::save(const char path[]) {

    return image.WriteToFile( path );
}


void Imagem::limiarize(double threshold)
{

    for(  int  j=0  ;  j  <  h  ;  j++) {

        for(  int  i=0  ;  i  <  w  ;  i++) {

            if( image(i,j)->Red > threshold ) {
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

void Imagem::binaryInversion()
//inverte uma imagem limiarizada
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

void Imagem::negative()
{
    for (int i=0; i < getW(); ++i)
    {
        for (int j=0; j < getH(); ++j)
        {
            image(i,j)->Red = 255 - image(i,j)->Red;
            image(i,j)->Green = 255 - image(i,j)->Green;
            image(i,j)->Blue = 255 - image(i,j)->Blue;
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

void Imagem::findConexComponents(int maxComponents)
//Aplicar essa função depois de já ter feito detecção de bordas
{
    int x, y;
    x = internalFrameX1+1;
    y = internalFrameY1+1;

//    static vector<ConexComponent*> conexComponents;

    Imagem drawingBuffer = *this;

    while( y < internalFrameY2 && conexComponents.size()!=maxComponents) {

        while( x < internalFrameX2-1 && conexComponents.size()!=maxComponents) {

            if( drawingBuffer.isWhitePix(x,y) )
                this->conexComponents.push_back(new ConexComponent(x,y,&drawingBuffer)); //dá um ponto qualquer do contorno do componente e
            x++;
        }

        y++;
        x=internalFrameX1+1;
    }

    cout<<conexComponents.size()<<" components found."<<endl;

//    desenhar drawingBoxes
//    vector<ConexComponent>::iterator it;
//    for(it = conexComponents.begin(); it!=conexComponents.end(); it++)
//        it->drawBoundingBox(this);

    //*this = drawingBuffer;
}

void Imagem::spatialMapping(Point oldPos[4], Point newPos[4])
{
    float **linSys = mallocMatrix(8,9);

    //4 primeiras equacoes com incognitas c1 a c4
    for(int i=0; i < 4; ++i)
    {
        linSys[i][0] = oldPos[i].x;
        linSys[i][1] = oldPos[i].y;
        linSys[i][2] = oldPos[i].x * oldPos[i].y;
        linSys[i][3] = 1;

        //incognitas c5 a c8 tem coeficiente 0
        for (int k=4; k < 8; ++k)
            linSys[i][k] = 0;

        linSys[i][8] = newPos[i].x;
    }

    for(int i=0; i < 4; ++i)
    {
        //incognitas c1 a c4 tem coeficiente 0
        for (int k=0; k < 4; ++k)
            linSys[i+4][k] = 0;

        //4 primeiras equacoes com incognitas c5 a c8
        linSys[i+4][4] = oldPos[i].x;
        linSys[i+4][5] = oldPos[i].y;
        linSys[i+4][6] = oldPos[i].x * oldPos[i].y;
        linSys[i+4][7] = 1;

        linSys[i+4][8] = newPos[i].y;
    }

    float *c = solve(linSys,8,9);

    BMP newImage;
    newImage.SetSize(getW(),getH());

    for (int i=0; i < getW(); ++i)
    {
        for (int j=0; j < getH(); ++j)
        {
            Point p = { i, j };
            Point p1 = spatialTransform(c,p);

            if ( (p1.x < getW() && p1.x >= 0 ) && (p1.y < getH() && p1.y >= 0) )
            {
                newImage(p1.x,p1.y)->Red = image(p.x,p.y)->Red;
                newImage(p1.x,p1.y)->Green = image(p.x,p.y)->Green;
                newImage(p1.x,p1.y)->Blue = image(p.x,p.y)->Blue;
            }
        }
    }

    copy(newImage);

}

void Imagem::copy(BMP im)
{
    if (getW() != im.TellWidth() || getH() != im.TellHeight())
    {
        DEBUG;
        cout << "Image sizes do not match, I wont do this sir!" << endl;
        return;
    }

    for (int i=0; i < getW(); ++i)
    {
        for (int j=0; j < getH(); ++j)
        {
            image(i,j)->Red = im(i,j)->Red;
            image(i,j)->Green = im(i,j)->Green;
            image(i,j)->Blue = im(i,j)->Blue;
        }
    }
}

float Imagem::bestLimiar()
{
    int m1 = 0;

    int quantos = 0;

    //média dos elementos nos cantos
    for (int i=0; i < h; ++i, quantos += 2)
    {
        m1 += image(0,i)->Red;
        m1 += image(w-1,i)->Red;
    }

    for (int i=1; i < w-1; ++i, quantos += 2)
    {
        m1 += image(i,0)->Red;
        m1 += image(i,h-1)->Red;
    }
    m1 /= quantos;
    //end média

    int m2 = 0;
    quantos = 0;

    //média dos elementos restantes
    for (int i=1; i < w-1; ++i)
        for (int j=1; j < h-1; ++j, ++quantos)
            m2 += image(i,j)->Red;

    m2 = m2/quantos;
    //end média

    int lanterior = 0;
    int latual = (m1 + m2)/2;

    while ( lanterior != latual)
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

        cout << lanterior << " " << latual;
    }

    return latual;
}

unsigned char * Imagem::getArray()
{
    unsigned char * arrayOfPixels = new unsigned char[w * h];
    Imagem copy = *this;
    copy.convertToGrayScale();
    copy.limiarize(copy.bestLimiar());

    for(int j = 0; j < h; ++j)
        for(int i = 0; i < w; ++i)
            arrayOfPixels[(j * w) + i] = copy.getR(i,j);

    return arrayOfPixels;
}

//NAO WORKA
//void Imagem::findEdge()
//{
//    Point neigh[8] = { {-1,-1},{0,-1},{1,-1},{-1,0},{1,0},{-1,1},{0,1},{1,1} };
//    int threshold = 10;

//    Point first = findFirstPixel(threshold);
//    Point invalid = {-1,-1};
//    Point cur, next;
//    cur = next = first;

//    do {
//        bool foundWay = false;

//        for (int i = 0; i < 8 && !foundWay ; ++i) {

//            Point test = { cur.x + neigh[i].x, cur.y + neigh[i].y};

//            if ( pixelIsEdge (test.x,test.y,threshold)  && !isGreenPix(test.x,test.y) )
//            {
//                foundWay = true;
//                next.x = cur.x + neigh[i].x; next.y = cur.y + neigh[i].y;
//                setGreenPix(next.x,next.y);
//            }

//            if (!foundWay)
//                next = invalid;
//        }

//    } while ( !(next == first) && !(next == invalid) );

//}

bool Imagem::isGreenPix(int i, int j)
{
    return  image(i,j)->Red == 0 &&
                image(i,j)->Green == 255 &&
                image(i,j)->Blue == 0;
}

bool Imagem::pixelIsEdge(int i,int j,int  threshold)
{
    return image(i,j)->Red < threshold;
}

Point Imagem::findFirstPixel(int threshold)
{
    for (int i=0; i < getW(); ++i)
    {
        for (int j=0; j < getH(); ++j)
        {
            if ( image(i,j)->Red < threshold)
            {
                Point first = { i, j };
                return first;
            }
        }
    }

    Point invalid = { -1,-1};
    return invalid;
}

