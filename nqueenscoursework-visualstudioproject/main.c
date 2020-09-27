
/*
 * File:   main.c
 * Author: j4-smith
 *N-Queens example in C
 * First Created on 25 April 2014, 18:42
 * Modified in light of student progress
 
 * Rewritten Oct 2015 to use more generic solution structures
 * and functions with NQueens-specific names that call the functions that modify the
 * modified still further 2018
 */


#include <stdio.h>
#include <stdlib.h>
#include "StructureDefinitions.h"
#include "SolutionListOperations.h"
#include "NQueensChecker.h"

#pragma warning(disable:4996)

typedef int bool;
#define true  1
#define false 0

//Variables workingCandidate, openList, closedList
candidateSolution workingCandidate;// this one will hold the soltion we are currently considering
candidateList  openList; // this list will store all the soltion we;ve created but not examined yet
candidateList closedList; // this is where we will store all the ones we're done with

int firstValueToAdd;

//************************ don't edit anything above this line***********************//

int main(int argc, const char * argv[])
{
    
    /* the next set of variables get used within our main function
     * but aren't declared globally becuase we don't want the other functions to change them inadvertently *///
    int indexOfSolutionWeAreLookingAt=0; //index in list of current solution being examined
    int currentRow=0; // used when we extend the working candidate
    bool goalReached = false; // used to indicate when to stop searching for new candidates
    int numRead=0;//used to read the inputs
    //start off by emptying the lists of candidate solutions
    CleanListsOfSolutionsToStart();
    CleanWorkingCandidate();
    
    /* So now let's start by creating our first solution
     * which we do by filling the values into the variable we declared as the workingCandidate
     * We'll begin by putting the first queen into column ), or specified from the command line
     */
    firstValueToAdd = 0;
    if(argc==2)
      {
          numRead=sscanf(argv[1],"%d",&firstValueToAdd);
          if (numRead != 1 || firstValueToAdd >=N || firstValueToAdd <0)
          {
#ifdef ONDEWIS
              extern void printInvalidInputFeedbackAndExit(void);
              printInvalidInputFeedbackAndExit();
#else
              PrintThisMessageAndExit("Invalid Input");
#endif
          }
      }
	   
    // we are using a constructive solution so first we have to add a queen.
    // There is a different function to move a queen.
    AddQueenToNextRowInColumn(firstValueToAdd); 
    //this shows you how to print the current working cnadidae if you need to for debugging
    PrintWorkingCandidate();
    //this is the function that tests whether a partial solution is feasible or not
    CalculateNumberOfVulnerableQueensForWorkingCandidate(); //should score zero because there is only one queen :)  
    //and we can put this as our first item in the list to start the process
    AddWorkingCandidateToOpenList();
    ///**********DONT CHANGE ANYTHING ABOVE THIS LINE
	/*Variables workingCandidate, openList, closedList 
	  SetworkingCandidate = StartSolution 
	  Test(working candidate) 
	  While(goal not reached AND Openlistnot empty) Do 
	  If(working candidate is not infeasible) 
		  Generate all 1 - step offspring and addto openList 
				 Moveworking candidate to closedList 
				 Movelast item in openListinto working candidate 
				 Test(working candidate)
	*/
    //**** YOUR DEPTH_FIRST SEARCH CODE GOES HERE ***////	
	// While(goal not reached AND Openlist not empty) Do
	while (goalReached == false && openList.size > 0){		
		if (workingCandidate.score == 0) {		//Checks the score of the working candidate			   
			AddQueenToNextRowInColumn(0);		//Adds queen to the next row in the column
			for (int i = 0; i < N; i++) {		//Generate every 1 step offspring
				PrintWorkingCandidate();     //Prints the working candidate
				MoveQueenInRowToNewCol(workingCandidate.size - 1, i);	//Moves the queen to a new column
				AddWorkingCandidateToOpenList();	//Adds the current working candidate to the open list
			}
		}
		printf("%d", workingCandidate.size);		
		AddWorkingCandidateToClosedList();			//Adds the working candidate to the closed list
		CopySolutionFromOpenListIntoWorkingCandidate(openList.size - 1);	//Copies next solution from open list to the working candidate
		RemoveSolutionFromOpenList(openList.size - 1);			//Removes the current solution from the openList
		CalculateNumberOfVulnerableQueensForWorkingCandidate();	//Calculates the number of vunerable queens
		if (workingCandidate.size == N && workingCandidate.score == 0){goalReached = true;}	//If a solution is found the the goalReached is set to true
	}
    ///**** YOU MUST CALL PrintFinalSolutionAndExit() to get a mark from the system	
	PrintFinalSolutionAndExit();	
    return 0;
}

