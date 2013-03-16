// Originally from GraphCT, version 0.6.0
// License: GeorgiaTech

#include "defs.h"

double timer(void) {
#if defined(__MTA__)
  return((double)mta_get_clock(0) / mta_clock_freq());
#elif defined(__MACH__)
  static mach_timebase_info_data_t info;
  mach_timebase_info(&info);
  uint64_t now = mach_absolute_time();
  now *= info.numer;
  now /= info.denom;
  return 1.0e-9 * (double)now;
#elif defined(__SIMONS_MAC__)
  struct timeval tp;
  gettimeofday(tp, NULL);
  return (double) tp.tv_sec + 1.0e-9 * (double)tp.tv_nsec;
#else
  struct timespec tp;
#if defined(CLOCK_PROCESS_CPUTIME_ID)
#define CLKID CLOCK_PROCESS_CPUTIME_ID
#elif  defined(CLOCK_REALTIME_ID)
#define CLKID CLOCK_REALTIME_ID
#endif
  clock_gettime(CLKID, &tp);
  return (double)tp.tv_sec + 1.0e-9 * (double)tp.tv_nsec;
#endif
}
