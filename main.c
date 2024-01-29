/***********************************************************************
*
* @Propòsit: Aquest programa està dissenyat per proporcionar un diagnòstic als 
* 				usuaris en funció dels seus símptomes. El programa llegeix un 
* 				fitxer que conté informació sobre diverses malalties i els seus 
* 				símptomes. A continuació, permet a l'usuari introduir els seus 
* 				símptomes i genera una llista de possibles malalties que puguin 
* 				tenir. El programa també pot actualitzar la rellevància dels 
* 				símptomes a la base de dades de malalties llegint des d'un fitxer 
* 				binari. El programa és interactiu, amb una interfície de menú que 
* 				guia l'usuari a través de les seves diferents opcions.	
* 
* @Autor:                      David Susagna Holgado
* @Data de creació:              5/04/2023
* @Data de l'última modificació: 19/04/2023
*
***********************************************************************/
// Llibreries del sistema
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Constants
#define MAX_CHAR 		50		// Nombre màxim de caràcters d'una paraula.
#define MAX_LINE 		60		// Nombre màxim de caràcters d'una línia.
#define	USER_REQUEST 	1000	// Nombre màxim de caràcters dels símptomes introduïts per l'usuari.

// Tipus propis
typedef struct {
	char symptom_name[MAX_CHAR];
	int relevance;
} Symptom;

typedef struct {
		char disease_name[MAX_CHAR];
		int num_symptoms;
		int total_relevance;
		Symptom* symptoms;
} Diseases;

typedef struct {
	char disease[MAX_CHAR];
	char symptom[MAX_CHAR];
	int relevance;
} FileDisease;

typedef struct {
	char user_symptoms_name[MAX_CHAR];
} UserSymptoms;



// Procediments i funcions


/***********************************************************************
*
* @Finalitat: 	Copiar una cadena de caràcters 'origen' en una nova cadena 'destino'
*        		començant des del índex 'i' i detenint-se quan es troba el caràcter 'end'.
* 
* @Paràmetres: 	origen - cadena de caràcters que es vol copiar.
* 		      	destino - cadena de caràcters on es copiarà la cadena origen.
*          		i - índex on es començarà la còpia de la cadena origen.
*          		end - caràcter que indica el final de la còpia.
* 
* @Retorn: Índex on s'ha trobat el caràcter 'end' a la cadena origen.
* 
***********************************************************************/
int cpyString(char origen[], char destino[], int i, char end){

	int n = 0;

	n = 0;
	while(end != origen[i]){
		destino[n] = origen[i];
		i++;
		n++;
	}
	destino[n] = '\0';
	return(i);
}

/***********************************************************************
*
* @Finalitat: Obrir un fitxer amb el format especificat i retornar el punter al fitxer obert.
* 
* @Paràmetres: format - cadena de caràcters que especifica el format del fitxer a obrir.
* 
* @Retorn: Retorna el punter al fitxer obert o NULL si no s'ha pogut obrir el fitxer.
* 
***********************************************************************/
FILE * openFile(char format[MAX_CHAR]){

	char file_name[MAX_CHAR];
	FILE *file = NULL;

	scanf("%s",file_name);
	file = fopen(file_name,format);
	
	return(file);
}

/***********************************************************************
*
* @Finalitat: Tancar el fitxer obert i assignar NULL al punter al fitxer per evitar problemes de referència.
* 
* @Paràmetres: file - punter al punter al fitxer que es vol tancar.
* 
* @Retorn: La funció no retorna cap valor.
* 
***********************************************************************/
void closeFile(FILE **file){
	fclose(*file);
	*file = NULL;
}	

/***********************************************************************
*
* @Finalitat: Mostrar un menú d'opcions a l'usuari i assignar l'opció seleccionada al punter passat com a paràmetre.
* 
* @Paràmetres: opcio - punter a un enter on es guardarà l'opció seleccionada per l'usuari.
* 
* @Retorn: La funció no retorna cap valor.
* 
***********************************************************************/
void menu(int *opcio){
	
	char user[MAX_CHAR];
	int aux = 0;

	printf("\n1. Show diseases | 2. Load research advances | 3. Help me! | 4. Quit \n");
	printf("\nEnter option: ");
	scanf("%s", user);

	aux = atoi(user);

	switch (aux) {
        case 1:
            *opcio = 1;
            break;
        case 2:
            *opcio = 2;
            break;
        case 3:
            *opcio = 3;
            break;
        case 4:
            *opcio = 4;
            break;
        default:
            // Opción inválida
            printf("\nERROR: Wrong option\n");
            *opcio = 0;
            break;
    }
}

/***********************************************************************
*
* @Finalitat: 	Llegir una línia de text d'un fitxer i guardar-la en una cadena de caràcters, eliminant el caràcter de nova línia.
* 
* @Paràmetres: 	name - cadena de caràcters on es guardarà la línia llegida del fitxer.
* 				doc - punter al fitxer on es llegirà la línia.
* 
* @Retorn: La funció no retorna cap valor.
* 
***********************************************************************/

void getString(char name[], FILE *doc){

	fgets(name, MAX_LINE, doc);
	name[strlen(name)-1] = '\0';		// Eliminar '\n'.

}

/***********************************************************************
*
* @Finalitat: 	Imprimir la informació de les malalties i els seus símptomes.
* 
* @Paràmetres: 	d - punter a l'estructura de dades de malalties, que conté la informació a imprimir.
* 				num_disease - nombre de malalties a imprimir.
* 
* @Retorn: 	La funció no retorna cap valor.
* 
***********************************************************************/

void printInfo(Diseases* d, int num_disease){
    int k = 0, i = 0;

    for(k = 0; k < num_disease; k++){

        printf("%s ", d[k].disease_name);
        printf("(");
        for(i = 0; i < d[k].num_symptoms; i++){
            if(i != d[k].num_symptoms-1){
                printf("%s#%d | ", d[k].symptoms[i].symptom_name, d[k].symptoms[i].relevance);
            }
            else{
                printf("%s#%d", d[k].symptoms[i].symptom_name, d[k].symptoms[i].relevance);
            }
        }
        printf(")\n");
    }
}






/***********************************************************************
*
* @Finalitat: A partir d'una llista d'símptomes de l'usuari i una llista de malalties amb 
* 				els seus símptomes i la rellevància d'aquests, la funció busca la malaltia 
* 				més probable a partir de la rellevància dels símptomes que coincideixen.
* 
* @Parametres: 	num_user_symptoms - Nombre de símptomes de l'usuari (int).
* 				isease_num - Nombre de malalties (int).
* 				user_symptoms - Array amb els símptomes de l'usuari (UserSymptoms[]).
* 				disease - Array amb les malalties i els seus símptomes (Diseases[]).
* 
* @Retorn: Retorna 0 si no hi ha hagut cap coincidència entre els símptomes de l'usuari 
* 			i les malalties. Si hi ha hagut coincidències, la funció retorna 1.
* 
***********************************************************************/
int findProbable(int num_user_symptoms,int disease_num,UserSymptoms user_symptoms[],Diseases disease[]){


	int k = 0,i = 0, j = 0, found = 0, already_found = 0;
	int num_simptomes_txt = 0;

	for(k = 0; k < disease_num; k++){
		num_simptomes_txt = num_simptomes_txt + disease[k].num_symptoms;

		for(i = 0; i < disease[k].num_symptoms; i++){
			for(j = 0; j < num_user_symptoms; j++){
				if (0 == strcmp(disease[k].symptoms[i].symptom_name, user_symptoms[j].user_symptoms_name)){
					disease[k].total_relevance += disease[k].symptoms[i].relevance;
					already_found = 1;
				}
				else{
					found++;
				}
			}
		}
	}

	if ((found == (num_simptomes_txt*num_user_symptoms)) && (0 == already_found)){
		return(0);
	}
	else{
		return(1);
	}
}

/***********************************************************************
 * 
 * @Finalitat: Ordena les malalties de manera descendent segons la seva relevància total.
 * 
 * @Parametres:		disease_num el nombre de malalties
 * 					disease un array de malalties
 * 
 * @Retorn: 	La funció no retorna cap valor.
 * 
***********************************************************************/



void ordenarProbable(int disease_num, Diseases disease[]){

	int i = 0,j = 0, ord = 0;
	Diseases aux;
	
	while(!ord){
		ord=1;
		for(j = 0; j < disease_num-1; j++){

			if(disease[j].total_relevance < disease[j+1].total_relevance){

				aux = disease[j];
				disease[j] = disease[j+1];
				disease[j+1] = aux;
				ord = 0;
			}
		}
		i++;
	}	
}


/***********************************************************************
 * 
 * @Finalitat: La funció imprimeix les malalties ordenades per la seva rellevància 
 * 				total, mostrant només aquelles amb una rellevància major que zero.
 * 
 * @Parametres: disease_num Nombre de malalties a comprovar
 * 				disease Array de les malalties amb les seves dades
 * 
 * @Retorn: 	La funció no retorna cap valor.
 * 
***********************************************************************/

void printProbable(int disease_num, Diseases disease[]){

	int k = 0;

	ordenarProbable(disease_num,disease);

	for(k = 0; k < disease_num; k++){
		if (0 < disease[k].total_relevance){
			printf("Total relevance %d: %s\n",disease[k].total_relevance, disease[k].disease_name);
			disease[k].total_relevance = 0;
		} 
	}
}


int main(){
	
	int opcio = 0;							// Indica l'opció del menú indicada per l'usuari.
	FILE *doc = NULL;						// Punter a fitxer pel document de text.
	FILE *bin = NULL;						// Punter a fitxer pel document de binari.
	Diseases* d;
	int num_disease = 0;

	int i = 0, k =0, p = 0, j = 0;
	char aux[MAX_LINE];
	char aux_Symptoms[MAX_LINE];
	int ignored = 0, existeix = 0, symptoms_upgrade = 0, diseases_ignored = 0;
	int symptoms_added = 0;
	FileDisease filed;
	Symptom *symptoms;
	UserSymptoms *user_symptoms;
	char buffer;
	char user[USER_REQUEST];
	int num_user_symptoms = 0, found = 0;

	printf("Enter diseases file name: ");
	doc = openFile("r");

	if (NULL == doc){
		// Output 1. S'introdueix el nom d'un fitxer que no existeix. 
    	printf("\nERROR: Diseases file not found \n");
	}
	else{

		// Guarda document TXT a l'estructura
		
		//Recollir num_disease
		fscanf(doc,"%d",&num_disease);

		// Crear memòria de la mida Diseases
		d = (Diseases*)malloc(sizeof(Diseases) * num_disease);
		if (NULL != d){

			// Llegir nom de la malaltia
			getString(d[k].disease_name,doc);

			for(k=0; k<num_disease; k++){
				// Llegir nom de la malaltia
				getString(d[k].disease_name,doc);

				// Llegir num Symptoms
				getString(aux_Symptoms,doc);
				d[k].num_symptoms = atoi(aux_Symptoms);

				if(0 < d[k].num_symptoms){			
				
					// Crear memòria de la mida Symptoms
					d[k].symptoms = (Symptom*)malloc(sizeof(Symptom) * (d[k].num_symptoms));
					if (NULL != d[k].symptoms){

						for(i = 0; i < d[k].num_symptoms; i++){
							// Llegir la línia del símptoma
							getString(aux,doc);

							// Llegir nom del símptoma
							p = 0;
							p = cpyString(aux, aux_Symptoms, 0, '(');
							aux_Symptoms[strlen(aux_Symptoms)-1] = '\0';  	// Eliminar ' '.
							strcpy(d[k].symptoms[i].symptom_name,aux_Symptoms);
							p++;

							p = cpyString(aux, aux_Symptoms, p, '\0');
							aux_Symptoms[strlen(aux_Symptoms)-1] = '\0';  	// Eliminar ')'.
							d[k].symptoms[i].relevance = atoi(aux_Symptoms);

						}
					}	
				}
			}

			printf("Welcome to myDoctor! \n");
			do{
				menu(&opcio);


				switch(opcio){

					// Opció 1: Show diseases 
					case 1:
						printf("\nRegistered diseases: \n\n");
						printInfo(d, num_disease);
						break;
					

					// Opció 2: Load research advances
					case 2:
						printf("Enter research file name: ");
						// Obrir fitxer binari
						bin = openFile("rb");

						if(NULL == bin){
							// Error amb el fitxer binari
							printf("\nERROR: Research file not found \n");	
						}
						else{
							ignored = 0;
							// Llegir 1r tram d'informació
							fread(&filed, sizeof(FileDisease), 1, bin);

							while(!feof(bin)){
								// Buscar si és la mateixa malaltia 
								for(k = 0 ; k <num_disease; k++){
									if(0 != strcmp(d[k].disease_name, filed.disease)){
										ignored++;
									}	
									else{
										// És la mateixa malatia
										for(j = 0 ; j <d[k].num_symptoms; j++){
											if(0 == strcmp(d[k].symptoms[j].symptom_name, filed.symptom)){
												if(d[k].symptoms[j].relevance != filed.relevance){
													d[k].symptoms[j].relevance = filed.relevance;
													symptoms_upgrade++;
												}
												existeix++;
											}
										}
										if(0 == existeix){

											d[k].num_symptoms++;
											// Crear una memoria num_symptoms + 1
											symptoms = (Symptom*)malloc(sizeof(Symptom) * (d[k].num_symptoms));
											if (NULL != symptoms){
												// Copiar de la memòria antiga a la memòria auxiliar

												for(p=0; p<(d[k].num_symptoms-1); p++){
													strcpy(symptoms[p].symptom_name,d[k].symptoms[p].symptom_name);
													symptoms[p].relevance = d[k].symptoms[p].relevance;
												}
												// Tancar memòria antiga
												free(d[k].symptoms);
												d[k].symptoms = NULL;


												// Crear una memòria de d[k].num_symptoms + 1
												d[k].symptoms = (Symptom*)malloc(sizeof(Symptom) * (d[k].num_symptoms));
												if (NULL != d[k].symptoms){
													// Copia de la auxiliar a la memòria principal
													for(p=0; p<(d[k].num_symptoms-1); p++){
														strcpy(d[k].symptoms[p].symptom_name,symptoms[p].symptom_name);
														d[k].symptoms[p].relevance = symptoms[p].relevance;
													}
													// Afegir el nou símptoma a l'última posició del fitxer binari
													strcpy(d[k].symptoms[d[k].num_symptoms-1].symptom_name,filed.symptom);
													d[k].symptoms[d[k].num_symptoms-1].relevance = filed.relevance;
													
													
												}
												// Tancar memòria auxiliar 
												free(symptoms);
												symptoms = NULL;
											}
											symptoms_added++;
										}
										existeix = 0;
									}
								}
								if (ignored == num_disease){
									diseases_ignored++;
								}
								ignored = 0;
								fread(&filed, sizeof(FileDisease), 1, bin);
							}
							// Output 6.
							printf("\n%d diseases ignored\n",diseases_ignored);
							printf("%d symptoms updated\n",symptoms_upgrade);
							printf("%d symptoms added\n",symptoms_added);
							diseases_ignored = 0;
							symptoms_upgrade = 0;
							symptoms_added = 0;
							closeFile(&bin);
						}
						break;

					// Opció 3: Help me! 
					case 3:

						printf("Enter your symptoms: ");
						scanf("%c",&buffer);
						fgets(user, USER_REQUEST, stdin);
						user[strlen(user)-1] = '\0';  	// Eliminar '\n'.

						// Contar el num_user_symptoms
						i = 0;
						num_user_symptoms = 1;
						while('\0' != user[i]){

							if ('+' == user[i]){
								num_user_symptoms++;
							}
							i++;
						}

						user_symptoms = (UserSymptoms*)malloc(sizeof(UserSymptoms) * num_user_symptoms);

						if(NULL != user_symptoms){

							j = 0;
							for (i = 0; i<num_user_symptoms; i++){
								if(i != num_user_symptoms-1){
									j = cpyString(user, user_symptoms[i].user_symptoms_name, j, '+');
									j++;
								}
								else{
									j = cpyString(user, user_symptoms[i].user_symptoms_name, j, '\0');
								}
							}

							found = findProbable(num_user_symptoms,num_disease,user_symptoms,d);

							if(0 == found){
								printf("\nNo diseases found!\n");
								num_user_symptoms = 0;
							}
							else{
								printf("\nMost probable diseases: \n");
								printProbable(num_disease,d);
								num_user_symptoms = 0;
							}				
							
							free(user_symptoms);
							user_symptoms = NULL;
						}
						break;
				}

			} while(4 != opcio);
			

			// Alliberar memòria Diseases
			for (k = 0; k < num_disease; k++) {
				if(0 < d[k].num_symptoms){
			        free(d[k].symptoms);
		    		d[k].symptoms = NULL;  
			    }  	
		    }

		    free(d);
		    d = NULL;

			printf("\nStay healthy!");
			closeFile(&doc);
		}
	}
	return(0);
}