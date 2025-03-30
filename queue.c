#include "queue.h"
#include "tile_game.h"
#include <stdlib.h>

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
   
   //printf("q.data.head == NULL = %d\n", q.data.head == NULL);
   while (q.data.head != NULL)
   {
      //printf("current queue:\n");
      //dump_list(stderr, q.data);
      //print_list(q.data);
      //printf("visisted:\n");
      //dump_list(stderr, visited);
      //print_list(visited);

      int done = 1;
      curState = dequeue(&q); 
      //printf("current board\n");
      //print_board(curState);

      //printf("current state: %ld\n", serialize(curState));  
      for (int r = 0; r < rows; r++)
      {
         for (int c = 0; c < cols; c++)
         {
            //printf("%d ", curState.tiles[r][c]);
            if ((curState.tiles)[r][c] != (c + r*4 +1) && !(r == 3 && c == 3 && curState.tiles[r][c] == 0))
            {
               //printf("curState[%d][%d] = %d\n", r, c, curState.tiles[r][c]);
               done = 0;
               break;
            }
         }
         if (!done)
         {
            break;
         }
         //printf("\n");
      }
      //printf("\n");
   
      if (done)
      {
         //printf("finihed!\n");
         //free_list(visited);
         return (curState.num_steps);
      }
       
      
      struct game_state * movedUp = malloc(sizeof(struct game_state));
      *movedUp = curState;
      //printf("before moved up\n");
      //print_board(*movedUp);
      move_up(movedUp);
      //printf("after moved up \n");
      //print_board(*movedUp);
      //printf("moved up\n");
      if ((movedUp -> empty_row != curState.empty_row) && !(check_in_list(visited, serialize(*movedUp))))
      {
         //printf("moved up\n");
         //print_board(*movedUp);
         //printf("in the if statement\n");
         enqueue(&q, *movedUp);
         insert_at_tail(&visited, serialize(*movedUp));
      }
      else
      {
         free(movedUp);
      }
      
      
      //printf("moved up complete\n");       
      
      struct game_state * movedDown = malloc(sizeof(struct game_state));
      *movedDown = curState;
      //printf("before moved down\n");
      //print_board(*movedDown);
      move_down(movedDown);
      //printf("aftter moved down\n");
      //print_board(*movedDown);
      if ((movedDown -> empty_row != curState.empty_row) && !(check_in_list(visited, serialize(*movedDown))))
      {
         //printf("moved down\n");
         //print_board(*movedDown);
         enqueue(&q, *movedDown);
         insert_at_tail(&visited, serialize(*movedDown));
      }
      else
      {
         free(movedDown);
      }
      
  
      struct game_state * movedRight = malloc(sizeof(struct game_state));
      *movedRight = curState;
      move_right(movedRight);
      if ((movedRight -> empty_col != curState.empty_col) && !(check_in_list(visited, serialize(*movedRight))))
      {
         //printf("moved right\n");
         //print_board(*movedRight);
         enqueue(&q, *movedRight);
         insert_at_tail(&visited, serialize(*movedRight));
      }
      else
      {
         free(movedRight);
      }
      
      
      struct game_state * movedLeft = malloc(sizeof(struct game_state));
      *movedLeft = curState;
      move_left(movedLeft);
      if ((movedLeft -> empty_col != curState.empty_col) && !(check_in_list(visited, serialize(*movedLeft))))
      {
         //printf("moved left:\n");
         //print_board(*movedLeft);
         enqueue(&q, *movedLeft);
         insert_at_tail(&visited, serialize(*movedLeft));
      }
      else
      {
         free(movedLeft);
      }
      
      
   }
              
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
