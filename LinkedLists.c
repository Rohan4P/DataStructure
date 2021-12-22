/*******************************
 * File Name	: Lab1.c
 * Author		: Shamseddin Elmasri
 * Date			: Jan 04, 2021
 * Description	: This file is the skeleton for Lab 1 (Linked Lists). A linked list has already been created.
 *				  insertNode() and deleteNode() functions have been defined for you.
 * Instructions	:
 *				- Complete InsertNode() and deleteNode() functions.
 *				- Modify printLinkedList() function to display the total number of vowels in the list.
 *				- Do not modify the main() function or any other line of code.
 *
 *
 * Student Name: Rohan Patel
 * Student Number: 8696839
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>



 /* Definition of linked list node */
typedef struct Node {

	char dataField;
	struct Node* ptrNextNode;	// Pointer to next node in the list (NULL if it's the tail)

} Node_t;



/* Private Functions Prototypes */
void createList(Node_t** ptrHead, char* data);
void printLinkedList(Node_t* head);
void insertNode(Node_t** ptrHead, char data, int targetPosition);
void deleteNode(Node_t** ptrHead, uint8_t targetPosition);
void deleteList(Node_t** ptrHead);



/* Do not change anything in this function */
int main(void)
{
	char mixedLetters[14] = { 'h','Y','V','w','R','U','a','j','o','M','q','Z','F','t' };
	char extraLetters[3] = { 'B','E','s' };

	// Define linked list head
	Node_t* head = NULL;
	Node_t** ptrHead = &head;

	createList(ptrHead, mixedLetters);		// Create linked list
	printLinkedList(head);				// Print out the linked list

	deleteNode(ptrHead, 4);
	insertNode(ptrHead, extraLetters[0], 0);
	insertNode(ptrHead, extraLetters[1], 3);
	insertNode(ptrHead, extraLetters[2], 15);


	printf("\nAfter modifying the list:\n");
	printLinkedList(head);				// Print out the linked list


	deleteList(ptrHead);
	printf("\nAfter deleting all nodes:\n");
	printLinkedList(head);				// Print out the linked list

	return 0;
}



// FUNCTION      : createList()
// DESCRIPTION   : This function creates a linked list
// PARAMETERS    :	
//		Node_t** ptrHead - Used to store address of header pointer
//		char data	 - Data to be stored in the list
// RETURNS       : Nothing
void createList(Node_t** ptrHead, char* data) {

	Node_t* newNode = NULL;							// Used for pointing to new node
	Node_t* currentNode = NULL;						// Used for traversing

	for (int i = 0; i < 14; i++) {

		/* Create new node, and check if allocation was successfull */
		newNode = (Node_t*)malloc(sizeof(Node_t));

		if (newNode != NULL) {

			newNode->dataField = data[i];				// Copy data into new node's data field
		}
		else {

			printf("No sufficient memory!\n");
			return;
		}

		/* Set first node as head */
		if (i == 0) {

			*ptrHead = newNode;
			currentNode = *ptrHead;					// Start traversing from head
			continue;
		}

		currentNode->ptrNextNode = newNode;				// Place new node at the end of the list	
		currentNode = currentNode->ptrNextNode;				// Traverse to next node			
	}

	newNode->ptrNextNode = NULL;						// Set pointer to next node as null		
}



// FUNCTION      : 	PrintLinkedList()
// DESCRIPTION   : 	This function prints out the data and address of each
//			node along with its next nodes address in the list.
//			The total number of nodes in the list is also printed.
// PARAMETERS    : 	Node_t *head: Pointer to head node
// RETURNS       : 	nothing
void printLinkedList(Node_t* head) {

	uint8_t nOfNodes = 0;			// Counter used to count number of nodes in the list
	Node_t* node;
	node = head;				// Pointing to the head of the list
	uint8_t lowCase = 0;
	uint8_t uppCase = 0;


	// Traverse through the whole list
	while (node != NULL) {
		if (node->dataField == 'a' || node->dataField == 'e' || node->dataField == 'i' ||
			node->dataField == 'o' || node->dataField == 'u') {
			lowCase++;
		}
		else if (node->dataField == 'A' || node->dataField == 'E' || node->dataField == 'I' ||
			node->dataField == 'O' || node->dataField == 'U') {
			uppCase++;
		}
		printf("Data = %c\t node address: %p\t next node: %p\n",	// Print list with address
			node->dataField, node, node->ptrNextNode);			// of each node and its next node
		nOfNodes++;							// Increment counter
		node = node->ptrNextNode;					// Go to next node
	}
	printf("\nNumber of nodes in the list is: %u\n", nOfNodes);

	/*Printing total number of vowels in Linked list with total number of lowercase and uppercase*/
	printf("Total number of vowels is %i with Lower case = %i  and Uppercase = %i \n", (lowCase + uppCase), lowCase, uppCase);

	return;
}



// FUNCTION      : 	insertNode()
// DESCRIPTION   : 	This function inserts a node into the linked list at a particular position
// PARAMETERS    : 	
//		Node_t** ptrHead	- Used to store address of header pointer
//	        char data 		- Data to be stored in the inserted node
//		int targetPosition	- Desired position in the linked list for the node to be inserted at
// RETURNS       :	Nothing
void insertNode(Node_t** ptrHead, char data, int targetPosition) {

	Node_t* newNode = NULL;					//Pointing to NULL
	Node_t* tempPtr = *ptrHead;				//Pointing to the head of the list

	newNode = (Node_t*)malloc(sizeof(Node_t));		// Create new node, and check if allocation was successfull  

	if (newNode) {								//Checking for newNode
		if (targetPosition == 0) {				//Checking for 0th target Position
			newNode->dataField = data;			//Copy data into new node's data field
			newNode->ptrNextNode = *ptrHead;	//Place ptrHead next to newNode
			*ptrHead = newNode;					//Assigning newNode as ptrHead 
		}
		else {
			while (targetPosition != 1) {			//Checking for target position if 1 then exist
				tempPtr = tempPtr->ptrNextNode;		// Traverse to next node
				targetPosition--;					//decrement target positon until it sets to 1
			}
			newNode->dataField = data;						//Copy data into new node's data field
			newNode->ptrNextNode = tempPtr->ptrNextNode;	//Assigning value of ptrNextNode of tempPtr to newNode's ptrNextNode 
															//so that newNode can points to next node of tempPtr.
			tempPtr->ptrNextNode = newNode;					//Place newNode next to tempPtr
		}
	}
}



// FUNCTION      : 	deleteNode()
// DESCRIPTION   : 	This function deletes a node defined by its position in the linked list
// PARAMETERS    : 	
//			Node_t** ptrHead	- Used to store address of header pointer
//			int targetPosition	- Desired position of node to be deleted
// RETURNS       :	Nothing
void deleteNode(Node_t** ptrHead, uint8_t targetPosition) {
	Node_t* currNode = *ptrHead;	//currNode pointing to the head of the list
	Node_t* prevNode = *ptrHead;	//prevNode pointing to the head of the list

	if (*ptrHead == NULL) {			//Checking if ptrHead is Null or not
		printf("List is Empty");
	}
	else if (targetPosition == 0) {				//Checking if targetPosition is 0  
		*ptrHead = currNode->ptrNextNode;		//Sets pointer head to next node of current node
		free(currNode);							//Free the memory of currNode
		currNode = NULL;						//Sets currNode to Null
	}
	else {
		while (targetPosition != 0) {			//while target position is not zero
			prevNode = currNode;				//Sets prevNode to currNode(Head pointer)
			currNode = currNode->ptrNextNode;	//Traversing currNode to next node
			targetPosition--;					//decrement target positon until it sets to 0
		}
		prevNode->ptrNextNode = currNode->ptrNextNode;	//Updating ptrNextNode of prevNode with value of ptrNextNode of currNode 
														//so that prevNode can points to next node of currNode.

		free(currNode);									//Free the memory of currNode
		currNode = NULL;								//Sets currNode to Null
	}
}



// FUNCTION      : 	deleteList()
// DESCRIPTION   : 	This function deletes all nodes in the list
// PARAMETERS    : 	Node_t** ptrHead	- Used to store address of header pointer
// RETURNS       :	Nothing
void deleteList(Node_t** ptrHead) {

	Node_t* tempPtr;

	while (*ptrHead != NULL)
	{
		tempPtr = *ptrHead;
		*ptrHead = (*ptrHead)->ptrNextNode;
		free(tempPtr);
	}
}