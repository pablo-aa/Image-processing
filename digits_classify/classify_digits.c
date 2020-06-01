#include <stdio.h> /* input, output */
#include "mnist.h"

#define VERBOSE 1


int classify(LecunDataType train, LecunDataType labels, LecunDataType test, LecunDataType *result, int K)
{
  int r, c, count, n_pixels;
  int class_label;

  int *class_hist = (int *) calloc(NCLASSES, sizeof(int));
  DistanceType *dists = (DistanceType *) calloc(train.dimensions[0], sizeof(DistanceType));

  n_pixels = train.dimensions[1]*train.dimensions[2];
  result->n_dimensions = 1; /* simple array of predicted labels */
  result->data_type = test.data_type;
  result->data_bytes = test.data_bytes;
  result->dimensions = (int *) calloc(result->n_dimensions, sizeof(int));
  result->dimensions[0] = test.dimensions[0];
  result->total_dims = result->dimensions[0];
  result->data = (unsigned char *) calloc(result->total_dims, result->data_bytes);
  if((result->dimensions==NULL) || (result->data == NULL))
  {
    printf("classify() failed to allocate predictions data structure.");
    return 1;
  }

  /*** Fill the gaps below. */

  /* Classify each test sample based on the label of the K nearest
     train samples.
     compiled with: gcc -Wall -ansi -pedantic mnist.c classify_digits.c -o classify_digits
     executed with: ./classify_digits train_imgs train_labels test_imgs_100 test_preds 5 test_labels_100 */

  for(r=0; r<test.dimensions[0]; r++)
  {
    for(c=0; c<train.dimensions[0]; c++)
    {
      /* Compute distance from test element r to all training elements
	 and store the results in dists array.
	 ... */

    dists[c].data = distance(&test.data[r*n_pixels], &train.data[c*n_pixels], n_pixels);
    dists[c].idx = c;

    }

    /* Sort distance array.
       ... */

    SortK(dists, train.dimensions[0], K);

    for(c=0; c < NCLASSES; c++)
      /* Set all class_hist elements to zero.
       ... */
       class_hist[c] = 0;

    for(c=0; c<K; c++)
    {
      /* Increment element of class_hist whose index is the label that
	 occured among the first K elements sorted according to the
	 distance.
      ... */
      class_hist[labels.data[dists[c].idx]]++;

    }

    count = 0;
    for(c=0; c<NCLASSES; c++)
    {
      /* Set result->data[r] = class label that occured more times.
	 ... */
      if (c == 0)
      {
        count = class_hist[c];
      }
      else if (class_hist[c] > count)
      {
        count = class_hist[c];
        class_label = c;
      }

    }
    result->data[r] = class_label;

    if(VERBOSE) printf("Image %d classified as %d\n", r, result->data[r]);
  }

  free(dists);
  free(class_hist);
  return 0;
}



int main(int nargin, char **argv){
  int c;
  LecunDataType train, test, labels, result, gt;

  if(VERBOSE){
    printf("nargin=%d\n", nargin);
    for(c=0; c < nargin; c++)
      printf("argv[%d] = %s\n", c, argv[c]);
  }

  if((nargin < 6) || (nargin > 7)){
    printf("\nK-nearest neighbour classifier for MNIST dataset.\n");
    printf("\nCopyright Teofilo E. de Campos, UnB, 2017.\n");
    printf("\nUsage: %s train_data train_labels test_data pred_file K gt\n", argv[0]);
    printf("  where\n");
    printf("\ttrain_data:   path of file containing training images.\n");
    printf("\ttrain_labels: path of file containing training labels.\n");
    printf("\ttest_data:    path of file containing training images.\n");
    printf("\tpred_file:    path of file where the classification results will be written.\n");
    printf("\tK:            number of neighbours used for KNN classification.\n");
    printf("\tg:            path of file containing ground truth labels for test set.\n");
    printf("\nAll files are in IDX format, which is used in Yann Lecun's MNIST dataset,\nyou can obtain them from\n");
    printf("http://yann.lecun.com/exdb/mnist/\n");
    printf("For example, you can download Yann's file using:\n");
    printf("  wget http://yann.lecun.com/exdb/mnist/train-images-idx3-ubyte.gz\n");
    printf("  wget http://yann.lecun.com/exdb/mnist/train-labels-idx1-ubyte.gz");
    printf("  wget http://yann.lecun.com/exdb/mnist/t10k-images-idx3-ubyte.gz\n");
    printf("  wget http://yann.lecun.com/exdb/mnist/t10k-labels-idx1-ubyte.gz\n");
    printf("uncompress all files:\n");
    printf("  gunzip *.gz\n");
    printf("compile this program:\n");
    printf("  gcc mnist.c classify_digits.c -o classify_digits\n");
    printf("and use it:\n");
    printf("  ./classify_digits train-images-idx3-ubyte train-labels-idx1-ubyte t10k-images-idx3-ubyte results-idx1-ubyte 3 t10k-labels-idx1-ubyte\n");

    return 0;
  }

  sprintf(train.filename, "%s", argv[1]);
  if(read_LecunData(&train)) return 0;
  if(VERBOSE>3) print_all_data(train);

  sprintf(labels.filename, "%s", argv[2]);
  if(read_LecunData(&labels)) return 0;
  if(VERBOSE>3) print_all_data(labels);

  sprintf(test.filename, "%s", argv[3]);
  if(read_LecunData(&test)) return 0;
  if(VERBOSE>3) print_all_data(test);

  if(VERBOSE>3){
    write_all_imgs("ImgTrain", train);
    write_all_imgs("ImgTest", test);
  }

  sprintf(result.filename, "%s", argv[4]);
  if(classify(train, labels, test, &result, atoi(argv[5]))){
    printf("Error in classify()\n");
  }

  if(nargin==7){
    sprintf(gt.filename, "%s", argv[6]);
    if(read_LecunData(&gt)) return 0;
    printf("Accuracy=%3.4f\n", get_accuracy(gt, result));
  }

  if(write_LecunData(result)){
    printf("Error saving results file.\n");
  }

  free(train.dimensions);
  free(train.data);

  free(test.dimensions);
  free(test.data);

  free(result.dimensions);
  free(result.data);

  free(gt.dimensions);
  free(gt.data);

  return 0;
}
