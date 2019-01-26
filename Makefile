CXX      = g++
CXXFLAGS = $(shell fltk-config --use-gl --use-images --cxxflags)
LFLAGS   = $(shell fltk-config --use-gl --use-images --ldflags )
INCL     = -I./include
DEBUG    = -g -Wall

SRCS = ./src/*.cpp
OBJS = $(SRCS:.cpp = .o)
MAIN = ./bin/nmrs-tool

.PHONY: depend clean
.SUFFIXES: .o .cpp

all:	$(MAIN)
	 @echo Compiled $(MAIN)

$(MAIN): $(OBJS)
	 $(CXX) $(CXXFLAGS) $(DEBUG) $(INCL) -o $(MAIN) $(OBJS) $(LFLAGS)

%.o : %.c
	 $(CXX) $(INCL) $(CXXFLAGS) -c $< -o $@

clean:
	 $(RM) *.o *~ $(MAIN)

depend: $(SRCS)
	 makedepend $(INCL) $^

#
