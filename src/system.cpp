#include <unistd.h>
#include <cstddef>
#include <set>
#include <string>
#include <vector>
#include <iostream>

#include "process.h"
#include "processor.h"
#include "system.h"
#include "linux_parser.h"

using std::set;
using std::size_t;
using std::string;
using std::vector;

// TODO: Return the system's CPU
Processor& System::Cpu() { 
    vector<string> cpuUtilizationData = LinuxParser::CpuUtilization();
    std::string cpu;
    float user;
    float nice;
    float kernal_mode_procs;
    float idle;
    float iowait;
    float irq;
    float softirq;
    float steal;
    float guest;
    float guest_nice;

    string aggregateCPU = cpuUtilizationData[0];
    std::istringstream linestream(aggregateCPU);
    linestream >> cpu >> user >> nice >> kernal_mode_procs >> idle >> iowait >> irq >> softirq >> steal >> guest >> guest_nice;
    cpu_.User(user);
    cpu_.Nice(nice);
    cpu_.Kernal_mode_procs(kernal_mode_procs);
    cpu_.Idle(idle);
    cpu_.Iowait(iowait);
    cpu_.Irq(irq);
    cpu_.Softirq(softirq);
    cpu_.Steal(steal);
    cpu_.Guest(guest);
    cpu_.Guest_nice(guest_nice);

    return cpu_;
}

// TODO: Return a container composed of the system's processes
vector<Process>& System::Processes() { 
    vector<int> pids = LinuxParser::Pids();

    for(int i=0 ; i<pids.size() ; i++){
        processes_.push_back(Process(pids[i]));
    }
    
    return processes_; 
}


// TODO: Return the system's kernel identifier (string)
std::string System::Kernel() { return LinuxParser::Kernel(); }

// TODO: Return the system's memory utilization
float System::MemoryUtilization() { return LinuxParser::MemoryUtilization(); }

// TODO: Return the operating system name
std::string System::OperatingSystem() { return LinuxParser::OperatingSystem(); }

// TODO: Return the number of processes actively running on the system
int System::RunningProcesses() { return LinuxParser::RunningProcesses(); }

// TODO: Return the total number of processes on the system
int System::TotalProcesses() { return LinuxParser::TotalProcesses(); }

// TODO: Return the number of seconds since the system started running
long int System::UpTime() { return LinuxParser::UpTime(); }