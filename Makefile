CC      = g++
CFLAGS  = $(shell fltk-config --use-gl)
LDFLAGS = $(shell fltk-config --use-gl --ldflags)
DEBG	  = -g -p -Wall -Wextra
GCOV		= -fprofile-arcs -ftest-coverage
#OPT		  = -O2
INC     = -Iinc
LIB     = -Llib

.PHONY: depend clean
.SUFFIXES: .o .cpp

MAIN = bin/run
SRCS = $(wildcard src/*.cpp)
OBJS = $(patsubst src/%.cpp, obj/%.o, $(SRCS))
OBJDIR = obj/
SRCDIR = src/

all: $(MAIN)

$(MAIN): $(OBJS)
	$(CC) $(LIB) $(GCOV) $^ -o $@ $(LDFLAGS)

$(OBJDIR)%.o: $(SRCDIR)%.cpp
	$(CC) $(GCOV) $(OPT) $(INC) $(DEBG) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS) $(MAIN) $(OBJDIR)*.gc*

