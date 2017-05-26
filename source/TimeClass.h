#pragma once

namespace Time
{
  long long Clock();

  class Timer
  {
    public:
      Timer();
      double GetFrame();
      double GetTotal();
      void Start();
      void Stop();
      void Reset();
    private:
      long long	FrameTime;
      long long FrameStart;
      long long total;
  };
}