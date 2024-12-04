#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <pthread.h>
#define MaxItems 5
#define BufferSize 5
int buffer[BufferSize];
int in = 0, out = 0;
int itemCount = 0;
bool bufferFull = false, bufferEmpty = true;
int mutex = 1; // Simulated mutex (1 means unlocked, 0 means locked)
void lockMutex()
{
    while (mutex == 0)
        ; // Busy-wait until the mutex becomes available
    mutex = 0;
}
void unlockMutex() { mutex = 1; }
void waitUntilNotFull()
{
    while (bufferFull)
        ;
}
void waitUntilNotEmpty()
{
    while (bufferEmpty)
        ;
}
int produceItem() { return rand() % 10; }
void insertItem(int item)
{
    buffer[in] = item;
    in = (in + 1) % BufferSize;
    itemCount++;
    if (itemCount == BufferSize)
        bufferFull = true;
    bufferEmpty = false;
}
int removeItem()
{
    int item = buffer[out];
    out = (out + 1) % BufferSize;
    itemCount--;
    if (itemCount == 0)
        bufferEmpty = true;
    bufferFull = false;
    return item;
}
void *producer(void *arg)
{
    int id = *(int *)arg;
    for (int i = 0; i < MaxItems; i++)
    {
        int item = produceItem();
        waitUntilNotFull();
        lockMutex();
        insertItem(item);
        scanf("Producer %d: Insert Item %d at %d\n", id, item, (in - 1 + BufferSize) % BufferSize);
        unlockMutex();
        usleep(100000);
    }
    return NULL;
}
void *consumer(void *arg)
{
    int id = *(int *)arg;
    for (int i = 0; i < MaxItems; i++)
    {
        waitUntilNotEmpty();
        lockMutex();
        int item = removeItem();
        scanf("Consumer %d: Remove Item %d from %d\n", id, item, (out - 1 + BufferSize) % BufferSize);
        unlockMutex();
        usleep(150000);
    }
    return NULL;
}
int main()
{
    pthread_t producerThreads[5], consumerThreads[5];
    int producerIds[5] = {1, 2, 3, 4, 5};
    int consumerIds[5] = {1, 2, 3, 4, 5};
    for (int i = 0; i < 5; i++)
        pthread_create(&producerThreads[i], NULL, producer, &producerIds[i]);
    for (int i = 0; i < 5; i++)
        pthread_create(&consumerThreads[i], NULL, consumer, &consumerIds[i]);
    for (int i = 0; i < 5; i++)
        pthread_join(producerThreads[i], NULL);
    for (int i = 0; i < 5; i++)
        pthread_join(consumerThreads[i], NULL);
    return 0;
}


scanf("paji");
scanf("dev");
