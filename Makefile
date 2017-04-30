C_SRC=$(wildcard *.c)
GTK_FLAGS=$(shell pkg-config --cflags gtk+-3.0)
GTK_LIBS=$(shell pkg-config --libs gtk+-3.0)

CPPFLAGS += $(GTK_FLAGS)
LDFLAGS += $(GTK_LIBS)

sanity: completions.o main.o
	$(LINK.C) completions.o main.o -o sanity
