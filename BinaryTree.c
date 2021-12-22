/*******************************************************************************************
 * File Name	: BinaryTree.c
 * Author	    : Shamseddin Elmasri
 * Date		    : Mar 11, 2021
 * Description	: This file is the skeleton for Lab 3 (Binary Search Tree).

 * Instructions	:
 *			            1) Complete the structure for the binary tree nodes. This structure should contain a data field,
 *                         and two pointers (one for right child and the other for the left child).
 *                         You may add more fields to the structure if necessary.
 *
 *	                    2) Complete the following functions:
 *
 *                              insertNode(): Creates a new node, inserts it to the binary search tree,
 *                                            and updates the height of the tree and its total number of nodes
 *
 *                              printInOrder(): Prints all the nodes in the tree in the ascending order
 *
 *                              deleteNode(): Deletes a specific node in the tree.
                                              (Cover all cases: node with no child, node with one child, and node with two children)
 *
 *                              deleteTree(): Deletes entire tree.
 *
 *     			        3) Uncomment the commented lines only to test your work for the intermediate and advanced outcomes, otherwise
 *                         do not modify any line in main() function.
 *
 *                      4) You may add more functions for your program, however these functions must not be called from main().
 *
 *
 * Student Name: Rohan Patel
 * Student Number: 8696839
 *
 * Reference 1:           https://www.youtube.com/watch?v=gcULXE7ViZw
 * Reference 2:           https://www.youtube.com/watch?v=COZK7NATh4k&t=860s
 * Reference 3:           https://www.geeksforgeeks.org/write-a-c-program-to-delete-a-tree/
 * Reference 4:           https://www.youtube.com/watch?v=gm8DUJJhmY4
 */

#include <stdio.h>
#include <stdlib.h>



#define SCALE_FACTOR 5
int index = 0;
int a[16] = { 0 };      //array used to store nodes for second tree (intermediate outcomes)



/* Definition of tree nodes*/
typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
}treeNode;



/* Private Function Prototypes*/
void insertNode(treeNode** node, int value);
void printInOrder(treeNode* root);
void deleteNode(treeNode** root, int value);
void deleteTree(treeNode** node);
treeNode *createNewNode(int value);

void postOrderCopy(treeNode* node);
int scaleUpAndDeleteOdd(int array[], int);
void createNewTree(int* array, treeNode** root);
void printPreOrder(treeNode* root);
int treeHeight(treeNode* node);


int main()
{
    int input[15] = { 43, 68, 77, 53, 12, 8, 59, 30, 16, 74, 36, 61, 20, 94, 2 };

    treeNode* treeRoot = NULL;

    int noOfNodes = 0;      // Total number of nodes in the tree

    /* Insert nodes into the tree */
    for (int i = 0; i < 15; i++) {

        insertNode(&treeRoot, input[i]);
    }

    printf("Inorder traversal of the given tree \n");
    printInOrder(treeRoot);

    /**********Advanced Outcomes***************

    int height = treeHeight(treeRoot);

    printf("\nThe tree has a height of %i and contains %i number nodes\n", height, noOfNodes);

    ********************************************/
    printf("\n");

    /***********Intermediate Outcomes****************/

    postOrderCopy(treeRoot);        // Copy tree into the globally defined array 'a' in post-order traversal
    
    // Print out elements of array 'a'
    for (int i = 0; i < 15; i++) {

            printf("%i ", a[i]);
    }

    /***********************************************/

    printf("\n");

    /************* Advanced Outcomes ****************

    height = treeHeight(treeRoot);
    printf("\nThe tree has a height of %i and contains %i number nodes\n", height, noOfNodes);


    ************************************************/


    /***********This section is prepared to test the tree*****************/
    int test[] = { 20, 43, 59, 77, 8 };                                  //
                                                                         //   
    for (int i = 0; i < sizeof test / sizeof * test; i++) {              //
                                                                         //
        printf("\nDelete %i:", test[i]);                             //
        deleteNode(&treeRoot, test[i]);                              //

        printf("\nInorder traversal of the modified tree \n");       //
        printInOrder(treeRoot);                                      //
    }                                                                    //
    /*********************************************************************/

    //******************Adding for new line******************************
    printf("\n");
    //*******************************************************************
    
    deleteTree(&treeRoot);      // Delete first tree

    // Intermediate Outcomes
    /*****************************************/

    int numberOfElements = scaleUpAndDeleteOdd(a, SCALE_FACTOR);

    // Print out elements of array 'a' after modification
    for (int i = 0; i < numberOfElements; i++) {

            printf("%i ", a[i]);
    }

    treeNode* newTreeRoot = NULL;

    createNewTree(a, &newTreeRoot);         // Create new tree using elements of array 'a'
    printf("\nPreorder traversal of the new tree: \n");
    printPreOrder(newTreeRoot);

    deleteTree(&newTreeRoot);      // Delete second tree

    /****************************************/

    return 0;
}



// FUNCTION      : createNewNode()
// DESCRIPTION   : This function creates a new node
// PARAMETERS    :	
//		int value	 - Data/Key to be stored in the node
// RETURNS       : newNode
treeNode *createNewNode(int value) {

    treeNode* newNode = NULL;                        //Pointing to NULL
    newNode = (treeNode*)malloc(sizeof(treeNode));   // Create new node, and check if allocation was successfull
    if (newNode) {
        newNode->data = value;
        newNode->left = NULL;
        newNode->right = NULL;
    }
    return newNode;
}



// FUNCTION      : insertNode()
// DESCRIPTION   : This function creates a new node and inserts it to a given binary search tree
// PARAMETERS    :	
//		treeNode** ptrRoot  - Used to store address of root pointer
//		int value	 - Data/Key to be stored in the node
// RETURNS       : Nothing
void insertNode(treeNode** ptrRoot, int value) {

    treeNode* tempPtr = *ptrRoot;

    if (tempPtr == NULL) {
        (*ptrRoot) = createNewNode(value);
    }
    else if (value < tempPtr->data) {               // Checking the value if it is less than BST data then it 
                                                    // Stores value to left branch of BST or else to right branch 
        insertNode((&tempPtr->left), value);
    }
    else if (value > tempPtr->data) {
        insertNode((&tempPtr->right), value);
    }
}



// FUNCTION      : printInOrder()
// DESCRIPTION   : This function prints out a given binary search tree in in-order traversal
// PARAMETERS    :	
//		treeNode* root  - Pointer to root of the binary search tree
// RETURNS       : Nothing
void printInOrder(treeNode* root) {
    if (root == NULL) return;
    printInOrder(root->left);           // Applying recursion to traverse to left branch nodes
    printf("%i ",root->data);
    printInOrder(root->right);          // Applying recursion to traverse to right branch nodes
}



// FUNCTION      : deleteNode()
// DESCRIPTION   : This function deletes a specific node in the tree given a specific key
// PARAMETERS    :	
//		treeNode** ptrRoot  - Used to store address of root pointer
//              int value        - Key of node to be deleted
// RETURNS       : Nothing
void deleteNode(treeNode** ptrRoot, int value) {

    treeNode* tempPtr = *ptrRoot;
    if ((*ptrRoot) == NULL)  return;
    else if (value < (*ptrRoot)->data) {                 // if value is less than (*ptrRoot)->data then
       deleteNode((&(*ptrRoot)->left), value);          // Applying recursion to traverse to left branch nodes
    }
    else if (value > (*ptrRoot)->data) {                 // if value is greater than (*ptrRoot)->data then
        deleteNode((&(*ptrRoot)->right), value);        // Applying recursion to traverse to right branch nodes
    }
    else {
        if ((*ptrRoot)->left == NULL) {   // if node have single rightchild 
               tempPtr = *ptrRoot;
              (*ptrRoot) = (*ptrRoot)->right; // make right node as root node
              free(tempPtr);
        }
        else if ((*ptrRoot)->right == NULL) {    // if node have single leftchild 
               tempPtr = *ptrRoot;
              (*ptrRoot) = (*ptrRoot)->left;     // make left node as root node
            free(tempPtr);
        }
         else if ((*ptrRoot)->left == NULL && (*ptrRoot)->right == NULL) {    // if node have no children
             tempPtr = *ptrRoot;
             free(tempPtr);
         }
         else {  
            /*if node have both left and right child*/
             tempPtr = (*ptrRoot)->right;      //getting minimum value from right sub-tree
             while (tempPtr->left != NULL) {
                 tempPtr = tempPtr->left;
             }
             (*ptrRoot)->data = tempPtr->data;      // copying data of minimum value from right sub-tree to root node of that subtree
             deleteNode(&(*ptrRoot)->right, tempPtr->data);   
         }
    }

}



// FUNCTION      : postOrderCopy()
// DESCRIPTION   : This function copies the elements from a given binary search tree into
//                 the global array in post-order traversal.
// PARAMETERS    :	
//		treeNode* root   - Pointer to root of the binary search tree
// RETURNS       : Nothing
void postOrderCopy(treeNode* root) {
    if (root != NULL) {
        postOrderCopy(root->left);                  // Applying recursion to traverse to left branch nodes
        postOrderCopy(root->right);                 // Applying recursion to traverse to right branch nodes
        a[index++] = root->data;                    // Copying tree post-order wise into array 
    }
}



// FUNCTION      : scaleUpAndDeleteOdd()
// DESCRIPTION   : This function scales up the data field of all nodes in the tree by a factor passed to the function as an argument
//                 then deletes all the odd elements inside the array and returns the number of elements in the
//		   array after modification.                 
//                 This function should reject scale factor of 0.
// PARAMETERS    :	
//		int array[]     - Pointer to array to be scaled up
//              int scaleFactor - Scaling factor
// RETURNS       : Number of elements in the array after modification
int scaleUpAndDeleteOdd(int array[], int scaleFactor) {
    
    int elements = 15;
    for (int i = 0; i < elements; i++) {            // Multiplying scale-factor with each elements of array[]
        array[i] = array[i] * scaleFactor;
    }

    for (int i = 0;i < elements;i++) {              // Deleting odd numbers fron an array
        if (array[i] % 2 != 0) {
            int k = i + 1;
            for (int j = i; j < elements ;j++) {
                array[j] = array[k];
                k++;
            }
            i--;
         elements--;
        }
    }
 return (elements);           
}



// FUNCTION      : createNewTree()
// DESCRIPTION   : This function creates a new BST using the elements from the new modified array (maintaining the post-order traversal). 
// PARAMETERS    :	
//		int* array     - Pointer to array to retreive data of nodes for the new tree
//              treeNode** ptrRoot  - Used to store address of root pointer
// RETURNS       : Nothing
void createNewTree(int* array, treeNode** ptrRoot) {
    treeNode* tempPtr = NULL;
    for (int i = 0; i < 10;i++) {                
        insertNode(&tempPtr, array[i]);             // inserting node in new tree with elements of array 
        (*ptrRoot) = tempPtr;
    }
   
}



// FUNCTION      : printPreOrder()
// DESCRIPTION   : This function prints out a given binary search tree in pre-order traversal
// PARAMETERS    :	
//		treeNode* root   - Pointer to root of the binary search tree
// RETURNS       : Nothing
void printPreOrder(treeNode* root) {
    if (root == NULL) return;
    printf("%i ",root -> data );
    printPreOrder(root->left);                       // Applying recursion to traverse to left branch nodes
    printPreOrder(root->right);                      // Applying recursion to traverse to right branch nodes
}



// FUNCTION      : treeHeight()
// DESCRIPTION   : This function finds and returns the height of a gievn binary search tree.
// PARAMETERS    :	
//		treeNode* root   - Pointer to root of the binary search tree
// RETURNS       : Height of tree
int treeHeight(treeNode* root) {
    return 0;
}



// FUNCTION      : deleteTree()
// DESCRIPTION   : This function deletes all nodes for a given binary search tree
// PARAMETERS    :	
//		treeNode** ptrRoot   - Used to store address of root pointer
// RETURNS       : Nothing
void deleteTree(treeNode** ptrRoot) {
    treeNode* tempPtr = *ptrRoot;
    if (*ptrRoot == NULL) return;
    deleteTree(&(*ptrRoot)->left);               // Applying recursion to traverse to left branch nodes 
    deleteTree(&(*ptrRoot)->right);             // Applying recursion to traverse to right branch nodes
    tempPtr = (*ptrRoot);
    free(tempPtr);                            // Free tempPtr 
}
