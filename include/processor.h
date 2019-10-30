#ifndef PROCESSOR_H
#define PROCESSOR_H

class Processor {
 public:
  float Utilization();  // TODO: See src/processor.cpp

  void IdleJiffes(float idleJiffies){this->idleJiffies = idleJiffies;};
  void ActiveJiffes(float activeJiffies){this->activeJiffies = activeJiffies;};
  void Jiffes(float jiffies){this->jiffies = jiffies;};
  // TODO: Declare any necessary private members
 private:
  float activeJiffies;
  float idleJiffies;
  float jiffies;

};

#endif