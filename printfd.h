#ifndef PRINTFD_H
#define PRINTFD_H

#include <stdarg.h>
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

#define FILENO_STDOUT 1
#define FILENO_STDERR 2
#define FILENO_STDDEBUG 3
#define FILENO_STDINFO 4
#define FILENO_STDTRACE 5

void _printfd(int fd, const char *format, va_list args);

void print(const char *format, ...);
void printerr(const char *format, ...);
void printdebug(const char *format, ...);
void printinfo(const char *format, ...);
void printtrace(const char *format, ...);

#endif // PRINTFD_dH

