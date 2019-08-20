SRCDIR = src
SRCS  := $(wildcard $(SRCDIR)/*.cxx)

PROGS=HGC jet_ntuple_merge

OBJDIR = obj
OBJS  := $(SRCS:$(SRCDIR)/%.cxx=$(OBJDIR)/%.o)

LD=g++

CXXFLAGS = -g -O0 -W -Wall -Wextra -pedantic -std=c++11 -MP -MD
INCLUDEFLAGS = -I./include

ROOTLIBS = `root-config --libs` -lFoam -lMinuit -lTreePlayer #-lXMLParser
ROOTCFLAGS = $(shell root-config --cflags)
ROOTGLIBS = $(shell root-config --glibs)
PWD = $(shell pwd)
MKDIR_P = mkdir -p

COMMONOBJS1 =  $(OBJS) 
COMMONOBJS = $(filter-out $(OBJDIR)/jet_ntuple_merge.o $(OBJDIR)/HGC.o, $(COMMONOBJS1))

# MyDict.cxx: ./include/Helpers.h Linkdef.h
# 	rootcling -f $@ -c `root-config --cflags` -p $^

# libMyLib.so: MyDict.cxx src/Helpers.cxx
# 	g++ -shared -o$@ `root-config --ldflags` $^

all: $(PROGS)

$(OBJS): | ${OBJDIR}

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(OBJDIR)/%.o : $(SRCDIR)/%.cxx
	$(CXX) $(CXXFLAGS) $(ROOTCFLAGS) $(INCLUDEFLAGS) -c $< -o $@

$(PROGS): $(OBJS) ${COMMONOBJS}
	$(LD) -o $@ ${COMMONOBJS} ${OBJDIR}/$@.o -lz $(ROOTLIBS)


-include $(OBJS:.o=.d)

clean:
	rm *.o *.d $(OBJDIR)/*.o $(OBJDIR)/*.d $(PROGS) 2> /dev/null || true
