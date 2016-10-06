/**
 * Sequential program to perform matrix-matrix multiplication
 *
 * To run this program:
 * 	(compile): g++ -std=c++11 -fopenmp optimized_parallel_tiled.cpp -o optimized_parallel_tiled
 * 	(run): ./optimized_parallel <matrix_size>
 *
 * 
 */

#include <iostream>
#include <random>
#include <chrono>
#include <omp.h>

using namespace std::chrono;
using namespace std;

#define S 50

int s = S;


double** initMat(int size){
  double** mat = new double*[size];
  for (int i = 0; i < size; i++) {
    mat[i] = new double[size];
  }
  return mat;
}

double** getTranspose(double** matrix, int size){
  double** trans_mat = initMat(size);

  #pragma omp parallel for
  for (int row = 0; row < size; row++) {
    for (int col = 0; col < size; col++) {
      trans_mat[row][col] = matrix[col][row];
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

  return trans_mat;
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

long tiled_mat_multiply(double **matA, double **matB, int size){
  double** matC = initMat(size);

  high_resolution_clock::time_point start = high_resolution_clock::now();//Start clock

  double** trans_matB=getTranspose(matB,size);

   #pragma omp parallel for 
   for (int i = 0; i < size; i+=s) {
      for (int j = 0; j < size; j+=s) {
         for (int k = 0; k < size; k+=s) {
        //#pragma omp task depend ( in: matA[i:s][k:s], matB[k:s][j:s] )  depend ( inout: matC[i:s][j:s] )
            for (int ii = i; ii < i+s; ii++ ){
               for (int jj = j; jj < j+s; jj++ ){
               double sum=0;
                  for (int kk = k; kk < k+s; kk++ ){
                     sum+= matA[ii][kk] * trans_matB[jj][kk];
                   }
                   matC[ii][jj] +=sum;
                }
             }
         }
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

void matMultiply(int size){
  double** matA = initMat(size);
  double** matB = initMat(size);
  populateMat(matA , size);
  populateMat(matB, size);
  tiled_mat_multiply(matA,matB, size);
}


int main(int argc, const char* argv[]) {

  int size = atoi(argv[1]);
  matMultiply(size);
  return 0;
}
