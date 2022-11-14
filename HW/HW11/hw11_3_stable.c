/*                                                           */
/*  EXTSORT.C  :  External Sort Alogorithm Test              */
/*                                                           */
/*                  Programmed By Lee jaekyu                 */
/*                                                           */
/* partly modified by jsahn */

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <memory.h>
#define BUFSIZE 4096

typedef int (*FCMP)(const void*, const void*);
typedef void (*ESFNC)(FILE*, FILE*, size_t, void*, size_t, FCMP);

void print_dat(FILE* dst, size_t nelem, size_t width, FCMP fcmp) {
    void* v = malloc(width);
    void* z = calloc(1, width);
    printf("\n Result : ");
	for (int i = 0; i < nelem; i++) {
		fread(v, width, 1, dst);
        printf("%d ", fcmp(v, z));
	}
}

int intcmp(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

int min(int x, int y) {
    if (x < y) return x;
    else return y;
}

void merge(void* a, void* b, void* c, int na, int nb, size_t width, FCMP fcmp) {
    int i = 0, j = 0, k = 0;
    while (k < na+nb)
        if (fcmp((char*)a + i*width, (char*)b + j*width)<= 0)
            if (i < na) memcpy((char*)c + (k++)*width, (char*)a + (i++)*width, width);
            else memcpy((char*)c + (k++)*width, (char*)b + (j++)*width, width);
        else
            if (j < nb) memcpy((char*)c + (k++)*width, (char*)b + (j++)*width, width);
            else memcpy((char*)c + (k++)*width, (char*)a + (i++)*width, width);
}

void merge_sort(void* a, size_t n, size_t w, FCMP fcmp) {
    int i, j, k, p, s, size;
    int *b = malloc(w*n);
    for (size = 1; size < n; size <<= 1) {
        p = 0; s = p + size;
        while (p < n) {
            merge((char*)a + p*w, (char*)a + s*w, (char*)b + p*w, size, min(size, n-s), w, fcmp);
            p = s + size; s = p + size;
        }
        for (i = 0; i < n; i++) memcpy(a, b, sizeof(int)*n);
    }
    free(b);
}

struct entry {
    FILE* fp;
    char fname[13];
    void* v;
    int is_eof;
};

void external_sort(FILE* src, FILE* dst, size_t width, void* buf, size_t buflen, FCMP fcmp) {
    int i, minindex, done;
    int nelem, nbuf, nfile;
    void* min;
    struct entry* tmp;

    min = malloc(width);

    fseek(src, 0L, SEEK_END);
    nelem = (int)(ftell(src) / width);
    nbuf = buflen / width;
    nfile = nelem / nbuf + 1;
    printf("\nnumber of element: %d\nnumber of tmp files: %d", nelem, nfile);

    tmp = (struct entry*)malloc(sizeof(struct entry)*nfile);
    for (i = 0; i < nfile; i++) {
        //sprintf_s(tmp[i].fname, 13, "%d.TMP", i)
        sprintf(tmp[i].fname, "%d.TMP", i);
        tmp[i].fp = fopen(tmp[i].fname, "wb+");
        tmp[i].v = malloc(width);
        tmp[i].is_eof = 0;
    }

    fseek(src, 0L, SEEK_SET);
    for (i = 0; i < nfile - 1; i++) {
        int ne;
        fread(buf, width, nbuf, src);
        merge_sort(buf, nbuf, width, fcmp);
        ne = fwrite(buf, width, nbuf, tmp[i].fp);

        printf("\n Reading & Sorting & Writing %s.", tmp[i].fname);
    }
    fread(buf, width, nelem % nbuf, src);
    merge_sort(buf, nelem % nbuf, width, fcmp);
    fwrite(buf, width, nelem % nbuf, tmp[i].fp);

    printf("\n Reading & Sorting & Writing %s.", tmp[i].fname);

    for (i = 0; i < nfile; i++) {
        rewind(tmp[i].fp);
        if (fread(tmp[i].v, width, 1, tmp[i].fp) == 0) tmp[i].is_eof = 1;
    }
    rewind(dst);

    printf("\n Now merging...");

    while (1) {
        done = 1;
        for (i = 0; i < nfile; i++) if (!tmp[i].is_eof) done = 0;
        if (done)  break;
        i = 0;
        while (tmp[i].is_eof) i++;
        minindex = i;
        memcpy(min, tmp[minindex].v, width);
        while (++i < nfile) {
            if (!tmp[i].is_eof && fcmp(min, tmp[i].v) > 0) {
                minindex = i;
                memcpy(min, tmp[i].v, width);
            }
        }
        fwrite(tmp[minindex].v, width, 1, dst);
        if (fread(tmp[minindex].v, width, 1, tmp[minindex].fp) == 0) tmp[minindex].is_eof = 1;
    }

    for (i = 0; i < nfile; i++) {
        fclose(tmp[i].fp);
        //unlink(tmp[i].fname);
        free(tmp[i].v);
    }
    free(min);
    free(tmp);
    rewind(dst);
    print_dat(dst, nelem, width, fcmp);
}

int main() {
    long t1, t2, t;
    void* buf;
    FILE* src, *dst;
    char* fn = "RANDOM.DAT";
    int i;
    if ((buf = malloc(BUFSIZE)) == NULL) {
        printf("Out of memory");
        exit(1);
    }
    
    if ((src = fopen(fn, "rb")) == NULL) {
        printf("\nDisk Error!");
        exit(1);
    }

    if ((dst = fopen("RESULT.DAT", "wb+")) == NULL) {
        printf("\nDisk Error!");
        exit(1);
    }
    external_sort(src, dst, sizeof(int), buf, BUFSIZE, intcmp);
    fclose(src);
    fclose(dst);
    free(buf);
}