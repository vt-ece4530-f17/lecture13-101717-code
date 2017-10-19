#include <stdio.h>

#define _GNU_SOURCE
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/syscall.h>
#include <linux/perf_event.h>

static int fddev = -1;
__attribute__((constructor)) static void init(void) {
	static struct perf_event_attr attr;
	attr.type = PERF_TYPE_HARDWARE;
	attr.config = PERF_COUNT_HW_CPU_CYCLES;
	fddev = syscall(__NR_perf_event_open, &attr, 0, -1, -1, 0);
}

__attribute__((destructor)) static void fini(void) {
	close(fddev);
}

static inline long long cpucycles(void) {
	long long result = 0;
	if (read(fddev, &result, sizeof(result)) < sizeof(result)) return 0;
	return result;
}

unsigned modk(unsigned x, unsigned k) {
  return (x & ((1 << k) - 1));
}

unsigned divk(unsigned x, unsigned k) {
  return (x >> k);
}

unsigned modulo(unsigned x) {
  unsigned r, q, k, a, m, z;
  m = 179;
  k = 8;
  a = (1 << k) - m;
  r = modk(x, k);
  q = divk(x, k);
  do {
    do {
      r = r + modk(q * a, k);
      q = divk(q * a, k);
    } while (q != 0);
    q = divk(r, k);
    r = modk(r, k);
  } while (q != 0);
  z = (r >= m) ? r - m : r;
  return z;
}

int compare_unsigned(const void *a, const void *b) {
  const unsigned *da = (const unsigned *) a;
  const unsigned *db = (const unsigned *) b;
  return (*da > *db) - (*da < *db);
} 

unsigned median(unsigned *thist) {
  qsort(thist, 10, sizeof(unsigned), compare_unsigned);
  return thist[4];
}
	   
int main() {
  unsigned j, s = 0;
  unsigned mytime[10], mediantime;

  unsigned k;
  
  for (k=0; k<10; k++) {
    mytime[k] = cpucycles();
    for (j = 1; j<10000; j++) {
      s += modulo(j);
    }
    mytime[k] = cpucycles() - mytime[k];
  }
  
  mediantime = median(mytime);

  printf("The sum is %d\n", s);
  printf("The execution time us %d\n", mediantime);
  return s;
}
