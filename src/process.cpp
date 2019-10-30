#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "process.h"
#include "linux_parser.h"

using std::string;
using std::to_string;
using std::vector;

// TODO: Return this process's ID
int Process::Pid() { return pid; }

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() { 
    long total_time = LinuxParser::ActiveJiffies(pid);
    long up_time = LinuxParser::UpTime();
    long start_time = LinuxParser::UpTime(pid);

    float seconds = up_time - (start_time *1.0 / sysconf(_SC_CLK_TCK));
    float cpu_usage = 100 * ((total_time *1.0 / sysconf(_SC_CLK_TCK)) / seconds);

    this->cpuUsage = cpu_usage;
    return cpu_usage;
}

// TODO: Return the command that generated this process
string Process::Command() { return LinuxParser::Command(pid); }

// TODO: Return this process's memory utilization
string Process::Ram() { return LinuxParser::Ram(pid); }

// TODO: Return the user (name) that generated this process
string Process::User() { return LinuxParser::User(pid); }

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() { return LinuxParser::UpTime(pid); }

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a) const { return this->cpuUsage < a.cpuUsage; }