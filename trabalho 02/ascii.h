#ifndef _ASCII_H_
#define _ASCII_H_

#include "Imagem.h"
#include <vector>
#include <fstream>
#include <climits>

#define MAX_PATERNS 36

class Ascii {
	
	private:
			
		static char patternsTable[] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
		
		Imagem image;
		Vector<int> candidates;
		Vector<int> buffaloBill;
		Vector<int> trust;
		
		char letter, number;
		
		void recognizeAsciies();
		
	public:
		
		Ascii(){};
		Ascii(Imagem inputImage, Vector<int> inputCandidates);
		
		~Ascii(){};
		
		char getLetter();
		char getNumber();
};

#endif
