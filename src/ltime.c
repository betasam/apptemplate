/**
 * @file        ltime.c
 * @brief       time stamper
 */

#include <stdlib.h>
#include <sys/time.h>

#include <lconst.h>
#include <ltypes.h>

/**
 * @function    u64_gettime_usec
 * @brief       gets current time in microseconds
 * @return      64-bit unsigned time in microseconds
 */
u64_t u64f_gettime_usec(void)
{
    struct timeval tv_s_now;
    u64_t u64v_time = U64C_ZERO;
    s32_t s32v_status = 0;

    do {
        if ((s32v_status = gettimeofday(&tv_s_now, NULL)) == -1) {
            break;
        }

        u64v_time = ((tv_s_now.tv_sec * U32C_USECS_PER_SEC) +
                     (tv_s_now.tv_usec));

    } while (0);

    return u64v_time;
}

/**
 * @function    u64f_getdelta
 * @param       u64v_from       first stamp
 * @param       u64v_to         second stamp
 * @return      mod[ u64v_from - u64v_to ] 
 */
u64_t u64f_getdelta(u64_t u64v_from, u64_t u64v_to)
{
    u64_t u64v_ret = U64C_ZERO;

    do {

        if (u64v_to > u64v_from) {
            u64v_ret = u64v_to - u64v_from;
            break;
        }

        if (u64v_from > u64v_to) {
            u64v_ret = u64v_from - u64v_to;
        }

    } while (0);

    return u64v_ret;
}

/*
 * end: ltime.c
 * no code after this
 **/
