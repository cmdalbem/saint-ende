# Project: FPI
# Makefile created by modifying the one created by Dev-C++ 4.9.9.2 :)

CPP  = colorgcc
CC   = colorgcc

OBJ  = Imagem.o bib/EasyBMP.o ImagemConvolution.o ImagemOperators.o BarCode.o ConexComponent.o $(RES)

FLAGS = -Wall -lstdc++
all: $(OBJ) fpi

fpi: main.cpp $(OBJ)
	$(CPP) $< -o $@ $(OBJ) $(FLAGS)

Imagem.o: Imagem.cpp Imagem.h
	$(CPP) -c Imagem.cpp -o $@ $(FLAGS)

bib/EasyBMP.o: bib/EasyBMP.cpp bib/EasyBMP.h
	$(CPP) -c bib/EasyBMP.cpp -o $@ $(FLAGS)

ImagemConvolution.o: ImagemConvolution.cpp ImagemConvolution.h
	$(CPP) -c ImagemConvolution.cpp -o $@ $(FLAGS)

ImagemOperators.o: ImagemOperators.cpp
	$(CPP) -c ImagemOperators.cpp -o $@ $(FLAGS)

BarCode.o: BarCode.cpp BarCode.h
	$(CPP) -c BarCode.cpp -o $@ $(FLAGS)

ConexComponent.o: ConexComponent.cpp ConexComponent.h
	$(CPP) -c ConexComponent.cpp -o $@ $(FLAGS)

