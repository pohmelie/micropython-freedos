include ../py/mkenv.mk
-include mpconfigport.mk

# define main target
PROG = micropython

# qstr definitions (must come before including py.mk)
QSTR_DEFS = qstrdefsport.h

# include py core make definitions
include ../py/py.mk

INC +=  -I.
INC +=  -I..
INC += -I$(BUILD)

# compiler settings
CWARN = -Wall -Werror
CWARN += -Wpointer-arith -Wuninitialized
CFLAGS = $(INC) $(CWARN) -ansi -std=gnu99 -DUNIX $(CFLAGS_MOD) $(COPT) $(CFLAGS_EXTRA)

# Debugging/Optimization
ifdef DEBUG
CFLAGS += -g
COPT = -O0
else
COPT = -Os #-DNDEBUG
endif

ifdef DJGPP
CC = $(DJGPP)/bin/i586-pc-msdosdjgpp-gcc
CROSS_COMPILE = $(DJGPP)/i586-pc-msdosdjgpp/bin/
endif

LDFLAGS_ARCH = -Wl,-Map=$@.map,--cref
LDFLAGS = $(LDFLAGS_MOD) $(LDFLAGS_ARCH) -lm $(LDFLAGS_EXTRA)

ifeq ($(MICROPY_USE_READLINE),1)
INC +=  -I../lib/mp-readline
CFLAGS_MOD += -DMICROPY_USE_READLINE=1
LIB_SRC_C_EXTRA += mp-readline/readline.c
endif

ifeq ($(MICROPY_USE_READLINE),2)
CFLAGS_MOD += -DMICROPY_USE_READLINE=2
LDFLAGS_MOD += -lreadline
# the following is needed for BSD
#LDFLAGS_MOD += -ltermcap
endif

ifeq ($(MICROPY_PY_TIME),1)
CFLAGS_MOD += -DMICROPY_PY_TIME=1
SRC_MOD += modtime.c
endif

ifeq ($(MICROPY_PY_TERMIOS),1)
CFLAGS_MOD += -DMICROPY_PY_TERMIOS=1
SRC_MOD += modtermios.c
endif

ifdef DJGPP
SRC_MOD += moddos.c
CFLAGS_MOD += -DMICROPY_NLR_SETJMP -Dtgamma=gamma -DMICROPY_EMIT_X86=0 -DMICROPY_PY_SOCKET=0 -DMICROPY_PY_BUILTINS_MINMAX_DEFAULT_KEYWORD
endif

# source files
SRC_C = \
	main.c \
	gccollect.c \
	unix_mphal.c \
	input.c \
	file.c \
	modos.c \
	alloc.c \
	coverage.c \
	$(SRC_MOD)

# Include builtin package manager in the standard build (and coverage)
ifeq ($(PROG),micropython)
SRC_C += $(BUILD)/_frozen_upip.c
else ifeq ($(PROG),micropython_coverage)
SRC_C += $(BUILD)/_frozen_upip.c
endif

LIB_SRC_C = $(addprefix lib/,\
	$(LIB_SRC_C_EXTRA) \
	utils/printf.c \
	)

OBJ = $(PY_O)
OBJ += $(addprefix $(BUILD)/, $(SRC_C:.c=.o))
OBJ += $(addprefix $(BUILD)/, $(LIB_SRC_C:.c=.o))

include ../py/mkrules.mk

TARGET = micropython
PREFIX = $(DESTDIR)/usr/local
BINDIR = $(PREFIX)/bin
PIPSRC = ../tools/pip-micropython
PIPTARGET = pip-micropython

$(BUILD)/_frozen_upip.c: $(BUILD)/frozen_upip/upip.py
	../tools/make-frozen.py $(dir $^) > $@

# Select latest upip version available
UPIP_TARBALL := $(shell ls -1 -v ../tools/micropython-upip-*.tar.gz | tail -n1)

$(BUILD)/frozen_upip/upip.py: $(UPIP_TARBALL)
	$(ECHO) "MISC Preparing upip as frozen module"
	$(Q)rm -rf $(BUILD)/micropython-upip-*
	$(Q)tar -C $(BUILD) -xz -f $^
	$(Q)rm -rf $(dir $@)
	$(Q)mkdir -p $(dir $@)
	$(Q)cp $(BUILD)/micropython-upip-*/upip*.py $(dir $@)


# Value of configure's --host= option (required for cross-compilation).
# Deduce it from CROSS_COMPILE by default, but can be overriden.
ifneq ($(CROSS_COMPILE),)
CROSS_COMPILE_HOST = --host=$(patsubst %-,%,$(CROSS_COMPILE))
else
CROSS_COMPILE_HOST =
endif
