#include "processor.h"
#include "system.h"
// TODO: Return the aggregate CPU utilization
float Processor::Utilization() {  
    float Total_CPU_time_since_boot = user + nice + kernal_mode_procs + idle + iowait + irq + softirq + steal;

    float Total_CPU_Idle_time_since_boot = idle + iowait;

    float Total_CPU_usage_time_since_boot = Total_CPU_time_since_boot - Total_CPU_Idle_time_since_boot;

    return Total_CPU_usage_time_since_boot / Total_CPU_time_since_boot;;
}