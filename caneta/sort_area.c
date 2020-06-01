/* Compile this with
      gcc mnist.c sort_area.c
   Optional (to prevent errors):
      gcc mnist.c sort_area.c -o sort_area -ansi -Wall -pedantic
*/

#include <stdio.h> /* input, output */
#include <string.h>/* strcpy */
#include "mnist.h" /* my library to handle the MNIST dataset */

int main(int nargin, char **argv)
{
  LecunDataType input;
  unsigned int option, n_pixels, n_samples, n, c, i, j;
  DistanceType *areas;
  unsigned char *aux;

  scanf("%s", input.filename);
  scanf("%u", &option);

  read_LecunData(&input);
  n_samples = input.dimensions[0];
  n_pixels = input.dimensions[1]*input.dimensions[2];


  areas = (DistanceType *) calloc(input.dimensions[0], sizeof(DistanceType));


  /* Write your own code here.
     Algorithm:*/

     /*1. Initialise the areas array where the field idx grows from 0 to n_samples
        and the field data is set to zero.*/
        for (n = 0; n < n_samples; n++)
        {
            areas[n].data = 0;
            areas[n].idx = n;
        }



    /* 2. For each sample image
          For each pixel of that image
             Add the number of foreground pixels of that image to areas[n],
	       i.e., pixels whose value is greater than 0.
	     Hint: to access the c pixel of an image n in the data vector, use
	       use input.data[n*n_pixels+c]*/
         for (n = 0; n < n_samples; n++)
         {
           for (c = 0; c < n_pixels; c++)
           {
             if (input.data[n*n_pixels+c] > 0)
             {
               areas[n].data++;
             }
           }
         }



     /*3. If option==0
        Print all values of areas[n].data
	Use printf("%.0f\n", ...), because data is of type double but the output is
	  expected to be a set of unsigned integers.
        End*/
        if(option == 0)
        {
          for (n = 0; n < n_samples; n++)
          {
              printf("%.0f\n", areas[n].data);
          }
        }


     /*4. Sort the areas array, e.g., using InsertionSort.*/

     InsertionSort(areas, n_samples);

     /*5. If option==1
        print all values of areas[n].idx
	End*/
      if(option == 1)
      {
        for (n = 0; n < n_samples; n++)
        {
            printf("%d\n", areas[n].idx);
        }
      }


    /* 6. Allocate the aux vector:
        aux = (unsigned char *) calloc(input.total_dims, input.data_bytes);*/

        aux = (unsigned char *) calloc(input.total_dims, input.data_bytes);


     /*7. For each sample n
          Copy it to the appropriated place of the aux vector, i.e., use
	    areas[n].idx to locate the sample of input.data
	    and copy it to aux.
	  The same hint in step 2 will help to access locations in both
	    input.data and aux.*/

        for (n = 0; n < n_samples; n++)
        {

          for (c = 0; c < n_pixels; c++)
          {
            if(c == 0)
            {
              aux[n*n_pixels + c] = input.data[areas[n].idx*n_pixels+c];
            }
          }

        }


     /*8. Now that aux has been sorted using idx, copy all its contents
        back to input.data.*/

        for (n = 0; n < n_pixels*n_samples; n++)
        {
          input.data[n] = aux[n];
        }


     /*9. free(aux)*/

      free(aux);

    /*10. If option==2
	  Reset the filename from the input structure to "out.bin" , i.e.,
   	    strcpy(input.filename, "out.bin");
	  Write it to the file using a function from mnist.h
	  End.*/
      if (option == 2)
      {
        strcpy(input.filename, "out.bin");
        write_LecunData(input);
      }

    /*10. If option==3
          Write all images from the input data structure to PGM images
	    using a function from mnist.h
	  For that, use the current directory as the first parameter (".")*/

    if (option == 3)
    {
      write_all_imgs(".", input);
    }


    /*11. Free the allocated arrays, i.e.
        free(input.dimensions);
        free(input.data);
        free(areas);
  */
    free(input.dimensions);
    free(input.data);
    free(areas);

  return 0;
}
