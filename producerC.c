#include <stdio.h>
#include <stdlib.h>

// Shared variables
int mutex = 1;         // Controls access to the critical section
int itemsInBuffer = 0; // Number of items in the buffer
int bufferSize = 3;    // Maximum size of the buffer
int currentItem = 0;   // Item counter

int wait(int semaphore) {
    return (--semaphore);
}

int signal(int semaphore) {
    return (++semaphore);
}

void producer() {
    // Enter critical section
    mutex = wait(mutex);
    itemsInBuffer = signal(itemsInBuffer); 
    currentItem++;                        
    printf("\nProducer produces item %d", currentItem);
    mutex = signal(mutex);
}

void consumer() {
    mutex = wait(mutex);
    printf("\nConsumer consumes item %d", currentItem);
    currentItem--;                       
    itemsInBuffer = wait(itemsInBuffer);  
    mutex = signal(mutex);
}

int main() {
    int choice;
    printf("Producer-Consumer Problem Simulation\n");
    while (1) {
        printf("\n\n1. Produce\n2. Consume\n3. Exit");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                if (mutex == 1 && itemsInBuffer < bufferSize) {
                    producer();
                } else {
                    printf("\nBuffer is full!");
                }
                break;

            case 2:
                if (mutex == 1 && itemsInBuffer > 0) {
                    consumer();
                } else {
                    printf("\nBuffer is empty!");
                }
                break;

            case 3:
                printf("\nExiting...");
                exit(0);
                break;

            default:
                printf("\nInvalid choice. Try again.");
        }
    }
    return 0;
}
