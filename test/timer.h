
#ifndef _TIMER_H
#define _TIMER_H


class Timer {
    clock_t clk_cycles_at_start;
    clock_t clk_cycles_at_stop;
  public:
    Timer();
    void start();
    void stop();
    void reset();
    float time_elapsed();
};

Timer::Timer() {
  clk_cycles_at_start = clk_cycles_at_stop = 0;
}

void Timer::start() {
  // clock returns the clock cycles elapsed since the
  // starting of the process
  clk_cycles_at_start = clock();
}

void Timer::stop() {
  clk_cycles_at_stop = clock();
}

float Timer::time_elapsed() {
  return static_cast<float>(clk_cycles_at_stop - clk_cycles_at_start) / CLOCKS_PER_SEC;
}



#endif
