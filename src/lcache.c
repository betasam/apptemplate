/**
 * @file	lcache.c
 * @brief	object cache with binary search
 */

#include <stdlib.h>

#include <ltypes.h>
#include <lcache.h>

s32_t s32f_lcache_init(  s32_t     s32v_lcache_cnt, u32_t u32v_lcache_flags, 
			 lcache_t* lcache_ptr )
{
  s32_t s32v_ret = 0;
  u32_t u32v_sz  = 0;
  s32_t s32v_idx = 0;

  do {

    if( (s32v_lcache_cnt     <= 0) || 
	(u32v_lcache_flags   == LCACHE_FLAG_INVALID) || 
	(lcache_ptr          == 0)) {
      s32v_ret = -1;
      break;
    }

    u32v_sz = LCACHE_SZ_ALIGN( ((sizeof(u64_t)*s32v_lcache_cnt)) );
    if( (lcache_ptr->u64p_element = malloc( u32v_sz )) == 0 ) {
      s32v_ret = -1;
      break;
    }

    u32v_sz = LCACHE_SZ_ALIGN( ((sizeof(u32_t)*s32v_lcache_cnt)) );
    if( (lcache_ptr->u32p_hash    = malloc( u32v_sz )) == 0 ) {
      s32v_ret = -1;
      free( lcache_ptr->u64p_element );
      break;
    }

    lcache_ptr->s32v_cnt   = s32v_lcache_cnt;
    lcache_ptr->s32v_last  = 0;
    lcache_ptr->u8v_filled = 0;

    while( s32v_idx < lcache_ptr->s32v_cnt ) {
      lcache_ptr->u32p_hash[ s32v_idx ] = 0;
      lcache_ptr->u64p_element[ s32v_idx ] = 0ULL;
      s32v_idx++;
    }

  } while(0);
  

  return s32v_ret;
}


s32_t s32f_lcache_add( lcache_t* lcache_ptr, u64_t u64v_value, 
		       u32_t u32v_hash )
{
  s32_t s32v_ret = 0;

  do {

    /* check if arguments can be processed */
    if( (lcache_ptr == 0) || (u64v_value == 0) || (u32v_hash == 0) ) {
      s32v_ret = -1;
      break;
    }

    /* check if extents are exceeded */
    if( lcache_ptr->s32v_last > lcache_ptr->s32v_cnt ) {
      s32v_ret = -1;
      break;
    }

    /* wrap around ring buffer if it has been filled already */
    if( (lcache_ptr->s32v_last  == lcache_ptr->s32v_cnt) &&
	(lcache_ptr->u8v_filled == 1) ) {
      lcache_ptr->s32v_last = 0;
    }

    /* WARNING! the following needs to be atomic to be threadsafe */
    lcache_ptr->u64p_element[lcache_ptr->s32v_last] = u64v_value;
    lcache_ptr->u32p_hash[ lcache_ptr->s32v_last  ] = u32v_hash;
    lcache_ptr->s32v_last++;

    /* indicate wrap around if that has happened */
    if( (lcache_ptr->u8v_filled == 0) && 
        (lcache_ptr->s32v_last  == lcache_ptr->s32v_cnt) ) {
      lcache_ptr->u8v_filled = 1;
    }

  } while(0);

  return s32v_ret;
}

u64_t u64f_lcache_find( lcache_t* lcache_ptr, u32_t u32v_hash )
{
  u64_t u64v_ret = 0ULL;
  s32_t s32v_idx = 0;

  do {
    if( (lcache_ptr == 0) || (u32v_hash == 0) ) {
      break;
    }

    while( s32v_idx < lcache_ptr->s32v_cnt ) {
      if( lcache_ptr->u32p_hash[ s32v_idx ] == u32v_hash ) {
	u64v_ret = lcache_ptr->u64p_element[ s32v_idx ];
	break;
      }
      s32v_idx++;
    }

  } while(0);
  
  return u64v_ret;
}
