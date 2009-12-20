#ifndef _ASCII_H_
#define _ASCII_H_

#include "Imagem.h"
#include <vector>
#include <fstream>
#include <climits>

#define MAX_PATERNS 36

static const char patternsTable[36] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};

class Ascii {
	
	private:
		
		Imagem image;
		vector<int> candidates;
		vector<int> buffaloBill;
		vector<int> trust;
		
		char letter, number;
		
		void recognizeAsciies();
		
	public:
		
		Ascii(){};
		Ascii(Imagem inputImage, vector<int> inputCandidates);
		
		~Ascii(){};
		
		char getLetter();
		char getNumber();
};

#endif
