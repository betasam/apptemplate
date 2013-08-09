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
ECHO     :=     echo

#
# PATHS
# first two paths contain source
# rest of the paths get output
#
INCPATH  :=     include
SRCPATH  :=     src

OBJPATH  :=     obj
BINPATH  :=     bin
DOCPATH  :=	doc

# CAVEAT! order of files here may affect linking
EXECNAME :=     fibonacci
SRCNAMES :=	test.c lcache.c lmessage.c lconfig.c

CFLAGSX  :=     -Wall
SRCEXT   :=     .c
OBJEXT   :=     .o

#
# pretty print
#
CCVAR    =	CC
LDVAR	 =	LD
RMVAR	 =	RM

#
# weak assertions
#
CC       ?=     gcc
VERBOSE  ?=     0
DEBUG    ?=     0

#
# conditional constructs
#
ifeq ($(V),1)
VERBOSE  :=	1
endif

ifeq ($(VERBOSE),1)
QUIET    :=     0
endif

QUIET    ?=     1
ifeq ($(QUIET),1)
Q        = @
else
Q        =      
endif

ifeq ($(DEBUG),1)
CFLAGSX += -g
endif

#
# derived variables
# WARNING!
#       do not add constants after this
#
TOPPATH  :=     $(dir $(CURDIR)/$(word $(words $(MAKEFILE_LIST)),$(MAKEFILE_LIST)))

SINCLUDE :=
LINCLUDE :=     $(addprefix -I$(TOPPATH), $(INCPATH))
INCLUDE  :=     $(SINCLUDE) $(LINCLUDE)
CFLAGS   :=	$(CFLAGSX) $(INCLUDE)

OBJNAMES :=     $(patsubst  %$(SRCEXT),%$(OBJEXT),  $(SRCNAMES))
SRCFILES :=	$(addprefix $(TOPPATH)/$(SRCPATH)/, $(SRCNAMES))
OBJFILES :=     $(addprefix $(TOPPATH)/$(OBJPATH)/, $(OBJNAMES))
EXECFILE :=     $(addprefix $(TOPPATH)/$(BINPATH)/, $(EXECNAME))

all: compile 

compile: $(OBJFILES)

binary: $(EXECFILE)

$(OBJFILES): $(SRCFILES)
	$(Q)$(CC) $(CFLAGS) $(COMPILE) $(patsubst %$(OBJEXT),%$(SRCEXT), $(subst $(OBJPATH),$(SRCPATH), $@)) -o $@
ifeq ($(QUIET),1)
	$(Q)$(ECHO) $(CCVAR) $(patsubst %$(OBJEXT),%$(SRCEXT), $(subst $(OBJPATH),$(SRCPATH), $@))
endif

$(EXECFILE): $(OBJFILES)
	$(Q)$(CC) $(OBJFILES) -o $@
ifeq ($(QUIET),1)
	$(Q)$(ECHO) $(LDVAR) $(OBJNAMES) \> $(EXECNAME)
endif

clean: 
	$(Q)$(RM) $(RMFLAGS) $(OBJFILES)
	$(Q)$(RM) $(RMFLAGS) $(EXECFILE)
ifeq ($(QUIET),1)
	$(Q)$(ECHO) $(RMVAR) $(OBJNAMES)
	$(Q)$(ECHO) $(RMVAR) $(EXECNAME)
endif

.PHONY: clean

#
## Makefile
