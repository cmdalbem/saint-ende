#ifndef _DEFINITIONS_H_
#define _DEFINITIONS_H_


//MACROS

#define DEBUG cout<<__LINE__<<endl
#define PRINTVAR(x) cout<<#x<<" = "<<x<<endl
#define WAIT cout<<"done! press any key to continue..."; system("pause")


//CONSTANTES

#define MAX_URL 1024

#define MIDTOM 128 //mid-tom (256/2)

#define RELATIVE_CODEBAR_POS 0.875

#define BARDCODE_NBARS 67


enum{
    
    RIGHTGROUP = 0,
    LEFTGROUP  = 1,    
};



enum{
    //tipos de máscara de convolução
    LAPLACE =0,
    MEDIA,
    GAUSS,
    DERIVADA_PRIMEIRA
};

//enum{
//    //tipos de cores
//    BLACK =0,
//    DARKBLUE,
//    GREEN,
//    RED,
//    WHITE,
//    LIGHTBLUE,
//    PINK,
//    YELLOW
//};


#endif
