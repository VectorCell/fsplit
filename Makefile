CSTD   := c99
CPPSTD := c++11

ifeq "$(CXX)" "g++"
	GCCVERSIONLT48 := $(shell expr `gcc -dumpversion` \< 4.8)
	ifeq "$(GCCVERSIONLT48)" "1"
		CPPSTD := c++0x
	endif
endif

CFLAGS   := -pedantic -std=$(CSTD) -Wall -Werror -O3
CPPFLAGS := -pedantic -std=$(CPPSTD) -Wall -Werror -O3
LIBFLAGS := -lcrypto -lssl

all : fsplit

fsplit : fsplit.cc
	$(CXX) $(CPPFLAGS) -o fsplit fsplit.cc $(LIBFLAGS)

test : clean all
	./test.sh

clean :
	rm -f *.d
	rm -f *.o
	rm -f fsplit

-include *.d
