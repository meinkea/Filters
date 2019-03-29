#ifndef LinAlg_H
#define LinAlg_H

#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int len;
  float * V;
} Vector;

void alloc_Vector(Vector * Vec, int l) {
  Vec->len = l;

  Vec->V = malloc(l * sizeof(float));

  return;
}

void init_Vector(Vector * Vec, float val) {
  for(int I=0; I<Vec->len; ++I) {
    (Vec->V)[I] = val;
  }
  return;
}

void free_Vector(Vector * Vec) {
  free(Vec->V);
  Vec->V = 0;
  Vec->len = 0; // Prevent Use after free bug
  return;
}

void printVector(Vector Vec) {
  for(int I=0; I<Vec.len; ++I) {
    printf("%f\n", Vec.V[I]);
  }
  return;
}



typedef struct {
  int row;
  int col;
  float ** M;
} Matrix;

void alloc_Matrix(Matrix * Mat, int r, int c) {
  Mat->row = r;
  Mat->col = c;

  Mat->M = malloc(r * sizeof(float *));
  for(int I=0; I < r; ++I) {
    (Mat->M)[I] = malloc(c * sizeof(float));
  }

  return;
}

void init_Matrix(Matrix * Mat, float val) {
  int r = Mat->row;
  int c = Mat->col;

  for(int I=0; I<r; ++I){
    for(int II=0; II<c; ++II){
      (Mat->M)[I][II] = val;
    }
  }
  return;
}

void free_Matrix(Matrix * Mat) {
  int r = Mat->row;
  int c = Mat->col;

  for(int I=0; I < r; ++I) {
    free( (Mat->M)[I] );
    (Mat->M)[I] = 0;
  }
  free(Mat->M);
  Mat->M = 0;

  Mat->row = 0;
  Mat->col = 0;

  return;
}

void identity_Matrix(Matrix * Mat, char opt) {
  int r = Mat->row;
  int c = Mat->col;

  if(opt=='v') {
    init_Matrix(Mat, 0);
  } else if(opt=='l') {
    
  } else {
    exit(-1);
  }

  switch(opt) {
    case 'l': break;
    case 'v': init_Matrix(Mat, 0.0);
              break;
    default : break;
  }

  int min = 0;
  (r >= c) ? (min = r) : (min = c);
  for(int I=0; I<min; ++I) {
    (Mat->M)[I][I] = 1;
  }
}
void printMatrix(Matrix Mat) {
  int r = Mat.row;
  int c = Mat.col;

  for(int I=0; I<r; ++I) {
    for(int II=0; II<c; ++II) {
      printf("%f\t", Mat.M[I][II]);
    }
    puts("");
  }
  return;
}

void transpose_Matrix(Matrix * Mres, Matrix Mat) {
  int r = Mat.row;
  int c = Mat.col;

  float temp; // for element swapping

  for(int I=0; I<r; ++I) { // row of Mres OR col of Mat
    // Copy the diagonal
    (Mres->M)[I][I] = (Mat.M)[I][I];

    // Move the Upper and Lower triangles
    for(int II=I+1; II<c; ++II) { // col of Mres OR row of Mat
      temp = (Mat.M)[I][II]; // Grab the upper element
      (Mres->M)[I][II] = (Mat.M)[II][I]; // Grab and place lower element
      (Mres->M)[II][I] = temp; // Place lower element
    } // WILL change Mat.M if Mat and Mres are the same matrix
  }

  return;
}


#endif /* LinAlg_H */
