#include "cuda_runtime.h"
#include <math.h>
#include <iostream>

__global__ void primeSieve(int* prime, int max){
    int index = blockIdx.x * blockDim.x + threadIdx.x;
    int stride = blockDim.x * gridDim.x;

    for(int i = 2 + index; i <= sqrtf(max); i += stride){
        if(prime[i]){
            for(int j = i * i; j <= max; j += i){
                prime[j] = 0;
            }
        }
    }
    __syncthreads();
}

int main(){
    int max = 1000000000;
    // calcualte size of memory needed
    size_t size = (max + 1) * sizeof(int);

    // assign mem on host
    int* prime = (int*)malloc(size);
    for (int i = 0; i <= max; i++) prime[i] = 1;
    prime[0] = prime[1] = 0;

    // assign + cpy mem to Gpu
    int* primed;
    cudaMalloc(&primed, size);
    cudaMemcpy(primed, prime, size, cudaMemcpyHostToDevice);

    // execute gpu code
    int block = 256;
    int numBlock = (max + block -1) / block;

    printf("%d:%d\n", block, numBlock);
    primeSieve <<<numBlock,block>>> (primed, max);

    cudaMemcpy(prime, primed, size, cudaMemcpyDeviceToHost);

    for(int i = 0; i <= max; i++){
        if(prime[i]){
            printf("%d, ", i);
        }
    }

    cudaFree(primed);
    free(prime);

    return 0;
}