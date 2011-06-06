CXXFLAGS=$(shell llvm-config --cxxflags) -fno-rtti
CPPFLAGS=$(shell llvm-config --cppflags)
LDFLAGS=$(shell llvm-config --ldflags)
LIBS=-lclangFrontend -lclang -lclangLex -lclangBasic $(shell llvm-config --libs)
SRCS=test.cpp

# See http://mad-scientist.net/make/autodep.html
MAKEDEPEND = $(CPP) $(CPPFLAGS) $< \
               | sed -n 's/^\# *[0-9][0-9]* *"\([^"<]*\)".*/$@: \1/p' \
               | sort -u > $*.d

default: test

-include $(SRCS:.cpp=.P)

.PHONY: all clean default

all: test

test: clang_test.o Makefile
	g++ -o $@ $(LDFLAGS) $< $(LIBS)

%.o: %.cpp
	@$(MAKEDEPEND); \
	cp $*.d $*.P;
	sed -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\\$$//' \
	    -e '/^$$/ d' -e 's/$$/ :/' < $*.d >> $*.P; \
	rm -f $*.d
	g++ $(CXXFLAGS) -O0 -c $< -o $@

clean:
	rm -f *.o *.P test
