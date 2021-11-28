#include <bits/stdc++.h>
using namespace std;

struct Process
{
    int processID;
    int arrivalTime;
    int burstTime;
    int priority;
    int completeTime;
    int waitTime;
    int turnAroundTime;
};

struct GanttChartData
{
    int processID;
    int startTime;
    int endTime;
};

int totalProcesses, totalWaitingTime, totalTurnAroundTime;
struct Process proc[9];
vector<struct GanttChartData> ganttChart;

int Digits(int n)
{
    if (n == 0)
        return 1;
    int count = 0;
    while (n != 0)
    {
        n = n / 10;
        ++count;
    }
    return count;
}

void Space(int n)
{
    for (int i = 0; i < n; i++)
    {
        cout << " ";
    }
}

bool CompareProcessFCFS(struct Process p1, struct Process p2)
{
    if (p1.arrivalTime != p2.arrivalTime)
    {
        return p1.arrivalTime < p2.arrivalTime;
    }
    else
    {
        return p1.processID < p2.processID;
    }
}

bool CompareProcessPriority(struct Process p1, struct Process p2);

bool CompareProcessRoundRobin(struct Process p1, struct Process p2);

bool CompareProcessTable(struct Process p1, struct Process p2)
{
    return p1.processID < p2.processID;
}

bool CompareGanttChart(struct GanttChartData g1, struct GanttChartData g2)
{
    return g1.startTime < g2.startTime;
}

void PrintCell(int x, int n)
{
    int l;
    if (n % 2 == 0)
    {
        l = n / 2 - 1;
    }
    else
    {
        l = n / 2;
    }
    cout << "|";
    Space(l);
    cout << x;
    Space(n - l - Digits(x));
}

void PrintTable()
{
    sort(proc, proc + totalProcesses, CompareProcessTable);
    cout << "\n+************+**************+************+***************+******************+**************+\n";
    cout << "| Process ID | Arrival Time | Burst Time | Complete Time | Turn Around Time | Waiting Time |\n";
    cout << "+************+**************+************+***************+******************+**************+\n";
    for (int i = 0; i < totalProcesses; i++)
    {
        PrintCell(proc[i].processID, 12);
        PrintCell(proc[i].arrivalTime, 14);
        PrintCell(proc[i].burstTime, 12);
        PrintCell(proc[i].completeTime, 15);
        PrintCell(proc[i].turnAroundTime, 18);
        PrintCell(proc[i].waitTime, 14);
        cout << "|\n";
        cout << "+------------+--------------+------------+---------------+------------------+--------------+\n";
    }
    cout << "\n";
}

void PrintData()
{
    cout << "Average Waiting Time = " << (float)totalWaitingTime / totalProcesses << "\n";
    cout << "Average Turn Around Time = " << (float)totalTurnAroundTime / totalProcesses << "\n";
}

void PrintGanttChart()
{
    cout << "\n";
    cout << "Gantt Chart\n";
    cout << "-----------\n";
    int n = ganttChart.size();
    int theEnd = ganttChart[n - 1].endTime;
    int idx = 0, printedFor = 0;
    cout << endl;
    cout << 0;
    for (int i = 0; i < theEnd; i++)
    {
        if (ganttChart[idx].startTime == i && printedFor != i)
        {
            cout << i;
            printedFor = i;
        }
        if (ganttChart[idx].endTime == i && printedFor != i)
        {
            cout << i;
            printedFor = i;
            idx++;
        }
        cout << "  ";
    }
    cout << theEnd << "\n";

    idx = 0;
    printedFor = 0;
    cout << "+";
    for (int i = 0; i < theEnd; i++)
    {
        if (ganttChart[idx].startTime == i && printedFor != i)
        {
            cout << "+";
            printedFor = i;
        }
        if (ganttChart[idx].endTime == i && printedFor != i)
        {
            cout << "+";
            printedFor = i;
            idx++;
        }
        cout << "--";
    }
    cout << "+";

    printedFor = 0;
    idx = 0;
    cout << "\n|";
    for (int i = 0; i < theEnd; i++)
    {
        if (ganttChart[idx].startTime == i && printedFor != i)
        {
            cout << "|";
            printedFor = i;
        }
        if (ganttChart[idx].endTime == i && printedFor != i)
        {
            cout << "|";
            printedFor = i;
            idx++;
        }
        if (ganttChart[idx].startTime == i)
        {
            cout << "P" << ganttChart[idx].processID;
        }
        else
        {
            cout << "  ";
        }
    }
    cout << "|";

    idx = 0;
    printedFor = 0;
    cout << "\n+";
    for (int i = 0; i < theEnd; i++)
    {
        if (ganttChart[idx].startTime == i && printedFor != i)
        {
            cout << "+";
            printedFor = i;
        }
        if (ganttChart[idx].endTime == i && printedFor != i)
        {
            cout << "+";
            printedFor = i;
            idx++;
        }
        cout << "--";
    }
    cout << "+";

    cout << "\n\n";
    ganttChart.clear();
}

void FCFS()
{
    cout << "\n==================================================\n";
    cout << "First Come First Serve (FCFS) Scheduling Algorithm\n";
    cout << "==================================================\n";
    sort(proc, proc + totalProcesses, CompareProcessFCFS);
    int currTime = proc[0].arrivalTime;
    totalWaitingTime = 0;
    totalTurnAroundTime = 0;
    for (int i = 0; i < totalProcesses; i++)
    {
        struct GanttChartData g;
        currTime = max(currTime, proc[i].arrivalTime);
        proc[i].waitTime = currTime - proc[i].arrivalTime;
        proc[i].turnAroundTime = proc[i].waitTime + proc[i].burstTime;
        proc[i].completeTime = proc[i].turnAroundTime + proc[i].arrivalTime;
        totalWaitingTime += proc[i].waitTime;
        totalTurnAroundTime += proc[i].turnAroundTime;
        g.processID = proc[i].processID;
        g.startTime = proc[i].completeTime - proc[i].burstTime;
        g.endTime = proc[i].completeTime;
        ganttChart.push_back(g);
        currTime += proc[i].burstTime;
    }
    PrintTable();
    PrintData();
    PrintGanttChart();
}

void SJF()
{
    cout << "\n=============================================\n";
    cout << "Shortest Job First (SJF) Scheduling Algorithm\n";
    cout << "=============================================\n";
    int currTime = 0, remTime[totalProcesses];
    int prevProcess = -1, currProcess = -1, completed = 0;
    struct GanttChartData g;
    totalTurnAroundTime = 0;
    totalWaitingTime = 0;
    for (int i = 0; i < totalProcesses; i++)
    {
        remTime[i] = proc[i].burstTime;
    }
    while (completed != totalProcesses)
    {
        int minTime = INT_MAX;
        prevProcess = currProcess;
        for (int i = 0; i < totalProcesses; i++)
        {
            if (proc[i].arrivalTime <= currTime && remTime[i] < minTime && remTime[i] > 0)
            {
                minTime = remTime[i];
                currProcess = i;
            }
        }
        if (currProcess != prevProcess || minTime == INT_MAX)
        {
            if (prevProcess != -1)
            {
                ganttChart.push_back(g);
            }
            g.processID = currProcess + 1;
            g.startTime = currTime;
            g.endTime = currTime + 1;
            if (prevProcess != -1 && remTime[prevProcess] == 0)
            {
                proc[prevProcess].completeTime = currTime;
                proc[prevProcess].turnAroundTime = currTime - proc[prevProcess].arrivalTime;
                proc[prevProcess].waitTime = proc[prevProcess].turnAroundTime - proc[prevProcess].burstTime;
                totalTurnAroundTime += proc[prevProcess].turnAroundTime;
                totalWaitingTime += proc[prevProcess].waitTime;
                completed++;
            }
        }
        else
        {
            g.endTime++;
        }
        if (currProcess >= 0)
        {
            remTime[currProcess]--;
        }
        currTime++;
    }
    PrintTable();
    PrintData();
    PrintGanttChart();
}

void Priority();
void RoundRobin();

int main()
{
    cout << "Enter number of processes: ";
    cin >> totalProcesses;
    int arr[4][3] = {{0,8,1},{1,4,1},{2,9,1},{3,5,1}};
    for(int i=0; i<4; i++)
    {
        proc[i].processID = i + 1;
        proc[i].arrivalTime=arr[i][0];
        proc[i].burstTime=arr[i][1];
        proc[i].priority=arr[i][2];
    }
    // for (int i = 0; i < totalProcesses; i++)
    // {
    //     cout << "\nEnter details for procsess " << i + 1 << ": \n";
    //     cout << "-------------------------------\n";
    //     proc[i].processID = i + 1;
    //     cout << "Arrival Time: ";
    //     cin >> proc[i].arrivalTime;
    //     cout << "Burst Time: ";
    //     cin >> proc[i].burstTime;
    //     if (proc[i].burstTime == 0)
    //     {
    //         printf("ERROR: Burst Time cannot be 0.\n");
    //         exit(0);
    //     }
    //     cout << "Priority: ";
    //     cin >> proc[i].priority;
    // }
    FCFS();
    SJF();
}
