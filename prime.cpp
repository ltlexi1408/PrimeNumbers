#include <iostream>
#include <vector>
#include <math.h>

bool isprime(int n);

int main(int argc, char* argv[]){

    std::vector<int> primes;

    for(int i = 0; i < int(argv[1]); i++){
        if(isprime(i)){
            primes.push_back(i);
        }
    }

    for(int i : primes){
        std::cout << i << ", ";
    }
    return 0;
}

bool isprime(int n){
    if (n <= 1){
        return false;
    }

    for(int i = 2; i <= std::sqrt(n); i++){
        if(n % i == 0){
            return false;
        }
    }

    return true;
}