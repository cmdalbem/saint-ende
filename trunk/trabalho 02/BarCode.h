#include "bib\EasyBMP.h"
#include "definitions.h"
#include "Imagem.h"

#include <vector>

using std::vector;



class BarCode
{
    private:        
        
        // Atributos
        Imagem image;
        int x1, y1; //ponto superior esquerdo da barra na imagem
        int x2, y2; //ponto inferior direito da barra na imagem
        int pixPerBar;

        // Funções
        int getPixPerBar();
        vector<int> translateBinaryStream(vector<int> stream);
        int parseEAN8digit(char binstring[7], int group);


    public:        
        BarCode();
        BarCode(int x1, int y1, int x2, int y2, Imagem image);
        ~BarCode();
        

        vector<int> translateBarCode();        
        
        
        
};
