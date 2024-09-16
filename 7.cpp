#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
struct Process
{
    int processID;
    int burstTime;
    int priority;
    int waitingTime;
    int turnaroundTime;
};
bool comparePriority(const Process &a, const Process &b)
{
    return a.priority < b.priority;
}
int main()
{
    int numProcesses;
    cout << "Enter the number of processes: ";
    cin >> numProcesses;
    vector<Process> processes(numProcesses);
    for (int i = 0; i < numProcesses; i++)
    {
        processes[i].processID = i + 1;
        cout << "Enter burst time for process " << i + 1 << ": ";
        cin >> processes[i].burstTime;
        cout << "Enter priority for process " << i + 1 << ": ";
        cin >> processes[i].priority;
    }
    sort(processes.begin(), processes.end(), comparePriority);
    processes[0].waitingTime = 0;
    processes[0].turnaroundTime = processes[0].burstTime;
    for (int i = 1; i < numProcesses; i++)
    {
        processes[i].waitingTime = processes[i - 1].waitingTime + processes[i - 1].burstTime;
        processes[i].turnaroundTime = processes[i].waitingTime + processes[i].burstTime;
    }
    double totalWaitingTime = 0;
    double totalTurnaroundTime = 0;
    for (const Process &p : processes)
    {
        totalWaitingTime += p.waitingTime;
        totalTurnaroundTime += p.turnaroundTime;
    }
    double averageWaitingTime = totalWaitingTime / numProcesses;
    double averageTurnaroundTime = totalTurnaroundTime / numProcesses;
    cout << "Process\tBurst Time\tPriority\tWaiting Time\tTurnaround Time\n";
    for (const Process &p : processes)
    {
        cout << p.processID << "\t\t" << p.burstTime << "\t\t" << p.priority << "\t\t" << p.waitingTime << "\t\t" << p.turnaroundTime << endl;
    }
    cout << "\nAverage Waiting Time: " << averageWaitingTime << endl;
    cout << "Average Turnaround Time: " << averageTurnaroundTime << endl;
    return 0;
}