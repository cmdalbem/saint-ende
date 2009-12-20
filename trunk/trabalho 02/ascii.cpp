#include "ascii.h"

Ascii::Ascii(Imagem inputImage) {
	
	image = inputImage;
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
	
	for(int i = 0; i < MAX_PATTERNS; i++) {

		string pattern;
		int equals = 0, k = 0;
		
		patternFile >> pattern;
		
		for(int w = 0; w < width; w++)
			for(int h = 0; h < height; h++) {
				
				if(ascii(x,y)->Red == (int)pattern[k++])
					equals++;
		}
			
		if(equals > highest)
			highest = equals, highestIndex = i;
	}

}