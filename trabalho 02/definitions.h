#ifndef _DEFINITIONS_H_
#define _DEFINITIONS_H_


//MACROS

#define DEBUG cout<<__LINE__<<endl
#define PRINTVAR(x) cout<<x<<" = "<<#x<<endl
#define WAIT cout<<"done! press any key to continue..."; getch()


//CONSTANTES

#define MAX_URL 1024

#define DEFAULT_LIMIARIZE 128

#define BARDCODE_NBARS 67


enum{
    
    RIGHTGROUP = 0,
    LEFTGROUP  = 1,    
};

//const char EAN8digits[][7] = {"0001101","0001101"};

enum{
    
    LGRP_0  = 0001101,
    LGRP_1  = 0011001,
    LGRP_2  = 0010011,
    LGRP_3  = 0111101,
    LGRP_4  = 0100011,
    LGRP_5  = 0110001,
    LGRP_6  = 0101111,
    LGRP_7  = 0111011,
    LGRP_8  = 0110111,
    LGRP_9  = 0001011,

    RGRP_0  = 1110010,
    RGRP_1  = 1100110,
    RGRP_2  = 1101100,
    RGRP_3  = 1000010,
    RGRP_4  = 1011100,
    RGRP_5  = 1001110,
    RGRP_6  = 1010000,
    RGRP_7  = 1000100,
    RGRP_8  = 1001000,
    RGRP_9  = 1110100,
};
    


enum{
    //tipos de máscara de convolução
    LAPLACE =0,
    MEDIA,
    GAUSS,
    DERIVADA_PRIMEIRA
};




#endif
