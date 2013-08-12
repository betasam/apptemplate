/**
 * @file        fibonacci_app.c
 * @brief       application to generate Fibonacci(N)
 *              where N belongs-to { Z+ }
 */

#include <ltypes.h>
#include <lconst.h>
#include <lmessage.h>
#include <lcache.h>
#include <lconfig.h>
#include <ltime.h>

#include <fibonacci_app.h>

/**
 * @function    u64f_fibonacci_recursive
 * @brief       calculate fibonacci(u32v_n) using recursive calls
 * @param       u32v_n
 * @return      64-bit unsigned integer
 */
u64_t u64f_fibonacci_recursive( u32_t u32v_n )
{
  u64_t u64v_ret = 0;

  if( (u32v_n == U64C_FIB_0) || (u32v_n == U64C_FIB_1) ) {
    /* fibonacci(0,1) = {0,1} */
    u64v_ret = u32v_n;
  } else {
    /* fibonacci(n) = fibonacci(n-1) + fibonacci(n-2) */
    u64v_ret = (u64f_fibonacci_recursive(u32v_n - 1) + 
                u64f_fibonacci_recursive(u32v_n - 2));
  }

  return u64v_ret;
}

/**
 * @function    u64f_fibonacci_recursive_cached
 * @brief       calculate fibonacci(u32v_n) using recursive calls
 *              uses caching to reduce execution time.
 * @param       u32v_n
 * @return      64-bit unsigned integer
 * @refer       lcache.c
 */
u64_t u64f_fibonacci_recursive_cached( u32_t u32v_n )
{
  static lcache_t lcache_fibonacci;
  static u32_t u32v_cache_sz;
  u64_t u64v_ret = 0;

  if( (u32v_n == U64C_FIB_0) || (u32v_n == U64C_FIB_1) ) {
    /* fibonacci(0,1) = {0,1} */
    u64v_ret = u32v_n;
  } else {

    /* search cache for a match */
    if( lcache_fibonacci.s32v_cnt > 0) {
#ifdef LMESSAGE_DEBUG
      umessage("u64f_lcache_find: searching hash[ %u ]\n", u32v_n);
#endif
      u64v_ret = u64f_lcache_find( &lcache_fibonacci, u32v_n );
#ifdef LMESSAGE_DEBUG
      umessage("u64f_lcache_find: retrieved [ %lu ]\n", u64v_ret);
#endif
    } else {
      /* cache depth is CEILING[ N/2 ] */
      u32v_cache_sz = ((u32v_n >> 1) + (u32v_n & 1));
      if( (s32f_lcache_init(u32v_cache_sz, 
                            LCACHE_FLAG_INITIAL, 
                            &lcache_fibonacci)) == -1 ) {
        uwarning("%s: cannot init cache [ %u ] of size [ %u ]\n",
                 __func__, u32v_n, LCACHE_DEFAULT_LEN);
      }
    }

    /* cannot find cached value, calculating ... */
    if( u64v_ret == U64C_ZERO ) {
      /* fibonacci(n) = fibonacci(n-1) + fibonacci(n-2) */
      u64v_ret = (u64f_fibonacci_recursive_cached(u32v_n - 1) + 
                  u64f_fibonacci_recursive_cached(u32v_n - 2));
      s32f_lcache_add( &lcache_fibonacci, u64v_ret, u32v_n );
    } 
  }

  return u64v_ret;
}

/**
 * @function    u64f_fibonacci_seq
 * @brief       calculate fibonacci(u32v_n) using a single loop.
 * @param       u32v_n
 * @return      64-bit unsigned integer
 */
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

    /* fibonacci(next) = fibonacci(curr) + fibonacci(prev) */
    while( u32v_idx > U64C_FIB_1 ) {
      u64v_sum  = u64v_curr + u64v_prev;
      u64v_prev = u64v_curr;
      u64v_curr = u64v_sum;
      u32v_idx  = u32v_idx  - 1;
    }
    
  }

  return u64v_sum;
}

/**
 * @function    s32f_fibonacci_app
 * @param       POSIX: argc (int)
 * @param       POSIX: argv (char**)
 * @return      0 on success, -1 on failure
 */
s32_t s32f_fibonacci_app( int argc, char *argv[] )
{
  s32_t s32v_ret    = 0;
  u32_t u32v_n      = 0;
  s32_t s32v_flags  = 0;
  u64_t u64v_r      = U64C_ZERO;

  u32_t u32v_stamp  = 0;
  u64_t u64v_time_1 = U64C_ZERO;
  u64_t u64v_time_2 = U64C_ZERO;
  u64_t u64v_time_3 = U64C_ZERO;
 
  if( (s32v_flags = s32f_parse_args( argc, argv, &u32v_n )) != -1 ) {

    do {

      /* print usage if necessary arguments not present */
      if( !(CHK_FLAG(s32v_flags, INTC_FLAG_NUMBER)) ) {
        uerror(  "number unspecified\n");
        umessage("usage: %s -n <number> [-r [-c]] [-t]\n", argv[0]);
        umessage("       -r       use recursive algorithm.\n");
        umessage("       -c       use caching with recursion.\n");
        umessage("       -t       timestamp microseconds.\n\n");
        s32v_ret = -1;
        break;
      } 

      /* timestamp(1) */
      if( CHK_FLAG(s32v_flags, INTC_FLAG_STAMP) ) {
        u32v_stamp = 1;
        TIMESTAMP(&u64v_time_1);
        umessage("stamp[1] = %lu\n", u64v_time_1);
      }

      /* select algorithm:routine, compute result */
      if( CHK_FLAG(s32v_flags, INTC_FLAG_RECURSE) ) {
        umessage("using recursive algorithm for result ...\n");
        if( CHK_FLAG(s32v_flags, INTC_FLAG_CACHE) ) {
          umessage("using recursive algorithm with cache ...\n");
          u64v_r = u64f_fibonacci_recursive_cached(u32v_n);
        } else {
          u64v_r = u64f_fibonacci_recursive(u32v_n);
        }

      } else {
        umessage("using sequential algorithm for result ...\n");
        u64v_r = u64f_fibonacci_seq(u32v_n);
      }

      /* timestamp(2) */
      if( u32v_stamp == 1 ) {
        TIMESTAMP(&u64v_time_2);
        umessage("stamp[2] = %lu\n", u64v_time_2);
      }

      umessage("input: %u, result: %lu \n", u32v_n, u64v_r);

      /* compute time elapsed */
      if( u32v_stamp == 1 ) {
        u64v_time_3 = TIMEDELTA( u64v_time_2, u64v_time_1 );
        umessage("time: %lu " STRC_TIME_UNIT "\n", u64v_time_3 );
      }

    } while(0);

  }

  return s32v_ret;
}

/* 
 * end:         fibonacci_app.c
 **/
