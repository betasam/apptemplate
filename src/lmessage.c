/**
 * @file        lmessage.c
 * @brief       message printing mechanism
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include <lmessage.h>

/* global stream pointer to { stdout, stderr } */
FILE *out_stream;

/* print a message to a selected stream */
static void stream_message(char *prefix, char *format,
                           va_list * arg_list)
{
    fprintf(out_stream, "%s: ", prefix);
    vfprintf(out_stream, format, (*arg_list));
    return;
}

/* stream a user message to STDOUT */
void umessage(char *format, ...)
{
    va_list arg_list;
    out_stream = stdout;
    va_start(arg_list, format);
    stream_message(STRC_MESSAGE, format, &arg_list);
    va_end(arg_list);
}

/* stream a warning message to STDOUT */
void uwarning(char *format, ...)
{
    va_list arg_list;
    out_stream = stdout;
    va_start(arg_list, format);
    stream_message(STRC_WARNING, format, &arg_list);
    va_end(arg_list);
}

/* stream an error message to STDERR */
void uerror(char *format, ...)
{
    va_list arg_list;
    out_stream = stderr;
    va_start(arg_list, format);
    stream_message(STRC_ERROR, format, &arg_list);
    va_end(arg_list);
}

/*
 * file:        lmessage.c
 * no code after this
 **/
