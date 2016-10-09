Matrix-matrix multiplication
****************************
By 120323L,120132B

To run the sequential program:
  	(compile): g++ -std=c++11 sequential.cpp -o sequential
  	(run): ./sequential_final

To run the parallel program:
  	(compile): g++ -std=c++11 -fopenmp parallel.cpp -o parallel
  	(run): ./parallel

To run the optimized parallel program:
  	(compile): g++ -mavx  -std=c++11 -fopenmp optimized_parallel.cpp -o optimized_parallel
  	(run): ./optimized_parallel


