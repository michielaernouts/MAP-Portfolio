#include <cutil_inline.h>
#include <sys/time.h>

__global__ void
addMatrix( float *C, float *A, float *B, int N) {
  int i = blockIdx.x * blockDim.x + threadIdx.x;
  int j = blockIdx.y * blockDim.y + threadIdx.y;

  int idx = i + j * N;

  if (i < N && j < N)
    C[idx] = A[idx] + B[idx];
}

void call_addMatrix(float *C, float *A, float *B, int N) {
  static int first_time = 1;

  if (first_time) {
    cudaSetDevice(cutGetMaxGflopsDeviceId());
    first_time = 0;
  }

  int devID;
  cudaDeviceProp props;

  cutilSafeCall(cudaGetDevice(&devID));
  cutilSafeCall(cudaGetDeviceProperties(&props, devID));

  printf("Device %d: \"%s\" with Compute %d.%d capability\n", devID, props.name, props.major, props.minor);

  float* d_A;
  cutilSafeCall(cudaMalloc((void**) &d_A, sizeof(*A) * N * N));
  float* d_B;
  cutilSafeCall(cudaMalloc((void**) &d_B, sizeof(*B) * N * N));

  cutilSafeCall(cudaMemcpy(d_A, A, sizeof(*A) * N * N,
                           cudaMemcpyHostToDevice) );
  cutilSafeCall(cudaMemcpy(d_B, B, sizeof(*B) * N * N,
                           cudaMemcpyHostToDevice) );

  float* d_C;
  cutilSafeCall(cudaMalloc((void**) &d_C, sizeof(*C) * N * N));

  dim3 dimBlock(16, 16);
  dim3 dimGrid(N / dimBlock.x, N / dimBlock.y);

  addMatrix<<<dimGrid, dimBlock>>>(d_C, d_A, d_B, N);

  struct timeval time_start;
  gettimeofday(&time_start, NULL);

  for (int i = 1024; i != 0; --i) {
    addMatrix<<<dimGrid, dimBlock>>>(d_C, d_A, d_B, N);
  }

  cudaThreadSynchronize();

  cutilCheckMsg("Kernel execution failed");

  struct timeval time_end;
  gettimeofday(&time_end, NULL);

  double time_float = (time_end.tv_sec - time_start.tv_sec) + (time_end.tv_usec - time_start.tv_usec) * 0.000001;

  printf("CUDA completed 1024 runs in %f\n", time_float);

  cutilSafeCall(cudaMemcpy(C, d_C, sizeof(*C) * N * N,
                           cudaMemcpyDeviceToHost) );

  cutilSafeCall(cudaFree(d_A));
  cutilSafeCall(cudaFree(d_B));
  cutilSafeCall(cudaFree(d_C));
}
