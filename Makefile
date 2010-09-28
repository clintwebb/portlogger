# make file for portlogger project.

all: portlogger



DEBUG_LIBS=
#DEBUG_LIBS=-lefence -lpthread

ARGS=-Wall -O2 -g $(DEBUG_LIBS)
OBJS=
LIBS=



portlogger: portlogger.c
	gcc -o $@ portlogger.c $(OBJS) $(LIBS) $(ARGS)
