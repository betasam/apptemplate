/**
 * @file        main.c
 * @brief       actual entry point used during execution
 */

#include <ltypes.h>

#include <fibonacci_app.h>

/**
 * @function    main
 * @brief       POSIX standard __entry
 * @return      0 on success -1 on failure
 */
int main( int argc, char *argv[] )
{
  int s32v_retval = 0;
  s32v_retval = s32f_fibonacci_app( argc, argv );
  return s32v_retval;
}

/* 
 * end:         main.c
 **/
