#ifndef _LTIME_H
#define _LTIME_H

#define TIMESTAMP(P)		do { (*P)=u64f_gettime_msec(); } while(0);
#define TIMEDELTA(F,T)		u64f_getdelta(F,T)

u64_t u64f_gettime_msec( void );
u64_t u64f_getdelta( u64_t u64v_from, u64_t u64v_to );

#endif	/* _LTIME_H */
