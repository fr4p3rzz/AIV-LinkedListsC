#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

struct node {
   int data;
   int key;
   struct node *next;
   struct node *prev;
};

struct node *head = NULL;
struct node *current = NULL;
struct node *tail = NULL;

// ALlocate memory for a new node
struct node *alloc_node(int key, int data)
{
   struct node *link = (struct node*) malloc(sizeof(struct node));
	
   link->key = key;
   link->data = data;

   return link;
}

// Check if list is empty
bool isEmpty() 
{
   return head == NULL;
}

// Get the last node of the list
struct node *get_tail(struct node *head)
{
   struct node *ptr = head;

   if(ptr)
   {
      //start from the beginning
      while(ptr->next != NULL) 
      {
         ptr = ptr->next;
      }

      tail = ptr;
   }
	
   return tail;
}

// Insert link at the first location
void insert_head(int key, int data) 
{

   // Create a link
   struct node *link = alloc_node(key, data);

   if(isEmpty()) 
   {
      //make it the last link
      tail = link;
   } 
   else 
   {
      //update first prev link
      head->prev = link;
   }

   //point it to old first link
   link->next = head;
	
   //point first to new first link
   head = link;
   
}

// Insert link at the last location
void insert_tail (int key, int data)
{
   // Create a link
   struct node *link = alloc_node(key, data);

   if (!tail)
   {
      head = link;
      tail = link;
   }
   else
   {
      tail->next = link;
   }

   link->prev = tail;
   tail = link;
   tail->next = NULL;
}

// Return the current length of the list
int list_length(struct node *head) 
{
   int length = 0;
   struct node *current;
	
   for(current = head; current != NULL; current = current->next) 
   {
      length++;
   }
	
   return length;
}

//find a node with given key
struct node* find_node(int key) 
{

   //start from the first link
   struct node* current = head;

   //if list is empty
   if(head == NULL) 
   {
      return NULL;
   }

   // Navigate through list
   while(current->key != key) 
   {
	
      // If it is last node, exit
      if(current->next == NULL) 
      {
         return NULL;
      } 
      else 
      {
         // If not, go to next link
         current = current->next;
      }
   }      
	
   // If there's a match, return the current Link
   return current;
}

// Find all nodes that share a given key
struct node* find_all(int key)
{

   // If list is empty, exit
   if(head == NULL) 
   {
      return NULL;
   }

   // Start from the first link
   struct node *current = head;

   // Create a head node for resulting list
   struct node *result = NULL;
 
   // Navigate through list
   while(current != NULL)
   {
      if(current->key == key)
      {
         struct node *link = (struct node*) malloc(sizeof(struct node));
         link = memcpy(link, current, sizeof(struct node));
         link->next = result;
         result = link; 
      }
      current = current->next;
   }

   return result;
}

// Display the list
void print_list() 
{
   struct node *ptr = head;
   printf("\n[ ");
	
   // Start from the beginning
   while(ptr != NULL) 
   {
      printf("(key: %d, data: %d) ",ptr->key,ptr->data);
      ptr = ptr->next;
   }
	
   printf(" ]");
}

// Delete first item
struct node* delete_head() 
{
   // Save reference to first link
   struct node *tempLink = head;
	
   // Mark next to first link as first 
   head = head->next;
   // Return the deleted link
   return tempLink;
}

// Delete last item
struct node* delete_tail() 
{
   // Save reference to first link
   struct node *tempLink = get_tail(head);
   struct node *new_tail = tempLink->prev;

   // Destroy the current last node, making new_tail the new last
   free(new_tail->next);
   new_tail->next = NULL;
   tail = new_tail;
	
   // Return the deleted link
   return tempLink;
}

// Delete a link with given key
struct node* delete_node(int key) 
{

   // Start from the first link
   struct node* current = head;
   struct node* previous = NULL;
	
   // If list is empty
   if(head == NULL) 
   {
      return NULL;
   }

   // Navigate through list
   while(current->key != key) 
   {
      // If it is last node
      if(current->next == NULL) 
      {
         return NULL;
      } 
      else 
      {
         // Store reference to current link
         previous = current;
         // Move to next link
         current = current->next;
      }
   }

   // Found a match, update the link
   if(current == head) 
   {
      // Change first to point to next link
      head = head->next;
   } 
   else 
   {
      // Bypass the current link
      previous->next = current->next;
   }    
	
   free(previous);
   return current;
}

// Wipe all the list and free the memory
void wipe_list()
{
   struct node *temp = NULL;
   while(!isEmpty()) 
   {            
      temp = delete_head();
   }  

   free(head);
   free(current);
   free(tail);
   head = NULL;
   current = NULL;
   tail = NULL;
}

// Sort the list by data (smaller to bigger)
void sort() 
{

   int i, j, k, tempKey, tempData;
   struct node *current;
   struct node *next;
	
   int size = list_length(head);
   k = size ;
	
   for ( i = 0 ; i < size - 1 ; i++, k-- ) 
   {
      current = head;
      next = head->next;
		
      for ( j = 1 ; j < k ; j++ ) 
      {   

         if ( current->data > next->data ) 
         {
            tempData = current->data;
            current->data = next->data;
            next->data = tempData;

            tempKey = current->key;
            current->key = next->key;
            next->key = tempKey;
         }
			
         current = current->next;
         next = next->next;
      }
   }   
}

// Sort the list by key value (smaller to bigger)
void sort_key() 
{

   int i, j, k, tempKey, tempData;
   struct node *current;
   struct node *next;
	
   int size = list_length(head);
   k = size ;
	
   for ( i = 0 ; i < size - 1 ; i++, k-- ) 
   {
      current = head;
      next = head->next;
		
      for ( j = 1 ; j < k ; j++ ) 
      {   

         if ( current->key > next->key ) 
         {
            tempData = current->data;
            current->data = next->data;
            next->data = tempData;

            tempKey = current->key;
            current->key = next->key;
            next->key = tempKey;
         }
			
         current = current->next;
         next = next->next;
      }
   }   
}

// Reverse the current order of the list
void reverse(struct node** head_ref) 
{
   struct node* prev = NULL;
   struct node* current = *head_ref;
   struct node* next;
	
   while (current != NULL) {
      next  = current->next;
      current->next = prev;   
      prev = current;
      current = next;
   }
	
   *head_ref = prev;
}

// Test if the shuffle has generated some bugs
void testshuffle(struct node *nodes[])
{
   int length =  list_length(nodes[0]);
   bool result = true;
   int key;
   
   for(int i = 0; i < length; i++)
   {
      key = nodes[i]->key;
      for(int j = 0; j < length; j++)
      {
         if(nodes[j]->key == key && nodes[j] != nodes[i])
         {
            result = false;
         }
      }
   }

   printf("[%d]", result);
}

// Shuffle the list
void shuffle(struct node *head, int shuffles)
{
   struct node* current = head;
   int length = list_length(current);
   struct node *nodes[length];

   // Create an array of pointers where each cell point to a node of the list
   for(int i = 0; i < length; i++)
   {
      nodes[i] = current;
      current = current->next;
   }

   //testshuffle(nodes);

   // Shuffle the array
   int rand_int = 0;
   while(shuffles > 0)
   {
      for(int i = 0; i < length; i++)
      {
         rand_int = rand() % length;
         struct node *temp = nodes[i];
         nodes[i] = nodes[rand_int];
         nodes[rand_int] = temp;   
      }
      shuffles--;
   }
   
   // Rebuild the list with the new order
   wipe_list();
   for(int i = 0; i < length; i++)
   {
      insert_head(nodes[i]->key, nodes[i]->data);
   }

   // Update the tail 
   nodes[0] = tail;
}



int main() 
{
   insert_tail(7, 70);
   insert_tail(8, 80); 
   insert_tail(9, 9); 

   insert_head(1,25);
   insert_head(2,20);
   insert_head(3,30);
   insert_head(4,1);
   insert_head(5,40);
   insert_head(6,56); 

   printf("Original List: "); 
   print_list();
   printf("\n\n");

   printf("Sorted by data: "); 
   sort();
   print_list();
   printf("\n\n");

   printf("Sorted by key: "); 
   sort_key();
   print_list();
   printf("\n\n");

   printf("Reverse the list order: ");
   reverse(&head);
   print_list();
   printf("\n\n");

   srand(time(NULL));
   printf("First shuffle: ");
   shuffle(head, 1);
   print_list();
   printf("\n\n");

   printf("Second shuffle: ");
   shuffle(head, 2);
   print_list();
   printf("\n\n");

   printf("Third shuffle: ");
   shuffle(head, 3);
   print_list();
   printf("\n\n");

   printf("Last value: %d %d\n", tail->key, tail->data);

   delete_tail();
   printf("Last value after tail deleted: key = %d data = %d\n", tail->key, tail->data);

   insert_tail(10, 100);
   printf("Last value after new tail insert: key = %d data = %d\n", tail->key, tail->data);

   delete_head();
   printf("First value after head deleted: key = %d value = %d\n", head->key, head->data);

   printf("\nCurrent list:");
   print_list();
   printf("\n\n");


   wipe_list();
	
   printf("List after deleting all items: ");
   print_list();

   insert_tail(1,10);
   insert_tail(5,40);
   insert_tail(3,36);

   insert_head(2,20);
   insert_head(3,30);
   insert_head(3,33);
   insert_head(3,39);
   insert_head(4,1);
   insert_head(6,56);
   
   printf("\n\nNew List: ");
   print_list();
   printf("\n\n");  

   struct node *found_node = find_node(4);
	
   if(found_node != NULL) 
   {
      printf("Node found: ");
      printf("(%d,%d) ",found_node->key,found_node->data);
      printf("\n\n");  
   } 
   else 
   {
      printf("Node not found.\n\n");
   }

   delete_node(4);
   printf("List after deleting an item: ");
   print_list();
   printf("\n\n");

   found_node = find_node(4);
   if(found_node != NULL) 
   {
      printf("Node found: ");
      printf("(%d,%d) ",found_node->key,found_node->data);
      printf("\n\n");
   } 
   else 
   {
      printf("Node not found.\n\n");
   }

   struct node *found_list = find_all(3);
   if(found_list != NULL) 
   {
      printf("found %d Nodes: ", list_length(found_list));
      while(found_list != NULL)
      {
         printf("(key: %d, data: %d) ",found_list->key,found_list->data);
         found_list = found_list->next;
      }
      printf("\n");
   } 
   else 
   {
      printf("Node not found.\n");
   }
}