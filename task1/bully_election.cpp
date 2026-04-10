#include <bits/stdc++.h>
using namespace std;

class BullyElection {

    public:
        int processes[20];
        int n;
        int coordinator;
        void input() {
            cout << "Enter number of processes: ";
            cin >> n;

            cout << "\nEnter status of each process (1 = Active, 0 = Failed):\n";
            for (int i = 1; i <= n; i++) {
                cout << "Process " << i << ": ";
                cin >> processes[i];
            }

            // Find initial coordinator (highest active process)
            coordinator = -1;
            for (int i = n; i >= 1; i--) {
                if (processes[i] == 1) {
                    coordinator = i;
                    break;
                }
            }
        }

        // Display processes
        void display() {
            cout << "\nProcess Status:\n";
            for (int i = 1; i <= n; i++) {
                if (processes[i] == 1)
                    cout << "Process " << i << ": Active\n";
                else
                    cout << "Process " << i << ": Failed\n";
            }
        }

        // Election function
        void election(int initiator) {
            cout << "\nProcess " << initiator << " is initiating election...\n";

            for (int i = initiator + 1; i <= n; i++) {
                if (processes[i] == 1) {
                    cout << "Process " << initiator
                        << " sends ELECTION to Process " << i << endl;

                    election(i); // higher process takes over
                    return;
                }
            }

            coordinator = initiator;
            cout << "\n>>> Process " << coordinator
                << " becomes the COORDINATOR <<<\n";
        }

        // Find initiator when coordinator fails
        int findInitiator() {
            for (int i = coordinator - 1; i >= 1; i--) {
                if (processes[i] == 1)
                    return i;
            }
            return -1;
        }

        // Fail a process
        void failProcess() {
            int p;
            cout << "Enter process number to fail: ";
            cin >> p;

            if (processes[p] == 0) {
                cout << "Process " << p << " already failed.\n";
                return;
            }

            processes[p] = 0;
            cout << "Process " << p << " has failed.\n";

            if (p == coordinator) {
                cout << "Coordinator failed! Starting election...\n";

                int initiator = findInitiator();
                if (initiator != -1)
                    election(initiator);
                else
                    cout << "No active processes available.\n";
            }
        }

        // Recover a process
        void recoverProcess() {
            int p;
            cout << "Enter process number to recover: ";
            cin >> p;

            if (processes[p] == 1) {
                cout << "Process " << p << " already active.\n";
                return;
            }

            processes[p] = 1;
            cout << "Process " << p << " has recovered.\n";

            if (p > coordinator) {
                cout << "Higher priority process recovered. Starting election...\n";
                election(p);
            } else {
                cout << "No election needed.\n";
            }
        }

        // Show coordinator
        void showCoordinator() {
            if (coordinator != -1 && processes[coordinator] == 1)
                cout << "Current Coordinator is Process " << coordinator << endl;
            else
                cout << "No active coordinator.\n";
        }

        // Menu system
        void menu() {
            int choice;

            do {
                cout << "\n--- MENU ---\n";
                cout << "1. Display Processes\n";
                cout << "2. Fail a Process\n";
                cout << "3. Recover a Process\n";
                cout << "4. Start Election\n";
                cout << "5. Show Coordinator\n";
                cout << "6. Exit\n";
                cout << "Enter choice: ";
                cin >> choice;

                switch (choice) {
                    case 1: display(); break;
                    case 2: failProcess(); break;
                    case 3: recoverProcess(); break;
                    case 4: {
                        int p;
                        cout << "Enter initiator: ";
                        cin >> p;
                        if (processes[p] == 1)
                            election(p);
                        else
                            cout << "Process is failed.\n";
                        break;
                    }
                    case 5: showCoordinator(); break;
                    case 6: {
                        cout << "Exiting...\n"; 
                        return;
                    }
                    default: cout << "Invalid choice!\n";
                }

            } while (choice <= 6);
        }
};

int main() {
    BullyElection obj;
    obj.input();
    obj.menu();
    return 0;
}