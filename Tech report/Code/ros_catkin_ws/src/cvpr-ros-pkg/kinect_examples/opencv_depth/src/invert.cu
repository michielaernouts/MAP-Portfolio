#include "invert.cuh"
#define IV_BW 16
#define IV_BH 16

__global__ void invert_kernel
(
	float *in_g,
	float *out_g,
	float  range,
	int    nx,
	int    ny,
	size_t    pitchbytes
)
{
	const int x = blockIdx.x*blockDim.x + threadIdx.x;
	const int y = blockIdx.y*blockDim.y + threadIdx.y;


	if(x < nx && y < ny)
	{
		*(float*)((char*)out_g + y*pitchbytes + x*sizeof(float)) = range -
				*(float*)((char*)in_g + y*pitchbytes + x*sizeof(float));
	}
}

__global__ void invert_kernel
(
	float3 *in_g,
	float3 *out_g,
	float  range,
	int    nx,
	int    ny,
	size_t    pitchbytes
)
{
	const int x = blockIdx.x*blockDim.x + threadIdx.x;
	const int y = blockIdx.y*blockDim.y + threadIdx.y;

	float3 result;

	if(x < nx && y < ny)
	{
		result = *(float3*)((char*)in_g + y*pitchbytes + x*sizeof(float3));
		result.x = range - result.x;
		result.y = range - result.y;
		result.z = range - result.z;
		*(float3*)((char*)out_g + y*pitchbytes + x*sizeof(float3)) = result;
	}
}


void invert
(
	float  *in,
	float  *out,
	float  range,
	int    nx,
	int    ny,
	float  **in_out_g,
	size_t *pitchbytes
)
{
	int ngx = (nx%IV_BW) ? ((nx/IV_BW)+1) : (nx/IV_BW);
	int ngy = (ny%IV_BH) ? ((ny/IV_BH)+1) : (ny/IV_BH);
	dim3 dimGrid(ngx,ngy);
	dim3 dimBlock(IV_BW,IV_BH);

	cutilSafeCall( cudaMallocPitch((void**)in_out_g,pitchbytes,nx*sizeof(float),ny ));
	cutilSafeCall( cudaMemcpy2D(*in_out_g,*pitchbytes,in,nx*sizeof(float),nx*sizeof(float),ny,cudaMemcpyHostToDevice));
	invert_kernel<<<dimGrid,dimBlock>>>(*in_out_g,*in_out_g,range,nx,ny,*pitchbytes);
	cutilSafeCall(cudaThreadSynchronize());
	cutilSafeCall( cudaMemcpy2D(in,nx*sizeof(float),*in_out_g,*pitchbytes,nx*sizeof(float),ny,cudaMemcpyDeviceToHost));
}

void invert
(
	float3 *in,
	float3 *out,
	float  range,
	int    nx,
	int    ny,
	float3 **in_out_g,
	size_t *pitchbytes
)
{
	int ngx = (nx%IV_BW) ? ((nx/IV_BW)+1) : (nx/IV_BW);
	int ngy = (ny%IV_BH) ? ((ny/IV_BH)+1) : (ny/IV_BH);
	dim3 dimGrid(ngx,ngy);
	dim3 dimBlock(IV_BW,IV_BH);

	cutilSafeCall( cudaMallocPitch((void**)in_out_g,pitchbytes,nx*sizeof(float3),ny ));
	cutilSafeCall( cudaMemcpy2D(*in_out_g,*pitchbytes,in,nx*sizeof(float3),nx*sizeof(float3),ny,cudaMemcpyHostToDevice));
	invert_kernel<<<dimGrid,dimBlock>>>(*in_out_g,*in_out_g,range,nx,ny,*pitchbytes);
	cutilSafeCall(cudaThreadSynchronize());
	cutilSafeCall( cudaMemcpy2D(in,nx*sizeof(float3),*in_out_g,*pitchbytes,nx*sizeof(float3),ny,cudaMemcpyDeviceToHost));
}



void invert
(
	float *in,
	float *out,
	float  range,
	int   nx,
	int   ny,
	float *in_out_g,
	size_t   pitchbytes
)
{
	int ngx = (nx%IV_BW) ? ((nx/IV_BW)+1) : (nx/IV_BW);
	int ngy = (ny%IV_BH) ? ((ny/IV_BH)+1) : (ny/IV_BH);
	dim3 dimGrid(ngx,ngy);
	dim3 dimBlock(IV_BW,IV_BH);

	cutilSafeCall( cudaMemcpy2D(in_out_g,pitchbytes,in,nx*sizeof(float),nx*sizeof(float),ny,cudaMemcpyHostToDevice));
	invert_kernel<<<dimGrid,dimBlock>>>(in_out_g,in_out_g,range,nx,ny,pitchbytes);
	cutilSafeCall(cudaThreadSynchronize());
	cutilSafeCall( cudaMemcpy2D(in,nx*sizeof(float),in_out_g,pitchbytes,nx*sizeof(float),ny,cudaMemcpyDeviceToHost));
}

void invert
(
	float3 *in,
	float3 *out,
	float  range,
	int   nx,
	int   ny,
	float3 *in_out_g,
	size_t   pitchbytes
)
{
	int ngx = (nx%IV_BW) ? ((nx/IV_BW)+1) : (nx/IV_BW);
	int ngy = (ny%IV_BH) ? ((ny/IV_BH)+1) : (ny/IV_BH);
	dim3 dimGrid(ngx,ngy);
	dim3 dimBlock(IV_BW,IV_BH);

	cutilSafeCall( cudaMemcpy2D(in_out_g,pitchbytes,in,nx*sizeof(float3),nx*sizeof(float3),ny,cudaMemcpyHostToDevice));
	invert_kernel<<<dimGrid,dimBlock>>>(in_out_g,in_out_g,range,nx,ny,pitchbytes);
	cutilSafeCall(cudaThreadSynchronize());
	cutilSafeCall( cudaMemcpy2D(in,nx*sizeof(float3),in_out_g,pitchbytes,nx*sizeof(float3),ny,cudaMemcpyDeviceToHost));
}

void cuda_delete(void *field_g)
{
	cutilSafeCall(cudaFree(field_g));
}
