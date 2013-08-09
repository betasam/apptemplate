/**
 * @file	lmessage.c
 * @brief	message printing mechanism
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include <lmessage.h>

FILE *out_stream;

static void stream_message( char *prefix, char *format, va_list *arg_list )
{
  fprintf(out_stream, "%s: ", prefix);
  vfprintf(out_stream, format, (*arg_list) );
  return;
}

void umessage( char *format, ... )
{
  va_list arg_list;
  out_stream = stdout;
  va_start( arg_list, format );
  stream_message( STRC_MESSAGE, format, &arg_list );
  va_end( arg_list );
}

void uwarning( char *format, ... )
{
  va_list arg_list;
  out_stream = stdout;
  va_start( arg_list, format );
  stream_message( STRC_WARNING, format, &arg_list );
  va_end( arg_list );
}

void uerror( char *format, ... )
{
  va_list arg_list;
  out_stream = stderr;
  va_start( arg_list, format );
  stream_message( STRC_ERROR, format, &arg_list );
  va_end( arg_list );
}


/*
 * no code after this
 **/
