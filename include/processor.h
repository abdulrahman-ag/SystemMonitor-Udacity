#ifndef PROCESSOR_H
#define PROCESSOR_H

class Processor {
 public:
  float Utilization();  // TODO: See src/processor.cpp

  void User(float user){this->user = user;};
  void Nice(float nice){this->nice = nice;};
  void Kernal_mode_procs(float kernal_mode_procs){this->kernal_mode_procs = kernal_mode_procs;};
  void Idle(float idle){this->idle = idle;};
  void Iowait(float iowait){this->iowait = iowait;};
  void Irq(float irq){this->irq = irq;};
  void Softirq(float softirq){this->softirq = softirq;};
  void Steal(float steal){this->steal = steal;};
  void Guest(float guest){this->guest = guest;};
  void Guest_nice(float guest_nice){this->guest_nice = guest_nice;};
  // TODO: Declare any necessary private members
 private:
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
};

#endif