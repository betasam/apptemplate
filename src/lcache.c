/**
 * @file        lcache.c
 * @brief       object cache with linear search
 */

#include <stdlib.h>

#include <ltypes.h>
#include <lconst.h>
#include <lcache.h>

/**
 * @function    s32f_lcache_init
 * @brief       initialize cache
 * @param       s32v_lcache_cnt         cache size
 * @param       s32v_lcache_flags       flags, see: lcache.h
 * @param       lcache_ptr              cache to initialize
 *
 * @return      0 on success, -1 on failure
 */
s32_t s32f_lcache_init(s32_t s32v_lcache_cnt,
                       u32_t u32v_lcache_flags, lcache_t * lcache_ptr)
{
    s32_t s32v_ret = 0;
    u32_t u32v_sz = 0;
    s32_t s32v_idx = 0;

    do {

        if ((s32v_lcache_cnt <= 0) ||
            (u32v_lcache_flags == LCACHE_FLAG_INVALID) ||
            (lcache_ptr == 0)) {
            s32v_ret = -1;
            break;
        }

        /* align along system word size (or quad-word size) 32-bit */
        u32v_sz = LCACHE_SZ_ALIGN(((sizeof(u64_t) * s32v_lcache_cnt)));
        /* allocate memory for elements */
        if ((lcache_ptr->u64p_element = malloc(u32v_sz)) == 0) {
            s32v_ret = -1;
            break;
        }

        /* align along system word size (or quad word size) 32-bit */
        u32v_sz = LCACHE_SZ_ALIGN(((sizeof(u32_t) * s32v_lcache_cnt)));
        /* allocate memory for hash references */
        if ((lcache_ptr->u32p_hash = malloc(u32v_sz)) == 0) {
            s32v_ret = -1;
            free(lcache_ptr->u64p_element);
            break;
        }

        /* initialize allocated memory [explicitly avoiding calloc] */
        lcache_ptr->s32v_cnt = s32v_lcache_cnt;
        lcache_ptr->s32v_last = 0;
        lcache_ptr->u8v_filled = 0;

        /* loop: initialize all elements to zero to avoid junking */
        while (s32v_idx < lcache_ptr->s32v_cnt) {
            lcache_ptr->u32p_hash[s32v_idx] = 0;
            lcache_ptr->u64p_element[s32v_idx] = U64C_ZERO;
            s32v_idx++;
        }

    } while (0);

    return s32v_ret;
}

/**
 * @function    s32f_lcache_free
 * @brief       frees memory inside the cache
 *              does not free the cache, as it is outside scope
 * @param       lcache_ptr      cache to free
 * @return      0 on success, -1 on failure
 */
s32_t s32f_lcache_free(lcache_t * lcache_ptr)
{
    s32_t s32v_ret = 0;

    do {
        if (lcache_ptr == 0) {
            s32v_ret = -1;
            break;
        }

        if ((lcache_ptr->u32p_hash == 0) ||
            (lcache_ptr->u64p_element == 0)) {
            s32v_ret = -1;
            break;
        }

        /* WARNING: this code must be atomic to be threadsafe */
        free(lcache_ptr->u32p_hash);
        free(lcache_ptr->u64p_element);
        lcache_ptr->s32v_cnt = 0;
        lcache_ptr->s32v_last = 0;
        lcache_ptr->u8v_filled = 0;

    } while (0);

    return s32v_ret;
}

/**
 * @function    s32f_lcache_add
 * @brief       add an item to the cache
 *              if it exceeds size, wrap around
 * @param       u64v_value      value to be added
 * @param       u64v_hash       hash to access value
 * @return      0 on success, -1 on failure
 */
s32_t s32f_lcache_add(lcache_t * lcache_ptr,
                      u64_t u64v_value, u32_t u32v_hash)
{
    s32_t s32v_ret = 0;

    do {

        /* check if arguments can be processed */
        if ((lcache_ptr == 0) || (u64v_value == 0) || (u32v_hash == 0)) {
            s32v_ret = -1;
            break;
        }

        /* check if extents are exceeded inside cache */
        if (lcache_ptr->s32v_last > lcache_ptr->s32v_cnt) {
            s32v_ret = -1;
            break;
        }

        /* wrap around ring buffer if it has been filled already */
        if ((lcache_ptr->s32v_last == lcache_ptr->s32v_cnt) &&
            (lcache_ptr->u8v_filled == 1)) {
            lcache_ptr->s32v_last = 0;
        }

        /* WARNING! the following needs to be atomic to be threadsafe */
        lcache_ptr->u64p_element[lcache_ptr->s32v_last] = u64v_value;
        lcache_ptr->u32p_hash[lcache_ptr->s32v_last] = u32v_hash;
        lcache_ptr->s32v_last++;

        /* indicate if cache is filled to support wrap-around */
        if ((lcache_ptr->u8v_filled == 0) &&
            (lcache_ptr->s32v_last == lcache_ptr->s32v_cnt)) {
            lcache_ptr->u8v_filled = 1;
        }

    } while (0);

    return s32v_ret;
}

/**
 * @function    u64f_lcache_find
 * @brief       searches for an element in the cache
 * @param       lcache_ptr      cache to be searched
 * @param       u32v_hash       hash value used for search
 * @return      u64_t 64-bit value corresponding to element
 */
u64_t u64f_lcache_find(lcache_t * lcache_ptr, u32_t u32v_hash)
{
    u64_t u64v_ret = U64C_ZERO;
    s32_t s32v_idx = 0;

    do {
        if ((lcache_ptr == 0) || (u32v_hash == 0)) {
            break;
        }

        /* 
         * perform linear search as this list is ordered
         * or a set of two ordered lists in sequence 
         */
        while (s32v_idx < lcache_ptr->s32v_cnt) {
            if (lcache_ptr->u32p_hash[s32v_idx] == u32v_hash) {
                u64v_ret = lcache_ptr->u64p_element[s32v_idx];
                break;
            }
            s32v_idx++;
        }

    } while (0);

    return u64v_ret;
}

/*
 * end: lcache.c
 **/
