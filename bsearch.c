#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

/**
 * Function takes an array, it's size and a number, which will be used to find
 * a closest position of a value that is greater than the given number. Using
 * binary search algorithm with a changed stop condition, that allows to find
 * last element with value equal to 'x'.
 * Returns position of element greater than 'x' or -1 if there are no
 * elements greater than 'x'.
 */
int _bsearch(const int * array, int size, int x)
{
   int min = 0, max = size;
   int pos = max / 2;

   if (size < 1) return -1;

   while ((max - min) > 1)
   {
      if (x < array[pos])
         max = pos;
      else
         min = pos;

      pos = min + (max - min) / 2;
   }

   return (x < array[pos]) ? pos : ((pos + 1) != size ? pos + 1 : -1);
}

/**
 * Simple application to test _bsearch function. First N numbers will be placed
 * into an array. N + 1 number will be used as a value for search.
 */
int main(int argc, char ** argv)
{
   int x = 0, counter = 0;
   int result = -1;

   if (argc >= 2)
   {
      int array_size = argc - 2;
      int * array = (int *) malloc(array_size * sizeof(int));

      if (!array_size || !array)
      {
         printf("Invalid parameters!\n");
         return -1;
      }

      printf("Process array: { ");

      while ((counter < argc - 1))
      {
         x = (int) strtol(argv[1 + counter], NULL, 10);

         if (errno == ERANGE)
         {
            printf("???\nInvalid number: %s\n", strerror(errno));
            return -1;
         }

         if (counter < array_size)
         {
            if ((counter == 0) || (array[counter - 1] <= x))
            {
               if (counter != array_size - 1)
                  printf("%d, ", x);
               else
                  printf("%d }", x);

               array[counter] = x;
            }
            else
            {
               printf("???\nPrevious element is greater than current!\n");
               return -1;
            }
         }
         else printf("\nSelected value: %d\n", x);

         counter++;
      }

      result = _bsearch(array, array_size, x);

      printf("A value greater than '%d' is placed at position: %d\n", x, result);

      free((void *) array);
   }
   else printf("Invalid arguments!\n");

   return result;
}
