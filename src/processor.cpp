#include "processor.h"
#include "system.h"
// TODO: Return the aggregate CPU utilization
float Processor::Utilization() { 
    return activeJiffies / jiffies;
}