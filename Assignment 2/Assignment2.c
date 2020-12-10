// Sebastian Gilarranz
// COP 3502, Fall 2018
// se171788
// Program 4

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "KindredSpirits.h"

// Here we are inserting the tree into an array in preorder, recursevly.
void insertPreorder(node *a, int *list, int *count)
{
	// If a is NULL we reached end and return.
	if (a == NULL)
		return;
	
	list[(*count)++] = a->data; // Insert data to array.
	
	// Recursive calls on left and right side of tree. 
	insertPreorder(a->left, list, count); 
	insertPreorder(a->right, list, count);
}

// Here we are inserting the tree into an array in postorder, recursevly.
void insertPostorder(node *a, int *list, int *count)
{
	// If a is NULL we have reached end and return.
	if (a == NULL)
		return;
	
	// Recursive calls on left and right side of tree.
	insertPostorder(a->left, list, count);
	insertPostorder(a->right, list, count);
	
	// Insert data to array.
	list[(*count)++] = a->data; 
}

// Dynamically allocting memory for array after fiding its size.
int *createArray(int *array, int size)
{
	// Dynamically allocate memory using size of tree.
	array = malloc(sizeof(int) * size);
	
	if (array == NULL)
		return NULL;
	
	return array;
}

// Find out if trees are equal using pre-made arrays, recursively.
int areEqual(int *pre, int *post, int *count, int size)
{
	// Check if end of array.
	if (*count == size) 
		return 1;

	// If not equal, return 0.
	else if (pre[*count] != post[*count])
		return 0;

	// Increment count using pointers. 
	(*count)++; 
	
	return areEqual(pre, post, count, size);
}

// Find the tree size, recursively.
int TreeSize(node *a)
{
	// Check if we hit last node and add nothing.
	if (a == NULL)
		return 0;

	// Loop through tree adding one at every step.
	return TreeSize(a->left) + TreeSize(a->right) + 1;
}

// Find out if tree is reflective, recursively.
int isReflection(node *a, node *b)
{
	// Check if either tree is NULL.
	if (a == NULL && b == NULL)
		return 1;
	
	// If arrived to this point both cannot be NULL 
	// but one can still be NULL so we check.
	else if (a == NULL || b == NULL)
		return 0;

	// Now we just check if data is equal.
	else if (a->data != b->data)
		return 0;

	// Check to see if Left side of node equals left 
	// side of node and vice versa.
	return isReflection(a->left, b->right) + isReflection(a->right, b->left);

}

// Create a reflection of array, recursively.
node *makeReflection(node *root)
{
	node *head;

	// Check if root is NULL, return NULL if yes.
	if (root == NULL)
		return NULL;
	
	// Dynamically allocate memory for new tree.

	head = malloc(sizeof(node));
	
	// Check if malloc failed.
	if (head == NULL)
		return NULL;
	
	// Reflect recursively.
	head->data = root->data;
	head->left = (makeReflection(root->right));
	head->right = (makeReflection(root->left));
	
	return head;
}

// Find out of two trees are KindredSpirits, using various helper functions.
int kindredSpirits(node *a, node *b)
{
	// Declare and intialize all pointers.
	// Declare and initialize integers.
	int *pre1 = NULL , *post1 = NULL, *pre2 = NULL, *post2 = NULL, *ptr = NULL;
	int size = 0, count = 0, retValue;

	// Check if trees are NULL and return 1.
	if (a == NULL && b == NULL)
		return 1;
	
	// If one is NULL but not both return 0.
	else if (a == NULL || b == NULL)
		return 0;
	
	// If the size of the trees are not equal then they cannot be equal.
	else if ((size = TreeSize(a)) != TreeSize(b))
		return 0;
	
	else 
	{
		// Create arrays to be used to compare trees.
		pre1 = createArray(pre1, size);
		post1 = createArray(post1, size);
		
		// If arrays are NULL then malloc failed.
		if(pre1 == NULL && post1 == NULL)
			return 0;

		// Point ptr to count and insert tree values
		// to array in desired order.
		ptr = &count;
		insertPreorder(a, pre1, ptr);
		*ptr = 0;
		insertPostorder(b, post1, ptr);
		
		// set ptr to 0 so we can use as counter.
		*ptr = 0;

		// Use helper function to see if trees are equal.
		retValue = areEqual(pre1, post1, ptr, size);
		
		// Have to clean up our mess.
		free(pre1);
		free(post1);

		if (retValue)
			return 1;

		// If first arrays arent kindred spirits we 
		// have to check with swapped oredr.
		pre2 = createArray(pre2, size);
		post2 = createArray(post2, size);
		
		// If arrays are NULL then malloc failed.
		if(pre2 == NULL && post2 == NULL)
			return 0;
		
		// Point ptr to count and insert tree values
		// to array in desired order.
		*ptr = 0;
		insertPreorder(b, pre2, ptr);
		*ptr = 0;
		insertPostorder(a, post2, ptr);
		
		// Do last comparison and return result.
		*ptr = 0;
		retValue = areEqual(pre2, post2, ptr, size);
		
		// Have to clean up our mess.
		free(pre2);
		free(post2);
		
		return retValue;
	}
}

double difficultyRating(void)
{
	return 3;
}

double hoursSpent(void)
{
	return 6;
}

