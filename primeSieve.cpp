#include <iostream>
#include <vector>
#include <math.h>

bool isprime(int n);

int main(int argc, char* argv[]){
    int max = 1000;

    int primes[max];

    for (int i = 0; i <= max; i++) primes[i] = 1;

    for(int i = 2; i <= sqrtf(max); i++){
        if(primes[i]){
            for(int j = i * i; j <= max; j += i){
                primes[j] = 0;
            }
        }
    }

    for(int i = 0; i <= max; i++){
        if(primes[i]){
            printf("%d, ", i);
        }
    }

    return 0;
}