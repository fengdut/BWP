TARGET = simplePIC

_SRCS := main.c particles.c update_grid.c update_particle.c constant.c vector.c

CC = gcc

SRCDIR = ./src
BINDIR = ./bin
INCLUDE = ./include
OBJDIR = ./obj

_OBJS := $(patsubst %.c,%.o,$(_SRCS))
SRCS = $(patsubst %,$(SRCDIR)/%,$(_SRCS))
OBJS = $(patsubst %,$(OBJDIR)/%,$(_OBJS))

CFLAGS = -O3 -Wall
CGLAGS = -g -Wall

all:: $(TARGET)

$(TARGET): ${OBJS}
	$(CC) -o $(BINDIR)/$@ $^

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) -I$(INCLUDE) $(CFLAGS) -o $@ -c $<

tidy :
	$(VERBOSE)find . | egrep "#" | xargs rm -f
	$(VERBOSE)find . | egrep "\~" | xargs rm -f

clean:  tidy
	rm $(OBJDIR)/* $(BINDIR)/*

