#include "imagem.h"
#include <iostream>
#include <fstream>

using namespace std;

#define MAX_PATTERNS 36

int main() {

	char patternsTable[] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};

	Imagem pattern;
	ofstream patternFile("asciiPaterns.pat");

	for(int i = 0; i < MAX_PATTERNS; i++) {

		char patternPath[6];
		sprintf(patternPath, "../../../Saint Ende - Soia's lab/%c.bmp", patternsTable[i]);

		pattern.load(patternPath);

		int x1,y1,x2,y2, height, width;
		height = pattern.getH();
		width = pattern.getW();

		for(int h = 0; h < height; h++)
			for(int w = 0; w < width; w++) {

				if(pattern.isBlackPix(w,h)) {
					
					y1 = h;
					h = height;
					break;
				}
		}
			
		for(int w = 0; w < width; w++)
			for(int h = 0; h < height; h++) {

				if(pattern.isBlackPix(w,h)) {
					
					x1 = w;
					w = width;
					break;
				}
		}
			
		for(int h = height-1; h >= 0; h--)
			for(int w = width-1; w >= 0; w--) {

				if(pattern.isBlackPix(w,h)) {
					
					y2 = h;
					h = -1;
					break;
				}
		}
			
		for(int w = width-1; w >= 0; w--)
			for(int h = height-1; h >= 0; h--) {

				if(pattern.isBlackPix(w,h)) {
					
					x2 = w;
					w = -1;
					break;
				}
		}
			
		for(int w = x1; w <= x2; w++)
			for(int h = y1; h <= y2; h++) {
				
				if(pattern.isWhitePix(w,h))
					patternFile << 0;
				else
					patternFile << 1;
		}
		
		patternFile << '\n';
	}

}
