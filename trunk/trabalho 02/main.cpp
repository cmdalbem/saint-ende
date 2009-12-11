#include <iostream>
#include <string>
#include "conio2.h"

#include "Imagem.h"
#include "BarCode.h"
#include "definitions.h"


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
    system(savename);
}        

void menuTransformations()
{
    system("cls");
    
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
    cout<<"13. Find Internal Box Delimiters"<<endl;
    cout<<"14. Find Conex Components"<<endl;
    cout<<endl;
    cout<<"default: Cancel"<<endl;          
    cout<<endl;
    
    cout<<"enter your option: ";
    cin >> option2;
    while(!cin){
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        gotoxy(20,wherey()-1); cout<<"                      "; gotoxy(20,wherey());
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
                gotoxy(32,wherey()-1); cout<<" "; gotoxy(32,wherey());
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
            {
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
            bufferImage.findConexComponents();
            
            WAIT;
            break;
                      
    }    
}

void mainMenu()
{
    int option;
    do{
        
            system("cls");
            gotoxy(1,1);
            
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
                gotoxy(20,wherey()-1); cout<<"                         "; gotoxy(20,wherey());
                cin >> option;
            }
           
            gotoxy(1,10);            
            
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
