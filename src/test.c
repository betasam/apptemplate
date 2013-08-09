/**
 * @file        test.c
 * @brief       basic C test source
 */

#include <ltypes.h>
#include <lconst.h>

u64_t u64f_fibonacci_recursive( u32_t u32v_n )
{
  u64_t u64v_ret = 0;

  if( (u32v_n == U64C_FIB_0) || (u32v_n == U64C_FIB_1) ) {
    u64v_ret = u32v_n;
  } else {
    u64v_ret = u64f_fibonacci_recursive(u32v_n) + u64f_fibonacci_recursive(u32v_n - 1);
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

/* 
 * end:         test.c
 **/
