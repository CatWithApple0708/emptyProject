

#include <unistd.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <assert.h>
#include "module.h"
#include <pthread.h>
#include <string.h>
#include <elog.h>
#include "inirwModule.h"

#if 0

#endif


/************************inner typedef*****************************/

typedef struct{
	int initflag;
}EasyLogModule_c;


/***********************static Var****************************/
EasyLogModule_c  __easyLogModule_c = {0};
EasyLogModule_c  *easyLogModule_c = &__easyLogModule_c;



/**********************Private Function*******************/
static inline EasyLogModule_c *getDev(){
	return easyLogModule_c;
}
/**
 *    This Function will be called by module_init automatic
 */
static inline void setInitFlag(){
	assert(getDev()->initflag == 0);
	getDev()->initflag = 0xB;
}
/**
 *    [如果没有init则立刻中止程序，用来规范程序的加载顺序]
 *
 */
static inline __maybe_unused int  isInit(){
	assert(getDev()->initflag == 0xB);
}






/***********************Extern function********************/







void prieasyLogModule_c(void){
	printf("*************************easyLogModule_c*************************\n");

	printf("\n");

}

#if 0

/* all formats index */
typedef enum {
    ELOG_FMT_LVL    = 1 << 0, /**< level */
    ELOG_FMT_TAG    = 1 << 1, /**< tag */
    ELOG_FMT_TIME   = 1 << 2, /**< current time */
    ELOG_FMT_P_INFO = 1 << 3, /**< process info */
    ELOG_FMT_T_INFO = 1 << 4, /**< thread info */
    ELOG_FMT_DIR    = 1 << 5, /**< file directory and name */
    ELOG_FMT_FUNC   = 1 << 6, /**< function name */
    ELOG_FMT_LINE   = 1 << 7, /**< line number */
} ElogFmtIndex;

#endif

static int  easyLogModule_c_init(void)
{



	INI_HANDLE *  pIniHandle = getINIHandle();
	int debug_level = iniGetInt(pIniHandle, "easyLogModule","debug_level",3);
	int debug_color = iniGetInt(pIniHandle, "easyLogModule","debug_color",0);
	printf("debug_level ::%d,  debug_color  ::%d\n",debug_level, debug_color);
	setbuf(stdout, NULL);
	/* initialize EasyLogger */
	elog_init();
	/* set EasyLogger log format */
	elog_set_fmt(ELOG_LVL_ASSERT, ELOG_FMT_ALL);
	elog_set_fmt(ELOG_LVL_ERROR, ELOG_FMT_ALL);
	elog_set_fmt(ELOG_LVL_WARN, ELOG_FMT_ALL);

	elog_set_fmt(ELOG_LVL_INFO, ELOG_FMT_LVL | ELOG_FMT_TAG);

	elog_set_fmt(ELOG_LVL_DEBUG, ELOG_FMT_LVL |	 \
						ELOG_FMT_TAG |		\
						ELOG_FMT_T_INFO | 	\
						ELOG_FMT_LINE );

	elog_set_fmt(ELOG_LVL_VERBOSE, ELOG_FMT_LVL |	 \
					ELOG_FMT_TAG |		\
					ELOG_FMT_T_INFO | 	\
					ELOG_FMT_LINE );



#ifdef ELOG_COLOR_ENABLE
	elog_set_text_color_enabled(!!(debug_color));
#endif
	/* start EasyLogger */
	elog_set_filter_lvl(debug_level);
	elog_start();
	return 0;
}

static void  __maybe_unused easyLogModule_c_exit(void){
	return;
}

static inline void  __attribute__ ((constructor(102)))  init_module(void)
{
	printf("Important102::loading.........%s Time::%s\n", __FILE__, __TIME__);
	easyLogModule_c_init();
	setInitFlag();
}

