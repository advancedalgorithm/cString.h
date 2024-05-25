#pragma once
#ifndef CSTRINGUTILS_H
#define CSTRINGUTILS_H

typedef struct cString {
    char *      Data;

    long        (*Length)       (struct cString *s);
    void        (*Strip)        (struct cString *s);
    void        (*Trim)         (struct cString *s, char ch);
    long        (*CountChar)    (struct cString *s, char ch);
    long        (*CountSubstr)  (struct cString *s, char *substr);
    int         (*StartsWith)   (struct cString *s, const char *str);
    int         (*EndsWith)     (struct cString *s, const char *str);
    int         (*IsLowercase)  (struct cString *s);
    int         (*IsUppercase)  (struct cString *s);
    void        (*RmChar)       (struct cString *s, const char chr);
    void        (*Replace)      (struct cString *s, char *substr, char *replacement);
    char **     (*Split)        (struct cString *s, const char delim);
} cString;

cString *new_string(const char *n);

long __Length(cString *s);
void __Strip(cString *s);
void __Trim(cString *s, char ch);
long __CountChar(cString *s, char ch);
long __CountSubstr(cString *s, char *substr);
int __StartsWith(cString *s, const char *str);
int __EndsWith(cString *s, const char *str);
int __IsLowercase(cString *s);
int __IsUppercase(cString *s);
void __RmChar(cString *s, const char chr);
void __Replace(cString *s, char *substr, char *replacement);
char **__Split(cString *s, const char delim);
void __updateString(cString *s, char *new_data);
#endif
