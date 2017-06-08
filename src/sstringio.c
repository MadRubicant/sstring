#include "sstringio.h"
#include "sstring.h"

#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>

extern sstring* sstring_alloc(size_t size);
extern int fileno(FILE*);

sstring* sstring_getline(FILE* file) {
  if (!file)
    return NULL;
  fpos_t start;
  fgetpos(file, &start);
  
  sstring* ret = sstring_create("");
  char inputbuf[SSTRINGIO_INPUT_BUFSIZE];
  char c = fgetc(file);
  if (c == EOF || c == '\n')
    return NULL;
  int i = 0;
  while (c != EOF && c != '\n') {
    if (i == SSTRINGIO_INPUT_BUFSIZE - 1) {
      inputbuf[i] = '\0';
      i = 0;
      if (sstring_cat(ret, inputbuf)) {
	goto failure;
      }
    }
    inputbuf[i++] = c;
    c = fgetc(file);
  }
  
  inputbuf[i] = '\0';
  if (sstring_cat(ret, inputbuf))
    goto failure;

  return ret;

 failure:
  sstring_destroy(ret);
  fsetpos(file, &start);
  return NULL;
  
}

sstring* sstring_loadfile(FILE* file) {
  if (!file)
    return NULL;
  struct stat sb;
  sstring* ret;
  int fd;
  fd = fileno(file);
  if (fstat(fd, &sb) == -1)
    return NULL;

  ret = sstring_alloc(sb.st_size);
  if (!ret)
    return NULL;
  char c;
  for (size_t i; i < ret->len; i++) {
    c = fgetc(file);
    ret->cstr[i] = c;
  }

  return ret;
}

sstring* sstring_sprintf(const char* fmt, ...) {
  sstring* pre_fmt = sstring_create(fmt);
  size_t fmtlen = strlen(fmt);
  int numfmts = 0;
  sstring** inserts = NULL;
  for (size_t i = 0; i < fmtlen; i++) {
    if (fmt[i] == '%') {
      numfmts++;
      if (fmt[i + 1] == '%')
	i++;
    }
  }
}
