/*da6ddbdce00373c123d81645b2b6dc0c20957f97*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define VMIN 5
#define VMAX 30
void Parametres(int *,int *,int *,int *,int *);
int Lire_Entier(int,int);
int max(int *,int *);
struct T_Case
{
	int indice_ligne;
	int indice_colonne;
};
struct T_Tab_Case
{
	struct T_Case tab[50];
};
struct T_Tab_Case Hasard_Ban(int,int *,int *);
int Affichage_Grille(struct T_Case,struct T_Tab_Case, int, int, int);

int main()
{int nlig,ncol,niveau,next,nban,i,zer;
	struct T_Tab_Case ban;
	struct T_Case pion;
	pion.indice_ligne=1;
	pion.indice_colonne=1;
	srand((unsigned int)time(NULL));
	Parametres(&nlig,&ncol,&niveau,&next,&nban);
	
	printf("%da%db%dc%dd%d",nlig,ncol,niveau,next,nban);
	ban=Hasard_Ban(nban,&nlig,&ncol);
	for(i=0;i<nban;i++){
		printf("\n %d : ligne",ban.tab[i].indice_ligne);
		printf("\n %d : colonne",ban.tab[i].indice_colonne);		
	}
	printf("\nposition pion : (%d,%d)\n",pion.indice_ligne,pion.indice_colonne);
	zer=Affichage_Grille(pion,ban,nlig,ncol,nban);
	return 0;
}
int Lire_Entier(int borne_inferieure,int borne_superieure)
{
	int entier;
	do
	{
		scanf("%d",&entier);
	}while((entier<borne_inferieure) || (entier>borne_superieure));
	return entier;
}
void Parametres(int *nlig,int *ncol,int *niveau, int *next, int *nban)
{
	printf("Paramètres du jeu :\nnombre de lignes :");
	*nlig=Lire_Entier(VMIN,VMAX);
	printf("nombre de colonnes :");
	*ncol=Lire_Entier(VMIN,VMAX);
	*nban=rand()%max(nlig,ncol)+1;
	printf("nombre de cases bannies generees :%d\n",*nban);
	
	printf("niveau de 1 à 4 :");
	*niveau=Lire_Entier(1,4);
	printf("qui commence ?\nl'ordinateur (1) ou le joueur (2) :");
	*next=Lire_Entier(1,2);
}
int max(int *nlig, int *ncol)
{
	if (*nlig>*ncol)return *nlig;
	else return *ncol;
}
struct T_Tab_Case Hasard_Ban(int nban,int *nlig,int *ncol)
{
	int ligne, colonne, i;
	struct T_Tab_Case table_cases_bannies;
	for(i=0;i<nban;i++)
	{
		do
		{
			ligne=rand()%max(nlig,ncol)+1;
			colonne=rand()%max(nlig,ncol)+1;
		}while((ligne==1 && colonne<*ncol) || (colonne==1 && ligne<*nlig) ||(ligne==*nlig && colonne>1) || (colonne==*ncol && ligne>1) );
	table_cases_bannies.tab[i].indice_ligne=ligne;
	table_cases_bannies.tab[i].indice_colonne=colonne;
	}
	
	return table_cases_bannies;
}
int Affichage_Grille(struct T_Case pion, struct T_Tab_Case ban, int nlig, int ncol, int nban)
{
	int i,z,nb;
	char premiere_ligne[50]="  ";
	char colonnes[10]="";
	char lignes[50]="";
	char caractere='-';
	char cases[10]="";
	char test[50]="";
	for(i=1;i<=ncol;i++)
	{
		sprintf(colonnes,"  %d",i);
		strcat(premiere_ligne,colonnes);

	}
	printf("%s\n",premiere_ligne);
	for(z=1;z<=nlig;z++)
	{
		sprintf(lignes,"%d  ",z);
		for(i=1;i<=ncol;i++)
		{
			for(nb=0;nb<nban;nb++)
			{
				if((ban.tab[nb].indice_ligne==z)&&(ban.tab[nb].indice_colonne==i))
				{
					caractere='X';
					break;
				}
				else if((pion.indice_ligne==z)&&(pion.indice_colonne==i))
					caractere='0';
				else
					caractere='-';
			}
			sprintf(cases,"|%c|",caractere);
			strcat(test,cases);
		}
		strcat(lignes,test);
		printf("%s\n",lignes);
		sprintf(test,"");
	}
	return 0;

}