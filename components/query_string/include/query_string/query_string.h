#ifndef __QUERY_STRING_H__
#define __QUERY_STRING_H__

#include <string.h>

typedef enum {
	QUERY_STRING_OK = 0,
	QUERY_STRING_ERR = 1
} Query_String_Status;

extern Query_String_Status query_string_get_value(const char* queryString, const char* parameterName, char* value);

#endif