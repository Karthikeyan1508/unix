#include <iostream>
#include <pthread.h>

void* countTo100(void* arg) {
    int item = *((int*)arg);
    for (int i = 1; i <= 100; ++i) {
        std::cout << "Thread " << item << ": Count " << i << std::endl;
    }
    pthread_exit(NULL);
}

int main() {
    const int numThreads = 2;
    pthread_t threads[numThreads];

    for (int i = 0; i < numThreads; ++i) {
        int* item = new int(i);
        int threadCreateStatus = pthread_create(&threads[i], NULL, countTo100, (void*)item);
        if (threadCreateStatus) {
            std::cerr << "Error creating thread: " << threadCreateStatus << std::endl;
            return -1;
        }
    }

    for (int i = 0; i < numThreads; ++i) {
        pthread_join(threads[i], NULL);
    }
    return 0;
}
