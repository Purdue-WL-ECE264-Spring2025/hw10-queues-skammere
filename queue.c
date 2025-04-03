#include "queue.h"
#include "tile_game.h"
#include <stdlib.h>

int check_in_list(struct linked_list, size_t);

void enqueue(struct queue *q, struct game_state state) 
{
   uint64_t curState = serialize(state);
   //printf("expected retVal = %d\n", curState);
   if (q->data.head == NULL)
   {
      insert_at_head(&(q->data), curState);
   }
   else
   {
      insert_at_tail(&(q->data), curState);
   }
}

struct game_state dequeue(struct queue *q) 
{
   
   return(deserialize(remove_from_head(&(q -> data))));
    
}

int number_of_moves(struct game_state start) 
{
   int rows = 4;
   int cols = 4;

   struct linked_list visited = {.head = NULL};
   struct linked_list ll = {.head = NULL};
   struct queue q = {.data = ll};
   struct game_state curState = start;
   //q.data.head = serialize(curState);
   enqueue(&q, curState);
   insert_at_head(&visited, (serialize(curState)));
  
   while (q.data.head != NULL)
   {
      int done = 1;
      curState = dequeue(&q); 
     
      //printf("curState.empty_row == %d, curState.empty_col == %d\n", curState.empty_row, curState.empty_col);        
      
      if (curState.empty_col != 3 || curState.empty_row != 3)
      {
         done = 0;
      }
      
      
      for (int r = 0; r < rows; r++)
      {
         for (int c = 0; c < cols; c++)
         {
            if ((curState.tiles)[r][c] != (c + r*4 +1) && !(r == 3 && c == 3 && curState.tiles[r][c] == 0))
            {
               done = 0;
               break;
            }
         }
         if (!done)
         {
            break;
         }
      }
      
      if (done)
      {
         free_list(visited);
         free_list(q.data);
         return (curState.num_steps);
      }
       
            
      struct game_state * movedUp = malloc(sizeof(struct game_state));
      *movedUp = curState;
      move_up(movedUp);
      if (movedUp -> empty_row != curState.empty_row && !(check_in_list(visited, serialize(*movedUp))))
      {
         enqueue(&q, *movedUp);
         insert_at_tail(&visited, serialize(*movedUp));
      }
      free(movedUp);
      //else
      //{
      //   free(movedUp);
      //}      
      
      struct game_state * movedDown = malloc(sizeof(struct game_state));
      *movedDown = curState;
      move_down(movedDown);
      if (movedDown -> empty_row != curState.empty_row && !(check_in_list(visited, serialize(*movedDown))))
      {
         enqueue(&q, *movedDown);
         insert_at_tail(&visited, serialize(*movedDown));
      }
      free(movedDown);
      //else
      //{
      //   free(movedDown);
      //}
      
  
      struct game_state * movedRight = malloc(sizeof(struct game_state));
      *movedRight = curState;
      move_right(movedRight);
      if (movedRight -> empty_col != curState.empty_col && !(check_in_list(visited, serialize(*movedRight))))
      {
         enqueue(&q, *movedRight);
         insert_at_tail(&visited, serialize(*movedRight));
      }
      free(movedRight);
      //else
      //{
      //   free(movedRight);
      //}
      
      
      struct game_state * movedLeft = malloc(sizeof(struct game_state));
      *movedLeft = curState;
      move_left(movedLeft);
      if (movedLeft -> empty_col != curState.empty_col && !(check_in_list(visited, serialize(*movedLeft))))
      {
         enqueue(&q, *movedLeft);
         insert_at_tail(&visited, serialize(*movedLeft));
      }
      free(movedLeft);
      //else
      //{
      //   free(movedLeft);
      //}
      
      
   }
   return 0;             
}

int check_in_list(struct linked_list list, size_t key)
{
   struct list_node * cur = list.head;
   while(cur != NULL)
   {
      //printf("board 1:\n");
      //print_board(deserialize(cur -> value));
      //printf("board 2:\n");
      //print_board(deserialize(key));

      if (cur -> value == key)
      {
         //printf("boards are the same\n");
         return 1;
      }
      //cur = cur -> next;
      /*
      struct game_state curState = deserialize(cur -> value);
      struct game_state keyState = deserialize(key);

      int count = 0;
      for (int r = 0; r < 4; r++)
      {
         for (int c = 0; c < 4; c++)
         {
            if (curState.tiles[r][c] == keyState.tiles[r][c])
            {
                count++;
            }
            else
            {
               break;
            }
         }
      }
      if (count == 16)
      {
         //printf("boards are the same\n");
         return 1;
      }
      */
      cur = cur -> next;
  
   }
   //printf("boards are different\n");
   return 0;
}


/*
void print_board(struct game_state curState)
{
   for (int r = 0; r < 4; r++)
   {
      for (int c = 0; c < 4; c++)
      {
          printf("%d ", curState.tiles[r][c]);
      }
      printf("\n");
   }
   printf("\n");
}
*/
