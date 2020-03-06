# extra includes paths (-I options)
INCLUDE = -I../libsndio -I../bsd-compat

# extra libraries paths (-L options)
LIB = -L../libsndio

# extra defines (-D options)
DEFS = -DDEBUG -DSNDIO_USER=\"_sndio\" -DADATA_BITS=16 -DHAVE_ARC4RANDOM -DHAVE_ISSETUGID \
		-DHAVE_STRLCAT -DHAVE_STRLCPY

# extra libraries (-l options)
LDADD = -lsndio 

# variables defined on configure script command line (if any)


#
# binaries, documentation, man pages and examples will be installed in
# ${BIN_DIR}, ${MAN1_DIR}
#
BIN_DIR = /usr/local/bin
MAN1_DIR = /usr/local/share/man/man1

#
# programs to build
#
PROG = aucat
MAN1 = aucat.1

all:		${PROG} ${MAN1}

install:
		mkdir -p ${DESTDIR}${BIN_DIR} ${DESTDIR}${MAN1_DIR}
		cp aucat ${DESTDIR}${BIN_DIR}
		cp aucat.1 ${DESTDIR}${MAN1_DIR}

uninstall:
		cd ${DESTDIR}${BIN_DIR} && rm -f ${PROG}
		cd ${DESTDIR}${MAN1_DIR} && rm -f ${MAN1}

clean:
		rm -f -- *.o aucat

# ---------------------------------------------------------- dependencies ---

OBJS = abuf.o afile.o aucat.o dsp.o utils.o

aucat:		${OBJS}
		${CC} ${LDFLAGS} ${LIB} -o aucat ${OBJS} ${LDADD}

.c.o:
		${CC} ${CFLAGS} ${INCLUDE} ${DEFS} -c $<

abuf.o:		abuf.c abuf.h utils.h
afile.o:	afile.c afile.h dsp.h defs.h utils.h
aucat.o:	aucat.c abuf.h afile.h dsp.h defs.h sysex.h utils.h \
		../bsd-compat/bsd-compat.h
dsp.o:		dsp.c dsp.h defs.h utils.h
utils.o:	utils.c utils.h
