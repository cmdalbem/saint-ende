#include<stdlib.h>
#include<iostream>
//#include<conio2.h>

#include "Imagem.h"

using namespace std;


void Imagem::convolucao_nxn(float *mask, int n)
{


    const int delta = (int)floor(n/2);

    int* bufaloR = (int*) malloc(sizeof(int)*w*h);
        zeraBufalo(bufaloR);
    int* bufaloG = (int*) malloc(sizeof(int)*w*h);
        zeraBufalo(bufaloG);
    int* bufaloB = (int*) malloc(sizeof(int)*w*h);
        zeraBufalo(bufaloB);


    for(int x=delta; x < w-delta; x++){

        for(int y=delta; y < h-delta; y++)

            for( int i = 0-delta;  i  <  n-delta; i++)

                for( int k = 0-delta;  k  <  n-delta; k++){

                    bufaloR[x+w*y] = bufaloR[x+w*y] + (int)(image(x+i,y+k)->Red)   * mask [i+delta + n*(k+delta)];
                    bufaloG[x+w*y] = bufaloG[x+w*y] + (int)(image(x+i,y+k)->Green) * mask [i+delta + n*(k+delta)];
                    bufaloB[x+w*y] = bufaloB[x+w*y] + (int)(image(x+i,y+k)->Blue)  * mask [i+delta + n*(k+delta)];
                }

    }
    cout<<endl<<endl;

    for(int x=0; x < w; x++)

			for(int y=0; y < h; y++) {

				//algoritmo pode gerar valores negativos e maiores que 255, números estes que não têm interpretação em níveis de cinza
				bufaloR[x+w*y] = truncaValor(bufaloR[x+w*y]);
				bufaloG[x+w*y] = truncaValor(bufaloG[x+w*y]);
				bufaloB[x+w*y] = truncaValor(bufaloB[x+w*y]);

			    image(x,y)->Red = (ebmpBYTE) bufaloR[x+w*y];
				image(x,y)->Blue = (ebmpBYTE) bufaloB[x+w*y];
				image(x,y)->Green = (ebmpBYTE) bufaloG[x+w*y];
			}
}




void Imagem::customMask(int n)
{
    float mask[n][n];

    for(int x=0; x<n; x++)
        for(int y=0; y<n; y++)
            mask[x][y] = 0;

    cout<<"-> Matriz de Convolucao"<<endl<<endl;


    //Entrada formatada de matriz

    int posx=1, posy=wherey();
    for(int y=0; y<n; y++){

        for(int x=0; x<n; x++){

            gotoxy( posx+(x+2)*8 , posy+y );

            cin >> mask[x][y];
            while(!cin){
                cin.clear(); cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                gotoxy( posx+(x+2)*8 , posy+y ); cout<<" \a"; gotoxy( posx+(x+2)*8 , posy+y );
                cin >> mask[x][y];
            }

        }
    }

    //Chamada da operação
    convolucao_nxn((float*)mask,n);
}


void Imagem::laplaciano()
{
    float mask[3][3] = { -1, -1, -1,
                         -1,  8, -1,
                         -1, -1, -1 };

    printMask((float*)mask,3);
    convolucao_nxn((float*)mask,3);
}
void Imagem::media()
{
    float mask[3][3] = { (float)1/9, (float)1/9, (float)1/9,
                         (float)1/9, (float)1/9, (float)1/9,
                         (float)1/9, (float)1/9, (float)1/9 };

    printMask((float*)mask,3);
    convolucao_nxn((float*)mask,3);
}
void Imagem::gaussiano()
{
    float mask[3][3] = { 0.0625, 0.125 ,0.0625,
                         0.125,  0.25,  0.125,
                         0.0625, 0.125 ,0.0625 };

    printMask((float*)mask,3);
    convolucao_nxn((float*)mask,3);
}
void Imagem::derivadaPrimeira()
{
    float mask[3][3] = {  0, -1,  0,
                         -1,  4, -1,
                          0, -1,  0 };

    printMask((float*)mask,3);
    convolucao_nxn((float*)mask,3);
}

