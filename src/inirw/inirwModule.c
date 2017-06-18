


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
#include "inirw.h"
#if 0

这个文件最先加载 此时 elog还没有启动
#endif


/************************inner typedef*****************************/

typedef struct{
	int initflag;
	char* iniFileName;
	INI_HANDLE ini_handle;
}InirwModule_c;


/***********************static Var****************************/
InirwModule_c  __inirwModule_c = {
	.iniFileName = "default.ini"
};
InirwModule_c  *inirwModule_c = &__inirwModule_c;



/**********************Private Function*******************/
static inline InirwModule_c *getDev(){
	return inirwModule_c;
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
static inline __maybe_unused int isInit(){
	assert(getDev()->initflag == 0xB);
	return 1;
}




/***********************Extern function********************/

 INI_HANDLE * getINIHandle(){
 	isInit();
 	return &getDev()->ini_handle;
 }





void priinirwModule_c(void){
	printf("*************************inirwModule_c*************************\n");
	printf("*inirwModule_c->iniFileName %s\n", getDev()->iniFileName);
	printf("*****\n");

}


static int  inirwModule_c_init(void)
{
	int ret = 0;

	FILE *filetmp = fopen(getDev()->iniFileName,"a+");
	fclose(filetmp);

	ret = iniFileLoad(&getDev()->ini_handle, getDev()->iniFileName);
	if (ret != 0){
		printf("%d",ret);
	}

	priinirwModule_c();
	return 0;
}

static void  __maybe_unused inirwModule_c_exit(void){
	return;
}

static inline void  __attribute__ ((constructor(101)))  init_module(void)
{
	printf("Important101::loading.........%s Time::%s \n", __FILE__, __TIME__);
	inirwModule_c_init();
	setInitFlag();
}