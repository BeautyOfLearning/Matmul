#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

int **create_2d_array(int nrow, int ncol)
{
  int **a = (int **)malloc(nrow * sizeof(int *));
  for (int i = 0; i < nrow; i++)
  {
    a[i] = (int *)malloc(ncol * sizeof(int));
  }
  return a;
}

void free_2d_array(int **a, int nrow)
{
  for (int i = 0; i < nrow; i++)
  {
    free(a[i]);
  }
  free(a);
}

int **get_rand_matrix(int nrow, int ncol)
{
  int **a = create_2d_array(nrow, ncol);
  srand(time(NULL));
  for (int i = 0; i < nrow; i++)
  {
    for (int j = 0; j < ncol; j++)
    {
      a[i][j] = rand() % 100;
    }
  }
  return a;
}

void write_matrix(int **a, int nrow, int ncol, char *filename)
{
  FILE *f = fopen(filename, "w");
  fprintf(f, "%d %d\n", nrow, ncol);
  for (int i = 0; i < nrow; i++)
  {
    for (int j = 0; j < ncol; j++)
    {
      fprintf(f, "%d", a[i][j]);
      if (j < ncol - 1)
        fprintf(f, " ");
    }
    if (i < nrow - 1)
      fprintf(f, "\n");
  }
  fclose(f);
}

int **read_matrix(char *filename)
{
  int nrow, ncol;
  FILE *f = fopen(filename, "r");
  fscanf(f, "%d %d\n", &nrow, &ncol);
  int **a = create_2d_array(nrow, ncol);
  for (int i = 0; i < nrow; i++)
  {
    for (int j = 0; j < ncol; j++)
    {
      fscanf(f, "%d", &a[i][j]);
    }
  }
  fclose(f);
  return a;
}

void print_matrix(int **a, int nrow, int ncol)
{
  for (int i = 0; i < nrow; i++)
  {
    for (int j = 0; j < ncol; j++)
    {
      printf("%d", a[i][j]);
      if (j < ncol - 1)
        printf(" ");
    }
    printf("\n");
  }
}

bool array_equal(int **a, int **b, int nrow, int ncol)
{
  for (int i = 0; i < nrow; i++)
  {
    for (int j = 0; j < ncol; j++)
    {
      if (a[i][j] != b[i][j])
        return false;
    }
  }
  return true;
}

int main(int argc, char const *argv[])
{
  assert(argc >= 3);
  int nrow = strtol(argv[1], NULL, 10), ncol = strtol(argv[2], NULL, 10);
  int **a = get_rand_matrix(nrow, ncol);
  print_matrix(a, nrow, ncol);
  char *filename = "mat.txt";
  write_matrix(a, nrow, ncol, filename);
  int **b = read_matrix(filename);
  assert(array_equal(a, b, nrow, ncol));
  free_2d_array(b, nrow);
  free_2d_array(a, nrow);
  return 0;
}