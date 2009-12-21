#include <iostream>
#include <string>

//inclui porque aparentemente o dev já incluía pra ti mano
#include <cstdlib>
//#include <cstring>
#include <limits>
#include <algorithm>

#include "Imagem.h"
#include "BarCode.h"
#include "definitions.h"
#include "ascii.h"

#include "ConexComponent.h"

#include "texture.h"

using namespace std;


//GLOBAIS
Imagem originalImage;
Imagem bufferImage;

void menuLoadOption()
{
    cout<<"enter path: ";
    char path[MAX_URL];
    cin >> path;
    strcat(path,".bmp");
		while( !originalImage.load(path) ) {
        cout << "Nao consegui abrir teu arquivo! Tenta de novo\a" << endl;
        cin >> path;
        strcat(path,".bmp");
    }

    bufferImage.load(path);
}

void menuSave()
{
    char savename[MAX_URL];
    strncpy(savename,bufferImage.getImagePath(),strlen(bufferImage.getImagePath())-3);
    savename[strlen(bufferImage.getImagePath())-4]='\0';
    sprintf(savename,"%s_edited.bmp",savename);
    bufferImage.save(savename);

    cout << endl << "Imagem salva em "<< savename << endl;
    cout << "Abrindo imagem... (feche-a para continuar)" << endl << endl;
    //system(savename);
}

void menuTransformations()
{
    system(CLEAR_STRING);

    int option2;

    cout<<"1. Media (passa-baixas)"<<endl;
    cout<<"2. Gaussiano"<<endl;
    cout<<"3. Derivada Primeira"<<endl;
    cout<<"4. Laplace"<<endl;
    cout<<"5. Enter custom kernel"<<endl;
    cout<<endl;
    cout<<"6. Somar esta com a original"<<endl;
    cout<<"7. Subtrair desta a original"<<endl;
    cout<<endl;
    cout<<"8. Limiarizar"<<endl;
    cout<<"9. Full Dilate"<<endl;
    cout<<"10. Convert to GrayScale"<<endl;
    cout<<endl;
    cout<<"11. Borders detection"<<endl;
    cout<<"12. Find And Tell Me The Bar Code Please"<<endl;
    cout<<"13. Find Internal Box Delimiters (use-me antes de procurar os componentes)"<<endl;
    cout<<"14. Find Conex Components And Tell Me What Time Is It"<<endl;
    cout<<"15. Spatial Mapping" << endl;
    cout<<"16. Crazy Limiar" << endl;
    cout<<"17. Find Edge" << endl;
    cout<<"18. Negative" << endl;
    cout<<"19. Let Apus show his hot naked body" << endl;
    cout<<"20. KHT" << endl;
    cout<<"21. Find Letter & Number" << endl;
    cout<<"default: Cancel"<<endl;
    cout<<endl;

    cout<<"enter your option: ";
    cin >> option2;
    while(!cin){
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cin >> option2;
    }
    switch(option2)
    {
        case 1:
            bufferImage.media();
            WAIT;
            break;
        case 2:
            bufferImage.gaussiano();
            WAIT;
            break;
        case 3:
            bufferImage.derivadaPrimeira();
            WAIT;
            break;
        case 4:
            bufferImage.laplaciano();
            WAIT;
            break;
        case 5:
            int n;

            cout<<"Enter square matrix dimensions: ";
            cin>>n;
            while(!cin){
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                cin >> n;
            }

            bufferImage.customMask(n);
            WAIT;
            break;
        case 6:
            bufferImage += originalImage;
            WAIT;
            break;
        case 7:
            bufferImage -= originalImage;
            WAIT;
            break;
        case 8:
            int treshold;
            cout<<"treshold: "; cin>>treshold;
            bufferImage.limiarize(treshold);
            WAIT;
            break;
        case 9:
            bufferImage.fullDilate();
            WAIT;
            break;
        case 10:
            bufferImage.convertToGrayScale();
            WAIT;
            break;
        case 11:
            {
                bufferImage.convertToGrayScale();
                bufferImage.limiarize(200);
                bufferImage.binaryInversion();

                Imagem limiarizada = bufferImage;

                bufferImage.fullDilate();
                bufferImage -= limiarizada;
            }
            WAIT;
            break;
        case 12:
            // Find And Tell Me The Bar Code Please
            {
                bufferImage.convertToGrayScale();
                bufferImage.limiarize(200);

                BarCode codigodebarras(bufferImage); //inicializa BarCode apenas com a imagem, então o construtor encontrará o código de barras pra nós

                vector<int> result = codigodebarras.translateBarCode();

                for(vector<int>::iterator it=result.begin(); it!=result.end(); it++)
                    cout<<*it;
                cout<<endl;
            }
            WAIT;
            break;
       case 13:
            {
                Imagem temp = bufferImage;
                bufferImage.convertToGrayScale();
                bufferImage.limiarize(200);
                bufferImage.findInternalBox();
                temp.setInternalFrameX1( bufferImage.getInternalFrameX1() );
                temp.setInternalFrameX2( bufferImage.getInternalFrameX2() );
                temp.setInternalFrameY1( bufferImage.getInternalFrameY1() );
                temp.setInternalFrameY2( bufferImage.getInternalFrameY2() );
                bufferImage = temp;
            }
            WAIT;
            break;
       case 14:
            {
                bufferImage.convertToGrayScale();
                bufferImage.limiarize(200);
                bufferImage.binaryInversion();
                Imagem limiarizada = bufferImage;
                bufferImage.fullDilate();
                bufferImage -= limiarizada;

                const int maxComponents = 5;
                bufferImage.findConexComponents(maxComponents);

                vector<ConexComponent*>::iterator it;
                for(it = bufferImage.conexComponents.begin(); it!=bufferImage.conexComponents.end(); it++) {
                    cout<< (*it)->isClock(&limiarizada) <<endl;
                    if( (*it)->isClock(&limiarizada) )
                        cout << (*it)->tellTimeOfClock(&limiarizada) << endl;
                }


                bufferImage = limiarizada;
            }

            WAIT;
            break;

        case 15:
            {
                Point o[4] = { {124,460}, {590,430}, {521,34}, {123,117} };
                Point p[4] = { {0,0}, {0,480},{640,480}, {640,0} };
                bufferImage.spatialMapping(o,p);
                WAIT;
                break;
            }
        case 17:
                //bufferImage.findEdge();
                break;

        case 16:
        {
            //float lim = bufferImage.bestLimiar();
            //bufferImage.limiarize(lim);

            int x1,x2,y1,y2;
            float lim;

            x1=0;x2=bufferImage.getW()/4;y1=0;y2=bufferImage.getH()/4;
            lim = bufferImage.bestLimiarByRegion(x1,x2,y1,y2);
            bufferImage.limiarizeRegion(x1,x2,y1,y2,lim);

            x1=x2+1;x2=bufferImage.getW()/2;
            lim = bufferImage.bestLimiarByRegion(x1,x2,y1,y2);
            bufferImage.limiarizeRegion(x1,x2,y1,y2,lim);

            x1=x2+1;x2=3*bufferImage.getW()/4;
            lim = bufferImage.bestLimiarByRegion(x1,x2,y1,y2);
            bufferImage.limiarizeRegion(x1,x2,y1,y2,lim);

            x1=x2+1;x2=bufferImage.getW()-1;
            lim = bufferImage.bestLimiarByRegion(x1,x2,y1,y2);
            bufferImage.limiarizeRegion(x1,x2,y1,y2,lim);

            x1=0;x2=bufferImage.getW()/4;y1=y2+1;y2=bufferImage.getH()/2;
            lim = bufferImage.bestLimiarByRegion(x1,x2,y1,y2);
            bufferImage.limiarizeRegion(x1,x2,y1,y2,lim);

            x1=x2+1;x2=bufferImage.getW()/2;
            lim = bufferImage.bestLimiarByRegion(x1,x2,y1,y2);
            bufferImage.limiarizeRegion(x1,x2,y1,y2,lim);

            x1=x2+1;x2=3*bufferImage.getW()/4;
            lim = bufferImage.bestLimiarByRegion(x1,x2,y1,y2);
            bufferImage.limiarizeRegion(x1,x2,y1,y2,lim);

            x1=x2+1;x2=bufferImage.getW()-1;
            lim = bufferImage.bestLimiarByRegion(x1,x2,y1,y2);
            bufferImage.limiarizeRegion(x1,x2,y1,y2,lim);

            x1=0;x2=bufferImage.getW()/4;y1=y2+1;y2=3*bufferImage.getH()/4;
            lim = bufferImage.bestLimiarByRegion(x1,x2,y1,y2);
            bufferImage.limiarizeRegion(x1,x2,y1,y2,lim);

            x1=x2+1;x2=bufferImage.getW()/2;
            lim = bufferImage.bestLimiarByRegion(x1,x2,y1,y2);
            bufferImage.limiarizeRegion(x1,x2,y1,y2,lim);

            x1=x2+1;x2=3*bufferImage.getW()/4;
            lim = bufferImage.bestLimiarByRegion(x1,x2,y1,y2);
            bufferImage.limiarizeRegion(x1,x2,y1,y2,lim);

            x1=x2+1;x2=bufferImage.getW()-1;
            lim = bufferImage.bestLimiarByRegion(x1,x2,y1,y2);
            bufferImage.limiarizeRegion(x1,x2,y1,y2,lim);

            x1=0;x2=bufferImage.getW()/4;y1=y2+1;y2=bufferImage.getH()-1;
            lim = bufferImage.bestLimiarByRegion(x1,x2,y1,y2);
            bufferImage.limiarizeRegion(x1,x2,y1,y2,lim);

            x1=x2+1;x2=bufferImage.getW()/2;
            lim = bufferImage.bestLimiarByRegion(x1,x2,y1,y2);
            bufferImage.limiarizeRegion(x1,x2,y1,y2,lim);

            x1=x2+1;x2=3*bufferImage.getW()/4;
            lim = bufferImage.bestLimiarByRegion(x1,x2,y1,y2);
            bufferImage.limiarizeRegion(x1,x2,y1,y2,lim);

            x1=x2+1;x2=bufferImage.getW()-1;
            lim = bufferImage.bestLimiarByRegion(x1,x2,y1,y2);
            bufferImage.limiarizeRegion(x1,x2,y1,y2,lim);

            WAIT;
            break;
        }

        case 18:
                bufferImage.negative();
                break;

        case 19:
            {
                Imagem temp = bufferImage;
                bufferImage.convertToGrayScale();
                bufferImage.limiarize(200);
                bufferImage.binaryInversion();
                Imagem limiarizada = bufferImage;
                bufferImage.fullDilate();
                bufferImage -= limiarizada;

                const int maxComponents = 5;
                bufferImage.findConexComponents(maxComponents);
                int biggerComponent = 0;

                for(int i = 0; i < bufferImage.conexComponents.size(); ++i)
                    if( bufferImage.conexComponents[i]->getX2() - bufferImage.conexComponents[i]->getX1() >=
                            bufferImage.conexComponents[biggerComponent]->getX2() - bufferImage.conexComponents[biggerComponent]->getX1()
                        &&
                        bufferImage.conexComponents[i]->getY2() - bufferImage.conexComponents[i]->getY1() >=
                            bufferImage.conexComponents[biggerComponent]->getY2() - bufferImage.conexComponents[biggerComponent]->getY1()
                      )
                            biggerComponent = i;

                cout << endl << "CELULA: " << findTexture(temp, bufferImage.conexComponents[biggerComponent]->getX1(), bufferImage.conexComponents[biggerComponent]->getY1()) << endl;

                bufferImage = temp;
                WAIT;
            	break;
            }

        case 20:
        {
            bufferImage.houghTransform();
            WAIT;
            break;
        }
        case 21:
	    {
		 	bufferImage.negative();
            vector<int> candidates = bufferImage.unknownComponents();

            Ascii asciiFinder(&bufferImage, candidates);

            cout << "Letter = " << asciiFinder.getLetter() << endl;
            cout << "Number = " << asciiFinder.getNumber() << endl;
            WAIT;
            break;
	  	}
    }
}

void mainMenu()
{
    int option;
    do{

            system(CLEAR_STRING); //clear screen portavel u.u

            cout<<"LOADED: "<<bufferImage.getImagePath()<<endl;
            cout<<endl;
            cout<<"1. Load different image"<<endl;
            cout<<"2. Save image & display"<<endl;
            cout<<"3. Transformations"<<endl;
            cout<<"4. EXIT"<<endl;
            cout<<endl;

            cout<<"enter your option: ";
            cin >> option;
            while(!cin){
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                cin >> option;
            }

            switch(option)
            {
                case 1:
                    menuLoadOption();
                    break;
                case 2:
                    menuSave();
                    break;
                case 3:
                    menuTransformations();
                    break;
            }

    }while(option!=4);
}



int main()
{
	menuLoadOption();

    mainMenu();
}

