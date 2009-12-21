#include "ascii.h"
//*
using namespace std;

Ascii::Ascii(Imagem* inputImage, vector<int> inputCandidates) {

	image = inputImage;
	candidates = inputCandidates;
	recognizeAsciies();
}

char Ascii::getLetter() {
	
	return letter;
}

char Ascii::getNumber() {
	
	return number;
}

void Ascii::recognizeAsciies(){
	
	//*
	for(int c = 0; c < candidates.size(); c++) {
			
	    ifstream patternFile("asciiPaterns.pat");
	    int highest = -1, highestIndex;

		int x1 = image->getConexComponent(candidates[c])->getX1() + 1;
		int x2 = image->getConexComponent(candidates[c])->getX2();
		int y1 = image->getConexComponent(candidates[c])->getY1() + 1;
		int y2 = image->getConexComponent(candidates[c])->getY2();
		
		for(int i = 0; i < MAX_PATTERNS; i++) {

			string pattern;
			patternFile >> pattern;
					
			int equals = 0, k = 0, maxK = pattern.size();
			
			for(int h = y1; h < y2 && k < maxK; h++) {
				for(int w = x1; w < x2 && k < maxK; w++) {

					if( (image->isWhitePix(w,h) && pattern[k] == '1') || (!image->isWhitePix(w,h) && pattern[k] == '0') )
						equals++;
					k++;
				}
			}
				
			if(equals > highest)
				highest = equals, highestIndex = i;
		}
		
		buffaloBill.push_back(patternsTable[highestIndex]);
		trust.push_back((float)highest / ((x2-x1) * (y2-y1)));
	}
	
	float mt, mmt = -1;
	for(int i = 0; i < trust.size(); i++)
		if(trust[i] > mmt)
			mmt = trust[i], mt = i;
	char buffinho = buffaloBill[mt];
	
	trust[mt] = mmt = -1;
	
	for(int i = 0; i < trust.size(); i++)
		if(trust[i] > mmt)
			mmt = trust[i], mt = i;
	char buffinho2 = buffaloBill[mt];
	
	if(buffinho >= 'A' && buffinho <= 'Z')
		letter = buffinho, number = buffinho2;
	else
		number = buffinho, letter = buffinho2;
	//*/
}
//*/
