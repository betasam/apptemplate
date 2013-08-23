#ifndef _LMESSAGE_H
#define _LMESSAGE_H

#define STRC_MESSAGE    "info"
#define STRC_WARNING    "warn"
#define STRC_ERROR      "ERROR"

void umessage(char *format, ...);
void uwarning(char *format, ...);
void uerror(char *format, ...);

#endif /* _LMESSAGE_H */
