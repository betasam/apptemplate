/**
 * @file	apps.c
 * @brief	framework for new applications
 *		styled as a multicaller binary
 */

#include <lconst.h>
#include <ltypes.h>
#include <lconfig.h>

#include <apps.h>

/**
 * @function	s32f_app_init
 * @brief	initializes a POSIX complaint application main(...)
 * @param	app_p_ref	pointer to app
 * @param	main_fp		function pointer to app main(...)
 * @return	-1 on failure, 0 on success
 */
s32_t s32f_app_init( app_t* app_p_ref, 
		     s32_t (*main_fp)(int argc, char *argv[])) {

  s32_t s32v_ret = 0;

  if( (app_p_ref == 0) || (main_fp == 0) ) {
    
    s32v_ret = -1;

  } else {

    app_p_ref->s32v_state = APP_STATE_INIT;
    app_p_ref->main = main_fp;
    app_p_ref->s32v_return = 0;
  }

  return s32v_ret;
}

/**
 * @function	s32f_app_exec
 * @brief	executes an application
 * @param	app_p_ref	pointer to application
 * @param	argc		POSIX compliant argc(int)
 * @param	argv		POSIX compliant argv(char**)
 * @return	-1 on failure, 0 on success
 */
s32_t s32f_app_exec( app_t *app_p_ref, int argc, char *argv[] )
{
  s32_t s32v_ret = 0;

  if( app_p_ref == 0 ) {
    
    s32v_ret = -1;

  } else {

    app_p_ref->s32v_state = (APP_STATE_RUNNING | APP_STATE_NORMAL);
    s32v_ret = app_p_ref->main( argc, argv );
    app_p_ref->s32v_state = (APP_STATE_FINISHED);
    if( s32v_ret != 0 ) {
      app_p_ref->s32v_state |= APP_STATE_EXCEPTION;
    } else {
      app_p_ref->s32v_state |= APP_STATE_NORMAL;
    }

  }

  return s32v_ret;
}


/*
 * end:		apps.c
 **/
