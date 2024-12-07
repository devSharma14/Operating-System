#include <stdio.h>
#include <stdlib.h>

int philosopherState[5]; // 0 -> Thinking, 1 -> Eating
int chopstick[5];        // 0 -> Available, 1 -> Busy

void releaseChopsticks(int philosopher) {
    int rightChopstick = (philosopher + 1) % 5;
    philosopherState[philosopher] = 0; // Philosopher stops eating
    chopstick[philosopher] = 0;        // Left chopstick released
    chopstick[rightChopstick] = 0;     // Right chopstick released
}

void pickChopsticks(int philosopher) {
    int rightChopstick = (philosopher + 1) % 5;
    // Check if both chopsticks are available
    if (chopstick[philosopher] == 0 && chopstick[rightChopstick] == 0) {
        philosopherState[philosopher] = 1; // Philosopher starts eating
        chopstick[philosopher] = 1;        // Left chopstick is now busy
        chopstick[rightChopstick] = 1;     // Right chopstick is now busy
    } 
    else if (philosopherState[philosopher] == 1) {
        // If already eating, ask if they want to stop
        int stopEating;
        printf("\nPhilosopher %d is already eating. Do you want them to stop? (1 for Yes): ", philosopher);
        scanf("%d", &stopEating);
        if (stopEating) {
            releaseChopsticks(philosopher);
        }
    } 
    else {
        // If chopsticks are busy, philosopher waits
        printf("\nChopsticks %d and %d are busy. Philosopher %d will wait.\n", philosopher, rightChopstick, philosopher);
    }
}

int main() {
    printf("Dining Philosophers Problem\n");
    for (int i = 0; i < 5; i++) {
        philosopherState[i] = 0; // All philosophers start by thinking
        chopstick[i] = 0;        // All chopsticks are available
    }
    int continueSimulation;
    do {
        // Display the current state of each philosopher
        for (int i = 0; i < 5; i++) {
            if (philosopherState[i] == 0) {
                printf("Philosopher %d is Thinking.\n", i);
            } else {
                printf("Philosopher %d is Eating.\n", i);
            }
        }
        int philosopher;
        printf("\nEnter the philosopher who wants to eat (0-4): ");
        scanf("%d", &philosopher);
        pickChopsticks(philosopher);
        printf("\nDo you want to continue? (1 for Yes, 0 for No): ");
        scanf("%d", &continueSimulation);
    } while (continueSimulation == 1);
    return 0;
}
