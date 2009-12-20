#include<stdlib.h>
#include<iostream>

#include "BarCode.h"


using namespace std;


BarCode::BarCode() {}

BarCode::BarCode(Imagem nuimage)
{
    image = nuimage;
    
    this->findCodeBar();
    
    pixPerBar = getPixPerBar();
}

BarCode::BarCode(int nux1, int nuy1, int nux2, int nuy2, Imagem nuimage)
{
    image = nuimage;
    
    x1 = nux1;
    y1 = nuy1;
    x2 = nux2;
    y2 = nuy2;
    
    pixPerBar = getPixPerBar();
}
    

BarCode::~BarCode() {}


int BarCode::getPixPerBar() {
    
    int barsize = (x2-x1)/BARDCODE_NBARS;

//    int barsize=0;
//    for( int x=x1; image.getR(x,0)==0; x++ )
//        barsize++;

    return barsize;
}



void BarCode::findCodeBar()
{
    
    int framex1=0;
    while( image.isWhitePix(framex1,image.getH()/2) ) //encontra lado esquerdo da margem
        framex1++;
    
    int framex2=image.getW()-1;
    while( image.isWhitePix(framex2,image.getH()/2) ) //encontra lado direito da margem
        framex2--;
        
    x1=framex1;
    while( image.isBlackPix(x1,image.getH() * RELATIVE_CODEBAR_POS ) ) //pula a margem esquerda
        x1++;
    while( image.isWhitePix(x1,image.getH() * RELATIVE_CODEBAR_POS ) ) //encontra o inicio do codigo de barras
        x1++;
        
    x2=framex2;
    while( image.isBlackPix(x2,image.getH() * RELATIVE_CODEBAR_POS ) ) //pula a margem direita
        x2--;
    while( image.isWhitePix(x2,image.getH() * RELATIVE_CODEBAR_POS ) ) //encontra o fim do codigo de barras
        x2--;
    x2 = x2+1;
      
    y1 = y2 = image.getH() * 0.875; //podemos usar os mesmos y1 e y2 para o caso de ler apenas uma linha de pixels do código
}


int BarCode::parseEAN8digit(char binstring[7], int group)
{
    if( group == LEFTGROUP ) {
        if( !strncmp(binstring,"0001101",7) )
            return 0;
        if( !strncmp(binstring,"0011001",7) )
            return 1;
        if( !strncmp(binstring,"0010011",7) )
            return 2;
        if( !strncmp(binstring,"0111101",7) )
            return 3;
        if( !strncmp(binstring,"0100011",7) )
            return 4;
        if( !strncmp(binstring,"0110001",7) )
            return 5;
        if( !strncmp(binstring,"0101111",7) )
            return 6;
        if( !strncmp(binstring,"0111011",7) )
            return 7;
        if( !strncmp(binstring,"0110111",7) )
            return 8;
        if( !strncmp(binstring,"0001011",7) )
            return 9;        
    }    
    else {
        if( !strncmp(binstring,"1110010",7) )
            return 0;
        if( !strncmp(binstring,"1100110",7) )
            return 1;
        if( !strncmp(binstring,"1101100",7) )
            return 2;
        if( !strncmp(binstring,"1000010",7) )
            return 3;
        if( !strncmp(binstring,"1011100",7) )
            return 4;
        if( !strncmp(binstring,"1001110",7) )
            return 5;
        if( !strncmp(binstring,"1010000",7) )
            return 6;
        if( !strncmp(binstring,"1000100",7) )
            return 7;
        if( !strncmp(binstring,"1001000",7) )
            return 8;
        if( !strncmp(binstring,"1110100",7) )
            return 9;
    }
        
    return -1;
}

vector<int> BarCode::translateBinaryStream(vector<int> stream)
//sistema de código de barras EAN-8
{
    vector<int> digits;
    
    //GRUPO DA ESQUERDA
    for(int i=0; i<4; i++) {

        char binstring[7];
        for(int k=0; k<7; k++)
            binstring[k] = stream[k + i*7 +3] +48/*transforma número em char*/;
        
        digits.push_back( parseEAN8digit(binstring,LEFTGROUP) );
    }
    
    //GRUPO DA DIREITA
    for(int i=4; i<8; i++) {

        char binstring[7];
        for(int k=0; k<7; k++)
            binstring[k] = stream[k + i*7 +8] +48/*transforma número em char*/;
        
        digits.push_back( parseEAN8digit(binstring,RIGHTGROUP) );
    }   
    
    return digits;
}



vector<int> BarCode::translateBarCode()
{
    vector<int> binaryStream;

    srand ( time(NULL) );


    //for ( int y=0; y<1; y++ ) {
    int y = y1 + ((y2-y1)/2); //vai pro meio do código
        for ( int x=x1 +pixPerBar/2; x<x2; x+=pixPerBar ) {
            
            //cout<<"image.getR("<<x<<","<<y<<") = "<<image.getR(x,y)<<endl;
//            int media=0;
//            for(int i=-1; i<=1; i++)
//                media+=image.getR(x+i,y);
//            
//            cout << media/3 << endl;
            
            if ( /*media/3*/ image.getR(x,y) > MIDTOM ){
                binaryStream.push_back(0);
            //    cout<<" ";
            }
            else{
                binaryStream.push_back(1);
            //    cout<<(char)178;
            }
        }
        cout<<endl;
    //}

    return translateBinaryStream(binaryStream);
}
