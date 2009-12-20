#include "ascii.h"

Ascii::Ascii(Imagem inputImage, vector<int> inputCandidates) {
	
	image = inputImage;
	candidates = inputCandidates;
	recognizeAsciees();
}

char Ascii::getLetter() {
	
	return letter;
}

char Ascii::getNumber() {
	
	return number;
}

void Ascii::recognizeAsciies(){
	
	ofstream patternFile("asciiPaterns.pat");
	int highest = MAX_INT, highestIndex;
	
	for(int c = 0; c < candidates.size(); c++) {
		
		int x1 = image.getConexComponents()[candidates[c]]->getX1();
		int x2 = image.getConexComponents()[candidates[c]]->getX2();
		int y1 = image.getConexComponents()[candidates[c]]->getY1();
		int y2 = image.getConexComponents()[candidates[c]]->getY2();
			
		for(int i = 0; i < MAX_PATTERNS; i++) {

			string pattern;
			int equals = 0, k = 0;
			
			patternFile >> pattern;
			
			for(int w = x1; w < x2; w++)
				for(int h = y1; h < y2; h++) {
					
					if(image(w,h)->Red == (int)pattern[k++])
						equals++;
			}
				
			if(equals > highest)
				highest = equals, highestIndex = i;
		}
		
		buffaloBill.push_back(highestIndex);
		trust.push_back(highest / ((x2-x1) * (y2-y1)));
	}
	
	vector<int>::iterator mt = max_element(trust.begin(), trust.end());
	char buffinho = patternsTable[buffaloBill[mt]];
	
	trust[mt] = 0;
	
	mt = max_elemento(trust.begin(), trust.end());
	char buffinho2 = patternsTable[buffaloBill[mt]];
	
	if(buffinho >= 'A' && buffinho <= 'Z')
		letter = buffinho, number = buffinho2;
	else
		number = buffinho, letter = buffinho2;
}