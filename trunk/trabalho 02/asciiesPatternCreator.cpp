#include "imagem.h"
#include <iostream>
#include <fstream>

using namespace std;

#define MAX_PATTERNS 36

int amain() {
/*	
	char patternsTable[] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};

	Imagem pattern;
	ifstream patternFile("asciiPaterns.pat");
	
	pattern.load("sesl/0.bmp");
	
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
		
	int maiorEquals = -1, aswI;
	/*
	string s;
	patternFile >> s;

	for(int i = 0; i < s.size(); i++) {
			if(i % 71 == 0 && i != 0)
			cout << endl;
			cout << s[i];
			if(s[i] == '1')a++;else b++;

	}
	cout << endl << s.size() << ".." << a << "." << b;
	a = 0;b = 0;
	for(int i = x1; i <= x2; i++) {
			for(int j = y1; j <= y2; j++) {
					e++;
					if(pattern.isWhitePix(i,j) && s[k] == '1') a++; else b++;k++;
			}}cout << endl << e << ".." << a << "." << b <<" " <<k;
	
	//*/

	/*
	for(int i = 0; i < MAX_PATTERNS; i++) {
		
		string iPattern;
		patternFile >> iPattern;
		int k = 0, maxK = iPattern.size(), equals = 0;
			
		for(int i = x1; i <= x2 && k < maxK; i++) {
			for(int j = y1; j <= y2 && k < maxK; j++) {
				
				if( (pattern.isWhitePix(i,j) && iPattern[k] == '1') || (!pattern.isWhitePix(i,j) && iPattern[k] == '0') )
					equals++;
				k++;
			}
		}
		
		if(equals > maiorEquals)
			maiorEquals = equals, aswI = i;
		
		cout << (x2-x1+1)*(y2-y1+1) << "," << maxK << "," << equals << endl;
	}///
	
	cout << patternsTable[aswI] << endl;
	getchar(); //*/
//*

	char patternsTable[] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};

	Imagem pattern;
	ofstream patternFile("asciiPaterns.pat");

	for(int i = 0; i < MAX_PATTERNS; i++) {

		char patternPath[6];
		sprintf(patternPath, "sesl/%c.bmp", patternsTable[i]);

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
			
		for(int h = y1; h <= y2; h++) {
			for(int w = x1; w <= x2; w++) {
				
				if(pattern.isWhitePix(w,h))
					patternFile << 1;
				else
					patternFile << 0;
			}
		}
		patternFile << '\n';
		if(patternsTable[i] == 'M') {
							
							for(int h = y1; h <= y2; h++){
							for(int w = x1; w <= x2; w++)
							if(pattern.isWhitePix(w,h)) cout << 1; else cout << 0; cout << endl;}
							}
	}
	getchar();//*/

}
