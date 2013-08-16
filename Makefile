##
#	Makefile
#
#	08-Aug-2013
#	Sunil Beta	<betasam@gmail.com>
#
#       To find out which targets to use:
#        make help
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
SRCNAMES :=	main.c apps.c fibonacci_app.c lcache.c lmessage.c lconfig.c ltime.c

CFLAGSX  :=     -Wall -O3
SRCEXT   :=     .c
OBJEXT   :=     .o

#
# pretty print
#
CCVAR    =	CC
LDVAR	 =	LD
RMVAR	 =	RM

#
# weak defaults/assertions
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

#
# target rules
#

all: compile 

compile: $(OBJFILES)

binary: $(EXECFILE)

$(OBJFILES): $(SRCFILES)
	$(Q)$(CC) $(CFLAGS) $(COMPILE) $(patsubst %$(OBJEXT),%$(SRCEXT), $(subst $(OBJPATH),$(SRCPATH), $@)) -o $@
ifeq ($(QUIET),1)
	$(Q)$(ECHO) $(CCVAR) $(patsubst %$(OBJEXT),%$(SRCEXT), $(subst $(OBJPATH),$(SRCPATH), $@))
endif

$(EXECFILE): $(OBJFILES)
	$(Q)$(CC) $(CFLAGS) $(OBJFILES) -o $@
ifeq ($(QUIET),1)
	$(Q)$(ECHO) $(LDVAR) $(OBJNAMES) \-\> $(EXECNAME)
endif

clean: 
	$(Q)$(RM) $(RMFLAGS) $(OBJFILES)
	$(Q)$(RM) $(RMFLAGS) $(EXECFILE)
ifeq ($(QUIET),1)
	$(Q)$(ECHO) $(RMVAR) $(OBJNAMES)
	$(Q)$(ECHO) $(RMVAR) $(EXECNAME)
endif

help:
	@$(ECHO)   "   make [options] [target]"
	@$(ECHO)   "       all:        only compiles files"
	@$(ECHO)   "       binary:     compiles and links binary [fibonacci]"
	@$(ECHO)   "       clean:      cleans artefacts from previous build"
	@$(ECHO)       
	@$(ECHO)   "       VERBOSE=1   provides verbose information"
	@$(ECHO)   "       DEBUG=1     enables debugging symbols"
	@$(ECHO)   "       QUIET=1     suppresses verbosity, default"
	@$(ECHO)
	@$(ECHO)   "  examples:"
	@$(ECHO)   "       $$ make clean && make binary"
	@$(ECHO)   "             builds bin/fibonacci"
	@$(ECHO)   "       $$ make VERBOSE=1 binary"
	@$(ECHO)   "             same as above, but verbose"
	@$(ECHO)

.PHONY: clean help

#
## Makefile
