/**
 * @file	lcache.c
 * @brief	object cache with binary search
 */

#include <ltypes.h>
#include <lcache.h>

s32_t s32_f_lcache_init( s32_t s32v_lcache_blk_cnt, u32_t u32v_lcache_flags, lcache_t* lcache_ptr )
{
  s32_t s32v_ret = 0;

  if( (s32v_lcache_blk_cnt <= 0) || 
      (u32v_lcache_flags == LCACHE_FLAG_INVALID) || 
      (!lcache_ptr)) {
    s32v_ret = -1;
  }

  return s32v_ret;
}

