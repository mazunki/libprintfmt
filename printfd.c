
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <term.h>
#include "printfd.h"

#ifndef VERBOSITY
#define VERBOSITY 2
#endif

void _printfd(int fd, const char *format, va_list args) {
    char *fd_name;
	char *colour;
	if (VERBOSITY < fd) return;
    switch(fd) {
		case FILENO_STDOUT:
			fd_name = "out";
			colour = ANSI_COLOR_GREEN;
			break;
		case FILENO_STDERR:
			fd_name = "error";
			colour = ANSI_COLOR_RED;
			break;
		case FILENO_STDDEBUG:
			fd_name = "debug";
			colour = ANSI_COLOR_YELLOW;
			break;
		case FILENO_STDINFO:
			fd_name = "info";
			colour = ANSI_COLOR_CYAN;
			break;
		case FILENO_STDTRACE:
			fd_name = "trace";
			colour = ANSI_COLOR_GRAY;
			break;
		default:
			fd_name = "[other]";
			colour = "";
	}
	
	int err, color_support;
	setupterm(NULL, 1, &err);
	if (err <= 0) {
		color_support = 0;
	} else {
		color_support = tigetnum("colors");
	}

    char prefix[64] = {0};
	char fmt[16] = {0};
	if (color_support >= 8) {
		snprintf(prefix, sizeof(prefix), "[%s%s%s]", colour, fd_name, ANSI_COLOR_RESET);
		strcpy(fmt, "%16s %s\n");
	} else {
		snprintf(prefix, sizeof(prefix), "[%s]", fd_name);
		strcpy(fmt, "%7s %s\n");
	}

    char buffer[1024];
    vsnprintf(buffer, sizeof(buffer), format, args);

    char *line = strtok(buffer, "\n");
    while (line != NULL) {
        printf(fmt, prefix, line);
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

void printtrace(const char *format, ...) {
    va_list args;
    va_start(args, format);
	_printfd(FILENO_STDTRACE, format, args);
	va_end(args);
}
