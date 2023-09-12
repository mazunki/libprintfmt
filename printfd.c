
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include "printfd.h"

#ifndef VERBOSITY
#define VERBOSITY 2
#endif

void _printfd(int fd, const char *format, va_list args) {
    char *prefix;
	if (VERBOSITY < fd) return;
    switch(fd) {
		case FILENO_STDOUT:
			prefix = "[" ANSI_COLOR_GREEN "out" ANSI_COLOR_RESET "]";
			break;
		case FILENO_STDERR:
			prefix = "[" ANSI_COLOR_RED "error" ANSI_COLOR_RESET "]";
			break;
		case FILENO_STDDEBUG:
			prefix = "[" ANSI_COLOR_YELLOW "debug" ANSI_COLOR_RESET "]";
			break;
		case FILENO_STDINFO:
			prefix = "[" ANSI_COLOR_CYAN "info" ANSI_COLOR_RESET "]";
			break;
		case FILENO_STDTRACE:
			prefix = "[" ANSI_COLOR_CYAN "trace" ANSI_COLOR_RESET "]";
			break;
		default:
			prefix = "[other]";
	}

    char buffer[1024];

    vsnprintf(buffer, sizeof(buffer), format, args);

    char *line = strtok(buffer, "\n");
    while (line != NULL) {
        printf("%16s %s\n", prefix, line);
		va_end(args);

        line = strtok(NULL, "\n");
    }
}

int fprintf(FILE *restrict stream, const char *format, ...) {
    va_list args;
    va_start(args, format);
	_printfd(fileno(stream), format, args);
	va_end(args);
	return 0;
}

int dprintf(int fd, const char *format, ...) {
    va_list args;
    va_start(args, format);
	_printfd(fd, format, args);
	va_end(args);
	return 0;
}

void print(const char *format, ...) {
    va_list args;
    va_start(args, format);
	_printfd(fileno(stdout), format, args);
	va_end(args);
}

void printerr(const char *format, ...) {
    va_list args;
    va_start(args, format);
	_printfd(fileno(stderr), format, args);
	va_end(args);
}

void printdebug(const char *format, ...) {
    va_list args;
    va_start(args, format);
	_printfd(FILENO_STDDEBUG, format, args);
	va_end(args);
}

void printinfo(const char *format, ...) {
    va_list args;
    va_start(args, format);
	_printfd(FILENO_STDINFO, format, args);
	va_end(args);
}

