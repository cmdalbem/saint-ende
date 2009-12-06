#include<stdlib.h>
#include<iostream>

#include "BarCode.h"


using namespace std;


BarCode::BarCode() {}

BarCode::BarCode(int nux1, int nuy1, int nux2, int nuy2, Imagem nuimage)
{
    image = nuimage;
    
    x1 = nux1;
    y1 = nuy1;
    x2 = nux2;
    y2 = nuy2;
    
    pixPerBar = getPixPerBar();
    
    cout<<"pixPerBar="<<pixPerBar<<endl;
}
    

BarCode::~BarCode() {}


int BarCode::getPixPerBar() {
    
    int barsize = (x2-x1)/BARDCODE_NBARS;

    return barsize;
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


    for ( int y=0; y<1; y++ ) {
    
        for ( int x=x1 +pixPerBar/2; x<x2; x+=(pixPerBar)) {
            
            //cout<<image.getR(x,y)<<endl;
            int media=0;
            for(int i=-2; i<=2; i++)
                media+=image.getR(x+i,y);
            
            //cout << media/3 << endl;
            
            if ( media/5 > 128 ){
                binaryStream.push_back(0);
                cout<<" ";
            }
            else{
                binaryStream.push_back(1);
                cout<<(char)178;
            }
        }
        cout<<endl;
    }

    return translateBinaryStream(binaryStream);
}
