#pragma once
#include <stdint.h>
#include "event.h"

// Thread data.
struct thread_t
{
  // The thread handle.
  void* handle;
  // The thread id.
  unsigned long id;
};

// Producer thread parameters.
struct producer_params_t
{
  // The event queue to work on.
  event_queue_t* queue;
  // The time in milliseconds between work iterations (sleep).
  int32_t period_ms;
  // Do an interation of work, otherwise do nothing.
  bool do_work;
  // Keep the thread running, otherwise stop.
  bool keep_alive;

  // The number of events produced.
  uint32_t produced_count;
  // The number of seconds elapsed while working.
  double elapsed_sec;
};

struct producer_metrics_t
{
  // The thread id.
  uint32_t thread_id;
  // The average number of events per-second.
  double events_per_sec;
  // An estimate of the max events per-second.
  double events_per_sec_max;
};

thread_t
create_producer_thread(producer_params_t* params);

unsigned long __stdcall producer_do_work(void* void_params);

void
calc_metrics(producer_params_t* params,
             uint32_t* thread_ids,
             producer_metrics_t* metrics,
             int producer_count);

void
print_metrics(producer_metrics_t* metrics, int producer_count);