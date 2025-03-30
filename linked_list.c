#include "linked_list.h"

#include <stdlib.h>

struct list_node *new_node(size_t value) 
{
   struct list_node * node = malloc(sizeof(struct list_node));
   node -> value = value; 
   return node;   
}

void insert_at_head(struct linked_list *list, size_t value) 
{
   
   struct list_node * node = new_node(value); 
   node -> next = list -> head;
   list -> head = node;  
}

void insert_at_tail(struct linked_list *list, size_t value) 
{
   struct list_node * node = new_node(value);
   node -> next = NULL;
   struct list_node * cur = list -> head;

   if (list -> head == NULL)
   {
      list -> head = node;
      return; 
   }   
   while (cur->next != NULL)
   {
      cur = cur -> next;
   }
    
   cur->next = node; 
   //node -> next = NULL; 
   
}

size_t remove_from_head(struct linked_list *list) 
{
   struct list_node * toDelete = list -> head;
   size_t retVal = toDelete -> value;
   list -> head = list -> head -> next; 
   free(toDelete);
   //printf("returning %ld\n", retVal);
   return retVal;
}

size_t remove_from_tail(struct linked_list *list)
{
  struct list_node * cur = list -> head;
  struct list_node * old = NULL;

  while (cur -> next != NULL)
  {
     old = cur; 
     cur = cur -> next;
  }
  struct list_node * toDelete = cur;
  size_t retVal = toDelete -> value; 
  old -> next = NULL; 
  free(toDelete);  
  return retVal;

}

void free_list(struct linked_list list) 
{
   struct list_node * cur = list.head;
   while (cur != NULL)
   {
      struct list_node * toDelete = cur;
      cur = cur -> next;
      free(toDelete);
   }
}
/*
void print_list(struct linked_list list)
{
   struct list_node * cur = list.head;
   while(cur != NULL)
   {
      printf("%ld -> ", cur->value);
      cur = cur -> next;
      
   }
   printf("\n");
}

int check_in_list(struct linked_list list, size_t key)
{ 
   struct list_node * cur = list.head; 
   while( cur != NULL)
   {
      //printf("here in check in list\n");
      if (cur -> value == key)
      {
         printf("here in check in list\n");
         return 1;
      }
      cur = cur -> next;
   }
   return 0;
}


void test_list()
{
   printf("first test: test insert at head");
   struct linked_list * list = malloc(sizeof(struct linked_list));
   insert_at_head(list, 4);
   insert_at_head(list, 5);
   insert_at_head(list, 6);
   printf("expected list: 6 -> 5 -> 4\n");
   printf("actual list: ");
   dump_list(stderr, *list);

   printf("\n");   

   printf("second test: test insert at tail\n");
   struct linked_list * list2 = malloc(sizeof(struct linked_list));
   printf("here1\n");
   insert_at_tail(list2, 4);
   printf("here2\n");
   dump_list(stderr, *list2);
   insert_at_tail(list2, 5);
   dump_list(stderr, *list2);
   insert_at_tail(list2, 6);
   dump_list(stderr, *list2);
   printf("expected list: 4 -> 5 -> 6\n");
   printf("actual list: ");
   dump_list(stderr, *list2);
  
   printf("\n");
 
   printf("third test: test mix of insert at tail and head");
   struct linked_list * list3 = malloc(sizeof(struct linked_list));
   insert_at_head(list3, 4);
   insert_at_head(list3, 5);
   insert_at_tail(list3, 3);
   insert_at_head(list3, 6);
   printf("expected list: 6 -> 5 -> 4 -> 3\n");
   printf("actual list: ");
   dump_list(stderr, *list3);

   printf("\n");
 
   printf("fourth test: test remove from head");
   remove_from_head(list3);
   remove_from_head(list3);
   printf("expected list: 4 -> 3\n");
   printf("actual list: ");
   dump_list(stderr, *list3);

   printf("\n");
  
   printf("fifth test: test remove from tail");
   remove_from_tail(list2);
   remove_from_tail(list2);
   printf("expected list: 4\n");
   printf("actual list: ");
   dump_list(stderr, *list2);
}
*/
// Utility function to help you debugging, do not modify
void dump_list(FILE *fp, struct linked_list list) {
  fprintf(fp, "[ ");
  for (struct list_node *cur = list.head; cur != NULL; cur = cur->next) {
    fprintf(fp, "%zu ", cur->value);
  }
  fprintf(fp, "]\n");
}
