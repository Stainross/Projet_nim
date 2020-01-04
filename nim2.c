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
void Calcul_Nimbers(int nim[][VMAX],int *,int *,int *,struct T_Tab_Case);
void Voisines(struct T_Case,int *, struct T_Tab_Case *,int *, struct T_Tab_Case,int *,int *);

int main()
{int nlig,ncol,niveau,next,nban,i,zer,z;
	int nim[VMAX][VMAX];
	struct T_Tab_Case ban,vois;
	struct T_Case pion;
	pion.indice_ligne=2;
	pion.indice_colonne=2;
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
	Calcul_Nimbers(nim,&nlig,&ncol,&nban,ban);
	/*Voisines(pion,&nb_vois,vois,&nban,ban,&nlig,&ncol);*/
	for(i=0;i<nlig;i++)
	{
		for(z=0;z<ncol;z++)
		{
			printf("%d |",nim[i][z]);
		}
		printf("\n");
		
	}
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
	*nban=rand()%(max(nlig,ncol)+1);
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
	int ligne, colonne, i,bannissable,z;
	struct T_Tab_Case table_cases_bannies;
	for(i=0;i<=nban;i++)
	{
		do
		{
			ligne=rand()%max(nlig,ncol)+1;
			colonne=rand()%max(nlig,ncol)+1;
			bannissable=1;
			for(z=0;z<nban;z++)
			{
				if((table_cases_bannies.tab[z].indice_ligne==ligne)&&(table_cases_bannies.tab[z].indice_colonne==colonne))
				{
					bannissable=0;
					break;
				}
				else if((table_cases_bannies.tab[z].indice_ligne==ligne+1)&&(table_cases_bannies.tab[z].indice_colonne==colonne-1))
				{
					bannissable=0;
					break;
				}
				else if((table_cases_bannies.tab[z].indice_ligne==ligne-1)&&(table_cases_bannies.tab[z].indice_colonne==colonne+1))
					{
						bannissable=0;
						break;
					}
			}
		}while((ligne==1 && colonne<*ncol) || (colonne==1 && ligne<*nlig) ||(ligne==*nlig && colonne>1) || (colonne==*ncol && ligne>1) || (bannissable==0));
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
			if(nban==0)
			{
				if((pion.indice_ligne==z)&&(pion.indice_colonne==i))
						caractere='0';
				else
					caractere='-';
			}
			else{
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
void Calcul_Nimbers(int nim[][VMAX],int *nlig,int *ncol,int *nban,struct T_Tab_Case ban)
{
	int z,i,x,nimber_voisine,a,b;
	int nb_vois=0;
	struct T_Tab_Case vois;
	struct T_Case case_;
	for(z=0;z<*nlig;z++)
	{
		for(i=0;i<*ncol;i++)
		{
			nim[z][i]=3;
		}
	}
	nim[*nlig-1][*ncol-1]=0;
	if(*nban!=0)
	{
		for(z=0;z<*nban;z++)
		{
			nim[ban.tab[z].indice_ligne-1][ban.tab[z].indice_colonne-1]=5;
		}
	}
	printf("%d",nim[*nlig-1][*ncol-1]);
	for(z=*nlig;z>=1;z=z-1)
	{
		for(i=*ncol;i>=1;i=i-1)
		{
			case_.indice_ligne=i;
			case_.indice_colonne=z;
			if(nim[i-1][z-1]!=5)
			{
				Voisines(case_,&nb_vois,&vois,nban,ban,nlig,ncol);
				nimber_voisine=1;
				if(nb_vois!=0)
				{

					for(x=0;x<nb_vois;x++)
					{
						a=vois.tab[x].indice_ligne;
						b=vois.tab[x].indice_colonne;
						if(nim[a-1][b-1]==0)
						{
							nimber_voisine=0;

						}

					}
					if(nimber_voisine==1)
					{
						nim[i-1][z-1]=0;
					}
						
					else 
					{
						nim[i-1][z-1]=1;
					}
				}
				
			}
		}
	}

	
}
void Voisines(struct T_Case case_,int *nb_vois, struct T_Tab_Case *vois,int *nban, struct T_Tab_Case ban,int *nlig,int *ncol)
{
	int z,n,i;
	int case_bannie=0;
	*nb_vois=0;

	for(z=(case_.indice_ligne)+1;z<=(case_.indice_ligne)+2;z++)
	{
		if(*nban!=0)
		{
			for(n=0;n<=*nban;n++)
			{
				if((z==ban.tab[n].indice_ligne)&&(case_.indice_colonne==ban.tab[n].indice_colonne))
					{
						case_bannie=1;
						break;
					}
					
			}
		}
		
		

		if((case_bannie==0)&&(z<=*nlig))
		{
			*nb_vois=(*nb_vois)+1;
			vois->tab[*nb_vois-1].indice_ligne=z;
			vois->tab[*nb_vois-1].indice_colonne=case_.indice_colonne;
		}
	}
	case_bannie=0;
	for(i=(case_.indice_colonne)+1;i<=(case_.indice_colonne)+2;i++)
	{
		if(*nban!=0)
		{
			for(n=0;n<=*nban;n++)
			{
				if((i==ban.tab[n].indice_colonne)&&(case_.indice_ligne==ban.tab[n].indice_ligne))
					{
						case_bannie=1;
						break;
					}
					
			}
		}
		
		
		if((case_bannie==0)&&(i<=*ncol))
		{
			*nb_vois=(*nb_vois)+1;
			vois->tab[*nb_vois-1].indice_colonne=i;
			vois->tab[*nb_vois-1].indice_ligne=case_.indice_ligne;
		}
	}

}