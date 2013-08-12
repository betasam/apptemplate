/**
 * @file        lconfig.c
 * @brief       handle arguments, etc.
 */

#include <unistd.h>
#include <stdlib.h>
#include <getopt.h>

#include <ltypes.h>
#include <lconfig.h>

/*
 *  POSIX adherence 
 *   getopt.h defines:
 *      extern char *optarg;
 *      extern int   optind, opterr, optopt;
 */

/**
 * @function    s32f_parse_args
 * @brief       parse command line arguments, extract number
 * @param       argc: POSIX (int)
 * @param       argv: POSIX (char**)
 * @param       u32p_num        pointer to number
 * @return      -1 on failure, +ve FLAGS on success. refer: lconfig.h
 */
s32_t s32f_parse_args( int argc, char *argv[], u32_t* u32p_num )
{
  s32_t s32v_ret = 0;
  s32_t u32v_num = INTC_DEFAULT_NUM;
  s32_t s32v_opt = 0;

  if( u32p_num == NULL ) {

    s32v_ret = -1;

  } else {

    while((s32v_opt = getopt( argc, argv, STRC_ARG_SET)) != -1) {

      switch( s32v_opt ) {

      case CHRC_ARG_NUMBER:
        u32v_num =  strtoul(optarg, NULL, INTC_DEFAULT_BASE);
        s32v_ret |= INTC_FLAG_NUMBER;
        break;
      case CHRC_ARG_RECURSE:
        s32v_ret |= INTC_FLAG_RECURSE;
        break;
      case CHRC_ARG_CACHE:
        s32v_ret |= INTC_FLAG_CACHE;
        break;
      case CHRC_ARG_STAMP:
        s32v_ret |= INTC_FLAG_STAMP;
        break;
      case CHRC_ARG_HELP:
        s32v_ret |= INTC_FLAG_HELP;
        break;
      default:
        s32v_ret |= INTC_FLAG_HELP;     

      }
    }

    (*u32p_num) = u32v_num;

  }

  return( s32v_ret );
}

/*
 * end: lconfig.c
 **/
