#include "mystring.h"

int mstrlen(const char* str) {
    int res = 0;
    while (*str != '\0'){
        str++;
        res++;
    }
    return res;
}

char* mstrcpy(char* to_str, const char* from_str) {
    char *ts = to_str;
    while (*from_str != '\0')
        *ts++ = *from_str++;
    *ts = '\0';//needs check
    return to_str;
}

char* mstrncpy(char* to_str, const char* from_str, int size) {
    char *ts = to_str;
    while (size) {
        *ts++ = *from_str++;
        size--;
    }
    *ts = '\0';
    return to_str;
}

int mstrcmp(const char* str1, const char* str2) {
    int res = 0;
    while (!res) {
        if (*str1 == '\0' && *str2 == '\0') break;

        res = (*str1 == *str2) ? 0 : 2;
        if (res)
            res = (*str1 < *str2) ? -1 : 1;
        str1++;
        str2++;
    }
    return res;
}

int mstrncmp(const char* str1, const char* str2, int size) {
    int res = 0;
    while (size || !res) {
        if (*str1 == '\0' && *str2 == '\0') break;

        res = (*str1 == *str2) ? 0 : 2;
        if (res)
            res = (*str1 < *str2) ? -1 : 1;
        str1++;
        str2++;
        size--;
    }//ignore ' ' ???
    return res;
}

char* mstrcat(char* str1, const char* str2) {
    char *s1 = str1;
    while (*s1 != '\0') s1++;
    while (*str2 != '\0') *s1++ = *str2++;
    *s1 = '\0';
    return str1;
}

char* mstrncat(char* str1, const char* str2, int size) {
    char *s1 = str1;
    while (*s1 != '\0') s1++;
    while (size) {
        *s1++ = *str2++;
        size--;
    }
    *s1 = '\0';
    return str1;
}
