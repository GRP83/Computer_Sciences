CMSIS_DIR	= ../CMSIS
DSP_DIR		= $(CMSIS_DIR)/DSP
NN_DIR		= $(CMSIS_DIR)/NN
CORE_DIR	= $(CMSIS_DIR)/Core/Include

APPINCLUDE:=-I$(APP_ROOT) \
	   -I$(APP_ROOT)/Include \
	   -I$(CORE_DIR) \
	   -I$(DSP_DIR)/Include \
	   -I$(NN_DIR)/Include \

VERBOSE=1
WORKING_FOLDER=$(shell pwd)
TOOL_CHAIN=gcc

APP_ROOT?=$(WORKING_FOLDER)

MULT?=
DEF=?

-include NN.makefile.include

GNG_CC=gcc -Wall
SRCINC?=
ASSDBG=
INCOBJ=$(patsubst %.c,%$(MULT).$(CROSS).o,$(SRCINC))
EXE=$patsubst %.c,%.o,$(SRC))
EXEPP=$(patsubst %.cpp,%.o,$(SRCPP))
CFLAS += -02
CFLAGS += -w -g
CFLAGS += -std=gnu99
CFLAGS += -pthread
CFLAGS += -fopenmp

SRC+= \
     $(wildcard *.c)

SRCPP+=$(wildcard *.cpp)

SRCOBJ := $(patsubst %.c, %.o, $(SRC))

all: all_$(TOOL_CHAIN)

ifeq ($(TOOL_CHAIN),gcc)

all_gcc: clean exe

exe::
	$(V) $(GNG_CC) $(CFLAGS) \
	$(SRC) \
	$(APPINCLUDE) -o app.exe
endif

clean::
	-rm -f *.$(CROSS).elf *.$(CROSS).o $(NN_DIR)/Source/*/*.o $(COREA_DIR)/Siource/*.o $(DEVICE_DIR)/Source/*.o *.o *.exe

