/**
 * Sequential program to perform matrix-matrix multiplication
 *
 * To run this program:
 * 	(compile): g++ -std=c++11 sequential.cpp -o sequential
 * 	(run): ./sequential <matrix_size>
 *
 * 
 */

#include <iostream>
#include <random>
#include <chrono>

using namespace std::chrono;
using namespace std;


double** initMat(int size){
  double** mat = new double*[size];
  for (int i = 0; i < size; i++) {
    mat[i] = new double[size];
  }
  return mat;
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

long multiply(double **matA, double **matB, int size){
  double** resMat = initMat(size);

  high_resolution_clock::time_point start = high_resolution_clock::now();//Start clock

  for(int row = 0; row < size; row++){
    for(int col = 0; col < size; col++){
      resMat[row][col] = 0.0;
      for (int cur = 0; cur < size; cur++) {
        resMat[row][col] += matA[row][cur] * matB[cur][col];
      }
      //cout<<resMat[row][col]<<" ";
    }
    //cout<<endl;
  }


  high_resolution_clock::time_point end = high_resolution_clock::now(); //End clock

  long duration = duration_cast<milliseconds>( end - start ).count();   //Get duration in milliseconds
  cout<<duration<<endl;

  delete matA;
  delete matB;
  delete resMat;

  return duration;

}

void matMultiply(int size){
  double** matA = initMat(size);
  double** matB = initMat(size);
  populateMat(matA , size);
  populateMat(matB, size);
  multiply(matA,matB, size);
}


int main(int argc, const char* argv[]) {

  int size = atoi(argv[1]);
  matMultiply(size);
  return 0;
}
