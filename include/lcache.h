#ifndef _LCACHE_H
#define _LCACHE_H

#define LCACHE_FLAG_INVALID	0xFFFFFFFF
#define LCACHE_SZ_ALIGN(bytes)	(((bytes>>2)<<2) + ((bytes & 3)?0:1))


typedef struct _lcache_s {

  s32_t		s32v_cnt;
  u64_t*	u64p_element;
  u32_t*        u32p_hash;
  s32_t		s32v_last;
  u8_t		u8v_filled;

} lcache_t;

s32_t s32f_lcache_init( s32_t s32v_lcache_cnt, u32_t u32v_lcache_flags, 
		        lcache_t* lcache_ptr_result );

s32_t s32f_lcache_add( lcache_t* lcache_ptr, u64_t u64v_value, 
		       u32_t u32v_hash );

u64_t u64f_lcache_find( lcache_t* lcache_ptr, u32_t u32v_hash );

#endif	/* _LCACHE_H */
