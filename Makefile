CXX      = g++
CXXFLAGS = $(shell fltk-config --use-gl)
LFLAGS   = $(shell fltk-config --use-gl --ldflags)
INCL     = -I./include
LIBS     = -L./libs
DEBUG    = -g -Wall

SRCS = ./src/*.cpp
OBJS = $(SRCS:.cpp = .o)
MAIN = ./bin/nmrs-tool

.PHONY: depend clean
.SUFFIXES: .o .cpp

all:	$(MAIN)
	 @echo Compiled $(MAIN)

$(MAIN): $(OBJS)
	 $(CXX) $(CXXFLAGS) $(DEBUG) $(INCL) $(LIBS) -o $(MAIN) $(OBJS) $(LFLAGS)

%.o : %.c
	 $(CXX) $(INCL) $(CXXFLAGS) -c $< -o $@

clean:
	 $(RM) *.o *~ $(MAIN)

depend: $(SRCS)
	 makedepend $(INCL) $^

#
