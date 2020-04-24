/**
 * CIO Open call
 */

#include <atari.h>
#include <6502.h>
#include <string.h>
#include <stdbool.h>
#include "sio.h"
#include "misc.h"
#include "config.h"

extern unsigned char err;
extern unsigned char ret;
extern unsigned char aux1_save[MAX_DEVICES];
extern unsigned char aux2_save[MAX_DEVICES];

void _cio_open(void)
{  
  // Save AUX1/AUX2 values
  aux_save(OS.ziocb.drive);

  err=siov(DEVIC_N,
	   OS.ziocb.drive,
	   'O',
	   DSTATS_WRITE,
	   OS.ziocb.buffer,
	   DBYT_OPEN,
	   DTIMLO_DEFAULT,
	   aux1_save[OS.ziocb.drive],
	   aux2_save[OS.ziocb.drive]);
  
  if (err==144)
    {
      // We got an SIO error, get the extended status error.
      err=siov(DEVIC_N,
	       OS.ziocb.drive,
	       'O',
	       DSTATS_WRITE,
	       OS.ziocb.buffer,
	       DBYT_OPEN,
	       DTIMLO_DEFAULT,
	       aux1_save[OS.ziocb.drive],
	       aux2_save[OS.ziocb.drive]);
    }
  
  clear_rx_buffer();
  clear_tx_buffer();
    
  ret=err;
}