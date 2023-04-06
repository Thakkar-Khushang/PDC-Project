#include <iostream>
#include <algorithm>
#include <iomanip>
#include <string.h>
#include <time.h>
using namespace std;
/*
AT - Arrival Time of the process
BT - Burst time of the process
ST - Start time of the process
CT - Completion time of the process
TAT - Turnaround time of the process
WT - Waiting time of the process
RT - Response time of the process
Formulas used:
TAT = CT - AT
WT = TAT - BT
RT = ST - AT
*/
struct process
{
    int pid;
    int arrival_time;
    int burst_time;
    int start_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
    int response_time;
};
int main()
{
    int pro = 100;
    int arr[100] = {95, 79, 21, 44, 14, 55, 46, 32, 83, 9, 47, 8, 49, 51, 75, 48, 74, 49, 1, 35, 82, 76, 79, 20, 31, 35, 42, 22, 53,
                    87, 40, 70, 65, 11, 7, 93, 11, 49, 21, 38, 54, 14, 93, 6, 14, 67, 15, 36, 99, 87, 88, 59, 89, 99, 6, 74, 5, 88, 70, 15, 90, 15, 77,
                    4, 7, 60, 81, 30, 92, 52, 50, 97, 65, 21, 96, 63, 38, 62, 13, 7, 91, 82, 38, 23, 23, 82, 71, 88, 4, 12, 4, 25, 73, 24, 87, 7, 75, 72,
                    9, 38};
    int bur[100] = {88, 49, 53, 14, 62, 74, 49, 88, 52, 80, 85, 5, 59, 8, 48, 44, 92, 89, 99, 42, 18, 52, 22, 43, 11, 96, 29, 100,
                    47, 0, 4, 8, 53, 13, 40, 95, 80, 60, 73, 55, 66, 76, 60, 31, 31, 68, 63, 6, 51, 81, 93, 96, 84, 73, 68, 27, 68, 91, 66, 57, 11, 53,
                    68, 94, 56, 20, 98, 89, 13, 57, 89, 65, 84, 47, 95, 33, 97, 26, 80, 31, 55, 37, 28, 19, 33, 85, 7, 52, 81, 45, 42, 99, 57, 37, 98,
                    77, 3, 1, 84, 33};
    double time_spent = 0.0;
    int n;
    struct process p[100];
    float avg_turnaround_time;
    float avg_waiting_time;
    float avg_response_time;
    float cpu_utilisation;
    int total_turnaround_time = 0;
    int total_waiting_time = 0;
    int total_response_time = 0;
    int total_idle_time = 0;
    float throughput;
    int is_completed[100];
    memset(is_completed, 0, sizeof(is_completed));
    cout << setprecision(2) << fixed;
    n = pro;
    for (int i = 0; i < n; i++)
    {
        p[i].arrival_time = arr[i];
        p[i].burst_time = bur[i];
        p[i].pid = i + 1;
    }
    clock_t begin = clock();
    int current_time = 0;
    int completed = 0;
    int prev = 0;
    while (completed != n)
    {
        int idx = -1;
        int mn = 10000000;
        for (int i = 0; i < n; i++)
        {
            if (p[i].arrival_time <= current_time && is_completed[i] == 0)
            {
                if (p[i].burst_time < mn)
                {
                    mn = p[i].burst_time;
                    idx = i;
                }
                if (p[i].burst_time == mn)
                {
                    if (p[i].arrival_time < p[idx].arrival_time)
                    {
                        mn = p[i].burst_time;
                        idx = i;
                    }
                }
            }
        }
        if (idx != -1)
        {
            p[idx].start_time = current_time;
            p[idx].completion_time = p[idx].start_time + p[idx].burst_time;
            p[idx].turnaround_time = p[idx].completion_time - p[idx].arrival_time;
            p[idx].waiting_time = p[idx].turnaround_time - p[idx].burst_time;
            p[idx].response_time = p[idx].start_time - p[idx].arrival_time;
            total_turnaround_time += p[idx].turnaround_time;
            total_waiting_time += p[idx].waiting_time;
            total_response_time += p[idx].response_time;
            total_idle_time += p[idx].start_time - prev;
            is_completed[idx] = 1;
            completed++;
            current_time = p[idx].completion_time;
            prev = current_time;
        }
        else
        {
            current_time++;
        }
    }
    int min_arrival_time = 10000000;
    int max_completion_time = -1;
    for (int i = 0; i < n; i++)
    {
        min_arrival_time = min(min_arrival_time, p[i].arrival_time);
        max_completion_time = max(max_completion_time, p[i].completion_time);
    }
    avg_turnaround_time = (float)total_turnaround_time / n;
    avg_waiting_time = (float)total_waiting_time / n;
    avg_response_time = (float)total_response_time / n;
    cpu_utilisation = ((max_completion_time - total_idle_time) / (float)max_completion_time) * 100;
    throughput = float(n) / (max_completion_time - min_arrival_time);
    cout << endl
         << endl;
    cout << "#P\t"
         << "AT\t"
         << "BT\t"
         << "ST\t"
         << "CT\t"
         << "TAT\t"
         << "WT\t"
         << "RT\t"
         << "\n"
         << endl;
    for (int i = 0; i < n; i++)
    {
        cout << p[i].pid << "\t" << p[i].arrival_time << "\t" << p[i].burst_time << "\t" << p[i].start_time << "\t" << p[i].completion_time << "\t"<<p[i].turnaround_time<<"\t "<<p[i].waiting_time<<"\t "<<p[i].response_time<<"\t "<<"\n "<<endl;
    }
    clock_t end = clock();
    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
    cout << "SJF Serial\n";
    cout << "Average Turnaround Time = " << avg_turnaround_time << endl;
    cout << "Average Waiting Time = " << avg_waiting_time << endl;
    cout << "Average Response Time = " << avg_response_time << endl;
    cout << "CPU Utilization = " << cpu_utilisation << "%" << endl;
    cout << "Throughput = " << throughput << " process/unit time" << endl;
    return 0;
}
