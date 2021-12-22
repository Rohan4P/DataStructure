/*******************************************************************************************
 * File Name	: Queues.c
 * Author	    : Shamseddin Elmasri
 * Date		    : Jan 10, 2021
 *
 * Description	: This file is the skeleton for lab 2 (Queues)
 *
 * Instructions	:
 *			- Complete enqueue1(), enqueue2(), enqueue3(), dequeue1(),
 *			  dequeue2(), dequeue3() functions.
 *
 *			- For advanced marks merge all the enqueuing and dequeuing
 *			  functions into one enqueue() and  one dequeue() respectively.
 *
 *
 * Student Name: Rohan Patel
 * Student Number: 8696839
 *
 */


#include <stdio.h>
#include <time.h>
#include <limits.h>
#include <malloc.h>

#define MAX_SIZE 40                             // Maximum size of queue

typedef struct Node {
    int data;
    struct Node* next;
} Node_t;

enum Queue {
    HIGH_PRIORITY,
    MED_PRIORITY,
    LOW_PRIORITY
};



/* Private Functions Prototypes */
void enqueue1(int);
void enqueue2(int);
void enqueue3(int);
int dequeue1();
int dequeue2();
int dequeue3();
void displayQueues(void);
int queueIsEmpty(enum Queue priority);



/* Queues Definitions */
int highPriorityQueue[MAX_SIZE] = { 0 };
int medPriorityQueue[MAX_SIZE] = { 0 };
int lowPriorityQueue[MAX_SIZE] = { 0 };

/* Indexes Definitions */
int hFront = 0, mFront = 0, lFront = 0;
int hRear = 0, mRear = 0, lRear = 0;


/* TypeDefs for timers */
time_t now, start, enqueueHighStart, enqueueMedStart, enqueueLowStart, dequeueStart;



/*** Do not change anything in this function unless for merging the enqueuing and
     dequeuing functions for the advanced outcomes ***/
int main(void)
{
    int dataHigh = 5, dataMed = 5, dataLow = 5;

    /* Add five elements to each queue*/
    for (int i = 0; i < 5; i++) {

        enqueue1(i);
        enqueue2(i);
        enqueue3(i);
    }

    displayQueues();

    /* Start timers */
    time(&start);
    time(&enqueueHighStart);
    time(&enqueueMedStart);
    time(&enqueueLowStart);
    time(&dequeueStart);
    time(&now);

    /* Run program for 30 seconds */
    while (difftime(now, start) < 30) {

        time(&now);     // Capture time

        /* Add an element to High Priority Queue if 4 seconds elapsed */
        if (difftime(now, enqueueHighStart) >= 4) {

            enqueue1(dataHigh);
            dataHigh++;
            time(&enqueueHighStart);        // Restart high priority enqueue timer
            displayQueues();
        }

        /* Add an element to Medium Priority Queue if 3 seconds elapsed */
        if (difftime(now, enqueueMedStart) >= 3) {

            enqueue2(dataMed);
            dataMed++;
            time(&enqueueMedStart);         // Restart medium priority enqueue timer
            displayQueues();
        }

        /* Add an element to Low Priority Queue if 2 seconds elapsed */
        if (difftime(now, enqueueLowStart) >= 2) {

            enqueue3(dataLow);
            dataLow++;
            time(&enqueueLowStart);         // Restart low priority enqueue timer
            displayQueues();
        }

        time(&now);     // Capture time


        /* Dequeue every second */
        if (difftime(now, dequeueStart) >= 1) {

            /* Dequeue based on priority */
            if (!queueIsEmpty(HIGH_PRIORITY)) {

                dequeue1();
            }
            else if (!queueIsEmpty(MED_PRIORITY)) {

                dequeue2();
            }
            else {
                dequeue3();
            }

            time(&dequeueStart);    // Restart dequeue timer
            displayQueues();
        }
    }

    return 0;
}


// FUNCTION      : enqueue1()
// DESCRIPTION   : This function adds an element to the rear of the high priority queue 
// PARAMETERS    : int value - represents the element to be added to the queue
// RETURNS       : Nothing
void enqueue1(int value) {
    
    if (hRear == (MAX_SIZE-1)) {    // Checks for size of array 
       printf("Overflow");
    }
    else if (hFront == -1 && hRear == -1) {     // Checking the condition for 1st element
        hFront = hRear = 0;                     // Setting front and rear value to zero
        highPriorityQueue[hRear] = value;       // Storing data in priority queue
    }
    else {
        
        highPriorityQueue[hRear] = value;     // Storing data in priority queue
        hRear = hRear + 1;                    // incrementing rear value by one 
    }
}



// FUNCTION      : enqueue2()
// DESCRIPTION   : This function adds an element to the rear of the medium priority queue 
// PARAMETERS    : int value - represents the element to be added to the queue
// RETURNS       : Nothing
void enqueue2(int value) {

    if (mRear == (MAX_SIZE - 1)) {          // Checks for size of array
        printf("Overflow");
    }
    else if (mFront == -1 && mRear == -1) {      // Checking the condition for 1st element
        mFront = mRear = 0;                      // Setting front and rear value to zero
        medPriorityQueue[mRear] = value;        // Storing data in priority queue
    }
    else {
        
        medPriorityQueue[mRear] = value;        // Storing data in priority queue
        mRear = mRear + 1;                      // incrementing rear value by one
    }
}



// FUNCTION      : enqueue3()
// DESCRIPTION   : This function adds an element to the rear of the low priority queue 
// PARAMETERS    : int value - represents the element to be added to the queue
// RETURNS       : Nothing
void enqueue3(int value) {
    
    if (lRear == (MAX_SIZE - 1)) {          // Checks for size of array
        printf("Overflow");
    }
    else if (lFront == -1 && lRear == -1) {     // Checking the condition for 1st element
        lFront = lRear = 0;                     // Setting front and rear value to zero
        lowPriorityQueue[lRear] = value;        // Storing data in priority queue
    }
    else {
        
        lowPriorityQueue[lRear] = value;        // Storing data in priority queue
        lRear = lRear + 1;                      // incrementing rear value by one
    }
}



// FUNCTION      : dequeue1()
// DESCRIPTION   : This function retrieves the element located at the front of the high priority queue
// PARAMETERS    : Nothing
// RETURNS       : highPriorityQueue[hFront]
int dequeue1(void) {
    
    if (hFront == -1 && hRear ==-1)         // Checking condition for empty queue
        printf("Under Flow");
    else if (hFront == hRear) {             // Checking condition for first element
        hFront = hRear = -1;               // Setting front and rear to  -1 to indicate
                                          // that queue is empty
    }
    else  
        for (int i = 0; i < hRear - 1; i++) {                    // applying for loop to last element of array
            highPriorityQueue[i] = highPriorityQueue[i + 1];    // updating ith element of array with ith+1 element of array
        }
    hRear=hRear-1;                                            // updating value of rear element to rear-1 
    return(highPriorityQueue[hFront]);
}



// FUNCTION      : dequeue2()
// DESCRIPTION   : This function retrieves the element located at the front of the medium priority queue
// PARAMETERS    : Nothing
// RETURNS       : medPriorityQueue[mFront]
int dequeue2() {
 
    if (mFront == -1 && mRear == -1)            // Checking condition for empty queue
        printf("Under Flow");
    else if (mFront == mRear) {             // Checking condition for first element
           mFront = mRear = -1;            // Setting front and rear to  -1 to indicate
                                          // that queue is empty
    }                                     
    else 
        for (int i = 0; i < mRear - 1; i++) {                   // applying for loop to last element of array 
            medPriorityQueue[i] = medPriorityQueue[i + 1];    // updating ith element of array with ith+1 element of array
        }
    mRear=mRear-1;                                          // updating value of rear element to rear-1 
    return(medPriorityQueue[mFront]);
}




// FUNCTION      : dequeue3()
// DESCRIPTION   : This function retrieves the element located at the front of the low priority queue
// PARAMETERS    : Nothing
// RETURNS       : lowPriorityQueue[lFront]
int dequeue3() {

    if (lFront == -1 && lRear == -1)          // Checking condition for empty queue
        printf("Under Flow");
    else if (lFront == lRear) {               // Checking condition for first element
        lFront = lRear = -1;                 // Setting front and rear to  -1 to indicate
                                            // that queue is empty
    }
    else
        for (int i = 0; i < lRear - 1; i++) {                    // applying for loop to last element of array
            lowPriorityQueue[i] = lowPriorityQueue[i + 1];     // updating ith element of array with ith+1 element of array
        }
        lRear=lRear-1;                                       // updating value of rear element to rear-1 
        return(lowPriorityQueue[lFront]);
}




// FUNCTION      : queueIsEmpty()
// DESCRIPTION   : This function is used to check if a certain queue is empty
// PARAMETERS    : enum Queue priority - HIGH_PRIORITY, MED_PRIORITY or LOW_PRIORITY
// RETURNS       : 1 if empty, 0 otherwise
int queueIsEmpty(enum Queue priority) {

    int* front = NULL;
    int* rear = NULL;

    /* Copy addresses of indexes based on queue chosen*/
    switch (priority) {
    case HIGH_PRIORITY:
        front = &hFront;
        rear = &hRear;
        break;
    case MED_PRIORITY:
        front = &mFront;
        rear = &mRear;
        break;
    case LOW_PRIORITY:
        front = &lFront;
        rear = &lRear;
        break;
    default:
        printf("Invalid entry\n");
        break;
    }

    return *front == *rear;
}



// FUNCTION      : displayQueues()
// DESCRIPTION   : This function displays the contents of all the queues.
// PARAMETERS    : Nothing
// RETURNS       : Nothing
void displayQueues(void) {

    if (hFront == hRear) {
        printf("High priority queue is empty\n");
    }
    if (mFront == mRear) {
        printf("Medium priority queue is empty\n");
    }
    if (lFront == lRear) {
        printf("Low priority queue is empty\n");
    }

    printf("\033[2J");      // Clear screen
    printf("\033[0;0H");    // Reset cursor

    /* Display contents of the high proirity queue */
    for (int i = hFront; i < hRear; i++) {

        printf(" %d ", highPriorityQueue[i]);
    }
    printf("\n");

    /* Display contents of the medium proirity queue */
    for (int i = mFront; i < mRear; i++) {

        printf(" %d ", medPriorityQueue[i]);
    }
    printf("\n");

    /* Display contents of the low proirity queue */
    for (int i = lFront; i < lRear; i++) {

        printf(" %d ", lowPriorityQueue[i]);
    }
    printf("\n");
}