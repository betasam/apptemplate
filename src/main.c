/**
 * @file	main.c
 */

#include <ltypes.h>

#include <fibonacci_app.h>

int main( int argc, char *argv[] )
{
  int retval = 0;
  retval = s32f_fibonacci_app( argc, argv );
  return retval;
}

/* 
 * end:         main.c
 **/
