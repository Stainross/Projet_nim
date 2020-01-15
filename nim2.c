/*Projet Algo C par 
CALVET Yann
HOUVER SING Irma
SAFSAF Sofyann*/


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
/*nombre de lignes et colonnes minimal*/
#define VMIN 5 
/*nombre de lignes et colonnes minimal*/
#define VMAX 30 


/*En-têtes de fonctions*/
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
	/*On récupère les paramètres de jeu entrés par l'utilisateur*/
	Parametres(&nlig,&ncol,&niveau,&next,&nban);
	
	/*création des cases bannies*/
	ban=Hasard_Ban(nban,&nlig,&ncol);
	/*fonction qui sert à afficher la grille de jeu*/
	variable_inutile=Affichage_Grille(pion,ban,nlig,ncol,nban);
	/*on remplit la table nim (sert à déterminer le coup gagnant de l'ordinateur)*/
	Calcul_Nimbers(nim,nlig,ncol,nban,ban);
	
	while(1)
	{
		/*si la variable next est paire c'est au tour du joueur, si elle est impaire c'est au tour de l'ordinateur*/
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
			else if(niveau==3)
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
		/*si le pion se trouve sur le puit, alors la partie s'arrête et on détermine le gagnant*/
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
	/*on ne récupère l'entier que si il est compris entre la borne minimale et la borne maximale*/
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
	/*nban est un nombre aléatoire compris entre 0 et max(nlig,ncol) inclus*/
	*nban=rand()%(max(nlig,ncol)+1);
	printf("nombre de cases bannies generees :%d\n",*nban);
	
	printf("niveau de 1 à 4 :");
	*niveau=Lire_Entier(1,4);
	printf("qui commence ?\nl'ordinateur (1) ou le joueur (2) :");
	*next=Lire_Entier(1,2);
}
int max(int *nlig, int *ncol)
{
	/*détermine le maximum entre deux entiers*/
	if (*nlig>*ncol)return *nlig;
	else return *ncol;
}
struct T_Tab_Case Hasard_Ban(int nban,int *nlig,int *ncol)
{
	int ligne, colonne, i,bannissable,z;
	struct T_Tab_Case table_cases_bannies;
	/*sert à déterminer nban cases bannies*/
	for(i=0;i<=nban;i++)
	{
		do
		{
			/*on génère aléatoirement une ligne et une colonne qui appartiennent à la grille*/
			ligne=rand()%max(nlig,ncol)+1;
			colonne=rand()%max(nlig,ncol)+1;
			bannissable=1;
			/*on parcourt toutes les cases bannies*/
			for(z=0;z<nban;z++)
			{
				/*la case n'est pas bannissable si:
				- la case est déjà une case bannie
				- la case située juste en haut à droite est une case bannie
				- la case située juste en bas à gauche est une case bannie*/
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
			/*on continue de chercher la case à bannir tant qu'elle ne remplit pas les conditions*/
		}while((ligne==1 && colonne<*ncol) || (colonne==1 && ligne<*nlig) ||(ligne==*nlig && colonne>1) || (colonne==*ncol && ligne>1) || (bannissable==0));
	/*on ajoute la case bannissable au tableau des cases bannies*/
	table_cases_bannies.tab[i].indice_ligne=ligne;
	table_cases_bannies.tab[i].indice_colonne=colonne;
	}
	
	return table_cases_bannies;
}
int Affichage_Grille(struct T_Case pion, struct T_Tab_Case ban, int nlig, int ncol, int nban)
{
	int i,z,nb;
	char premiere_ligne[100]="   ",colonnes[10]="";
	char lignes[100]="",caractere='-',cases[5]="",ligne_de_cases[100]="";
	/*création de la ligne contenant les indices des colonnes*/
	for(i=1;i<=ncol;i++)
	{
		//if(i<10)sprintf(colonnes," %.2d ",i);
		/*else */sprintf(colonnes,"%.2d ",i);
		strcat(premiere_ligne,colonnes);

	}
	printf("%s\n",premiere_ligne);
	/*création des lignes suivantes*/
	for(z=1;z<=nlig;z++)
	{
		//if(z<10)sprintf(lignes,"%d  ",z);
		/*else */sprintf(lignes,"%.2d ",z);
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
	/*pour la table des nimbers:
	- le plus petit indice de ligne est 0
	- le plus petit indice de colonne est 0*/
	/*on initialise le nimber du puit à 0*/
	nim[nlig-1][ncol-1]=0;
	if(nban!=0)
	{
		/*dans la table des nimbers, les cases bannies sont représentées par des 5*/
		for(z=0;z<nban;z++)
		{
			nim[ban.tab[z].indice_ligne-1][ban.tab[z].indice_colonne-1]=5;
		}
	}
	/*on part du puit pour déterminer les nimbers de toutes les cases*/
	for(z=nlig;z>=1;z=z-1)
	{
		for(i=ncol;i>=1;i=i-1)
		{
			case_.indice_ligne=i;
			case_.indice_colonne=z;
			/*si la case n'est pas une case bannie alors on détermine son nimber*/
			if(nim[i-1][z-1]!=5)
			{
				Voisines(case_,&nb_vois,&vois,nban,ban,nlig,ncol);
				/*nimber_voisine sert de booleen:
				- vaut 1 si il n'existe pas de cases voisines ayant pour nimber 0
				- vaut 0 sinon*/
				nimber_voisine=1;
				if(nb_vois!=0)
				{
					/*on parcourt toutes les cases voisines*/
					for(x=0;x<nb_vois;x++)
					{
						/*si une de ces cases à un nimber égal à 0, alors nimber_voisine vaut 0*/
						if(nim[vois.tab[x].indice_ligne-1][vois.tab[x].indice_colonne-1]==0)
						{
							nimber_voisine=0;

						}

					}
					/*si nimber_voisine vaut 1 alors le nimber de la case vaut 0*/
					if(nimber_voisine==1)
					{
						nim[i-1][z-1]=0;
					}
					/*sinon il vaut 1*/
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
	/*case_bannie est utilisé comme un booléen:
	- vaut 1 si on rencontre une case bannie
	- vaut 0 sinon*/
	int case_bannie=0;
	*nb_vois=0;

	/*on parcourt les 2 cases se trouvant à droite de la case actuelle*/
	for(z=(case_.indice_ligne)+1;z<=(case_.indice_ligne)+2;z++)
	{
		if(nban!=0)
		{
			for(n=0;n<=nban;n++)
			{
				/*si une de ces cases est bannie, alors case_bannie vaudra 1*/
				if((z==ban.tab[n].indice_ligne)&&(case_.indice_colonne==ban.tab[n].indice_colonne))
					{
						case_bannie=1;
						break;
					}
					
			}
		}
		
		
		/*si case_bannie vaut 0 et que la case se situe toujours dans la grille alors cette case est une voisine*/
		if((case_bannie==0)&&(z<=nlig))
		{
			*nb_vois=(*nb_vois)+1;
			vois->tab[*nb_vois-1].indice_ligne=z;
			vois->tab[*nb_vois-1].indice_colonne=case_.indice_colonne;
		}
	}
	case_bannie=0;
	/*on parcourt les 2 cases se trouvant en-dessous de la case actuelle*/
	for(i=(case_.indice_colonne)+1;i<=(case_.indice_colonne)+2;i++)
	{
		if(nban!=0)
		{
			for(n=0;n<=nban;n++)
			{
				/*si une de ces cases est bannie, alors case_bannie vaudra 1*/
				if((i==ban.tab[n].indice_colonne)&&(case_.indice_ligne==ban.tab[n].indice_ligne))
					{
						case_bannie=1;
						break;
					}
					
			}
		}
		
		/*si case_bannie vaut 0 et que la case se situe toujours dans la grille alors cette case est une voisine*/
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
		/*le pion se déplace*/
		pion.indice_ligne=vois.tab[0].indice_ligne;
		pion.indice_colonne=vois.tab[0].indice_colonne;
	}
	else {
		printf("choisir la destination ");
		/*affiche les destinations possibles*/
		for(i=1;i<=nb_vois;i++)
		{
			printf("%d:(%d,%d) ",i,vois.tab[i-1].indice_ligne,vois.tab[i-1].indice_colonne);
		}
		/*sert à ne récupérer un choix que si il est possible*/
		do
		{
			printf("\n---> ");
			while(getchar()!='\n');
			scanf("%d",&choix);
			if(choix<1 || choix>nb_vois)
				printf("erreur !");

				
		}while(choix<1 || choix>nb_vois);
		
		/*le pion se déplace*/
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
	/*l'ordinateur choisi au hasard parmi les coups possibles*/
	choix=rand()%nb_vois;
	printf("L'ordinateur deplace le pion en (%d,%d)\n",vois.tab[choix].indice_ligne,vois.tab[choix].indice_colonne);
	/*le pion se déplace*/
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
	/*l'ordinateur prend un choix au hasard*/
	choix=rand()%nb_vois;
	for(i=0;i<nb_vois;i++)
	{
		/*mais si une voisine a un nimber égal à zéro, alors l'ordinateur choisira d'aller vers cette voisine*/
		if(nim[vois.tab[i].indice_ligne-1][vois.tab[i].indice_colonne-1]==0)
		{
			choix=i;
			break;
		}
	}
	/*le pion se déplace*/
	pion.indice_ligne=vois.tab[choix].indice_ligne;
	pion.indice_colonne=vois.tab[choix].indice_colonne;
	printf("L'ordinateur deplace le pion en (%d,%d)\n",vois.tab[choix].indice_ligne,vois.tab[choix].indice_colonne);
	return pion;
}