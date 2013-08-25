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
LD       :=     ld
LDFLAGS  :=	
ECHO     :=     echo
ETAGS    :=     etags
ETAGARG  :=     -a
MKDIR    :=     mkdir
MKDARGS  :=     -p
EQUIVS   :=     equivs-build
PKGDSUFF :=     depends
PKGDARCH :=     all
PKGDEXT  :=     deb

#
# command dependency list
#
CMD_DEPS :=	$(CC) $(ETAGS) $(EQUIVS)

#
# PATHS
# first three paths contain source
# rest of the paths get output
#
INCPATH  :=     include
SRCPATH  :=     src
DOCPATH  :=	doc
ETCPATH  :=     etc

OBJPATH  :=     obj
BINPATH  :=     bin

OUTPATHS := $(OBJPATH) $(BINPATH)

# CAVEAT! order of files here may affect linking
PACKAGE  :=     apptemplate
EXECNAME :=     fibonacci
SRCNAMES :=	main.c apps.c fibonacci_app.c lcache.c lmessage.c lconfig.c ltime.c
TAGNAMES :=     TAGS
VERSION  :=     0.1

CFLAGSX  :=     -Wall -O3
SRCEXT   :=     .c
OBJEXT   :=     .o
HDREXT   :=     .h

#
# pretty print
#
CCVAR    =	CC
LDVAR	 =	LD
RMVAR	 =	RM
TAGVAR   =      TAGS
MKDVAR   =      MKDIR

#
# weak defaults/assertions
#
CC       ?=     gcc
VERBOSE  ?=     0
DEBUG    ?=     0
DEPLIST  ?=

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
DEPLIST += -DDEBUG
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
CFLAGS   :=	$(CFLAGSX) $(INCLUDE) $(DEPLIST)

OBJNAMES :=     $(patsubst  %$(SRCEXT),%$(OBJEXT),  $(SRCNAMES))
SRCFILES :=	$(addprefix $(TOPPATH)/$(SRCPATH)/, $(SRCNAMES))
OBJFILES :=     $(addprefix $(TOPPATH)/$(OBJPATH)/, $(OBJNAMES))
EXECFILE :=     $(addprefix $(TOPPATH)/$(BINPATH)/, $(EXECNAME))
DEPSFILE :=     $(TOPPATH)/$(ETCPATH)/$(PACKAGE)-$(PKGDSUFF)
PKGDFILE :=     $(PACKAGE)-$(PKGDSUFF)_$(VERSION)_$(PKGDARCH).$(PKGDEXT)

#
# target rules
#

all: dircheck binary

dircheck: $(OUTPATHS)

$(OUTPATHS):
	$(Q)$(MKDIR) $(MKDARGS) $@
ifeq ($(QUIET),1)
	$(Q)$(ECHO) $(MKDVAR) $@
endif

compile: $(OBJFILES)

binary: $(EXECFILE)

tags: TAGS

TAGS: $(SRCFILES)
	$(Q)$(ETAGS) $(ETAGARG) $(SRCFILES) $(patsubst %$(SRCEXT),%$(HDREXT), $(subst $(SRCPATH),$(INCPATH), $(SRCFILES)))
ifeq ($(QUIET),1)
	$(Q)$(ECHO) $(TAGVAR) \*$(SRCEXT) \*$(HDREXT)
endif

$(OBJFILES): $(SRCFILES)
	$(Q)$(CC) $(CFLAGS) $(COMPILE) $(patsubst %$(OBJEXT),%$(SRCEXT), $(subst $(OBJPATH),$(SRCPATH), $@)) -o $@
ifeq ($(QUIET),1)
	$(Q)$(ECHO) $(CCVAR) $(patsubst %$(OBJEXT),%$(SRCEXT), $(subst $(OBJPATH),$(SRCPATH), $@))
endif

$(EXECFILE): $(OBJFILES)
	$(Q)$(CC) $(LDFLAGS) $(OBJFILES) -o $@
ifeq ($(QUIET),1)
	$(Q)$(ECHO) $(LDVAR) $(OBJNAMES) \-\> $(EXECNAME)
endif

mrproper: distclean

distclean: clean package-clean

package: package-depends

package-depends: $(DEPSFILE)
	$(EQUIVS) $(DEPSFILE)

package-clean:
	$(Q)$(RM) $(PKGDFILE)
ifeq ($(QUIET),1)
	$(Q)$(ECHO) $(RMVAR) $(PKGDFILE)
endif

clean: 
	$(Q)$(RM) $(RMFLAGS) $(OBJFILES) $(TAGNAMES)
	$(Q)$(RM) $(RMFLAGS) $(EXECFILE)
ifeq ($(QUIET),1)
	$(Q)$(ECHO) $(RMVAR) $(OBJNAMES) $(TAGNAMES)
	$(Q)$(ECHO) $(RMVAR) $(EXECNAME)
endif

help:
	@$(ECHO)   "   make [options] [target]"
	@$(ECHO)   "       all:        build target:binary"
	@$(ECHO)   "       compile:    only compiles files"
	@$(ECHO)   "       binary:     compiles and links binary [fibonacci]"
	@$(ECHO)   "       clean:      cleans artefacts from previous build"
	@$(ECHO)   "       tags:       creates emacs [exuberant] TAGS file"
	@$(ECHO)   "       package:    build debian packages"
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

.PHONY: clean help distclean mrproper tags dircheck package-clean

#
## Makefile
