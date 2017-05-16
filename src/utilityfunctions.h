#ifndef UTILITYFUNCTIONS_H 
#define UTILITYFUNCTIONS_H 

#define LAST_CHAR(X) (X)[strlen(X)-1]
#define INF_LAST_CHAR(X) LAST_CHAR(string_get_last_elem(X)->string)

char* strdup (char* src);

#endif