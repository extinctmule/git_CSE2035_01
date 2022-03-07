#include <stdio.h>
#include <stdlib.h>
#include "mystring.h"

#define MAX_WORDS 6500

typedef struct {
    char* word;
    int length;
    int count;
} elem;

typedef struct {
    elem words[MAX_WORDS];
    int word_count;
} dictionary;

void add_count(dictionary* D, char* word);
void split(dictionary* D, const char* sent);
void merge(elem* WA, elem* MWA, int n);
void freqSort(elem* WA, int n);

int main(void) {

    FILE* fp;
    const char* input_file_name = "Little_Lord_Fauntleroy.txt";
    const int num25 = 25;

    dictionary D;// is not a pointer, at least for NOW..
    elem* pDwords;
    char buf[3001];
    int i;

    D.word_count = 0;// init dictionary

    fp = fopen(input_file_name, "r");
    if (fp == NULL) {
        printf("input file open error.\n");
        return 1;
    }

    // build dictionary
    while (1) {
        if (fgets(buf, 3000, fp) == NULL) break;
        split(&D, buf);
    }

    // sort dictionary
    pDwords = D.words;
    freqSort(pDwords, D.word_count);//D.words or &D.words? or new pointer?

    // print result
    printf("File name: %s\n\n", input_file_name);
    printf(" < Top 25 frequently used words list > \n");

    i = 0;
    while (i < num25) {
        printf("  # %-2d:  %-10s [%d]\n", i + 1, (pDwords + i)->word, (pDwords + i)->count);
        i++;
    }
    i = fclose(fp);
    if (i != 0) {
        printf("input file close error.\n");
        return 1;
    }

    return 0;
}

void add_count(dictionary* D, char* w) {
    int cnt = D->word_count;
    int len = mstrlen(w);
    elem* pEle = D->words;
    char* pThe;
    while (cnt) {
        if (!mstrcmp(w, pEle->word)) {
            (pEle->count)++;
            return;
        }//RETURN if word already exist

        pEle++;
        cnt--;
    }
    D->word_count++;

    pEle->word = (char*)malloc((len + 1) * sizeof(char));

    mstrcpy(pEle->word, w);
    pEle->length = len;
    pEle->count = 1;

    return;
}

void split(dictionary* D, const char* line) {
    char splitted[41];//40 is max len of ONE word
    char* pSpl = splitted;
    while (*line != '\n') {
        while (*line == ' ') line++;
        if (*line == '\n') break;

        while (*line != ' ' && *line != '\n') {
            *pSpl++ = *line++;
        }
        *pSpl = '\0';
        add_count(D, splitted);
        pSpl = splitted;//come back!!
    }
    return;
}

void merge(elem* WA, elem* MWA, int n) {
    elem* sortedWA = (elem*)malloc((n + 2) * sizeof(elem));
    elem* first = WA, * mid = MWA, * LWA = WA + n, * sor = sortedWA;

    if (WA + 1 >= LWA) return;
    while (first < MWA && mid < LWA) {
        if (first->count >= mid->count)
            *sor++ = *first++;
        else
            *sor++ = *mid++;
    }
    while (first < MWA) *sor++ = *first++;
    while (mid < LWA) *sor++ = *mid++;

    sor = &sortedWA[0];
    while (WA < LWA) {
        *WA++ = *sor++;
    }
    free(sortedWA);
    return;
}

void freqSort(elem* WA, int n) {
    int mid;
    if (n != 1) {
        mid = n / 2;
        freqSort(WA, mid);
        freqSort(WA + mid, n - mid);
        merge(WA, WA + mid, n);
    }
    return;
}

