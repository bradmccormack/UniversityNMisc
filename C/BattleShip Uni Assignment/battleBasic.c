/****************************************************************************
* COSC2138/CPT220 - Programming Principles 2A
* Study Period 2  2010 Assignment #1 - battleship program
* Full Name        : Bradley Jason Mccormack
* Student Number   : S3258798
* Yallara Username : ?
* Course Code      : COSC2138
* Program Code     : ?
* Start up code provided by the CTeach Team

This file is the implementation of the basic algorithm where the AI just randomly picks spots
****************************************************************************/

#include "bship.h"

/****************************************************************************
* Function main() is the entry point for the program.
****************************************************************************/
int main(void)
{
   /* Stores player ship position information secret to opponent. */
   char playerHidden[SIZE][SIZE];
   /* Stores player ship position information known to opponent. */
   char playerReveal[SIZE][SIZE];
   /* Stores computer ship position information secret to opponent. */
   char computHidden[SIZE][SIZE];
   /* Stores computer ship position information known to opponent. */
   char computReveal[SIZE][SIZE];

   /*set the seed for random numbers later*/
   srand((unsigned int)time(NULL));

   /*Initialise game player and board*/
   init(playerHidden,playerReveal,computHidden,computReveal);
   placePlayerShips(playerHidden);
   placeComputerShips(computHidden);

   /*Keep playing until somebody has won*/
   do
   {
      displayKnownInfo(playerReveal,playerHidden,computReveal);
      playerGuess(computHidden,computReveal);
      computerGuess(playerHidden,playerReveal);

   }
   while(!isGameOver(playerHidden,playerReveal,computHidden,computReveal));
   displayAllInfo(playerHidden,playerReveal,computHidden,computReveal);

   return EXIT_SUCCESS;
}


/****************************************************************************
* Function init() initialises every cell in the four grids to a safe default
* value. The UNKNOWN constant is used for the initialisation value.
****************************************************************************/
void init(char playerHidden[SIZE][SIZE], char playerReveal[SIZE][SIZE],
          char computHidden[SIZE][SIZE], char computReveal[SIZE][SIZE])
{

   /*i like memset better than my original code .. neater and faster :-)*/
   memset(&playerHidden[0][0],UNKNOWN,CELLS);
   memset(&playerReveal[0][0],UNKNOWN,CELLS);
   memset(&computHidden[0][0],UNKNOWN,CELLS);
   memset(&computReveal[0][0],UNKNOWN,CELLS);

   /*
      cleargrid(&playerHidden[0][0],SIZE,SIZE);
      cleargrid(&playerReveal[0][0],SIZE,SIZE);
      cleargrid(&computHidden[0][0],SIZE,SIZE);
      cleargrid(&computReveal[0][0],SIZE,SIZE);
      */
}

/*
void cleargrid(char* gridstart,int sizex,int sizey)
{
   char* endaddress=gridstart+(sizex*sizey);
   while(gridstart<endaddress)
      *gridstart++=UNKNOWN;
}
*/



/****************************************************************************
* Function placePlayerShips() adds the player ships to the grid in the
* following fixed pattern:
*    1 2 3 4 5 6 7 8 9 0
*   +-+-+-+-+-+-+-+-+-+-+
* a |A| | | | | | | | | |
*   +-+-+-+-+-+-+-+-+-+-+
* b |A| | | | | |D|D|D| |
*   +-+-+-+-+-+-+-+-+-+-+
* c |A| | | | | | |S| | |
*   +-+-+-+-+-+-+-+-+-+-+
* d |A| | | | | | |S| | |
*   +-+-+-+-+-+-+-+-+-+-+
* e |A| | | | | | | | | |
*   +-+-+-+-+-+-+-+-+-+-+
* f | | | | | | | | | | |
*   +-+-+-+-+-+-+-+-+-+-+
* g | | | | | | | | | | |
*   +-+-+-+-+-+-+-+-+-+-+
* h | | | | | | | | | | |
*   +-+-+-+-+-+-+-+-+-+-+
* i | |F|F|F| | | | | | |[0][0]
*   +-+-+-+-+-+-+-+-+-+-+
* j | | | | | | |B|B|B|B|
*   +-+-+-+-+-+-+-+-+-+-+
****************************************************************************/
void placePlayerShips(char playerHidden[SIZE][SIZE])
{
   register int index=0;
   char* celladdr;

   /*position Aircraft carrirer */
   for(; index<AIRCRAFT_CARRIER_LEN; index++)
      playerHidden[index][0]=AIRCRAFT_CARRIER;

   /*position the Destroyer*/
   playerHidden[1][6]=DESTROYER;
   playerHidden[1][7]=DESTROYER;
   playerHidden[1][8]=DESTROYER;

   /*position the Submarine*/
   playerHidden[2][7]=SUBMARINE;
   playerHidden[3][7]=SUBMARINE;

   /*position the Fridate*/
   playerHidden[8][1]=FRIGATE;
   playerHidden[8][2]=FRIGATE;
   playerHidden[8][3]=FRIGATE;


   /*position the Battleship*/
   celladdr=&playerHidden[SIZE-1][6];
   for(index=0; index<BATTLESHIP_LEN; index++)
      *(celladdr+(SIZE-1*SIZE)+index)=BATTLESHIP;
}


/****************************************************************************
* Function placeComputerShips() adds the computer ships to the grid in a
* similar pattern as the placePlayerShips() function except that the grid has
* been mirrored horizontally:
*    1 2 3 4 5 6 7 8 9 0
*   +-+-+-+-+-+-+-+-+-+-+
* a | | | | | | | | | |A|
*   +-+-+-+-+-+-+-+-+-+-+
* b | |D|D|D| | | | | |A|
*   +-+-+-+-+-+-+-+-+-+-+
* c | | |S| | | | | | |A|
*   +-+-+-+-+-+-+-+-+-+-+
* d | | |S| | | | | | |A|
*   +-+-+-+-+-+-+-+-+-+-+
* e | | | | | | | | | |A|
*   +-+-+-+-+-+-+-+-+-+-+
* f | | | | | | | | | | |
*   +-+-+-+-+-+-+-+-+-+-+
* g | | | | | | | | | | |
*   +-+-+-+-+-+-+-+-+-+-+
* h | | | | | | | | | | |
*   +-+-+-+-+-+-+-+-+-+-+
* i | | | | | | |F|F|F| |
*   +-+-+-+-+-+-+-+-+-+-+
* j |B|B|B|B| | | | | | |
*   +-+-+-+-+-+-+-+-+-+-+
****************************************************************************/
void placeComputerShips(char computHidden[SIZE][SIZE])
{
   register int index=0;

   /*position Aircraft carrirer */
   char* celladdr=&computHidden[0][0];
   for(index=0; index<AIRCRAFT_CARRIER_LEN; index++)
      *(celladdr+(index*SIZE)+SIZE-1)=AIRCRAFT_CARRIER;

   /*position the Destroyer*/
   computHidden[1][1]=DESTROYER;
   computHidden[1][2]=DESTROYER;
   computHidden[1][3]=DESTROYER;

   /*position the Submarine*/
   computHidden[2][2]=SUBMARINE;
   computHidden[3][2]=SUBMARINE;

   /*position the Fridate*/
   computHidden[8][6]=FRIGATE;
   computHidden[8][7]=FRIGATE;
   computHidden[8][8]=FRIGATE;

   /*position the Battleship*/
   celladdr=&computHidden[0][0];
   for(index=0; index<BATTLESHIP_LEN; index++)
      *(celladdr+(SIZE*(SIZE-1))+index)=BATTLESHIP;
}

/****************************************************************************
* Function renderGridds() will display the ascii information for the grids
that are passed to the function where they are gridsize by gridsize dimension
*/
void renderGrids(char* gridleft,char* gridright,int gridsize)
{
   int gridcount=0;
   register int i,j,row;
   char ascii;

   /*If both grids are empty then return*/
   if(gridleft==0 && gridright==0)
      return;
   /*determine the grid count*/
   if(gridleft!=0 || gridright!=0)
      gridcount=1;

   if(gridleft!=0 && gridright!=0)
      gridcount=2;

   /*Headings for both grids*/
   if(gridleft!=0)
      printf("\n          Player           ");
   if(gridleft!=0&& gridright!=0)
      printf("|         ");
   if(gridright!=0)
      printf("Computer");
   printf("\n    ");

   /*Numbers at the top*/
   for(i=0; i<gridcount; i++)
   {
      for(ascii=49; ascii<58; ascii++)
         printf("%c ",ascii);
      printf("0 ");
      if(i!=gridcount-1)
         printf("   %c    ",PLAYERDELIM);
   }
   printf("\n");

   row=0;
   ascii=LOWERCASEA;

   /*display the cell information for each row*/
   while(row<=gridsize)
   {
      /*alternating +- pattern each grid for this row*/
      for(i=0; i<gridcount; i++)
      {
         printf("   ");
         for(j=0; j<gridsize; j++)
            printf("+-");
         putchar('+');

         /*if its not the last grid to render then show the grid delimiter*/
         if(i!=gridcount-1)
            printf("   %c",PLAYERDELIM);
      }
      putchar('\n');

      /*cell values each grid for this row*/
      for(i=0; i<gridcount; i++)
      {
         if(row<gridsize)
         {
            printf(" %c ",ascii);
            /*each cell value*/
            for(j=0; j<gridsize; j++)
            {
               if(i==0)
                  printf("%c%c",PLAYERDELIM,*(gridleft+(row*gridsize)+j));
               else
                  printf("%c%c",PLAYERDELIM,*(gridright+(row*gridsize)+j));
            }
            putchar(PLAYERDELIM);

            /*grid delimiter if required*/
            if(i!=gridcount-1)
               printf("   %c",PLAYERDELIM);
         }
      }
      /*next row*/
      ascii++;
      printf("\n");
      row++;
   }
}



/****************************************************************************
* Function displayKnownInfo() presents revealed information about the game in
* the format below. In this example, both contestants have made five
* guesses.
* As you can see, the computer player got lucky with all five guesses and has
* sunk the human players' aircraft carrier. The identity of the ship was
* revealed when the aircraft carrier was HIT the fifth time.
* The human player has been less lucky. The first four guesses were a MISS.
* However, the fifth guess was a HIT on the computer players' submarine. The
* human player does not yet know the identity of this ship yet as it is still
* afloat.
* All other squares are still UNKNOWN.
*
*          Player         |         Computer
*    1 2 3 4 5 6 7 8 9 0  |    1 2 3 4 5 6 7 8 9 0
*   +-+-+-+-+-+-+-+-+-+-+ |   +-+-+-+-+-+-+-+-+-+-+
* a |A| | | | | | | | | | | a | | | | | | | | | | |
*   +-+-+-+-+-+-+-+-+-+-+ |   +-+-+-+-+-+-+-+-+-+-+
* b |A| | | | | | | | | | | b | | | | | | | | | | |
*   +-+-+-+-+-+-+-+-+-+-+ |   +-+-+-+-+-+-+-+-+-+-+
* c |A| | | | | | | | | | | c | | | | | | |=| | | |
*   +-+-+-+-+-+-+-+-+-+-+ |   +-+-+-+-+-+-+-+-+-+-+
* d |A| | | | | | | | | | | d | | |x| | | | | | | |
*   +-+-+-+-+-+-+-+-+-+-+ |   +-+-+-+-+-+-+-+-+-+-+
* e |A| | | | | | | | | | | e | | | | | | | | | | |
*   +-+-+-+-+-+-+-+-+-+-+ |   +-+-+-+-+-+-+-+-+-+-+
* f | | | | | | | | | | | | f | | | | |=| | | | | |
*   +-+-+-+-+-+-+-+-+-+-+ |   +-+-+-+-+-+-+-+-+-+-+
* g | | | | | | | | | | | | g | | | | | | | | | | |
*   +-+-+-+-+-+-+-+-+-+-+ |   +-+-+-+-+-+-+-+-+-+-+
* h | | | | | | | | | | | | h | |=| | | | |=| | | |
*   +-+-+-+-+-+-+-+-+-+-+ |   +-+-+-+-+-+-+-+-+-+-+
* i | | | | | | | | | | | | i | | | | | | | | | | |
*   +-+-+-+-+-+-+-+-+-+-+ |   +-+-+-+-+-+-+-+-+-+-+
* j | | | | | | | | | | | | j | | | | | | | | | | |
*   +-+-+-+-+-+-+-+-+-+-+ |   +-+-+-+-+-+-+-+-+-+-+
* Aircraft Carrier  (5/5) | 0/5 ships sunk.
* Battleship        (0/4) | 1 hits.
* Destroyer         (0/3) | 4 misses.
* Frigate           (0/3) |
* Submarine         (0/2) |
****************************************************************************/
void displayKnownInfo(char playerReveal[SIZE][SIZE],
                      char playerHidden[SIZE][SIZE],
                      char computReveal[SIZE][SIZE])
{
   /*playerHitInfo stores the damage the computer has inflicted
   on the player*/
   struct shipRecord playerHitInfo;
   /*computerHitInfo stores the damage the player has inflicted
   on the computer*/
   static struct shipRecord computerHitInfo;


   char* playerloc,*playerhiddenloc,*computerloc;
   char cellvalue;
   int hit,miss;
   static int shipssunk;
   register int i;

   /*initialize variables*/
   playerloc=&playerReveal[0][0];
   playerhiddenloc=&playerHidden[0][0];
   computerloc=&computReveal[0][0];
   miss=0;
   hit=0;
   memset(&playerHitInfo,0,sizeof(playerHitInfo));

   /*display the current grids for computer and player*/
   renderGrids(&playerReveal[0][0],&computReveal[0][0],SIZE);

   /*gather current status of players ships which is looked up in playerHidden
     information for the left grid*/
   for(i=0; i<CELLS; i++)
   {
      /*gather current status of hit /miss and ship amount sinking on computer
      .. information for the right grid*/

      switch(*(computerloc+i))
      {
         case HIT:
            hit++;
            break;
         case MISS:
            miss++;
            break;

         case AIRCRAFT_CARRIER:
            hit++;
            computerHitInfo.ahits++;
            if(computerHitInfo.ahits==AIRCRAFT_CARRIER_LEN)
               shipssunk++;
            break;
         case BATTLESHIP:
            hit++;
            computerHitInfo.bhits++;
            if(computerHitInfo.bhits==BATTLESHIP_LEN)
               shipssunk++;
            break;

         case DESTROYER:
            hit++;
            computerHitInfo.dhits++;
            if(computerHitInfo.dhits==DESTROYER_LEN)
               shipssunk++;
            break;
         case FRIGATE:
            hit++;
            computerHitInfo.fhits++;
            if(computerHitInfo.fhits==FRIGATE_LEN)
               shipssunk++;
            break;

         case SUBMARINE:
            hit++;
            computerHitInfo.shits++;
            if(computerHitInfo.shits==SUBMARINE_LEN)
               shipssunk++;
            break;

      }

      /*if the visible value is a miss or nothing then skip it*/
      if(*(playerloc+i)==MISS || *(playerloc+i)==UNKNOWN)
         continue;
      /*a hit is in the cell so get the ship type*/
      else
         cellvalue=*(playerhiddenloc+i);

      switch(cellvalue)
      {
         case AIRCRAFT_CARRIER:
            playerHitInfo.ahits++;
            break;
         case BATTLESHIP:
            playerHitInfo.bhits++;
            break;
         case DESTROYER:
            playerHitInfo.dhits++;
            break;
         case FRIGATE:
            playerHitInfo.fhits++;
            break;
         case SUBMARINE:
            playerHitInfo.shits++;
            break;
      }
   }

   printf(" Aircraft Carrier (%d/%d)    | %d/%d ships sunk.\n",
          playerHitInfo.ahits,AIRCRAFT_CARRIER_LEN,shipssunk,NUMSHIPS);
   printf(" Battleship       (%d/%d)    | %d hits.\n",
          playerHitInfo.bhits,BATTLESHIP_LEN,hit);
   printf(" Destroyer        (%d/%d)    | %d misses\n",
          playerHitInfo.dhits,DESTROYER_LEN,miss);
   printf(" Frigate          (%d/%d)\n",playerHitInfo.fhits,FRIGATE_LEN);
   printf(" Submarine        (%d/%d)\n\n",playerHitInfo.shits,SUBMARINE_LEN);

}
/***************************************
* Function: getValidCell() enforces cell reference rules when
* inputting a cell. valid reference is saved in passed in param*/
void getValidCell(char* guess)
{
   int valid;

   valid=FALSE;
   while(!valid)
   {
      getString(guess,2,2,"Enter a grid reference (a1-j0) :");

      /*enforce valid Row reference*/
      if(guess[0]<LOWERCASEA || guess[0]>LOWERCASEJ)
      {
         printf("First digit must be a valid row reference (a-j)\n");
         continue;
      }
      /*enforce valid column reference*/
      if(guess[1]<ASCII0 || guess[1]>ASCII9)
      {
         printf("Second digit must be a valid column reference (1-0)\n");
         continue;
      }
      valid=TRUE;
   }
}


/****************************************************************************
* Function playerGuess() allows the user to guess the position of an
* opponents' ship by providing the cell reference. This guess information is
* recorded in the computReveal[][] variable. The user is given feedback about
* the accuracy of the guess. Additional feedback is given if the guess sinks
* the enemy ship. Example:
*
* Enter a grid reference (a1-j0): c3
* You hit an enemy ship.
* You sunk the enemy submarine.
****************************************************************************/
void playerGuess(char computHidden[SIZE][SIZE],
                 char computReveal[SIZE][SIZE])
{
   int valid,row,col;
   char guess[3];

   /*this maintains list of hits on computer*/
   static struct shipRecord hitInfo;

   /*input a grid cell reference with validation*/
   valid=FALSE;
   while(!valid)
   {
      /*get a valid cell reference*/
      getValidCell(&guess[0]);

      row=tolower(guess[0]);
      /*convert the cell reference into numerical grid reference*/
      row=row-LOWERCASEA;
      if(guess[1]==ASCII0)
         col=SIZE-1;
      else
         col=guess[1]-ASCII0-1;

      /*check if the player has already fired at this spot*/
      if(computReveal[row][col]!=UNKNOWN)
      {
         printf("you have already fired at that cell.\n");
         continue;
      }
      valid=TRUE;
   }

   /*the player hit something*/
   if(computHidden[row][col]!=UNKNOWN)
   {

      computReveal[row][col]=HIT;
      printf("You hit an enemy ship.\n");

      /*keep tally of the amount of hits of the ship type
      if its sunken then reflect this on grid and result text*/
      switch(computHidden[row][col])
      {
         case AIRCRAFT_CARRIER:
            hitInfo.ahits++;
            if(hitInfo.ahits==AIRCRAFT_CARRIER_LEN)
            {
               printf("You sunk the enemy Aircraft carrier!\n");
               showKnown(computHidden,computReveal,AIRCRAFT_CARRIER);
            }
            break;
         case BATTLESHIP:
            hitInfo.bhits++;
            if(hitInfo.bhits==BATTLESHIP_LEN)
            {
               printf("You sunk the enemy Battleship!\n");
               showKnown(computHidden,computReveal,BATTLESHIP);
            }
            break;

         case DESTROYER:
            hitInfo.dhits++;
            if(hitInfo.dhits==DESTROYER_LEN)
            {
               printf("You sunk the enemy Destroyer!\n");
               showKnown(computHidden,computReveal,DESTROYER);
            }

            break;
         case FRIGATE:
            hitInfo.fhits++;
            if(hitInfo.fhits==FRIGATE_LEN)
            {
               printf("You sunk the enemy Frigate!\n");
               showKnown(computHidden,computReveal,FRIGATE);
            }
            break;

         case SUBMARINE:
            hitInfo.shits++;
            if(hitInfo.shits==SUBMARINE_LEN)
            {
               printf("You sunk the enemy Submarine!\n");
               showKnown(computHidden,computReveal,SUBMARINE);
            }
            break;
      }

   }
   /*the player missed so track this*/
   else
   {
      computReveal[row][col]=MISS;
      printf("you missed !\n");

   }
   printf("\n");
}



/*****************************************************************************
* Function showKnown() will replace generic hits with
actual ship type when a ship is sunk*/
void showKnown(char hidden[SIZE][SIZE],char shown[SIZE][SIZE],char shipType)
{
   register int i;
   char* hiddenptr=&hidden[0][0];
   char* shownptr=&shown[0][0];

   /*Find any location in the hidden grid that contains ship of ShipType
     for those that do set the corresponding location in the revealed grid
     to that ship type*/
   for(i=0; i<CELLS; i++)
   {
      if(*(hiddenptr+i)==shipType)
         *(shownptr+i)=shipType;
   }
}



/****************************************************************************
* Function computerGuess() has a lot in common with the playerGuess()
* function. This function allows the computer-controlled opponent to randomly
* guess the positions of the players' ships. The guess information is stored
* in the playerReveal[][] variable. Any square that hasn't been previously
* guessed is selected. The user is given feedback about the accuracy of the
* guess. Additional feedback is given if the guess sinks one of your ships.
* Example:
*
* Opponent guessed square 'f9'.
* Opponent missed your ships.
*
* This function uses the s_rand() and rand() standard library functions to
* implement random number generation.
****************************************************************************/
void computerGuess(char playerHidden[SIZE][SIZE],
                   char playerReveal[SIZE][SIZE])
{
   int row,col,valid;
   static struct shipRecord playerHitInfo;

   valid=FALSE;

   while(!valid)
   {
      row=rand() % 9;
      col=rand() % 9;
      /*make sure computer is firing on a empty cell -they have not
      fired before on it*/
      if(playerReveal[row][col-1]==UNKNOWN)
         valid=TRUE;
   }

   printf("Opponent guessed square %c%d\n",LOWERCASEA+row,col);

   /*record a hit*/
   if(playerHidden[row][col-1]!=UNKNOWN)
   {
      printf("Opponent has hit your ships.\n");
      playerReveal[row][col-1]=HIT;
   }

   /*record actual ship hit info*/
   switch(playerHidden[row][col-1])
   {
      case AIRCRAFT_CARRIER:
         playerHitInfo.ahits++;
         if(playerHitInfo.ahits==AIRCRAFT_CARRIER_LEN)
         {
            printf("Opponent has sunk your Aircraft Carrier!\n");
            showKnown(playerHidden,playerReveal,AIRCRAFT_CARRIER);
         }
         break;
      case BATTLESHIP:
         playerHitInfo.bhits++;
         if(playerHitInfo.bhits==BATTLESHIP_LEN)
         {
            printf("Opponent has sunk your Battleship!\n");
            showKnown(playerHidden,playerReveal,BATTLESHIP);
         }
         break;
      case DESTROYER:
         playerHitInfo.dhits++;
         if(playerHitInfo.dhits==DESTROYER_LEN)
         {
            printf("Opponent has sunk your Destroyer !\n");
            showKnown(playerHidden,playerReveal,DESTROYER);
         }
         break;
      case FRIGATE:
         playerHitInfo.fhits++;
         if(playerHitInfo.fhits==FRIGATE_LEN)
         {
            printf("Opponent has sunk your Frigate !\n");
            showKnown(playerHidden,playerReveal,FRIGATE);
         }
         break;
      case SUBMARINE:
         playerHitInfo.shits++;
         if(playerHitInfo.shits==SUBMARINE_LEN)
         {
            printf("Opponent has sunk your Submarine !\n");
            showKnown(playerHidden,playerReveal,SUBMARINE);
         }
         break;
      default:
         printf("Opponent missed your ships\n");
         playerReveal[row][col-1]=MISS;
         break;
   }
}



/****************************************************************************
* Fuction getSunkShips() checks how many ships are sunk in the passed in grid*/
int getSunkShips(char grid[SIZE][SIZE])
{
   register int i;
   int sunkShips;
   struct shipRecord hitinfo;
   char* gridptr;

   sunkShips=0;
   memset(&hitinfo,0,sizeof(hitinfo));
   gridptr=&grid[0][0];

   for(i=0; i<CELLS; i++)
   {
      switch(*(gridptr+i))
      {
         case AIRCRAFT_CARRIER:
            hitinfo.ahits++;
            if(hitinfo.ahits==AIRCRAFT_CARRIER_LEN)
               sunkShips++;
            break;
         case BATTLESHIP:
            hitinfo.bhits++;
            if(hitinfo.bhits==BATTLESHIP_LEN)
               sunkShips++;
            break;
         case DESTROYER:
            hitinfo.dhits++;
            if(hitinfo.dhits==DESTROYER_LEN)
               sunkShips++;
            break;
         case FRIGATE:
            hitinfo.fhits++;
            if(hitinfo.fhits==FRIGATE_LEN)
               sunkShips++;
            break;
         case SUBMARINE:
            hitinfo.shits++;
            if(hitinfo.shits==SUBMARINE_LEN)
               sunkShips++;
            break;

      }
   }
   return sunkShips;

}



/****************************************************************************
* Function isGameOver() checks to see if a threshold number of ships has been
* sunk by either the user or computer-controlled opponent (use SHIPS_TO_SINK
* constant). The function returns TRUE or FALSE.
****************************************************************************/
int isGameOver(char playerHidden[SIZE][SIZE], char playerReveal[SIZE][SIZE],
               char computHidden[SIZE][SIZE], char computReveal[SIZE][SIZE])
{
   int sunkPlayerShips,sunkComputerShips;

   /*get the amount of sunken ships for each side and determine if a winner*/
   sunkPlayerShips=getSunkShips(playerReveal);
   sunkComputerShips=getSunkShips(computReveal);

   if(sunkPlayerShips==SHIPS_TO_SINK || sunkComputerShips==SHIPS_TO_SINK)
      return TRUE;
   else
      return FALSE;
}


void revealHidden(char hiddengrid[SIZE][SIZE],char displayedgrid[SIZE][SIZE])
{
   register int i;
   char* hiddenptr=&hiddengrid[0][0];
   char* shownptr=&displayedgrid[0][0];

   for(i=0; i<CELLS; i++)
   {
      /*if a hit or unknown is shown then reveal the actual possible ship
      in lowercase*/
      if(*(shownptr+i)==HIT ||*(shownptr+i)==UNKNOWN)
         *(shownptr+i)=tolower(*(hiddenptr+i));

   }
}


/****************************************************************************
* Function displayAllInfo() is called at the end of the game and provides
* information about the outcome. The output is very similar to that of the
* displayKnownInfo() function. This function additionally reveals all
* ship locations with unrevealed ship positions represented in lower case
* letters. Finally, a congratulatory or commiserative message is displayed to
* the user depending on the outcome of the game. Example:
*
*          Player         |         Computer
*    1 2 3 4 5 6 7 8 9 0  |    1 2 3 4 5 6 7 8 9 0
*   +-+-+-+-+-+-+-+-+-+-+ |   +-+-+-+-+-+-+-+-+-+-+
* a |A| | | | | | | | | | | a | | | | | | | | | |a|
*   +-+-+-+-+-+-+-+-+-+-+ |   +-+-+-+-+-+-+-+-+-+-+
* b |A| | | |=| |d|d|d| | | b | |d|d|d| | | | | |a|
*   +-+-+-+-+-+-+-+-+-+-+ |   +-+-+-+-+-+-+-+-+-+-+
* c |A| | | | | | |s| | | | c | | |S| | | |=| | |a|
*   +-+-+-+-+-+-+-+-+-+-+ |   +-+-+-+-+-+-+-+-+-+-+
* d |A| | | | | | |s| | | | d | | |S| | | | | | |a|
*   +-+-+-+-+-+-+-+-+-+-+ |   +-+-+-+-+-+-+-+-+-+-+
* e |A| | | | | | | | | | | e | | | | | | | | | |a|
*   +-+-+-+-+-+-+-+-+-+-+ |   +-+-+-+-+-+-+-+-+-+-+
* f | | | | | | | | |=| | | f | | | | |=| | | | | |
*   +-+-+-+-+-+-+-+-+-+-+ |   +-+-+-+-+-+-+-+-+-+-+
* g | | | | | | | | | | | | g | | | | | | | | | | |
*   +-+-+-+-+-+-+-+-+-+-+ |   +-+-+-+-+-+-+-+-+-+-+
* h | |=| | | | | | |=| | | h | |=| | | | |=| | | |
*   +-+-+-+-+-+-+-+-+-+-+ |   +-+-+-+-+-+-+-+-+-+-+
* i |=|F|F|f| | | | | | | | i | | | | | | |F|F|F| |
*   +-+-+-+-+-+-+-+-+-+-+ |   +-+-+-+-+-+-+-+-+-+-+
* j | |=| | | | |b|b|b|b| | j |B|B|B|B| | | | | | |
*   +-+-+-+-+-+-+-+-+-+-+ |   +-+-+-+-+-+-+-+-+-+-+
* Aircraft Carrier  (5/5) | 3/5 ships sunk.
* Battleship        (0/4) | 9 hits.
* Destroyer         (0/3) | 4 misses.
* Frigate           (2/3) |
* Submarine         (0/2) |
*           YOU WON - CONGRATULATIONS !!!
****************************************************************************/
void displayAllInfo(char playerHidden[SIZE][SIZE],
                    char playerReveal[SIZE][SIZE],
                    char computHidden[SIZE][SIZE],
                    char computReveal[SIZE][SIZE])
{

   int playerShipsSunk,computerShipsSunk;
   char key;

   /*Store total of ships each side has sunk*/
   playerShipsSunk=getSunkShips(playerReveal);
   computerShipsSunk=getSunkShips(computReveal);

   /*Reveal the hidden ships for each grid*/
   revealHidden(playerHidden,playerReveal);
   revealHidden(computHidden,computReveal);

   /*display the information for both grids*/
   displayKnownInfo(playerReveal,playerHidden,computReveal);

   /*congratulatory or commiserative message */
   if(computerShipsSunk>playerShipsSunk)
      printf("           YOU WON - CONGRATULATIONS !!!  ");
   else
      printf("           THE COMPUTER HAS BEATEN YOU :-(");


   printf("\nPress a key\n");
   key=getchar();
}


/****************************************************************************
* getString(): An interactive string input function.
* Source: http://blackboard.rmit.edu.au/courses/1/COSC2138OUA_1037/content/
  _2307602_1/dir_CLibFunctEx_220.zip/CLibFunctEx_220/
  InputValidation/getString-basic.c
  Modified to add minimum length by me - Shows implementation using fgets
  as requested
****************************************************************************/
int getString(char* string, unsigned length,unsigned minlength, char* prompt)
{
   int finished = FALSE;
   char tempString[TEMP_STRING_LENGTH + 2];

   /* Continue to interact with the user until the input is valid. */
   do
   {
      /* Provide a custom prompt. */
      printf("%s", prompt);

      /* Accept input. "+2" is for the \n and \0 characters. */
      fgets(tempString, length + 2, stdin);

      /* A string that doesn't have a newline character is too long. */
      if (tempString[strlen(tempString) - 1] != '\n' )
      {
         printf("Input was too long.\n");
         readRestOfLine();
      }
      else if(strlen(tempString)<minlength+1)
      {
         printf("Input was too short.\n");

      }
      else
      {
         finished = TRUE;
      }

   }
   while (finished == FALSE);

   /* Overwrite the \n character with \0. */
   tempString[strlen(tempString) - 1] = '\0';

   /* Make the result string available to calling function. */
   strcpy(string, tempString);

   return SUCCESS;
}



/****************************************************************************
* Function readRestOfLine() is used for buffer clearing. Source:
* https://inside.cs.rmit.edu.au/~sdb/teaching/C-Prog/CourseDocuments/
* FrequentlyAskedQuestions/#alternative
****************************************************************************/
void readRestOfLine()
{
   int c;

   /* Read until the end of the line or end-of-file. */
   while ((c = fgetc(stdin)) != '\n' && c != EOF)
      ;

   /* Clear the error and end-of-file flags. */
   clearerr(stdin);
}
