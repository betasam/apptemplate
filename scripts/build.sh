#!/bin/bash
#
# FILE		build.sh
#
# BRIEF		builds using gcc and clang
#		generates log for both
#
# USAGE		build.sh [x]
#		    x	option to exit after clean
#

THIS="./build.sh"
BUILD="build-apptemplate:"
BINDIR=bin
BINARY=fibonacci
LOGDIR=log
LOGEXT=log
CLANG=clang
GCC=gcc
RM=rm
MV=mv
MAKE=make
CAT=cat
SED=sed
DIFF=diff
DIFFNAME="gcc-clang"
DIFFEXT=diff
DIFFARGS="-NrU 3"
OBJDUMP=objdump
DISARGS="-d -S"
CLEANONLY=0

function f_setup_topdir {

    if [ -x ${THIS} ]; then
	export TOPDIR=$(cd .. && pwd)
    else
	export TOPDIR=$(pwd)
    fi
    echo -e "${BUILD} using TOPDIR=${TOPDIR} ..."

}

function f_enter_topdir {
    echo -e "${BUILD} entering TOPDIR=${TOPDIR} ..."
    pushd ${TOPDIR}
}

function f_leave_topdir {
    echo -e "${BUILD} leaving  TOPDIR=${TOPDIR} ..."
    popd
}

function f_setup_clean {
    EXTENT="$1"
    if [ "$EXTENT" == "" ]; then
	EXTENT=0
    else
	EXTENT=1
	export CLEANONLY=1
    fi
}

function f_check_deps {

    EXITNOW=0
    CHECK_GCC=$(which ${GCC})
    CHECK_CLANG=$(which ${CLANG})
    CHECK_OBJDUMP=$(which ${OBJDUMP})

    if [ ! -x ${CHECK_GCC} ]; then
	echo -e "${BUILD} unable to execute ${GCC} in PATH ..."
	EXITNOW=1
    fi

    if [ ! -x ${CHECK_CLANG} ]; then
	echo -e "${BUILD} unable to execute ${CLANG} in PATH ..."
	EXITNOW=1
    fi

    if [ ! -x ${CHECK_OBJDUMP} ]; then
	echo -e "${BUILD} unable to execute ${OBJDUMP} in PATH ..."
	EXITNOW=1
    fi

    if [ "${EXITNOW}" == "1" ]; then
	echo -e "${BUILD} please correct dependencies, exiting!"
	echo
	f_leave_topdir
	exit 1
    else
	echo -e "${BUILD} dependencies verified."
    fi

}

function f_clean_subdirs {

    if [ -f ${BINDIR}/${BINARY}.${GCC} ]; then
	echo -e "${BUILD} ${RM} ${BINARY}.${GCC}"
	${RM} ${BINDIR}/${BINARY}.${GCC}
    fi

    if [ -f ${BINDIR}/${BINARY}.${CLANG} ]; then
	echo -e "${BUILD} ${RM} ${BINARY}.${CLANG}"
	${RM} ${BINDIR}/${BINARY}.${CLANG}
    fi

    if [ -f ${LOGDIR}/${BINARY}.${GCC}.${LOGEXT} ]; then
	echo -e "${BUILD} ${RM} ${BINARY}.${GCC}.${LOGEXT}"
	${RM} ${LOGDIR}/${BINARY}.${GCC}.${LOGEXT}
    fi

    if [ -f ${LOGDIR}/${GCC}.${LOGEXT} ]; then
	echo -e "${BUILD} ${RM} ${GCC}.${LOGEXT}"
	${RM} ${LOGDIR}/${GCC}.${LOGEXT}
    fi

    if [ -f ${LOGDIR}/${BINARY}.${CLANG}.${LOGEXT} ]; then
	echo -e "${BUILD} ${RM} ${BINARY}.${CLANG}.${LOGEXT}"
	${RM} ${LOGDIR}/${BINARY}.${CLANG}.${LOGEXT}
    fi

    if [ -f ${LOGDIR}/${CLANG}.${LOGEXT} ]; then
	echo -e "${BUILD} ${RM} ${CLANG}.${LOGEXT}"
	${RM} ${LOGDIR}/${CLANG}.${LOGEXT}
    fi

    if [ -f ${LOGDIR}/${DIFFNAME}.${DIFFEXT} ]; then
	echo -e "${BUILD} ${RM} ${DIFFNAME}.${DIFFEXT}"
	${RM} ${LOGDIR}/${DIFFNAME}.${DIFFEXT}
    fi

    if [ "${CLEANONLY}" == "1" ]; then
	echo -e "${BUILD} done cleaning, exiting as requested."
	echo
	f_clean_targets
	f_leave_topdir
	exit 0
    fi

}

function f_clean_targets {
    echo -e "${BUILD} cleaning ..."
    ${MAKE} clean
}

function f_build_targets {

    COMPILER="$1"
    if [ "${COMPILER}" == "" ]; then
	COMPILER=${GCC}
    fi

    echo -e "${BUILD} building with ${COMPILER} ..."
    CC=${COMPILER} ${MAKE} DEBUG=1 binary
    ${MV} ${BINDIR}/${BINARY} ${BINDIR}/${BINARY}.${COMPILER}

}

function f_disas_targets {

    COMPILER="$1"
    if [ "${COMPILER}" == "" ]; then
	COMPILER=${GCC}
    fi

    echo -e "${BUILD} disassembling binary executable ${BINARY}.${COMPILER} ..."
    ${OBJDUMP} ${DISARGS} ${BINDIR}/${BINARY}.${COMPILER} &> ${LOGDIR}/${BINARY}.${COMPILER}.${LOGEXT}

 ${CAT} ${LOGDIR}/${BINARY}.${COMPILER}.${LOGEXT} | ${SED} "s/^.[ 0-9a-f]*://" | ${SED} "s/^0.*\</\</" &> ${LOGDIR}/${COMPILER}.${LOGEXT}
 
}

function f_diffx_targets {
    echo -e "${BUILD} creating ${DIFFNAME}.${DIFFEXT} ..."
    ${DIFF} ${DIFFARGS} ${LOGDIR}/${GCC}.${LOGEXT} ${LOGDIR}/${CLANG}.${LOGEXT} &> ${LOGDIR}/${DIFFNAME}.${DIFFEXT}
}

#
# ENTRY
# main execution begins here.
#

f_setup_topdir

f_setup_clean "$1"

f_enter_topdir

f_check_deps

f_clean_subdirs

f_clean_targets

f_build_targets ${GCC}

f_clean_targets

f_build_targets ${CLANG}

f_disas_targets ${GCC}

f_disas_targets ${CLANG}

f_diffx_targets

f_leave_topdir

# end: build.sh
##
