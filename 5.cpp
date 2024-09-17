#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <vector>
#define MAX_BUFFER_SIZE 5
#define NUM_PRODUCERS 2
#define NUM_CONSUMERS 2
std::vector<int> buffer; // Shared buffer
sem_t mutex;             // Semaphore for mutual exclusion
sem_t empty;             // Semaphore for tracking empty slots in the buffer
sem_t full;              // Semaphore for tracking filled slots in the buffer
void *producer(void *arg)
{
    int item = *((int *)arg);
    while (true)
    {
        sleep(1);
        sem_wait(&empty);       // Wait for an empty slot in the buffer
        sem_wait(&mutex);       // Enter critical section
        buffer.push_back(item); // Produce an item and add it to the buffer
        std::cout << "Produced: " << item << ", Buffer size: " << buffer.size() << std::endl;
        sem_post(&mutex); // Exit critical section
        sem_post(&full);  // Signal that a slot in the buffer is filled
    }
    return NULL;
}
// Consumer function
void *consumer(void *arg)
{
    while (true)
    {
        sleep(1);                 // Simulate time to consume an item
        sem_wait(&full);          // Wait for a filled slot in the buffer
        sem_wait(&mutex);         // Enter critical section
        int item = buffer.back(); // Consume an item from the buffer
        buffer.pop_back();
        std::cout << "Consumed: " << item << ", Buffer size: " << buffer.size() << std::endl;
        sem_post(&mutex); // Exit critical section
        sem_post(&empty); // Signal that a slot in the buffer is empty
    }
    return NULL;
}
int main()
{
    // Initialize semaphores
    sem_init(&mutex, 0, 1);               // Mutex semaphore
    sem_init(&empty, 0, MAX_BUFFER_SIZE); // Empty semaphore (buffer slots available)
    sem_init(&full, 0, 0);                // Full semaphore (buffer slots filled)
    // Create producer and consumer threads
    pthread_t producer_threads[NUM_PRODUCERS];
    pthread_t consumer_threads[NUM_CONSUMERS];
    for (int i = 0; i < NUM_PRODUCERS; ++i)
    {
        int *item = new int(i);
        pthread_create(&producer_threads[i], NULL, producer, (void *)item);
    }
    for (int i = 0; i < NUM_CONSUMERS; ++i)
    {
        pthread_create(&consumer_threads[i], NULL, consumer, NULL);
    }
    // Join threads
    for (int i = 0; i < NUM_PRODUCERS; ++i)
    {
        pthread_join(producer_threads[i], NULL);
    }
    for (int i = 0; i < NUM_CONSUMERS; ++i)
    {
        pthread_join(consumer_threads[i], NULL);
    }
    // Destroy semaphores
    sem_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);
    return 0;
}