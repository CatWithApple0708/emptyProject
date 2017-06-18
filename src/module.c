#include "module.h"
#include <stdio.h>
#include "elog_cfg.h"
#include "elog.h"

char g_LoadEnd = 0;

int   __attribute__ ((constructor(1000))) endModule(void)
{
	log_i("#EndLoad.............\n");
	g_LoadEnd = 1;
	return 1;
}