/**
 * @file        test.c
 * @brief       basic C test source
 */

#include <ltypes.h>
#include <lconst.h>
#include <lmessage.h>
#include <lconfig.h>

u64_t u64f_fibonacci_recursive( u32_t u32v_n )
{
  u64_t u64v_ret = 0;

  if( (u32v_n == U64C_FIB_0) || (u32v_n == U64C_FIB_1) ) {
    /* fibonacci(0,1) = {0,1} */
    u64v_ret = u32v_n;
  } else {
    /* fibonacci(n) = fibonacci(n-1) + fibonacci(n-2) */
    u64v_ret = u64f_fibonacci_recursive(u32v_n - 1) + u64f_fibonacci_recursive(u32v_n - 2);
  }

  return u64v_ret;
}

u64_t u64f_fibonacci_seq( u32_t u32v_n )
{
  u64_t u64v_prev = U64C_FIB_0;
  u64_t u64v_curr = U64C_FIB_1;
  u64_t u64v_sum  = 0;
  u32_t u32v_idx  = 0;

  u32v_idx = u32v_n;
  
  if( (u32v_n == U64C_FIB_0) || (u32v_n == U64C_FIB_1) ) {
    u64v_sum = u32v_n;
  } else {

    while( u32v_idx > U64C_FIB_1 ) {
      u64v_sum  = u64v_curr + u64v_prev;
      u64v_prev = u64v_curr;
      u64v_curr = u64v_sum;
      u32v_idx  = u32v_idx  - 1;
    }
    
  }

  return u64v_sum;
}

s32_t s32f_fibonacci( int argc, char *argv[] )
{
  s32_t s32v_ret   = 0;
  u32_t u32v_n     = 0;
  s32_t s32v_flags = 0;
  u32_t u64v_r     = 0ULL;

  if( (s32v_flags = s32f_parse_args( argc, argv, &u32v_n )) != -1 ) {

    do {

      if( !(CHK_FLAG(s32v_flags, INTC_FLAG_NUMBER)) ) {
	uerror("no number specified\nusage: %s -n <number> [-r]\n", argv[0]);
	s32v_ret = -1;
	break;
      } 

      if( CHK_FLAG(s32v_flags, INTC_FLAG_RECURSE) ) {
	umessage("using recursive algorithm for result ...\n");
	u64v_r = u64f_fibonacci_recursive(u32v_n);
      } else {
	umessage("using sequential algorithm for result ...\n");
	u64v_r = u64f_fibonacci_seq(u32v_n);
      }

      umessage("requested: %u, computed-result: %lu \n", u32v_n, u64v_r);

    } while(0);

  }

  return s32v_ret;
}

int main( int argc, char *argv[] )
{
  int retval = 0;
  retval = s32f_fibonacci( argc, argv );
  return retval;
}

/* 
 * end:         test.c
 **/
