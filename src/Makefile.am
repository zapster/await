AM_CFLAGS=-Wall -Werror -pedantic
AM_CXXFLAGS=-Wall -Werror -pedantic

if NDEBUG
AM_CFLAGS+= -O2
AM_CXXFLAGS+= -O2
else
AM_CFLAGS+= -g -O0
AM_CXXFLAGS+= -g -O0
endif

bin_PROGRAMS = await await-del
await_SOURCES = await.c

await_del_SOURCES = await-del.c
