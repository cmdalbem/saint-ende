#include "imagem.h"
#include <iostream>
#include <fstream>
#include <string>
#include <climits>

using namespace std;

#define MAX_PATTERNS 36

	char patternsTable[] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
	
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
	
	return patternsTable[highestIndex];