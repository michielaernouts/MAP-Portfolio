#ifndef INVERT_CUH
#define INVERT_CUH

#include <cutil.h>
#include <cutil_inline.h>


void invert
(
	float  *in,
	float  *out,
	float  range,
	int    nx,
	int    ny,
	float  **in_out_g,
	size_t *pitchbytes
);

void invert
(
	float3 *in,
	float3 *out,
	float  range,
	int    nx,
	int    ny,
	float3 **in_out_g,
	size_t *pitchbytes
);



void invert
(
	float *in,
	float *out,
	float  range,
	int   nx,
	int   ny,
	float *in_out_g,
	size_t   pitchbytes
);

void invert
(
	float3 *in,
	float3 *out,
	float  range,
	int   nx,
	int   ny,
	float3 *in_out_g,
	size_t   pitchbytes
);

void cuda_delete(void *field_g);

#endif


