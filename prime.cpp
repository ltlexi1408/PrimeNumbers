#include <iostream>
#include <vector>

bool isprime(int n);

int main(){

    std::vector<int> primes;

    for(int i = 0; i < 1000; i++){
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


}