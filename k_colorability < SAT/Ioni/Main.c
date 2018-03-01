//Ionela Turcuman 321CB
//informatiile privitoare la logica programului sunt specificate pe larg in README
#include<stdio.h>
#include<stdlib.h>

int main(int argc, char *argv[])
{
	//iau doua fisiere:f1 - din care citesc
  //f2 - in care scriu
	FILE *f1,*f2;
  	int aux,aux2;	//auxiliare pentru creare expresii
	f1 = fopen("test.in","r"); 
	f2 = fopen("test.out","w");
	int numarNod,nrMch,nrColor;//numar de noduri,muchii si culori

	fscanf(f1,"%d %d %d",&numarNod,&nrMch,&nrColor);

	for (int i = 0; i < numarNod; i++){
		if (nrColor > 1)	//daca avem mai multe culori pentru nod folosim paranteze
		fprintf(f2,"(");

		for(int j = 0; j < nrColor;j++){ //pentru fiecare culoare
			aux2 = i*nrColor + j;	//aux2 -indicele specific pentru culoarea j a nodului i
			fprintf(f2,"x%d",aux2); //literal
			if(j < nrColor -1) //verificare sfarsit clauza
						fprintf(f2,"V");
				}
			if( nrColor > 1)
				fprintf(f2,")");
			
			if(i < numarNod -1)//daca n-am realizat clauze pentru toate nodurile
				fprintf(f2,"^"); 
				
			}
	//verificare ca un nod sa aiba maxim o culoare
		for(int i = 0 ;i < numarNod;i++){
			for(int j = 0; j < nrColor;j++){
				aux = i*nrColor + j;	//culoare j;
					for(int k = j+1; k < nrColor; k++){
						aux2 = i*nrColor + k;	//culoare k != j;
						fprintf(f2,"^(~x%dV~x%d)",aux2,aux);	//sau intre negatul acestora
						}
					}
			}
	//verificare culori pentru nodurile intre care exista muchie	
			for(int i = 0 ; i < nrMch;i++){
				fscanf(f1,"%d",&aux);	//primul nod
				fscanf(f1,"%d",&aux2);	//al doilea
				aux = aux*nrColor;	//forma ceruta 
				aux2 = aux2*nrColor;
				for(int j = 0; j < nrColor;j++){ //pentru fiecare culoare
					fprintf(f2,"^(~x%dV~x%d)",aux,aux2); //sau intre negatul aceleiasi culori a nodurilor intre care exista muchie
					aux++;
					aux2++;
					}
				}
	//inchid fisierele			
	fclose(f1);
	fclose(f2);											 
	return 0;
}
