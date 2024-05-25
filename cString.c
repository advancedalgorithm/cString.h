/*
*   [ C String Library ]
*   Using the minimum library(s) possible
*
* Length       ( cString->Length(n)                 )   long     DONE
* Strip        ( cString->Strip(n)                  )   long     DONE
* Trim         ( cString->Trim(n, "")               )   void     DONE
* Contains     ( cString->Contains(n, "Hello")      )   int      DONE
* CountChar    ( cString->CountChar(n, 'c')         )   long     DONE
* CountSubstr  ( cString->CountSubstr(n, "")        )   long     DONE
* StartsWith   ( cString->StartsWith(n, "Hello")    )   int      DONE
* EndsWith     ( cString->EndsWith(n, "World")      )   int      DONE
* IsLowercase  ( cString->IsLowercase(n)            )   int      DONE
* IsUppercase  ( cString->IsUppercase(n)            )   int      DONE
* RmChar       ( cString->RmChar(n, 'c')            )   void     DONE
* Replace      ( cString->ReplaceChar(n, 'c')       )   void     DONE
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "cString.h"

cString *new_string(const char *n) {
    cString *s  = (cString *)malloc(sizeof(cString));

    /* Set members of struct */
    s->Length       = __Length;
    s->Strip        = __Strip;
    s->Trim         = __Trim;
    s->CountChar    = __CountChar;
    s->CountSubstr  = __CountSubstr;
    s->StartsWith   = __StartsWith;
    s->EndsWith     = __EndsWith;
    s->IsLowercase  = __IsLowercase;
    s->IsUppercase  = __IsUppercase;
    s->RmChar       = __RmChar;
    s->Replace      = __Replace;
    s->Split        = __Split;
    
    s->Data     = (char *)malloc((strlen(n) + 1));
    memset(s->Data, '\0', (strlen(n) + 1));
    strcpy(s->Data, n);

    return s;
}

long __Length(cString *s) { 
    if(sizeof(s->Data) == 0) return 0;
    return strlen(s->Data); 
}

void __Strip(cString *s) {
    char *new = (char *)malloc(strlen(s->Data) + 1);
    memset(new, '\0', (strlen(s->Data) + 1));

    for(int i = 0; i < strlen(s->Data); i++) {
        if(s->Data[i] != '\t' && s->Data[i] != '\r' && s->Data[i] != '\n')
            strncat(new, &s->Data[i], sizeof(char));
    }

    __updateString(s, new);
}

void __Trim(cString *s, char ch) {
    char *new = (char *)malloc(strlen(s->Data) + 1);
    memset(new, '\0', (strlen(s->Data) + 1));

    for(int i = 0; i < strlen(s->Data); i++) {
        if(s->Data[i] != ch)
            strncat(new, &s->Data[i], sizeof(char));
    }

    __updateString(s, new);
}

long __CountChar(cString *s, char ch) {
    long count = 0;
    for(int i = 0; i < strlen(s->Data); i++) {
        if(s->Data[i] == ch)
            count++;
    }

    return count;
}

long __CountSubstr(cString *s, char *substr) {
    long count = 0;
    if(strlen(substr) < 2) return 0;

    for(int i = 0; i < strlen(s->Data); i++)
        if(s->Data[i] == substr[0] && s->Data[ i + strlen(substr)-1 ] == substr[strlen(substr) - 1])
            count++;

    return count;
}

int __StartsWith(cString *s, const char *str) {
    if(s->Data[0] != str[0] && s->Data[1] != str[1]) return 0;

    for(int i = 0; i < strlen(str); i++)
        if(s->Data[i] == str[i] && i == strlen(str)-1) return 1;

    return 0;
}

int __EndsWith(cString *s, const char *str) {
    if(s->Data[strlen(s->Data) - 1] != str[strlen(str) -1] && s->Data[strlen(s->Data) - 2] != str[strlen(str) - 2]) return 0;

    long counter = strlen(s->Data)-1;
    for(int i = strlen(str)-1; i < strlen(str); i--)
        if(s->Data[counter--] == str[i] && i == 0) 
            return 1;

    return 0;
}

int __IsLowercase(cString *s) {
    for(int i = 0; i < strlen(s->Data); i++)
        if(!islower(s->Data[i]) && s->Data[i] != ' ') 
            return 0;

    return 1;
}

int __IsUppercase(cString *s) {
    for(int i = 0; i < strlen(s->Data); i++)
        if(!isupper(s->Data[i]) && s->Data[i] != ' ') 
            return 0;

    return 1;
}

void __RmChar(cString *s, const char chr) {
    char *new = (char *)malloc(strlen(s->Data) + 1);
    memset(new, '\0', strlen(s->Data) + 1);

    for(int i = 0; i < strlen(s->Data); i++) {
        if(s->Data[i] != chr)
            strncat(new, &s->Data[i], sizeof(char));
    }

    __updateString(s, new);
}

void __Replace(cString *s, char *substr, char *replacement) {
    char* data = (char *)malloc(strlen(s->Data) + 1);
    memset(data, '\0', strlen(s->Data) + 1);

    for(int i = 0; i < strlen(s->Data); i++) {
        if(substr[0] == s->Data[i] && substr[1] == s->Data[i+1] && substr[strlen(substr) - 1] == s->Data[i + strlen(substr) - 1]) {
                strcat(data, replacement);
                i += strlen(substr);
        }
        strncat(data, &s->Data[i], sizeof(char));
    }
    strncat(data, "\0", sizeof(char));

    __updateString(s, data);
}

char **__Split(cString *s, const char delim) {
    long arr_sz = __CountChar(s, delim);
    char **arr = (char **)malloc(sizeof(char *) * arr_sz + 1);
    memset(arr, '\0', sizeof(char *) * arr_sz + 1);

    char *token = strtok(s->Data, &delim);
    for(int idx = 0; idx <= (arr_sz); idx++) {
        arr[idx] = strdup(token);
        token = strtok(NULL, &delim);
    }

    return arr;
}

void __CleanUp(cString *s) {
    if(s->Data != NULL)
        free(s->Data);
}

void __updateString(cString *s, char *new_data) {
    if(s->Data != NULL)
        free(s->Data);

    s->Data = strdup(new_data);
}
