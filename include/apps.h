#ifndef _APPS_H
#define _APPS_H

#define APP_STATE_INIT          1
#define APP_STATE_RUNNING       2
#define APP_STATE_FINISHED      4
#define APP_STATE_NORMAL        8
#define APP_STATE_EXCEPTION     16

typedef struct _app_s {

    s32_t s32v_state;
     s32_t(*main) (int argc, char *argv[]);
    s32_t s32v_return;

} app_t;

s32_t s32f_app_init(app_t * app_p_ref,
                    s32_t(*main) (int argc, char *argv[]));

s32_t s32f_app_exec(app_t * app_p_ref, int argc, char *argv[]);

#endif /* _APPS_H */
