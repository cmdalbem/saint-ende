# Project: FPI
# Makefile created by modifying the one created by Dev-C++ 4.9.9.2 :)

CPP  = colorgcc
CC   = colorgcc
RES  =
OBJ  = main.o Imagem.o bib/EasyBMP.o ImagemConvolution.o ImagemOperators.o BarCode.o ConexComponent.o $(RES)
LINKOBJ  = main.o Imagem.o bib/EasyBMP.o ImagemConvolution.o ImagemOperators.o BarCode.o ConexComponent.o $(RES)

BIN  = fpi.o
CXXFLAGS = -Wall
CFLAGS = -Wall
RM = rm -f

.PHONY: all all-before all-after clean clean-custom

all: $(BIN)


clean: clean-custom
	${RM} $(OBJ) $(BIN)

$(BIN): $(OBJ)
	$(CPP) $(LINKOBJ) -o $@ $(LIBS)

main.o: main.cpp
	$(CPP) -c main.cpp -o main.o $(CXXFLAGS)

Imagem.o: Imagem.cpp
	$(CPP) -c Imagem.cpp -o Imagem.o $(CXXFLAGS)

bib/EasyBMP.o: bib/EasyBMP.cpp
	$(CPP) -c bib/EasyBMP.cpp -o bib/EasyBMP.o $(CXXFLAGS)

ImagemConvolution.o: ImagemConvolution.cpp
	$(CPP) -c ImagemConvolution.cpp -o ImagemConvolution.o $(CXXFLAGS)

ImagemOperators.o: ImagemOperators.cpp
	$(CPP) -c ImagemOperators.cpp -o ImagemOperators.o $(CXXFLAGS)

BarCode.o: BarCode.cpp
	$(CPP) -c BarCode.cpp -o BarCode.o $(CXXFLAGS)

ConexComponent.o: ConexComponent.cpp
	$(CPP) -c ConexComponent.cpp -o ConexComponent.o $(CXXFLAGS)

