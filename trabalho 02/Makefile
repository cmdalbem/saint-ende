# Project: FPI
# Makefile created by modifying the one created by Dev-C++ 4.9.9.2 :)

CPP  = gcc
CC   = gcc

OBJ  = Imagem.o bib/EasyBMP.o ImagemConvolution.o ImagemOperators.o BarCode.o ConexComponent.o \
        linearAlgebra.o texture.o

KHT_FILES = buffer_2d.o eigen.o kht.o linking.o peak_detection.o subdivision.o voting.o

#KHT = $(KHT_FILES:%=kht/%)

FLAGS = -Wall -lstdc++ -g
all: $(OBJ) fpi

ascii.o: ascii.cpp ascii.h
        $(CPP) -c $< -o $@ $(FLAGS)

fpi: main.cpp $(OBJ)
	$(CPP) $< -o $@ $(OBJ) $(KHT) $(FLAGS)

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

linearAlgebra.o: linearAlgebra.cpp linearAlgebra.h
	$(CPP) -c $< -o $@ $(FLAGS)

texture.o: texture.cpp texture.h
	$(CPP) -c $< -o $@ $(FLAGS)

clean:
	rm *.o ; rm bib/*.o

