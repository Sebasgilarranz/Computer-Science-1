// Sebastian Gilarranz
// COP 3502, Fall 2018
// Se171788
// Program 1

#include "Glowworm.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

double difficultyRating (void)
{
    return 2.5;
}

double hoursSpent (void)
{
    return 6;
}

// function "printGlowworm" takes 5 integers and prints glowworm accordingly.
void printGlowworm (int tail, int bigO, int head, int maxLength, int end)
{
    int i;
    // modular arithmetic to reset variables once they pass maxlength.(===)
    tail = tail % maxLength;
    head = head % maxLength;
    bigO = bigO % maxLength;
    
    // if tail is to be printed before head this code will excecute.
    if (tail < head)
    {
        // for loop is used to go through each possible thing to print depending on the position of i.
        for (i = 0; i < maxLength; i++)
        {
            // if i is in the same position as tail, bigO, or head, it will print the corresponding letter. (line 32-48)
            if (i == tail)
                printf ("~");
            
            else if (i == bigO)
            {
                if (!end)
                    printf ("O");
                else
                    printf ("X");
            }
            
            else if (i == head)
            {
                if (!end)
                    printf ("G");
                else
                    printf ("x");
            }
            // if head,tail,or bigO isnt printed but i is less than tail and head a space will be printed.
           
            else if (i < tail && i < head)
                printf (" ");
            // if head,tail, or bigO isnt printed
            
            else if (i > tail && i < head)
            {
                if (i != head)
                printf ("o");
            }
        }
    }
    
    // if head is to be printed before tail this if will execute.
    if (tail > head)
    {
        // for loop will go through all possible things to print ('~','O','G','o') depending on the position of i. ( line 64 - 81)
        for (i = 0; i < maxLength; i++)
        {
            if (i == tail)
                printf ("~");
           
            else if (i == bigO)
            {
                if (!end)
                    printf ("O");
                else
                    printf ("X");
            }
            
            else if (i == head)
            {
                if (!end)
                    printf ("G");
                else
                    printf ("x");
            }
            
            // in this else if i is less than head and tail which means 'o' should be printed.
            else if (i < head && i < tail)
            {
                // this is included so that 'o' wont be printed in the spot reserved for 'O'.
                if (i != bigO)
                    printf ("o");
            }
            
            // in this else if i is greater than head and tail then 'o' should be printed as well.
            else if (i > head && i > tail)
            {
                // this is included so that 'o' wont be printed in the spot reserved for 'O'.
                if (i != bigO)
                    printf ("o");
            }
            
            // in all other cases a ' ' will be printed.
            else
                printf (" ");
        }
    }
}

int main (int argc, char **argv)
{
    // integer maxlength is being assigned to the integer form of argument 1 passed from the command line.
    // char pointerConsume will be pointing to argument 2's location in memory.
    int maxLength = atoi (argv[1]);
    char *Consume = argv[2];
    int tail = 0, bigO = 1, head = 2, end = 0, i, q;
    
    // Heres where we print the intitial glowworm. Wohoooo!
    printf ("%s\n\nGlowworm appears! Hooray!\n", Consume);
    printGlowworm (tail ,bigO, head, maxLength, end);
    printf ("\n");
    
    for (i = 0; i < maxLength; i++)
        printf ("=");
    
    printf ("\n\n");
    
    // for loop to go through pointer to char array consume.
    for (q = 0; q < strlen(Consume); q++)
    {
        // depending on what type of letter is held in the Consume[i] there will be several different cases to run. Each case will determine what action is required with corresponding letters in Consume.
        switch (Consume[q])
        {
            case 'o':
                // if loop is required to check if the lenght of the glowworm is at its max, if not another 'o' can be added.
                if (head - tail == maxLength - 1)
                {
                    printf ("Glowworm chills:\n");
                    break;
                }
                head ++;
                bigO++;
                printf ("Glowworm grows:\n");
                break;
                
            case 'O':
                // if loop is required to check if the lenght of the glowworm is at its max, if not another 'o' can be added.
                if (head - tail == maxLength - 1)
                {
                    printf("Glowworm chills: \n");
                    break;
                }
                head++;
                bigO++;
                printf ("Glowworm grows:\n");
                break;
                
            case '@':
                // if loop is required to check if the lenght of the glowworm is at its max, if not another 'o' can be added.
                if (head - tail == maxLength - 1)
                {
                    printf("Glowworm chills:\n");
                    break;
                }
                head++;
                bigO++;
                printf ("Glowworm grows:\n");
                break;
                
            case 's':
                // this checks to see if glowworm is at its smallest. if it isnt it will continue on with the case.
                if (bigO - 1 == tail)
                {
                    printf ("Glowworm chills:\n");
                    break;
                }
                head--;
                bigO--;
                printf ("Glowworm shrinks:\n");
                break;
                
            case 'S':
                // this checks to see if glowworm is at its smallest. if it isnt it will continue on with the case.
                if (bigO - 1 == tail)
                {
                    printf ("Glowworm chills:\n");
                    break;
                }
                head--;
                bigO--;
                printf ("Glowworm shrinks:\n");
                break;
                
            case '-':
                head++;
                bigO++;
                tail++;
                printf ("Glowworm inches forward:\n");
                break;
                
            case '=':
                head++;
                bigO++;
                tail++;
                printf ("Glowworm inches forward:\n");
                break;
                
            case 'x':
                end = 1;
                printf ("Glowworm meets its demise. SAD.\n");
                break;
                
            case 'X':
                end = 1;
                printf ("Glowworm meets its demise. SAD.\n");
                break;
                
            // if letter is not defined, the glowworm will chill.
            default:
                printf ("Glowworm chills:\n");
        }
        
        // after switch has updated variables, printGlowworm should be called to print the appropiate glowworm.
        printGlowworm (tail, bigO, head, maxLength, end);
        printf ("\n");
        
        for (i = 0; i < maxLength; i++)
            printf ("=");
        
        printf ("\n\n");
        
        // this line is important because if switch read an X or x, end will be updated to 1.
        if (end == 1)
            return 0;
    }
    
    return 0;
}
