/**
 * Sequential program to perform matrix-matrix multiplication
 *
 * To run this program:
 * 	(compile): g++ -msse3 -std=c++11 -fopenmp optimized_parallel_new.cpp -o optimized_parallel_new
 * 	(run): ./optimized_parallel <matrix_size>
 *
 * 
 */

#include <iostream>
#include <random>
#include <chrono>
#include <omp.h>
#include <x86intrin.h>


using namespace std::chrono;
using namespace std;

#define S 50

#pragma intrinsic ( _mm_hadd_pd )

int s = S;


double** initMat(int size){
  double** mat = new double*[size];
  for (int i = 0; i < size; i++) {
    mat[i] = new double[size];
  }
  return mat;
}

double** getTranspose(double** matrix, int size){
  //double** trans_mat = initMat(size);

  #pragma omp parallel for
  for (int row = 0; row < size; row++) {
    for (int col = 0; col < size; col++) {
      std::swap(matrix[row][col], matrix[col][row]);
    }
  }
  
  

/*Display the transpose
  for (int row = 0; row < size; row++) {
    for (int col = 0; col < size; col++) {
      cout<<trans_mat[row][col]<<" ";
    }
    cout<<endl;
  }
  cout<<endl;  */

  return matrix;
}

void populateMat(double** matrix, int size){
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<> dis(0,8);//The distribution in range 1-8

  for (int row = 0; row < size; row++) {
    for (int col = 0; col < size; col++) {
      matrix[row][col] = dis(gen);
      //cout<<matrix[row][col]<<" ";
    }
    //cout<<endl;
  }
  //cout<<endl;
}

long mat_multiply_compiler_intrinsics(double **matA, double **matB, int size){
  double** matC = initMat(size);

  high_resolution_clock::time_point start = high_resolution_clock::now();//Start clock

  double** trans_matB=getTranspose(matB,size);

   #pragma omp parallel for
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            __m128d c = _mm_setzero_pd();

            for (int k = 0; k < size; k += 2) {
                c = _mm_add_pd(c, _mm_mul_pd(_mm_load_pd(&matA[i][k]), _mm_load_pd(&trans_matB[j][k])));
            }
            c = _mm_hadd_pd(c, c);
            _mm_store_sd(&matC[i][j], c);
        }
    }  

  high_resolution_clock::time_point end = high_resolution_clock::now(); //End clock

  long duration = duration_cast<milliseconds>( end - start ).count();   //Get duration in milliseconds
  cout<<duration<<endl;

  delete matA;
  delete matB;
  delete matC;

  return duration;

}

long matMultiply(int size){
  double** matA = initMat(size);
  double** matB = initMat(size);
  populateMat(matA , size);
  populateMat(matB, size);
  mat_multiply_compiler_intrinsics(matA,matB, size);
}

int main(int argc, const char* argv[]) {

  int size = atoi(argv[1]);
  matMultiply(size);
  return 0;
}
