/**
 * Sequential program to perform matrix-matrix multiplication
 *
 * To run this program:
 *  (compile): g++ -mavx -std=c++11 -fopenmp optimized_parallel_avx.cpp -o optimized_parallel_avx
 *  (run): ./optimized_parallel <matrix_size>
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
void display(double** mat,int size){

for(int i=0; i<size;i++){
  for(int j=0; j <size;j++){
    cout<<mat[i][j]<<"\t";
  }
  cout<<endl;
}
}
double** getTranspose(double** matrix, int size){
  for (int row = 0; row < size; row++) {
    for (int col = row+1; col < size; col++) {
      std::swap(matrix[row][col], matrix[col][row]);
    }
  }
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

long mat_multiply_avx(double **matA, double **matB, int size){
  double** matC = initMat(size);

  high_resolution_clock::time_point start = high_resolution_clock::now();//Start clock

  double** trans_matB=getTranspose(matB,size);

   #pragma omp parallel for
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            __m256d c = _mm256_setzero_pd();
            double tempresult[4];

            for (int k = 0; k < size; k += 4) {
                c = __builtin_ia32_addpd256(c, __builtin_ia32_mulpd256(__builtin_ia32_loadupd256(&matA[i][k]), __builtin_ia32_loadupd256(&trans_matB[j][k])));
            }
            __builtin_ia32_storeupd256(tempresult, c);
            matC[i][j] = tempresult[0]+tempresult[1]+tempresult[2]+tempresult[3];
        }
    } 

  high_resolution_clock::time_point end = high_resolution_clock::now(); //End clock


  long duration = duration_cast<nanoseconds>( end - start ).count();   //Get duration in milliseconds
  cout<<(double)duration/1000000<<"ms"<<endl;
  //cout<<"matC"<<endl;
  // display(matC,size);

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


  //cout<<"matA"<<endl;
  //display(matA,size);
  // cout<<"matB"<<endl;
  //display(matB,size);
  mat_multiply_avx(matA,matB, size);
}

int main(int argc, const char* argv[]) {

  int size = atoi(argv[1]);
  matMultiply(size);
  return 0;
}
