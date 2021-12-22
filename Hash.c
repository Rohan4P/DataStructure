/*******************************************************************************************
 * File Name	: Hash.c
 * Author	    : Shamseddin Elmasri
 * Date		    : Apr 17, 2021
 * Description	: This file is the skeleton for Lab 4 (Hashing).

 * Instructions	:
 *			            1) Complete the state machine as indicated in the comments inside
 *                         each state.
 *                      2) Create your own hash function to find the hash value for each
 *                         input (You may use the example provided in the lecture slides
 *                         as a starting point, however, your hash function must be
 *                         different)
 *                      3) For advanced outcomes, create another state machine inside
 *                         FINISH_STATE to enable the user of restarting the program
 *
 * Student Name: Rohan Patel
 * Student Number: 8696839
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>


uint32_t hashFunction(char* ptrInputBuffer);


int main()
{
    enum StateMachine
    {
        START_STATE,
        INITIALIZATION_STATE,
        WAIT_FOR_INPUT_STATE,
        GET_HASH_STATE,
        FINISH_STATE

    }State = START_STATE;


    uint32_t counter;                       // Used to count number of valid inputs
    char inputString[20];                   // Stores the user's input string
    char exitMessage[5] = "EXIT";
    uint32_t hashValue;

    while (1)
    {
        switch (State)
        {
        case START_STATE:

            printf("Program started!\n");

            State = INITIALIZATION_STATE;

            break;


        case INITIALIZATION_STATE:

            // Reset the counter and clear the input string array
            counter = 0;
            for (int i = 0;i < strlen(inputString);i++) {
                inputString[i] = { 0 };
            }
            State = WAIT_FOR_INPUT_STATE;
            break;


        case WAIT_FOR_INPUT_STATE:

            // User enters the input string from the terminal
            printf("User Please Enter Input Data:");
            gets_s(inputString);

            // If the user enters "exit" or "EXIT", go to FINISH_STATE
            if (strcmp(inputString,"exit")==0 || strcmp(inputString,"EXIT")==0) {
                State = FINISH_STATE;
                break;
            }

            // Checking the first character of the input,
            // if it's not a letter (upper case or lower case),
            // then considering the input as invalid.
            // If the input is valid, incrementing the counter and go
            // to GET_HASH_STATE
            // Checking the input and setting the next state accordingly
            if ((inputString[0] >= 65 && inputString[0] <= 90) || (inputString[0] >= 97 && inputString[0] <= 122)) {
                counter++;
                State = GET_HASH_STATE;
                break;
            }
            else {
                printf("Invalid Data\n");
            }
            break;


        case GET_HASH_STATE:

            // Calling the hash function and display the hash value
            hashValue=hashFunction(inputString);
            printf("Hash Value=%i\n",hashValue);
           
            // Returning back to WAIT_FOR_INPUT_STATE
            State = WAIT_FOR_INPUT_STATE;
            break;


        case FINISH_STATE:

            // Display a message indicating program ended along with the 
            // number of valid inputs entered during the life of the program
            // before entering this state
            //
            // After entering this state, the state machine remain
            // in this state

            printf("Inputs entered :%d \n",counter);
            printf("Program Ended\n");
            return 0;

            /* Advanced Outcomes */
            // The message should be displayed only once inside this state
            // (not before entering this state). This can be done by creating
            // another statemachine that runs inside this state. The inner
            // state machine should also allow the user to restart the 
            // program if "restart" or "RESTART" is entered.

        default:
            State = START_STATE;
            break;
        }
    }

    return 0;
}



// FUNCTION      : hashFunction()
// DESCRIPTION   : This function receives an string, calculates a hash for it and returns the hash value
// PARAMETERS    :	
//		   char* ptrInputBuffer: Pointer to input string
//
// RETURNS       : calculated hash value
uint32_t hashFunction(char* ptrInputBuffer) {

    uint32_t calculatedHashValue = 510;
    int c = 0;
    while (c = *ptrInputBuffer++) {
        calculatedHashValue = calculatedHashValue * 34 + c;
    }
    return calculatedHashValue;
}