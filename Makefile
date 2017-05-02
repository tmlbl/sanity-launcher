C_SRC=$(wildcard *.cc)
GTK_FLAGS=$(shell pkg-config --cflags gtk+-3.0)
GTK_LIBS=$(shell pkg-config --libs gtk+-3.0)

CPPFLAGS += $(GTK_FLAGS)
CPPFLAGS += -std=c++11
LDFLAGS += $(GTK_LIBS)

.PHONY: clean

sanity: completions.o main.o
	$(LINK.cc) completions.o main.o -o sanity -std=c++11

clean:
	rm *.o sanity
