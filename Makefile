CXXFLAGS = $(shell root-config --cflags) -I./include/ 
LIBS = $(shell root-config --glibs) 
SRCS := \
	averageModel.cc \
	src/interpolatePEs.cc

OFILES := $(addsuffix .o,$(basename $(SRCS)))

all: avgModel

avgModel: $(OFILES)
		g++ -Wall -ggdb -o $@ $^ $(LIBS)

%.o: %.cpp
		g++ -Wall -ggdb -c $(CXXFLAGS) -o $@ $^

clean:
	rm -f tree_fill *.o
