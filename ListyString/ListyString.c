// Sebastian Gilarranz
// COP 3502, Fall 2018
// se171788
// Program 3

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "ListyString.h"

#define string_size 1024

// Handy-dandy Helper function
ListyNode *find_tail(ListyString *str)
{
	ListyNode *curr;

	if (str->head == NULL)
		return NULL;
	
	for (curr = str->head; curr->next != NULL; curr = curr->next)
		;

	return curr;
}

void printListyString(ListyString *listy)
{
	ListyNode *curr;
	
	// Check if listy is null.
	if (listy == NULL)
	{
		printf("(empty string)\n");
		
		return;
	}

	// If listy wasnt NUll but listy->head is NULL.(Cannot check with listy because would cause segfault.)
	else if (listy->head == NULL)
	{
		printf("(empty string)\n");
		
		return;
	}

	// If listy has information loop through while printhing data stored. 
	else
	{
		for (curr = listy->head; curr != NULL; curr = curr->next)
			printf("%c", curr->data);

		printf("\n");
	}

}

int listyLength(ListyString *listy)
{
	// Check if listy is NULL.
	if (listy == NULL)
		return -1;
	
	// If not return the current length of Listy.
	else 
		return listy->length;
}

int listyCmp(ListyString *listy1, ListyString *listy2)
{
	// Create Local nodes to hold listyString data.
	ListyNode *one, *two;
	int equal = 0;

	if (listy1 == NULL && listy2 == NULL)
		return 0;
	
	else if (listy1 == NULL || listy2 == NULL)
		return -1;
	
	else if (listy1->head == NULL && listy2->head == NULL)
		return 0;
	
	else if (listy1->length == listy2->length)
	{
		// Set one and two equal to 
		// head of their corresponding ListyStrings. 
		one = listy1->head; 
		two = listy2->head;
		
		// Do listy length # of iterations to check if 
		// information is equal.
		for (int i = 0; i < listy1->length; i++)
		{	
			// If they arent equal.
			if (one->data != two->data)
			{
				return -1;
			}
			
			// Go to next node in linked lists.
			one = one->next;
			two = two->next;
		}
		
		return 0;
	}

	else 
		return -1;

}

void reverseListyString(ListyString *listy)
{
	// Create local nodes.
	ListyNode *prev = NULL, *curr, *next = NULL;

	if (listy == NULL || listy->head == NULL)
		return;
	
	curr = listy->head; // Set curr to listy->head
	
	while (curr != NULL) // While until curr == NULL;
	{ 
		next = curr->next; // Set next to curr's next node
		curr->next = prev; // Set curr's next node to previous node.
		prev = curr; // Set pervious to current node. 
		curr = next; // Set current node to next.
	}

	listy->head = prev; // after everything set listy->head as prev node.
}

ListyString *listyCat(ListyString *listy, char *str)
{
	ListyNode *curr, *str_head, *head, *tail; // local nodes
	ListyString *str_list; // create local ListyString

	if (str == NULL)
	{
		if (listy == NULL) // Both listy and Str are null so we return NULL
			return NULL;
		
		else if (listy != NULL) // Here str is NULL but Listy is not so we just return Listy.
			return listy;
		
	}

	else 
	{
		if (listy == NULL) // Str wasnt NULL but Listy is so we create/return a new ListyString with str.
		{
			return createListyString(str);
		}

		else // for all other cases.
		{
			// Str wasnt NUll and listy wasnt null so now check if Listy->head is null.
			if (listy->head == NULL) 
			{
				// we are going to create a listyString from the str and append 
				// to end of Listy. 
				str_list = createListyString(str); 
				listy->head = str_list->head;
				listy->length = (listy->length + str_list->length);
				
				// Can't forget to free that temporary ListyString
				free(str_list);
			}

			else
			{
				// we are going to create a listyString from the str and append 
				// to end of Listy. 
				str_list = createListyString(str);
				str_head = str_list->head;
				head = listy->head;
				tail = find_tail(listy); // find tail.
				tail->next = str_head;
				listy->head = head;
				listy->length = (listy->length + str_list->length); // update length of listy

				// Can't forget to free that temporary ListyString
				free(str_list);
			}
		}
	}
	
	return listy;
}

void replaceChar(ListyString *listy, char key, char *str)
{
	// create local nodes and ListyString.
	ListyString *str_list;
	ListyNode *head, *temp, *curr, *prev, *str_tail, *str_head;

	if (listy == NULL || listy->head == NULL)
		return;
	
	head = listy->head;
	prev = head;
	
	// Checking to see if Str is null or empty.
	if (str == NULL || strcmp(str, "") == 0)
	{		
		curr = listy->head;
		
		while (curr != NULL)
		{
			// If head is equal to key and curr == head
			if (head->data == key && curr == head)
			{
				// set head to next node
				temp = head;
				head = head->next;
				curr = head;
				prev = head;
				free(temp); // free curr node(head)
				listy->length--; // update length counter
				
				continue; // go to next iteration
			}

			// We got a match!
			else if (curr->data == key)
			{
				// set curr to temp, and prev->next to curr->next
				// to delete curr node
				temp = curr;
				prev->next = curr->next;
				curr = prev->next;
				free(temp); // free(curr) node
				listy->length--; // update length counter
				
				continue; // go to next iteration
			}
		
			// update nodes to the next node.
			prev = curr;
			curr = curr->next;
		}
		
		listy->head = head;

	}

	// Str isnt null and string isnt an empty string.
	else if (str != NULL && strcmp(str,"") != 0)
	{

		// For to loop through nodes.
		for (curr = listy->head; curr != NULL; curr = curr->next)
		{
			// If head is a match and curr == head
			// we do curr == head incase new strings head is a match.
			if (head->data == key && curr == head)
			{
				// We are going to create a new ListyString which contains
				// str and make the tail->next point to old head.
				str_list = createListyString(str);
				str_tail = find_tail(str_list);
				str_tail->next = head->next;
				str_head = str_list->head;
				temp = head;
				head = str_head;
				curr = str_tail;
				prev = str_tail;
				
				free(temp); 
				listy->length = (listy->length + (str_list->length - 1)); // update length counter
				free(str_list); // free new ListyString
				
				// go to next iteration
				continue;
			}

			// If we get a match thats not head
			else if (curr->data == key)
			{
				// We are going to create a new listy string which contains
				// str and make old prev point to new ListyString head and 
				// newListryString tail->next point to old curr->next.
				str_list = createListyString(str);
				str_tail = find_tail(str_list);
				str_head = str_list->head;
				prev->next = str_head;
				str_tail->next = curr->next;
				temp = curr;
				curr = str_tail;
				prev = str_tail;
				
				free(temp); 
				listy->length = (listy->length + (str_list->length - 1)); // update length counter.
				free(str_list); // free new ListyString

				// go to next iteration
				continue; 
			}

			prev = curr;
		}

		listy->head = head;
	}
}

ListyString *cloneListyString(ListyString *listy)
{
	// create local node and ListyString
	ListyNode *head1, *head2;
	ListyString *newListyString;

	if (listy == NULL)
		return NULL;
	
	// allocate memory for new ListyString components.
	newListyString = malloc(sizeof(ListyString));
	newListyString->head = malloc(sizeof(ListyNode));
	
	// assign length and head for new ListyString.
	newListyString->length = 0; 
	head2 = listy->head;

	if (listy->head == NULL)
	{
		newListyString->head = NULL;
		return newListyString;
	}
	
	head1 = newListyString->head;

	// for loop to go through each node using length.
	for (int i = 0; i < listy->length; i++)
	{
		head1->data = head2->data; // Assign data from list1 to list2 
		newListyString->length++;

		// check to see if we should stop allocating in order to not overallocate 
		// and possible segfault.
		if (i != listy->length - 2)
		{
			head1->next = malloc(sizeof(ListyNode)); // allocate next node.
			
			// go to next node.
			head1 = head1->next;
			head2 = head2->next;
		}
		
		head1->next = NULL; 
	}

	return newListyString;
}

ListyString *destroyListyString(ListyString *listy)
{
	// local variables
	ListyNode *head, *temp;

	if (listy == NULL)
		return NULL;

	head = listy->head;

	// Loop through ndoes
	while (head != NULL)
	{
		// set head to temp, go to next node, free (temp).
		temp = head;
		head = head->next;
		free(temp);
	}
	
	// Cant forget to free the ListyString!
	free(listy); 

	return NULL;
}

ListyString *createListyString(char *str)
{
	// Local Variables
	ListyNode *head, *tail;

	ListyString *newListyString = malloc(sizeof(ListyString)); // Allocating memory for the new ListyString to be created. 

	if (str == NULL || strcmp(str, "") == 0)
	{
		// Setting the appropiate values for the case.
		newListyString->head = NULL;
		newListyString->length = 0;
		
		return newListyString;
	}
	
	// Allocating head since we dont have null Strings. 
	newListyString->head = malloc(sizeof(ListyNode)); 
	
	newListyString->length = 0; // Update variables.
	tail = newListyString->head;

	// Was getting weird newLine from txt but not when Str passed through other functions
	// we take into account both cases.
	if (str[strlen(str) - 1] == '\n')
	{
		// Loop through letters and allocate and assign 
		// data corresponding. 
		for (int i = 0; str[i] != '\n'; i++)
		{
			tail->data = str[i];
			newListyString->length++;

			if(str[i + 1] != '\n')
			{
				tail->next = malloc(sizeof(ListyNode));
				tail = tail->next;
			}

		}
		tail->next = NULL;
	}

	// Same as above, except if no newLine appears. 
	else 
	{
		// Loop through nodes.
		for (int i = 0; i < strlen(str); i++)
		{
			tail->data = str[i];
			newListyString->length++;
			tail->next = NULL;

			if (str[i + 1] == '\0')
				break;

			tail->next = malloc(sizeof(ListyNode));
			tail = tail->next;

		}

	}

	return newListyString;
}

int processInputFile(char *filename)
{
	// Local variables
	ListyString *theListyString, *testclone;
	char *string, *token, *token2, comm;

	FILE *open_file = fopen(filename, "r"); // Opening file. 


	if (open_file == NULL)
		return 1;


	string = malloc(sizeof(char) * string_size); // Allocate memory for string.
	
	fgets(string, string_size, open_file); 
	
	theListyString = createListyString(string); // creating new Listry String to work with.

		// Looping through file.
		while ((comm = fgetc(open_file)) != EOF)
		{
			fgets(string, string_size, open_file);

			// Where we see what command we are using based on character read.
			switch (comm)
			{
				case '@':
				token = strtok(string, " ");
				token2 = strtok(NULL, " ");
				replaceChar(theListyString, token[0], token2);
				break;

				case '+':
				token2 = strtok(string, " ");
				listyCat(theListyString, token2);
				break;

				case '-':
				token = strtok(string, " ");
				replaceChar(theListyString, token[0], "");
				break;

				case '~':
				reverseListyString(theListyString);
				break;

				case '?':
				printf ("%d\n", listyLength(theListyString));
				break;

				case '!':
				printListyString(theListyString);
				break;
			}
		}
	
	// cant forget to clean up after ourselves!
	fclose(open_file); 
	free(string);
	destroyListyString(theListyString);

	return 0;
}

int main(int argc, char **argv)
{
	processInputFile(argv[1]); // Easy peasy pass filename to be opened.

	return 0;
}


double difficultyRating(void)
{
	return 4; // :,(
}

double hoursSpent(void)
{
	return 40; // :((((
}

