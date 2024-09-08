#include <iostream>
using namespace std;

int main() {
    int i, limit, total = 0, x, counter = 0, time_quantum;
    int wait_time = 0, turnaround_time = 0, arrival_time[10], burst_time[10], temp[10];
    float average_wait_time, average_turnaround_time;

    cout << "Enter Total Number of Processes: ";
    cin >> limit;
    x = limit; // x is the remaining number of processes

    for (i = 0; i < limit; i++) {
        cout << "\nEnter Details of Process[" << i + 1 << "]\n";
        cout << "Arrival Time: ";
        cin >> arrival_time[i];
        cout << "Burst Time: ";
        cin >> burst_time[i];
        temp[i] = burst_time[i]; // Copy burst times into temp array
    }

    cout << "\nEnter Time Quantum: ";
    cin >> time_quantum;

    cout << "\nProcess ID\tBurst Time\tTurnaround Time\tWaiting Time\n";

    i = 0;
    while (x != 0) {
        if (temp[i] > 0) {
            if (temp[i] <= time_quantum && temp[i] > 0) {
                total += temp[i]; // total is the current time
                temp[i] = 0;
                counter = 1;
            } else {
                temp[i] -= time_quantum;
                total += time_quantum;
            }

            if (temp[i] == 0 && counter == 1) {
                x--; // Decrement process count
                cout << "\nProcess[" << i + 1 << "]\t\t" << burst_time[i] << "\t\t" << total - arrival_time[i] << "\t\t\t" << total - arrival_time[i] - burst_time[i];
                wait_time += total - arrival_time[i] - burst_time[i];
                turnaround_time += total - arrival_time[i];
                counter = 0;
            }
        }

        i = (i + 1) % limit; // Ensure circular process scheduling
    }

    average_wait_time = (float)wait_time / limit;
    average_turnaround_time = (float)turnaround_time / limit;

    cout << "\n\nAverage Waiting Time: " << average_wait_time;
    cout << "\nAvg Turnaround Time: " << average_turnaround_time << endl;

    return 0;
}
