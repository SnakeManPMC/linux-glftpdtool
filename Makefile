#
# Makefile --- gltool (c) PMC 1999 - 2015
#

CC	= gcc

INCLUDE = /home/snakeman/code/include

CFLAGS  = -I$(INCLUDE) -W

all:		gltool log logconvert log_year_create

clean:          rm core gltool log logconvert log_year_create

gtool:          gltool.c
		$(CC) $(CFLAGS) -o $@ $<

log:	        log.c
		$(CC) $(CFLAGS) -o $@ $<

logconvert:	logconvert.c
		$(CC) $(CFLAGS) -o $@ $<

log_year_create:	log_year_create.c
		$(CC) $(CFLAGS) -o $@ $<
