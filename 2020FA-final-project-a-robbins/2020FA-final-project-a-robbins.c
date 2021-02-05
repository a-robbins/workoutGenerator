#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "struct.h"


//put struct in it's own header file

//prototypes
void userInput(int *type, int *time, int *intensity, int *muscle);
void assignChars(int typeNum, char *typeChar, int intensityNum, char *intensityChar, int muscleNum, char *muscleChar); 
int readFile(int type, move *arr); //return size
void moveFunc(int size, move *arr, char group[], int start, int numMoves, FILE *ofp);
void workoutGen(char group[], int size, move *arr, char type[], char intensity[]);
void intensityFunc(char intensity[], char type[], FILE *ofp );
 

int main(void) 
{
  int typeNum = 0;
  char typeChar[50]; 
  int time = 0; 
  int intensityNum = 0; 
  char intensityChar[15];
  int muscleNum = 0; 
  char muscleChar[15];
  int size = 0; 
  move arr[500]; 
 
  
  printf("Hello, welcome to this handy dandy workout generator, I am glad you are here!\n\n"); 
  
  userInput(&typeNum, &time, &intensityNum, &muscleNum); 
  assignChars(typeNum, typeChar, intensityNum, intensityChar, muscleNum, muscleChar); 
 
  printf("Perfect, we will be doing a %d minute %s intensity %s session focused on %s...\n\nlet's get started!\n", time, intensityChar, typeChar, muscleChar); 

  size = readFile(typeNum, arr); 


  workoutGen(muscleChar, size, arr, typeChar, intensityChar);

 
   
  return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "struct.h"

void userInput(int *type, int *time, int *intensity, int *muscle)
{
  //function to take in user input

  printf("Please pick the type of workout you would like:\n 1. Cardio \n 2. Muscular Endurance \n 3. Hypertrophy \n 4. Max Strength \n "); 

  scanf("%d", type); 
    while(*type < 1 || *type > 4)
    {
      printf("Please choose a number between 1-4\n"); 
      scanf("%d", type); 
    }
  printf("Now, please enter how long you would like your workout to be (in minutes): "); 

  scanf("%d", time); 
  
  printf("What intensity level would you like to go for: \n 1. Low \n 2. Moderate \n 3. All Out \n "); 

  scanf("%d", intensity);
    while(*intensity < 1 || *intensity > 3)
    {
      printf("Please choose a number between 1-3 \n");
      scanf("%d", intensity);  
    }

  printf("Awesome, we can do that! Finally, what muscle groups would you like to focus on: \n 1. Full Body \n 2. Upper Body \n 3. Lower Body \n 4. N/A, Doing Cardio\n"); 

  scanf("%d", muscle); 
    while(*muscle < 1 || *muscle > 4)
    {
      printf("Please choose a number between 1-4\n"); 
      scanf("%d", muscle); 
    }

}

void assignChars(int typeNum, char *typeChar, int intensityNum, char *intensityChar, int muscleNum, char *muscleChar)
{
  //function to populate char arrays

    switch(typeNum)
    {
      case 1: strcpy(typeChar, "cardio"); 
              break;
      case 2: strcpy(typeChar, "muscular endurance");
              break;
      case 3: strcpy(typeChar, "hypertrophy");
              break;
      case 4: strcpy(typeChar, "max strength"); 
              break;
      
    }

    if(intensityNum == 1)
    {
      strcpy(intensityChar, "low"); 
    }
    else if(intensityNum ==2 )
    {
      strcpy(intensityChar, "moderate"); 
    }
    else
    {
      strcpy(intensityChar, "high");
    }

    if(muscleNum > 0 && muscleNum <= 4)
    {
      switch(muscleNum)
      {
        case 1: strcpy(muscleChar, "full body"); 
                break; 
        case 2: strcpy(muscleChar, "upper body"); 
                break;
        case 3: strcpy(muscleChar, "lower body"); 
                break;
        case 4: strcpy(muscleChar, "N/A"); 
                break;
      }
    }

}

int readFile(int type, move *arr)
{
  //function to read in from file

  int size = 0; 
  FILE *ifp = NULL; 

  if(type == 1)
  {
    ifp = fopen("cardio.txt", "r");
      if(ifp == NULL)
      {
        printf("encountered an error, exiting...\n"); 
        exit(1); 
      } 
    fscanf(ifp, "%d", &size); 
    for(int i = 0; i < size; i++)
    {
      fscanf(ifp, "%s", arr[i].intensity); 
      fscanf(ifp, "%s", arr[i].group);
      fscanf(ifp, "%s", arr[i].movement);
      strcpy(arr[i].location, ""); //making sure to overwrite any data in location 
    }
      
  }
  else if(type > 1 && type <= 4)
  {
    ifp = fopen("fullbody.txt", "r");
     if(ifp == NULL)
      {
        printf("encountered an error, exiting...\n"); 
        exit(1); 
      } 
    fscanf(ifp, "%d", &size);
    for(int i = 0; i < size; i++)
    {
      fscanf(ifp, "%s", arr[i].intensity); 
      fscanf(ifp, "%s", arr[i].location); 
      fscanf(ifp, "%s", arr[i].group);
      fscanf(ifp, "%s", arr[i].movement);
    }
  }
  else
  {
    printf("error...exiting\n"); 
    exit(1); 
  }
 
 fclose(ifp); 
 return size;
}





void moveFunc(int size, move *arr, char group[], int start, int numMoves, FILE *ofp) 
{
  //function to recursively generate movements

  char move1[50]; 
  char move2[50]; 
  
  for(int i = start; i < size; i++)
  {
    if((strcmp(arr[i].group, group) == 0) && (numMoves > 0))
    {
      if(strcmp(arr[i].location, "anterior") == 0)
      {
        strcpy(move1, arr[i].movement); 
        fprintf(ofp, "%s\n", move1); 
        numMoves--;
      }
      if(strcmp(arr[i].location, "posterior") == 0)
      {
        strcpy(move2, arr[i].movement); 
        fprintf(ofp, "%s\n",move2);
      numMoves--;
      }
    } 
  }
  
  if(strcmp(group, "cardio") == 0)
 {
   for(int i = 0; i < 2; i += 2)
   {
     strcpy(move1, arr[i].movement); 
     fprintf(ofp, "%s\n", move1); 
     strcpy(move2, arr[i+1].movement); 
     fprintf(ofp, "%s\n", move2); 
     numMoves -= 2; 
   }
 }
  start += 2; 
  
  if(numMoves > 0)
  {
    moveFunc(size, arr, group, start, numMoves, ofp); 
  }
}

void workoutGen(char group[], int size, move *arr, char type[], char intensity[])
{
  //function to generate the workout

  FILE *ofp = NULL; 
  ofp = fopen("output.txt", "w"); 
    if(ofp == NULL)
    {
      printf("error...exiting\n"); 
      exit(1); 
    }
  int numMoves; 
  int start = 0;

  fprintf(ofp, "Movements: \n"); 
  fprintf(ofp, "---------------------\n"); 


  if(strcmp(group, "full body") == 0 )
  {
    numMoves = 4;
    strcpy(group, "upper"); 
    moveFunc(size, arr, group, start, numMoves, ofp); 
    numMoves = 4; 
    strcpy(group, "lower"); 
    moveFunc(size, arr, group, start, numMoves, ofp); 
  }
  else if(strcmp(group, "upper body") == 0)
  {
    numMoves = 6; 
    strcpy(group, "upper"); 
    moveFunc(size, arr, group, start, numMoves, ofp); 
  }
  else if(strcmp(group, "lower body") == 0)
  {
    numMoves = 6; 
    strcpy(group, "lower"); 
    moveFunc(size, arr, group, start, numMoves, ofp); 
    
  }
  else if(strcmp(group, "N/A") == 0)
  {
    if(strcmp(type, "cardio") == 0)
    {
      numMoves = 2; 
      strcpy(group, "cardio"); 
      moveFunc(size, arr, group, start, numMoves, ofp); 
    }
  }
  
  fprintf(ofp, "\n\nRepetitions & Rest: \n"); 
  fprintf(ofp, "---------------------\n"); 
  
  intensityFunc(intensity, type, ofp); 

  fprintf(ofp, "\n\nGuidance: \n"); 
  fprintf(ofp, "---------------------\n"); 
    
    if(strcmp(type, "muscular endurance") == 0)
    {
      fprintf(ofp, "When performing muscular endurance, be sure to focus on the slow, deliberate contraction of the appropriate muscle groups. This is the best place to work on form and proper recruitement through slow, steady, controlled movements.\n\nIdeally, you should be doing these movements at 0-50%% of your bodyweight."); 
    }
    else if(strcmp(type, "hypertrophy") == 0)
    {
      fprintf(ofp, "When performing hypertrophy, make sure you have already mastered the basics with muscular endurance. Once you are sure you are able to correctly do the movement, practice with smooth, controlled motions, making sure NOT to pause at the bottom of your movement.\n\nIdeally, you should be doing these movement at 30-100%% of your bodyweight. The last few reps should be difficult, but your form should not fail! If your form starts to slip, immediately stop, rest, and lighten the weight for the next set."); 
    }
    else if(strcmp(type, "max strength") == 0)
    {
      fprintf(ofp, "When performing max strength movements, it is absolutely critical that you have mastered your form and understand when you are failing. These movements are dangerous because you are under a heavy load...miscalculations and falters in form can cause SERIOUS injury!!\n\nIf you do feel ready to attempt this workout, then do so at a high speed, not pausing anywhere throughout the movement. Your focus is to move the weight as many times as possible and in order to do this you have to keep moving.\n\nIdeally, you will know you 1 Rep Max by this point and be lifting at 80-100%% of it.\n"); 
    }
    else if(strcmp(type, "cardio") == 0)
    {
      fprintf(ofp, "When performing cardio exercises, go at a pace that you are breathing heavier than normal, but that you feel like you can maintain for the chosen amount of time.\n"); 
    }

  fclose(ofp); 
}

void intensityFunc(char intensity[], char type[], FILE *ofp )
{
  //function to determine rep and rest ranges

  int reps; 
  int rest; 
  char tempo[10];

  if(strcmp(intensity, "low") == 0)
  {
      if(strcmp(type, "muscular endurance") == 0)
      {
        reps = 10; 
        rest = 60; 
        strcpy(tempo, "4-2-1"); 
      }
      else if(strcmp(type, "hypertrophy") == 0)
      {
        reps = 8; 
        rest = 60;
        strcpy(tempo, "2-0-2");  
      }
      else if(strcmp(type, "max strength") == 0)
      {
        reps = 3; 
        rest = 300; 
        strcpy(tempo, "0-0-0"); 
      }
      else if(strcmp(type, "cardio") == 0)
      {
        reps = 1; 
        rest = 0; 
        strcpy(tempo, "N/A"); 
      }
  }
   
   if(strcmp(intensity, "moderate") == 0)
  {
      if(strcmp(type, "muscular endurance") == 0)
      {
        reps = 12; 
        rest = 45;
        strcpy(tempo, "4-2-1"); 
      }
      else if(strcmp(type, "hypertrophy") == 0)
      {
        reps = 10; 
        rest = 45; 
        strcpy(tempo, "2-0-2");  
      }
      else if(strcmp(type, "max strength") == 0)
      {
        reps = 4; 
        rest = 240;
        strcpy(tempo, "0-0-0"); 

      }
      else if(strcmp(type, "cardio") == 0)
      {
        reps = 1; 
        rest = 0; 
        strcpy(tempo, "N/A");
      }
  }
   if(strcmp(intensity, "high") == 0)
  {
      if(strcmp(type, "muscular endurance") == 0)
      {
        reps = 12; 
        rest = 30; 
        strcpy(tempo, "4-2-1"); 
      }
      else if(strcmp(type, "hypertrophy") == 0)
      {
        reps = 10; 
        rest = 30;
        strcpy(tempo, "2-0-2");  
      }
      else if(strcmp(type, "max strength") == 0)
      {
        reps = 5; 
        rest = 300; 
        strcpy(tempo, "0-0-0"); 
      }
      else if(strcmp(type, "cardio") == 0)
      {
        reps = 1; 
        rest = 0; 
        strcpy(tempo, "N/A");
      }
  }

  fprintf(ofp, "reps: %d\n", reps); 
  fprintf(ofp, "rest: %d seconds\n", rest);
  fprintf(ofp, "tempo: %s\n", tempo);  

}


