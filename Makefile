##
#	Makefile
#
#	08-Aug-2013
#	Sunil Beta	<betasam@gmail.com>
##

#
# commands and static command flags
#
GCC      :=	gcc
COMPILE  :=     -c
RM       :=     rm
RMFLAGS  :=     -f

INCPATH  :=     include
OBJPATH  :=     obj
SRCPATH  :=     src

SRCNAMES :=	test.c
CFLAGSX  :=     -Wall
SRCEXT   :=     .c
OBJEXT   :=     .o

#
# weak assertions
#
CC       = $(GCC)

#
# derived variables
#
TOPPATH  :=     $(dir $(CURDIR)/$(word $(words $(MAKEFILE_LIST)),$(MAKEFILE_LIST)))

SINCLUDE :=
LINCLUDE :=     $(addprefix -I$(TOPPATH), $(INCPATH))
INCLUDE  :=     $(SINCLUDE) $(LINCLUDE)
CFLAGS   :=	$(CFLAGSX) $(INCLUDE)

OBJNAMES :=     $(patsubst %$(SRCEXT),%$(OBJEXT), $(SRCNAMES))
SRCFILES :=	$(addprefix $(TOPPATH)/$(SRCPATH)/, $(SRCNAMES))
OBJFILES :=     $(addprefix $(TOPPATH)/$(OBJPATH)/, $(OBJNAMES))

all: compile 

compile: $(SRCFILES)
	$(CC) $(CFLAGS) $(COMPILE) $< -o  $(patsubst %$(SRCEXT),%$(OBJEXT),  $(subst $(SRCPATH),$(OBJPATH), $<))

clean: 
	$(RM) $(RMFLAGS) $(OBJFILES)

.PHONY: clean

#
## Makefile
