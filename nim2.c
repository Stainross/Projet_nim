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
void Calcul_Nimbers(int nim[][VMAX],int ,int ,int ,struct T_Tab_Case);
void Voisines(struct T_Case,int *, struct T_Tab_Case *,int , struct T_Tab_Case,int ,int );
struct T_Case Coup_joueur(struct T_Case,int, struct T_Tab_Case, int ,int);
struct T_Case Coup_Ordi_Hasard(struct T_Case,int,struct T_Tab_Case,int,int);
struct T_Case Coup_Ordi_Gagnant(struct T_Case,int,struct T_Tab_Case,int,int,int nim[][VMAX]);

int main()
{
	int nlig,ncol,niveau,next,nban,variable_inutile,proba,nim[VMAX][VMAX];
	struct T_Tab_Case ban,vois;
	struct T_Case pion;
	pion.indice_ligne=1;
	pion.indice_colonne=1;
	srand((unsigned int)time(NULL));
	Parametres(&nlig,&ncol,&niveau,&next,&nban);
	
	ban=Hasard_Ban(nban,&nlig,&ncol);
	variable_inutile=Affichage_Grille(pion,ban,nlig,ncol,nban);
	
	Calcul_Nimbers(nim,nlig,ncol,nban,ban);
	while(1)
	{
		if(next%2==0)
		{
			pion=Coup_joueur(pion,nban,ban,nlig,ncol);
		}
		else
		{
			if(niveau==1)
			{
				pion=Coup_Ordi_Hasard(pion,nban,ban,nlig,ncol);
			}
			else if(niveau==2)
			{
				proba=rand()%3;
				if(proba==0)
					pion=Coup_Ordi_Gagnant(pion,nban,ban,nlig,ncol,nim);
				else
					pion=Coup_Ordi_Hasard(pion,nban,ban,nlig,ncol);
			}
			else if(niveau=3)
			{
				proba=rand()%3;
				if(proba==0)
					pion=Coup_Ordi_Hasard(pion,nban,ban,nlig,ncol);
				else
					pion=Coup_Ordi_Gagnant(pion,nban,ban,nlig,ncol,nim);
			}
			else
				pion=Coup_Ordi_Gagnant(pion,nban,ban,nlig,ncol,nim);
		}
		variable_inutile=Affichage_Grille(pion,ban,nlig,ncol,nban);
		if(pion.indice_ligne==nlig && pion.indice_colonne==ncol)
		{
			if(next%2==0)
				printf("C'est terminé. BRAVO TU AS GAGNE !");
			else
				printf("C'est terminé. DOMMAGE TU AS PERDU !");
			return 0;
		}
		next++;
		}
	

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
	char premiere_ligne[50]="   ",colonnes[10]="";
	char lignes[50]="",caractere='-',cases[5]="",ligne_de_cases[50]="";
	for(i=1;i<=ncol;i++)
	{
		if(i<10)sprintf(colonnes," %d ",i);
		else sprintf(colonnes,"%d ",i);
		strcat(premiere_ligne,colonnes);

	}
	printf("%s\n",premiere_ligne);
	for(z=1;z<=nlig;z++)
	{
		if(z<10)sprintf(lignes,"%d  ",z);
		else sprintf(lignes,"%d ",z);
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
			strcat(ligne_de_cases,cases);
		}
		strcat(lignes,ligne_de_cases);
		printf("%s\n",lignes);
		sprintf(ligne_de_cases,"");
	}
	return 0;

}
void Calcul_Nimbers(int nim[][VMAX],int nlig,int ncol,int nban,struct T_Tab_Case ban)
{
	int z,i,x,nimber_voisine,a,b;
	int nb_vois=0;
	struct T_Tab_Case vois;
	struct T_Case case_;
	for(z=0;z<nlig;z++)
	{
		for(i=0;i<ncol;i++)
		{
			nim[z][i]=3;
		}
	}
	nim[nlig-1][ncol-1]=0;
	if(nban!=0)
	{
		for(z=0;z<nban;z++)
		{
			nim[ban.tab[z].indice_ligne-1][ban.tab[z].indice_colonne-1]=5;
		}
	}
	printf("%d",nim[nlig-1][ncol-1]);
	for(z=nlig;z>=1;z=z-1)
	{
		for(i=ncol;i>=1;i=i-1)
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
						if(nim[vois.tab[x].indice_ligne-1][vois.tab[x].indice_colonne-1]==0)
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
void Voisines(struct T_Case case_,int *nb_vois, struct T_Tab_Case *vois,int nban, struct T_Tab_Case ban,int nlig,int ncol)
{
	int z,n,i;
	int case_bannie=0;
	*nb_vois=0;

	for(z=(case_.indice_ligne)+1;z<=(case_.indice_ligne)+2;z++)
	{
		if(nban!=0)
		{
			for(n=0;n<=nban;n++)
			{
				if((z==ban.tab[n].indice_ligne)&&(case_.indice_colonne==ban.tab[n].indice_colonne))
					{
						case_bannie=1;
						break;
					}
					
			}
		}
		
		

		if((case_bannie==0)&&(z<=nlig))
		{
			*nb_vois=(*nb_vois)+1;
			vois->tab[*nb_vois-1].indice_ligne=z;
			vois->tab[*nb_vois-1].indice_colonne=case_.indice_colonne;
		}
	}
	case_bannie=0;
	for(i=(case_.indice_colonne)+1;i<=(case_.indice_colonne)+2;i++)
	{
		if(nban!=0)
		{
			for(n=0;n<=nban;n++)
			{
				if((i==ban.tab[n].indice_colonne)&&(case_.indice_ligne==ban.tab[n].indice_ligne))
					{
						case_bannie=1;
						break;
					}
					
			}
		}
		
		
		if((case_bannie==0)&&(i<=ncol))
		{
			*nb_vois=(*nb_vois)+1;
			vois->tab[*nb_vois-1].indice_colonne=i;
			vois->tab[*nb_vois-1].indice_ligne=case_.indice_ligne;
		}
	}

}
struct T_Case Coup_joueur(struct T_Case pion,int nban,struct T_Tab_Case ban,int nlig,int ncol)
{
	int nb_vois=0;
	int i,choix;
	struct T_Tab_Case vois;
	printf("A toi de jouer !\n");
	Voisines(pion,&nb_vois,&vois,nban,ban,nlig,ncol);
	
	if(nb_vois==1)
	{
		printf("Seule possibilite : (%d,%d)\nvalider --->",vois.tab[0].indice_ligne,vois.tab[0].indice_colonne);
		scanf("%d",&choix);
		pion.indice_ligne=vois.tab[0].indice_ligne;
		pion.indice_colonne=vois.tab[0].indice_colonne;
	}
	else {
		printf("choisir la destination ");
		for(i=1;i<=nb_vois;i++)
		{
			printf("%d:(%d,%d) ",i,vois.tab[i-1].indice_ligne,vois.tab[i-1].indice_colonne);
		}
		do
		{
			printf("\n---> ");
			while(getchar()!='\n');
			scanf("%d",&choix);
			if(choix<1 || choix>nb_vois)
				printf("erreur !");

				
		}while(choix<1 || choix>nb_vois);
		
		pion.indice_ligne=vois.tab[choix-1].indice_ligne;
		pion.indice_colonne=vois.tab[choix-1].indice_colonne;
	}
	

	return pion;
}
struct T_Case Coup_Ordi_Hasard(struct T_Case pion,int nban,struct T_Tab_Case ban,int nlig,int ncol)
{
	int nb_vois=0;
	int choix;
	struct T_Tab_Case vois;
	Voisines(pion,&nb_vois,&vois,nban,ban,nlig,ncol);
	choix=rand()%nb_vois;
	printf("L'ordinateur deplace le pion en (%d,%d)\n",vois.tab[choix].indice_ligne,vois.tab[choix].indice_colonne);
	pion.indice_ligne=vois.tab[choix].indice_ligne;
	pion.indice_colonne=vois.tab[choix].indice_colonne;
	return pion;
}
struct T_Case Coup_Ordi_Gagnant(struct T_Case pion,int nban,struct T_Tab_Case ban,int nlig,int ncol,int nim[][VMAX])
{
	int nb_vois=0;
	int choix,i;
	struct T_Tab_Case vois;
	Voisines(pion,&nb_vois,&vois,nban,ban,nlig,ncol);
	choix=rand()%nb_vois;
	for(i=0;i<nb_vois;i++)
	{
		if(nim[vois.tab[i].indice_ligne-1][vois.tab[i].indice_colonne-1]==0)
		{
			choix=i;
			break;
		}
	}
	pion.indice_ligne=vois.tab[choix].indice_ligne;
	pion.indice_colonne=vois.tab[choix].indice_colonne;
	printf("L'ordinateur deplace le pion en (%d,%d)\n",vois.tab[choix].indice_ligne,vois.tab[choix].indice_colonne);
	return pion;
}