#ifndef _LCACHE_H
#define _LCACHE_H

#define LCACHE_FLAG_INVALID	0xFFFFFFFF

typedef struct _lcache_s {

  s32_t		s32v_cnt;
  u64_t*	u64p_element;
  s32_t		s32v_last;

} lcache_t;

s32_t s32_f_lcache_init( s32_t s32v_lcache_cnt, u32_t u32v_lcache_flags, lcache_t* lcache_ptr );


#endif	/* _LCACHE_H */
