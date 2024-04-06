#include "query_string.h"

Query_String_Status query_string_get_value(const char* queryString, const char* parameterName, char* value) {
    char* temp = NULL;
    temp = strstr(queryString, parameterName);
    if (temp == NULL)
        return QUERY_STRING_ERR;
    temp = temp + strlen(parameterName);
    int i = 0;
    while (temp[i] != '&' && temp[i] != '\0') {
        value[i] = temp[i];
        i++;
    }
    value[i] = '\0';
    return QUERY_STRING_OK;
}