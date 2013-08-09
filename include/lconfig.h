#ifndef _LCONFIG_H
#define _LCONFIG_H

#define STRC_ARG_SET		"n:rh"
#define CHRC_ARG_NUMBER		'n'
#define CHRC_ARG_RECURSE	'r'
#define CHRC_ARG_HELP		'h'

#define INTC_DEFAULT_NUM	0
#define INTC_DEFAULT_BASE	10
#define INTC_FLAG_INIT		0
#define INTC_FLAG_NUMBER	1
#define INTC_FLAG_RECURSE	2
#define INTC_FLAG_HELP		4

#define CHK_FLAG(n,f)		((n & f) ? 1 : 0)

s32_t s32f_parse_args( int argc, char *argv[], u32_t* u32p_num );

#endif	/* _LCONFIG_H */
