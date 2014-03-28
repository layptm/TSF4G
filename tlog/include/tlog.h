#ifndef _H_TLOG
#define _H_TLOG

#include "platform/tlibc_platform.h"
#include "tlog_config_types.h"
#include "tlog_rolling_file_instance.h"
#include "tlog_shm_instance.h"


#include <stdio.h>
#include <stdbool.h>
#include "terrno.h"

#define TLOG_VERSION "0.0.1"
typedef union tlog_appender_body_u
{
	tlog_rolling_file_instance_t rolling_file;
	tlog_shm_instance_t shm;
}tlog_appender_body_t;

typedef struct tlog_appender_instance_s
{
	tlog_appender_type_t type;
	tlog_appender_body_t body;
}tlog_appender_instance_t;

typedef struct tlog_instance_s
{
	uint32_t appender_instance_num;
	tlog_appender_instance_t appender_instance[TLOG_MAX_APPENDER_NUM];
}tlog_instance_t;

typedef struct tlog_s
{
	tlog_config_t config;
	tlog_instance_t instance;
}tlog_t;


TERROR_CODE tlog_init(tlog_t *self, const char *config_file);

void tlog_write(tlog_t *self, const char *message, size_t message_size);

void tlog_fini(tlog_t *self);

#endif//_H_TLOG