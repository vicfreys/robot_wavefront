#define rien 0
#define murs 255
#define robot 253
#define sortie 1
#define balles 254
#define reset_min 250
#define nbBalles 8

#define DIRECTION_A 8
#define MOT_A 6

#define DIRECTION_B 7
#define MOT_B 5

#define inputA 4
#define inputB 3
#define bp 9
#define ir A1



const int s0=2, s1=10, s2=11, s3=12; 
int flag=0;
int counter=0;
int countR=0,countG=0,countB=0;

// Configuration 1
byte laby1[12][12]=	
	{{0,0,0,0,0,0,255,0,0,255,0,0},
	{0,0,0,0,0,0,255,0,0,255,0,0},		
	{0,0,255,0,0,0,255,0,0,0,0,0},		
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
byte laby2[12][12]=	
	{{0,0,0,0,0,0,255,0,0,255,0,0},
	{0,0,0,0,0,0,255,0,0,255,0,0},		
	{0,0,255,0,0,0,255,0,0,0,0,0},		
	{0,0,255,0,0,0,255,0,0,0,0,0},			
	{0,0,255,0,0,0,255,0,0,0,0,0},
	{0,0,255,0,0,0,255,255,255,0,0,255},
	{0,0,255,0,255,0,0,0,255,0,0,0},
	{0,0,255,255,255,0,0,0,255,0,0,0},
	{255,255,255,0,255,0,0,0,255,0,0,0},
	{0,0,255,0,255,0,255,255,255,0,0,255},	
	{0,0,0,0,255,0,0,0,0,0,0,0},
	{0,0,0,0,255,0,0,0,0,0,0,0}};

// Configuration 3
byte laby3[12][12]=	
	{{0,0,0,0,0,0,255,0,0,255,0,0},
	{0,0,0,0,0,0,255,0,0,255,0,0},		
	{0,0,255,0,0,0,255,0,0,0,0,0},		
	{0,0,255,0,0,0,255,0,0,0,0,0},			
	{0,0,255,0,0,0,255,0,0,0,0,0},
	{0,0,255,0,0,0,255,255,255,0,0,255},
	{0,0,255,0,255,0,0,0,0,0,0,0},
	{0,0,255,255,255,0,255,255,255,255,255,0},
	{255,255,255,0,255,0,0,0,0,0,0,0},
	{0,0,255,0,255,0,255,255,255,0,0,255},	
	{0,0,0,0,255,0,0,0,0,0,0,0},
	{0,0,0,0,255,0,0,0,0,0,0,0}};

// Configuration 4
byte laby4[12][12]=	
	{{0,0,0,0,0,0,255,0,0,255,0,0},
	{0,0,0,0,0,0,255,0,0,255,0,0},		
	{0,0,255,0,0,0,255,0,0,0,0,0},		
	{0,0,255,0,0,0,255,0,0,0,0,0},			
	{0,0,255,0,0,0,255,0,0,0,0,0},
	{0,0,255,0,255,0,255,255,255,0,0,255},
	{0,0,255,0,255,0,0,0,255,0,0,0},
	{0,0,255,0,255,255,0,0,255,0,0,0},
	{255,255,255,0,255,0,0,0,255,0,0,0},
	{0,0,255,0,255,255,255,255,255,0,0,255},	
	{0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,255,0,0,0,0,0,0,0}};

// Configuration 5
byte laby5[12][12]=	
	{{0,0,0,0,0,0,255,0,0,255,0,0},
	{0,0,0,0,0,0,255,0,0,255,0,0},		
	{0,0,255,0,0,0,255,0,0,0,0,0},		
	{0,0,255,0,0,0,255,0,0,0,0,0},			
	{0,0,255,0,0,0,255,0,0,0,0,0},
	{0,0,255,0,255,0,255,255,255,0,0,255},
	{0,0,255,0,255,0,0,0,255,0,0,0},
	{0,0,255,0,255,255,0,0,255,0,0,0},
	{255,255,255,0,255,0,0,0,255,0,0,0},
	{0,0,255,0,255,0,255,255,255,0,0,255},	
	{0,0,0,0,255,0,0,0,0,0,0,0},
	{0,0,0,0,255,0,0,0,0,0,0,0}};

// Matrice 12*12 sur laquelle le programme va calculer
byte laby[12][12];

// Coordonnées de départ du robot et de la sortie
byte robot_x = 7;
byte robot_y = 1;
byte sortie_x = 1;
byte sortie_y = 10;

// Coordonnées des balles sous formes de tableau
/********************************************************************
  Pour une balle n° N, ses coordonnées balleN_x[N-1] et balleN_y[N-1]
Exemple:
  La balle n°1 a pour coordonnées balleN_x[0] = 2 et balleN_y[0] = 5
*********************************************************************/
byte balleN_x[nbBalles] = {2,6,8,10,11,10,4,3};
byte balleN_y[nbBalles] = {5,3,7,1,5,11,7,7};

// Variables booleene
boolean sortieballe = 1; // Permet le déplacement vers tous les emplacements des balles

// Varibles pour la boucle for afin d'aller à chaque emplacement des balles
byte pos = 0;

// Variables pour le balayage de la carte
byte x = 0;
byte y = 0;

unsigned int cpt = 0; // Compteur pour le wavefront

int choix;

int val;

// Variables pour les codeurs
byte QEM [16] = {0,-1,1,2,1,0,2,-1,-1,2,0,1,2,1,-1,0}; 
int Out, New, Old;

// Variables pour la recherche de la plus petite valeur a retourné: 1, 2, 3 ou 4 suivant l'oritentation du robot (N,E,S,O)
byte case_min = 250;
byte case_min_localisation = 250;
byte nouvel_emplacement = 1; // Au départ, le robot est dirigé vers le Nord (= 1)
byte emplacement_precedent = 1;

// Déclaration des fonctions
byte wavefront(byte robot_x, byte robot_y);
void unpropagate(byte robot_x, byte robot_y);
byte valeur_min(byte x, byte y);
void mouvementRobot();
void rotation180();
void rotation90_SH();
void rotation90_SAH();
void avancer();
byte selec(int a);
void testDistanceMurs();
boolean testPresenceBalle();
boolean testCouleur();
void activerFicelle(boolean a);

void TCS()
 {
   digitalWrite(s1,HIGH);
   digitalWrite(s0,LOW);
   flag=0;
   attachInterrupt(0, ISR_INTO, CHANGE);
   timer2_init();
 }
void ISR_INTO()
 {
   counter++;
 }
 void timer2_init(void)
 {
   TCCR2A=0x00;
   TCCR2B=0x07; //the clock frequency source 1024 points
   TCNT2= 100;    //10 ms overflow again
   TIMSK2 = 0x01; //allow interrupt
 }
 int i=0;
 ISR(TIMER2_OVF_vect)//the timer 2, 10ms interrupt overflow again. Internal overflow interrupt executive function
{
 TCNT2=100;
 flag++;
 if(flag==1)
  {
    counter=0;
  }
 else if(flag==2)
   {
    digitalWrite(s2,LOW);
    digitalWrite(s3,LOW); 
    countR=counter/1.051;
    Serial.print("red=");
    Serial.println(countR,DEC);
    digitalWrite(s2,HIGH);
    digitalWrite(s3,HIGH);   
   }
 else if(flag==3)
    {
     countG=counter/1.0157;
    Serial.print("green=");
    Serial.println(countG,DEC);
     digitalWrite(s2,LOW);
     digitalWrite(s3,HIGH); 
   
    }
 else if(flag==4)
    {
     countB=counter/1.114;
    Serial.print("blue=");
    Serial.println(countB,DEC);
     digitalWrite(s2,LOW);
     digitalWrite(s3,LOW);
     }
 else
     {
     flag=0; 
      TIMSK2 = 0x00;
     }
     counter=0;
     delay(2);
}

void setup()
{
  pinMode(MOT_A, OUTPUT);
  pinMode(MOT_B, OUTPUT);
  
  pinMode(DIRECTION_A, OUTPUT);
  pinMode(DIRECTION_B, OUTPUT);
  
  pinMode(inputA, INPUT);
  pinMode(inputB, INPUT);
  
  pinMode(bp, INPUT);
  pinMode(ir, INPUT);
  
  // Capteur de couleur
  pinMode(s0,OUTPUT);
  pinMode(s1,OUTPUT); 
  pinMode(s2,OUTPUT);
  pinMode(s3,OUTPUT);
  
  Old =0;
  New = 0;
  Out = 0;
  
  choix = 0;
  
  laby[robot_x][robot_y] = robot;
}

void loop()
{
  // Sélection de la configuration
  switch(selec(choix))
	{
	case 1:
		{for(x=0;x<12;x++)
				for(y=0;y<12;y++)
					laby[x][y]=laby1[x][y];} // On copie la matrice laby1 dans la matrice laby
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
		break;
	}
  
  //////////////Algorithme de Waverfont adapté//////////////
  while(laby[robot_x][robot_y] != sortie)
  {	
    
    while(sortieballe) // Tant qu'il n'est pas allé à chaque emplacements de balle
    {
      
      for(pos = 0; pos < nbBalles; pos++)
      {
       
            if ((choix == 2 || choix == 3) && pos == 3)
            pos++; // On ignore la balle
          
            sortie_x = balleN_x[pos]; 
            sortie_y = balleN_y[pos];
            
            laby[sortie_x][sortie_y] = sortie;
            
            while(laby[robot_x][robot_y] != sortie)
            {
              mouvementRobot();
            }
            
            laby[robot_x][robot_y] = robot;
            
            
            
            if(pos == nbBalles-1) // Si le robot est allé à  tous les emplacements des balles, alors on va vers la sortie
            {
              sortieballe = 0;
            }
          }
        }
        
        sortie_x = 1;
        sortie_y = 10;
       
        laby[sortie_x][sortie_y] = sortie;
       
        mouvementRobot();
       
        laby[robot_x][robot_y] = robot;
      }
      
      return;
}

byte wavefront(byte robot_x, byte robot_y)
{
  // Initialiser l'ancien Wavefront
  unpropagate(robot_x, robot_y);
  
  laby[sortie_x][sortie_y] = sortie;
  
  cpt = 0;
  
  while(cpt < 1000) // Permet de trouver le robot en plusieurs cycles
  {
    
    x = 0;
    y = 0;
    
    while(x < 12 && y < 12) // Tant que la map n'est pas scannÃ©e complÃ©tement
    {
      
      // Si l'emplacement est un mur ou la sortie, on l'ignore
      if (laby[x][y] != murs && laby[x][y] != sortie)
      {
        // Un chemin complet est trouvÃ©e
        if (valeur_min(x, y) < reset_min && laby[x][y] == robot)
        return case_min_localisation; // TerminÃ©, dire au robot de commencer son dÃ©placement
        
        else if (case_min != reset_min) // Sans ce test, les cases 'rien' serai Ã  cet emplacement
        
        laby[x][y] = case_min+1;
      }
      
      // Aller Ã  la prochaine case et/ou Ã  la prochaine rangÃ©e
      y++;
      if (y == 12 && x != 12) // Si on arrive au bout de la ligne, on passe Ã  la rangÃ©e suivante
      {
        x++;
        y = 0;
      }
    }
    cpt++;
  }
  return 0;
}

// Effacer l'ancien chemin afin d'en dÃ©terminer un autre et Ã©viter de surcharger la carte
void unpropagate(byte robot_x, byte robot_y)
{
  // Balayage de la carte entiÃ¨re
  for (x = 0; x < 12; x++)
  {
    for (y = 0; y < 12; y++)
    {
      if (laby[x][y] != murs && laby[x][y] != sortie) // Si l'emplacement est un mur ou la sortie, on l'ignore
        laby[x][y] = rien; // On efface la case, on la rÃ©initialise
    }
  }
  // Comme l'ancienne position du robot a Ã©tÃ© effacÃ©e, on lui affecte sa nouvelle position
  laby[robot_x][robot_y] = robot;
}

/*Cette fonction regarde les cases adjacentes d'un emplacement, et retourne la plus petite valeur
1 reprÃ©sente le Nord, 2 l'Est, 3 le Sud et 4 l'Ouest (sens horaire)*/
byte valeur_min(byte x, byte y)
{
  case_min = reset_min;
  // Sud
  if(x < 11)
  {
    if  (laby[x+1][y] < case_min && laby[x+1][y] != rien) // Trouver la plus petite valeur en excluant les cases '0', c'est Ã  dire "rien"
    {
      case_min = laby[x+1][y];
      case_min_localisation = 3;
    }
  }
  
  // Nord
  if(x > 0)
  {
    if  (laby[x-1][y] < case_min && laby[x-1][y] != rien)
    {
      case_min = laby[x-1][y];
      case_min_localisation = 1;
    }
  }
      
     // Est
     if(y < 11)
     {
        if  (laby[x][y+1] < case_min && laby[x][y+1] != rien)
        {
          case_min = laby[x][y+1];
          case_min_localisation = 2;
        }
     }
     
     // Ouest
     if(y > 0)
     {
       if  (laby[x][y-1] < case_min && laby[x][y-1] != rien)
       {
         case_min = laby[x][y-1];
         case_min_localisation = 4;
       }
     }
       return case_min;
	}

void mouvementRobot()
{
  
  nouvel_emplacement = wavefront(robot_x, robot_y);

	// Mettre Ã  jour le nouvel emplacement du robot
	if (nouvel_emplacement==1)
		robot_x--;
	if (nouvel_emplacement==2)
		robot_y++;
	if (nouvel_emplacement==3)
		robot_x++;
	if (nouvel_emplacement==4)
		robot_y--;

       
       testDistanceMurs();
	  			
      if (abs(emplacement_precedent - nouvel_emplacement) == 2) 
        rotation180();
      if ((emplacement_precedent - nouvel_emplacement) == 1 || (signed int)(emplacement_precedent - nouvel_emplacement) == -3) 
        rotation90_SAH(); // rotation de 90° en sens anit horaire (trigo)
      if ((signed int)(emplacement_precedent - nouvel_emplacement) == -1 || (emplacement_precedent - nouvel_emplacement) == 3)
        rotation90_SH(); // rotation de 90° en sens horaire
      
      // Si le robot se trouve sur une case adjacente à un emplacement de balle
      if(((robot_x == balleN_x[pos] || robot_x == balleN_x[pos]) && robot_y==balleN_y[pos]) || ((robot_y == balleN_y[pos] || robot_y == balleN_y[pos])&& robot_x==balleN_x[pos]))
      {
            /* Présence de la balle ? */
            if(testPresenceBalle())
            {
              if(testCouleur())
              {
                
                Out=0;
              New=0;
                Old=0;
                digitalWrite(DIRECTION_A, 1);
                digitalWrite(DIRECTION_B, 1);
   
              while(Out < 150)
              {
                Old = New;
                New = digitalRead (inputA) * 2 + digitalRead (inputB); 
                Out += QEM [Old * 4 + New];
              
              analogWrite (MOT_A, 200);
              analogWrite(MOT_B, 200);
              }
  
              analogWrite(MOT_A, 0);
              analogWrite(MOT_B, 0);
              delay(1000);
              
              
              New=0;
              Old=0;
              digitalWrite(DIRECTION_A, 0);
              digitalWrite(DIRECTION_B, 0);
               
              while(Out < 150)
              {
                Old = New;
                New = digitalRead (inputB) * 2 + digitalRead (inputA); 
                Out += QEM [Old * 4 + New];
              
              analogWrite (MOT_A, 200);
              analogWrite(MOT_B, 200);
              }
              
              analogWrite(MOT_A, 0);
              analogWrite(MOT_B, 0);
              delay(1000);
                
                sortie_x = 0;
                sortie_y = 10;
                
                laby[sortie_x][sortie_y] = sortie;
                
                while(laby[robot_x][robot_y] != sortie)
                {
                  mouvementRobot(); 
                }
                
                return; // On quitte le programme
                
              }
            }
      }
      		
     //Aller au nouvel emplacement
     avancer();
     
     emplacement_precedent = nouvel_emplacement; // Enregistrer l'emplacement précédent du robot 
}

void rotation180()
{
  Out=0;
  New=0;
  Old=0;
  digitalWrite(DIRECTION_A, 1);
  digitalWrite(DIRECTION_B,0);
   
  while(Out < 940)
  {
   Old = New;
   New = digitalRead (inputA) * 2 + digitalRead (inputB); // Convert binary input to decimal value
   Out += QEM [Old * 4 + New];
  
   analogWrite (MOT_A, 125);
   analogWrite(MOT_B, 125);
  }
  
  analogWrite(MOT_A, 0);
  analogWrite(MOT_B, 0);
  delay(1000);
}

void rotation90_SH()
{
 Out=0;
  New=0;
  Old=0;
   digitalWrite(DIRECTION_A, 1);
   digitalWrite(DIRECTION_B,0);
   
  while(Out < 479)
  {
    Old = New;
    New = digitalRead (inputA) * 2 + digitalRead (inputB); 
    Out += QEM [Old * 4 + New];
  
  analogWrite (MOT_A, 125);
  analogWrite(MOT_B, 125);
  }
  
  analogWrite(MOT_A, 0);
  analogWrite(MOT_B, 0);
  delay(1000);
}

void rotation90_SAH()
{
  Out=0;
  New=0;
  Old=0;
   digitalWrite(DIRECTION_A, 0);
   digitalWrite(DIRECTION_B, 1);
   
  while(Out < 479)
  {
    Old = New;
    New = digitalRead (inputB) * 2 + digitalRead (inputA); // Convert binary input to decimal value
    Out += QEM [Old * 4 + New];
  
  analogWrite (MOT_A, 100);
  analogWrite(MOT_B, 100);
  }
  
  analogWrite(MOT_A, 0);
  analogWrite(MOT_B, 0);
  delay(1000);
}

void avancer()
{
  Out=0;
  New=0;
  Old=0;
  digitalWrite(DIRECTION_A, 1);
  digitalWrite(DIRECTION_B, 1);
   
  while(Out < 330)
  {
    Old = New;
    New = digitalRead (inputA) * 2 + digitalRead (inputB); 
    Out += QEM [Old * 4 + New];
  
  analogWrite (MOT_A, 200);
  analogWrite(MOT_B, 200);
  }
  
  analogWrite(MOT_A, 0);
  analogWrite(MOT_B, 0);
  delay(1000);
  
}

byte selec(int a)
{
  boolean b =true;
  while(b)
  {
    if(a == 6)
    {
      a = 0;
    }
    
    if(digitalRead(bp)== HIGH)
    {
      delay(100);
      if(digitalRead(bp)== HIGH)
      {
        a++;
        delay(500);
        
        if(digitalRead(bp)== HIGH)
        {
          delay(1000);
          
          if(digitalRead(bp) == HIGH)
          {
            b = false;
            return a; //return a-1
          }
         }
       }
    }
  }
}

void testDistanceMurs()
{
  val = 0;
  val = analogRead(ir);

       // On teste si l'on est trop proche d'un mur
       if((2885.2*pow(val, -100/97)-2) < 6)
       {
         Out=0;
         New=0;
         Old=0;
         digitalWrite(DIRECTION_A, 0);
         digitalWrite(DIRECTION_B, 0);
   
         while(Out < 100)
         {
          Old = New;
          New = digitalRead (inputB) * 2 + digitalRead (inputA);
          Out += QEM [Old * 4 + New];
  
          analogWrite (MOT_A, 200);
          analogWrite(MOT_B, 200);
          }
  
          analogWrite(MOT_A, 0);
          analogWrite(MOT_B, 0);
          delay(1000);
        }
}

boolean testPresenceBalle()
{
  val = 0;
  val = analogRead(ir);
  
  if((2885.2*pow(val, -100/97)-2) < 4)
  {
    return true;
  }
  else
    return false;
}

boolean testCouleur()
{
  delay(10);
  TCS();
  if((countR>10)||(countG>10)||(countB>10))
   {
      if((countR>countG)&&(countR>countB))
       {
         return true;
       }
       else
         return false;
    }
  else 
  {
     delay(1000);       
  }
}
