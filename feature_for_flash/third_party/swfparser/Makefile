
###########################################################
#
# Project: swfparser
# Output: docode4sa/third_party/swfparser/libswfparser.a
#
###########################################################

# Please note that this file is write by hand!

CC = g++
CFLAGS := $(COMMON_CFLAGS)
CFLAGS +=  \
	-fPIC\
	-I.\

SRC_EXT = cpp
SRC_DIRS := .\ 

SRCS_EXCLUDE := \
	./swfparser.cpp\

###########################################################
# Search Source Files
SRCS := $(foreach _dir, $(SRC_DIRS), \
		$(shell ls $(_dir)/*.$(SRC_EXT) 2>/dev/null))
SRCS := $(basename $(SRCS))
SRCS := $(filter-out $(basename $(SRCS_EXCLUDE)), $(SRCS))
###########################################################

_objs := $(addsuffix .o, $(SRCS))

libswfparser.a: $(_objs)
	ar rcs libswfparser.a $(_objs) 

clean: 
	rm -f $(addsuffix .o, $(SRCS))
	rm -f $(addsuffix .d, $(SRCS))
	rm -f $(addsuffix .d.*, $(SRCS))
	rm -f libswfparser.a

clean_all: clean

##############################################################
# Auto Establish Depandency
include $(addsuffix .d, $(SRCS))

%.d: %.$(SRC_EXT)
	@set -e; rm -f $@; \
	$(CC) -MM $(CFLAGS) $< > $@.$$$$; \
	sed 's,.*:,$(basename $@).o $@ :,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

%.o: %.$(SRC_EXT)
	$(CC) -c $(CFLAGS) -o $@ $<
##############################################################




