#ifndef __INC_QUERY_STRING_H__
#define __INC_QUERY_STRING_H__

#include "string.h"

typedef enum {
	GP_OK = 0,
	GP_ERR
} Get_Parameter_Status;

Get_Parameter_Status getParameter(const char* queryString, const char* parameterName, char* value);

#endif