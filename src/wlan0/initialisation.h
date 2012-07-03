#include <sys/ioctl.h>
#include <net/if.h>
#include <sstream>
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <net/ethernet.h>
#include "wireless.h"
#include <string.h>
#include "iwlib.h"
//#define KILO	1e3
typedef struct iw_freq		iwfreq;


typedef struct iwscan_state
{
  /* State */
  int			ap_num;		/* Access Point number 1->N */
  int			val_index;	/* Value in table 0->(N-1) */
} iwscan_state;


