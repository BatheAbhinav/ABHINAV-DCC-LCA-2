#include <stdio.h>

int processes[20];
int n;
int coordinator;

void input() {
    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("\nEnter status of each process (1 = Active, 0 = Failed):\n");
    for (int i = 1; i <= n; i++) {
        printf("Process %d: ", i);
        scanf("%d", &processes[i]);
    }

    coordinator = -1;
    for (int i = n; i >= 1; i--) {
        if (processes[i] == 1) {
            coordinator = i;
            break;
        }
    }
}

void display() {
    printf("\nProcess Status:\n");
    for (int i = 1; i <= n; i++) {
        if (processes[i] == 1)
            printf("Process %d: Active\n", i);
        else
            printf("Process %d: Failed\n", i);
    }
}

void election(int initiator) {
    printf("\nProcess %d is initiating election...\n", initiator);

    for (int i = initiator + 1; i <= n; i++) {
        if (processes[i] == 1) {
            printf("Process %d sends ELECTION to Process %d\n", initiator, i);
            election(i);
            return;
        }
    }

    coordinator = initiator;
    printf("\n>>> Process %d becomes the COORDINATOR <<<\n", coordinator);
}

int findInitiator() {
    for (int i = coordinator - 1; i >= 1; i--) {
        if (processes[i] == 1)
            return i;
    }
    return -1;
}

void failProcess() {
    int p;
    printf("Enter process number to fail: ");
    scanf("%d", &p);

    if (processes[p] == 0) {
        printf("Process %d already failed.\n", p);
        return;
    }

    processes[p] = 0;
    printf("Process %d has failed.\n", p);

    if (p == coordinator) {
        printf("Coordinator failed! Starting election...\n");

        int initiator = findInitiator();
        if (initiator != -1)
            election(initiator);
        else
            printf("No active processes available.\n");
    }
}

void recoverProcess() {
    int p;
    printf("Enter process number to recover: ");
    scanf("%d", &p);

    if (processes[p] == 1) {
        printf("Process %d already active.\n", p);
        return;
    }

    processes[p] = 1;
    printf("Process %d has recovered.\n", p);

    if (p > coordinator) {
        printf("Higher priority process recovered. Starting election...\n");
        election(p);
    } else {
        printf("No election needed.\n");
    }
}

void showCoordinator() {
    if (coordinator != -1 && processes[coordinator] == 1)
        printf("Current Coordinator is Process %d\n", coordinator);
    else
        printf("No active coordinator.\n");
}

void menu() {
    int choice;

    do {
        printf("\n--- MENU ---\n");
        printf("1. Display Processes\n");
        printf("2. Fail a Process\n");
        printf("3. Recover a Process\n");
        printf("4. Start Election\n");
        printf("5. Show Coordinator\n");
        printf("6. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: display(); break;
            case 2: failProcess(); break;
            case 3: recoverProcess(); break;
            case 4: {
                int p;
                printf("Enter initiator: ");
                scanf("%d", &p);
                if (processes[p] == 1)
                    election(p);
                else
                    printf("Process is failed.\n");
                break;
            }
            case 5: showCoordinator(); break;
            case 6: {
                printf("Exiting...\n");
                return;
            }
            default: printf("Invalid choice!\n");
        }

    } while (choice <= 6);
}

int main() {
    input();
    menu();
    return 0;
}