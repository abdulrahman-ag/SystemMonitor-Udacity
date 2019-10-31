#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <iostream>
#include <map>

#include "linux_parser.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, kernel;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> kernel;
  }
  return kernel;
}

vector<int> pids;
// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

// TODO: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() { 
  string line;

  string key;
  float value;
  std::map<string,float> data;

  std::ifstream stream(kProcDirectory + kMeminfoFilename);
  if (stream.is_open()) {
    while (std::getline(stream, line)) {
      std::replace(line.begin(), line.end(), ':', ' ');
      line.replace(line.end()-2,line.end(), " ");
      std::istringstream linestream(line);
      linestream >> key >> value;
      data.insert(std::pair(key, value));
    }
  }
  
  return (data.find("MemTotal")->second - data.find("MemFree")->second) / data.find("MemTotal")->second; 
}

// TODO: Read and return the system uptime
long LinuxParser::UpTime() { 
  long time = -1;
  string line;
  
  std::ifstream stream(kProcDirectory + kUptimeFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
  	std::istringstream linestream(line);
    linestream >> time;
  }
  
  return time;
}

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { 
  return ActiveJiffies() + IdleJiffies();
}

// TODO:  Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid) { 
  string line = "";
  long int  utime = -100, stime = -100, cutime = -100, cstime = -100;
  string x;

  std::ifstream stream(kProcDirectory + to_string(pid) + kStatFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    for (int i =1; i<=12 ; i++){
      linestream >> x;
    }
    linestream >> utime >> stime >> cutime >> cstime;
    
  }

  return utime + stime;
}

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { 
  vector<string> cpuUtilizationData = CpuUtilization();
  string aggregateCPU = cpuUtilizationData[0];

  long user, nice, kernal_mode_procs, irq, softirq, steal;
  string x;

  std::istringstream linestream(aggregateCPU);
  linestream >> x >> user >> nice >> kernal_mode_procs >> x >> x >> irq >> softirq >> steal >> x >> x;
  //linestream >> cpu >> user >> nice >> kernal_mode_procs >> idle >> iowait >> irq >> softirq >> steal >> guest >> guest_nice;

  return user + nice + kernal_mode_procs + irq + softirq + steal;   
}

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { 
  vector<string> cpuUtilizationData = CpuUtilization();
  string aggregateCPU = cpuUtilizationData[0];

  long idle, iowait;
  string x;

  std::istringstream linestream(aggregateCPU);
  linestream >> x >> x >> x >> x >> idle >> iowait >> x >> x >> x >> x >> x;
  //linestream >> cpu >> user >> nice >> kernal_mode_procs >> idle >> iowait >> irq >> softirq >> steal >> guest >> guest_nice;

  return idle + iowait; 
}

// TODO: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() {
  vector<string> cpuUtilizationData;
  string line;

  std::ifstream stream(kProcDirectory + kStatFilename);
  if (stream.is_open()) {
    while (std::getline(stream, line)) {
      if(line.substr(0,3) == "cpu"){
        cpuUtilizationData.push_back(line);
      }
    }
  }
  
  return cpuUtilizationData;
}

// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses() {
  int totalProcesses = -1;
  string line, key;
  
  std::ifstream stream(kProcDirectory + kStatFilename);
  if (stream.is_open()) {
    while (std::getline(stream, line)) {
      std::istringstream linestream(line);
      linestream >> key;
      
      if(key == "processes")
      {
        linestream >> totalProcesses;
        break;
      }
    }
  }
  
  return totalProcesses;
}

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses() {
  int runningProcesses = -1;
  string line, key;
  
  std::ifstream stream(kProcDirectory + kStatFilename);
  if (stream.is_open()) {
    while (std::getline(stream, line)) {
      std::istringstream linestream(line);
      linestream >> key;
      
      if(key == "procs_running")
      {
        linestream >> runningProcesses;
        break;
      }
    }
  }
  
  return runningProcesses;
}


// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid) {
  string command = "[empty]";

  std::ifstream stream(kProcDirectory + to_string(pid) + kCmdlineFilename);
  if (stream.is_open()) {
    std::getline(stream, command);
  }
  return command; 
}

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid) { 
  string ram = "[empty]", line = "", key;

  std::ifstream stream(kProcDirectory + to_string(pid) + kStatusFilename);
  if (stream.is_open()) {
    while (std::getline(stream, line)) {
      std::istringstream linestream(line);
      linestream >> key;
      
      if(key == "VmSize:")
      {
        linestream >> ram;
        break;
      }
    }
  }
  return ram; 
}

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid) {
  string uid = "[empty]", line = "", key;

  std::ifstream stream(kProcDirectory + to_string(pid) + kStatusFilename);
  if (stream.is_open()) {
    while (std::getline(stream, line)) {
      std::istringstream linestream(line);
      linestream >> key;
      
      if(key == "Uid:")
      {
        linestream >> uid;
        break;
      }
    }
  }
  return uid;
}

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid) {
  string uid = Uid(pid);
  string username = "[empty]", line = "", x, id;

  std::ifstream stream(kPasswordPath);
  if (stream.is_open()) {
    while (std::getline(stream, line)) {
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream(line);
      linestream >> username >> x >> id;
      
      if(id == uid)
      {
        break;
      }
    }
  }
  return username;
}

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid) {
  string line = "";
  string upTime ;

  std::ifstream stream(kProcDirectory + to_string(pid) + kStatFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    for (int i =1; i<=22 ; i++){
      linestream >> upTime;
    }
  }

  return std::stoi(upTime);
}