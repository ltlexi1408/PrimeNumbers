#include <iostream>
#include <vector>
#include <math.h>
#include <thread>
#include <mutex>

std::mutex mtx;

bool isprime(int n);
void multi(int start, int end, std::vector<int> &p);

int main(int argc, char* argv[]){

    std::vector<int> primes;

    unsigned int numthreads = std::thread::hardware_concurrency();
    std::thread t[numthreads];
    int max = 1000000;
    int range = max / numthreads;
    int start = 0;
    int end = range;
    
    std::cout << numthreads << std::endl;

    for(int i = 0; i < numthreads; i++){
        if(i == numthreads - 1){
            end = max;
        }
        t[i] = std::thread(multi, start, end, std::ref(primes));
        start = end;
        end += range;
    }

    for(int i = 0; i < numthreads; i++){
        t[i].join();
    }

    for(int i : primes){
        std::cout << i << ", ";
    }
    return 0;
}

void multi(int start, int end, std::vector<int> &primes){
    std::vector<int> p;
    for(int i = start; i < end; i++){
        if(isprime(i)){
            p.push_back(i);
        }
    }
    std::lock_guard<std::mutex> lock(mtx);
    primes.insert(primes.end(), p.begin(), p.end());
}

bool isprime(int n){
    if (n <= 1){
        return false;
    }

    if(n == 2 || n == 3){
        return true;
    }

    if (n % 2 == 0 || n % 3 == 0) {
        return false;
    }

    for(int i = 5; i <= std::sqrt(n); i++){
        if(n % i == 0){
            return false;
        }
    }

    return true;
}