/************************************************************************************
 *   Programme de simulation de balayage du robot Rover 5 pour le PPE 2012/2013
 *
 *   Principe de l'algorithme de Wavefront modifié afin de s'adapter au cahier
 *   des charges du PPE:
 *
 *		-Ajouter toute les confiurations possibles du labyrinthe et choisir la
 *		configuration correspondante
 *
 *		-Balayer tout le labrinthe, et non recherché le chemin le plus rapide, pour
 *		cela on rensigne l'emplacement des balles et le robot se dirige vers chaque
 *		emplacement de balles
 *
 ************************************************************************************/

#include <stdlib.h>
#include <stdio.h>

// Configuration 1
int laby1[12][12]=
	{{0,0,0,0,0,0,255,0,0,255,0,0},
	{0,0,0,0,0,0,255,0,0,255,0,0},
	{0,0,0,0,0,0,255,0,0,0,255,0},
	{0,0,255,0,0,0,255,0,0,0,0,0},
	{0,0,255,0,0,0,255,0,0,0,0,0},
	{0,0,255,0,0,0,255,255,255,0,0,255},
	{0,0,255,0,255,0,0,0,0,0,0,0},
	{0,0,255,255,255,0,0,255,255,255,255,0},
	{255,255,255,0,255,0,0,0,0,0,0,0},
	{0,0,255,0,255,255,255,255,255,0,0,255},
	{0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,255,0,0,0,0,0,0,0}};

// Configuration 2
int laby2[12][12]=
	{{0,0,0,0,0,0,255,0,0,255,0,0},
	{0,0,0,0,0,0,255,0,0,255,0,0},
	{0,0,0,0,0,254,255,0,0,0,255,0},
	{0,0,255,0,0,0,255,254,0,0,0,0},
	{0,0,255,0,0,0,255,254,0,0,0,0},
	{0,0,255,0,0,0,255,255,255,0,0,255},
	{0,0,255,254,255,0,0,0,255,0,0,0},
	{0,0,255,255,255,0,0,0,255,0,0,0},
	{255,255,255,0,255,0,0,254,255,0,0,0},
	{0,0,255,0,255,0,255,255,255,0,0,255},
	{0,254,0,0,255,254,0,0,0,0,0,254},
	{0,0,0,0,255,254,0,0,0,0,0,0}};

// Configuration 3
int laby3[12][12]=
	{{0,0,0,0,0,0,255,0,0,255,0,0},
	{0,0,0,0,0,0,255,0,0,255,0,0},
	{0,0,0,0,0,254,255,0,0,0,255,0},
	{0,0,255,0,0,0,255,254,0,0,0,0},
	{0,0,255,0,0,0,255,254,0,0,0,0},
	{0,0,255,0,0,0,255,255,255,0,0,255},
	{0,0,255,254,255,0,0,0,0,0,0,0},
	{0,0,255,255,255,0,255,255,255,255,255,0},
	{255,255,255,0,255,0,0,254,0,0,0,0},
	{0,0,255,0,255,0,255,255,255,0,0,255},
	{0,254,0,0,255,254,0,0,0,0,0,254},
	{0,0,0,0,255,254,0,0,0,0,0,0}};

// Configuration 4
int laby4[12][12]=
	{{0,0,0,0,0,0,255,0,0,255,0,0},
	{0,0,0,0,0,0,255,0,0,255,0,0},
	{0,0,0,0,0,254,255,0,0,0,255,0},
	{0,0,255,0,0,0,255,254,0,0,0,0},
	{0,0,255,0,0,0,255,254,0,0,0,0},
	{0,0,255,0,255,0,255,255,255,0,0,255},
	{0,0,255,254,255,0,0,0,255,0,0,0},
	{0,0,255,0,255,255,0,0,255,0,0,0},
	{255,255,255,0,255,0,0,254,255,0,0,0},
	{0,0,255,0,255,255,255,255,255,0,0,255},
	{0,254,0,0,0,254,0,0,0,0,0,254},
	{0,0,0,0,255,254,0,0,0,0,0,0}};

// Configuration 5
int laby5[12][12]=
	{{0,0,0,0,0,0,255,0,0,255,0,0},
	{0,0,0,0,0,0,255,0,0,255,0,0},
	{0,0,0,0,0,254,255,0,0,0,255,0},
	{0,0,255,0,0,0,255,254,0,0,0,0},
	{0,0,255,0,0,0,255,254,0,0,0,0},
	{0,0,255,0,255,0,255,255,255,0,0,255},
	{0,0,255,254,255,0,0,0,255,0,0,0},
	{0,0,255,0,255,255,0,0,255,0,0,0},
	{255,255,255,0,255,0,0,254,255,0,0,0},
	{0,0,255,0,255,0,255,255,255,0,0,255},
	{0,254,0,0,255,254,0,0,0,0,0,254},
	{0,0,0,0,255,254,0,0,0,0,0,0}};

// Matrice 12*12
int laby[12][12];

int choix;

// Déclaration des variables construisant le labyrinthe
const int rien = 0;
const int murs = 255;
const int sortie = 1;
const int robot = 253;
const int balles = 254;

// Coordonnées de départ du robot et de la sortie
int robot_x = 7;
int robot_y = 1;
int sortie_x = 0;
int sortie_y = 10;

// Variables booleene
int sortieballe = 1; // Boucle de déplacement vers les balles
int bonneBalle ; // Bonne ou mauvaise balle
int sonar; // Balle proche du robot (1) ou non (0)

// Varibles pour la boucle for
int i = 0;

// Coordonnées des balles sous fromes de tableau
int balleN_x[9] = {2,6,8,10,10,11,10,4,3};
int balleN_y[9] = {5,3,7,1,5,5,11,7,7};

// Variables pour le balayage de la carte
int x = 0;
int y = 0;

// Variables pour la fonction dessiner_map()
int temp_A = 0;
int temp_B = 0;
int cpt = 0;
int steps = 0; // Permet de déterminer le nombre de calculs le processeur va effectuer

// Variables pour la recherche de la plus petite valeur
int case_min = 250;
int case_min_localisation = 250;
int nouvel_emplacement = 1; // Initialement dirigé vers le Nord (=1)
int emplacement_precedent = 1;
int reset_min = 250; // Tout ce qui est supérieur à cette valeur est un objet spécial, un robot, mur, etc..

FILE *out ; // Fichier texte

// Déclaration des fonctions
void choixConfig();
int wavefront(int robot_x, int robot_y);
void unpropagate(int robot_x, int robot_y);
int valeur_min(int x, int y);
void dessiner_map(void);
void mouvementRobot();

int main(void)
	{
		choixConfig();

		out = fopen("results.txt","w");
		fprintf(out,"Début du Wavefront\n");
		printf("Debut du Wavefront\n\n");

	//////////////Code du waveront//////////////
		while(laby[robot_x][robot_y] != sortie)
					{
						while(sortieballe)
						{
							for(i = 0; i < 9; i++)
							{
								if ((choix==2 || choix==3) && i==3)
									i++; // On ignore la balle

								sortie_x = balleN_x[i];
								sortie_y = balleN_y[i];

								laby[sortie_x][sortie_y] = sortie;

								while(laby[robot_x][robot_y] != sortie)
								{
									mouvementRobot();
								}

								printf("R_x= %d ; ", robot_x);
								printf("R_y = %d\n", robot_y);
								printf("B_x = %d ; ", sortie_x);
								printf("B_y = %d\n", sortie_y);

								laby[robot_x][robot_y] = robot;

								system("pause");

								printf("Presence de balle ? 1(oui)/0(non) : ");
								scanf("%d",sonar);

								if(sonar)
								{
									printf("Balle de bonne couleur ? 1(oui)/0(non)");
									scanf("%d", bonneBalle);

									if(bonneBalle)
									{
										//attraperBalle();
										sortie_x = 0;
										sortie_y = 10;
										laby[sortie_x][sortie_y] = sortie;

										while(laby[robot_x][robot_y] != sortie)
										{
											mouvementRobot();
										}

										printf("steps: %d\n", steps);
										fclose(out);
										system("PAUSE");
										return 0;
									}
								}

								if(i == 8) // Si le robot est allé à tous les emplacements des balles, on va vers la sortie
								{
									sortieballe = 0;
								}
							}
						}

						sortie_x = 0;
						sortie_y = 10;

						laby[sortie_x][sortie_y] = sortie;

						mouvementRobot();
					}
			//////////////////////////////////////////

		printf("steps: %d\n", steps);
		fclose(out);
		system("PAUSE");
		return 0;
	}


int wavefront(int robot_x, int robot_y)
	{
		// Initialiser l'ancien Wavefront
		unpropagate(robot_x, robot_y);

		laby[sortie_x][sortie_y] = sortie;

		printf("Sortie ajoute:\n");
		dessiner_map();

		cpt = 0;

		while(cpt < 1000) // Permet de trouver le robot en plusieurs cycles
			{
				x = 0;
				y = 0;

    			while(x < 12 && y < 12) // Tant que la map n'est pas scannée complètement
    				{
    					// Si l'emplacement est un mur ou la sortie, on l'ignore
    					if (laby[x][y] != murs && laby[x][y] != sortie)
    						{
								// Un chemin complet est trouvé
    							if (valeur_min(x, y) < reset_min && laby[x][y] == robot)
    								{
                						printf("Finished Wavefront:\n");
                						dessiner_map();
    									// Terminé, dire au robot de commencer son déplacement
    									return case_min_localisation;
    								}

    							// Enregister une valeur à cette case
    							else if (case_min != reset_min) // Sans ce test, les cases 'rien' serai à cet emplacement
    								laby[x][y] = case_min+1;
    						}

    					// Aller à la prochaine case et/ou à la prochaine rangée
    					y++;
    					if (y == 12 && x != 12) // Si on arrive au bout de la ligne, on passe à la rangée suivante
    						{
    							x++;
    							y = 0;
    						}
    				}

   				printf("Sweep #: %d\n", cpt+1);
				dessiner_map();
   				cpt++;
			}

		return 0;
	}

// Effacer l'ancien chemin afin d'en déterminer un autre et éviter de surcharger la carte
void unpropagate(int robot_x, int robot_y)
	{
		printf("Map precedente:\n");
		dessiner_map();

		printf("Début Unpropagate\n");

		// Balayage de la carte entière
		for (x = 0; x < 12; x++)
			for (y = 0; y < 12; y++)
				if (laby[x][y] != murs && laby[x][y] != sortie) // Si l'emplacement est un mur ou la sortie, on l'ignore
					laby[x][y] = rien; // On efface la case, on la réinitialise

		// Comme l'ancienne position du robot a été effacée, on lui affecte sa nouvelle position
		laby[robot_x][robot_y] = robot;

		printf("Unpropagation Complete:\n");
		fprintf(out, "Unpropagation Complete:\n");
		dessiner_map();
	}

/*Cette fonction regarde les cases adjacentes d'un emplacement, et retourne la plus petite valeur
1 représente le Nord, 2 l'Est, 3 le Sud et 4 l'Ouest (sens horaire)*/
int valeur_min(int x, int y)
	{
		case_min = reset_min;

		// Sud
		if(x < 11)
			if  (laby[x+1][y] < case_min && laby[x+1][y] != rien) // Trouver la plus petite valeur en excluant les cases '0', c'est à dire "rien"
				{
				case_min = laby[x+1][y];
				case_min_localisation = 3;
				}

		// Nord
		if(x > 0)
			if  (laby[x-1][y] < case_min && laby[x-1][y] != rien)
				{
				case_min = laby[x-1][y];
				case_min_localisation = 1;
				}

		// Est
		if(y < 11)
			if  (laby[x][y+1] < case_min && laby[x][y+1] != rien)
				{
				case_min = laby[x][y+1];
				case_min_localisation = 2;
				}

		// Ouest
		if(y > 0)
			if  (laby[x][y-1] < case_min && laby[x][y-1] != rien)
				{
				case_min = laby[x][y-1];
				case_min_localisation = 4;
				}

		return case_min;
	}

void dessiner_map(void)
	{
		for (temp_B=0; temp_B<12; temp_B++)
			{
			for (temp_A=0; temp_A<12; temp_A++)
				{
				if (laby[temp_B][temp_A] == murs)
				   printf("M ");
				else if(laby[temp_B][temp_A] == balles)
					printf("B ");
				else if (laby[temp_B][temp_A] == robot)
				   printf("R ");
				else if (laby[temp_B][temp_A] == sortie)
				   printf("S ");
				else
				   printf("%d ",laby[temp_B][temp_A]);

				fprintf(out, "%d",laby[temp_B][temp_A]);
				fprintf(out, "\t");
				}
			printf("\n"); // Aller à la prochaine ligne Y
			fprintf(out, "\n");
			}
		printf("\n");
		fprintf(out, "\n\n");
		steps++;
	}

void mouvementRobot()
{
	nouvel_emplacement=wavefront(robot_x, robot_y);

	// Mettre à jour le nouvel emplacement du robot
	if (nouvel_emplacement==1)
		{
		robot_x--;
		//printf("x=%d y=%d\n\n",robot_x,robot_y);
		}
	if (nouvel_emplacement==2)
		{
		robot_y++;
		//printf("x=%d y=%d\n\n",robot_x,robot_y);
		}
	if (nouvel_emplacement==3)
		{
		robot_x++;
		//printf("x=%d y=%d\n\n",robot_x,robot_y);
		}
	if (nouvel_emplacement==4)
		{
		robot_y--;
		//printf("x=%d y=%d\n\n",robot_x,robot_y);
		}

	emplacement_precedent=nouvel_emplacement; // Enregistrer l'emplacement précédent du robot
}

void choixConfig()
{

	printf("Choix configuration :");
	scanf("%d", &choix);

	switch(choix)
	{
	case 1:
		{for(x=0;x<12;x++)
				for(y=0;y<12;y++)
					laby[x][y]=laby1[x][y];}
		break;
	case 2:
		{for(x=0;x<12;x++)
				for(y=0;y<12;y++)
					laby[x][y]=laby2[x][y];}
		break;
	case 3:
		{for(x=0;x<12;x++)
				for(y=0;y<12;y++)
					laby[x][y]=laby3[x][y];}
		break;
	case 4:
		{for(x=0;x<12;x++)
				for(y=0;y<12;y++)
					laby[x][y]=laby4[x][y];}
		break;
	case 5:
		{for(x=0;x<12;x++)
				for(y=0;y<12;y++)
					laby[x][y]=laby5[x][y];}
		break;
	default:
		choixConfig();
		break;
	}
}
