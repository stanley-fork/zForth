
BIN	:= zforth
SRC	:= main.c zforth.c

OBJS    := $(subst .c,.o, $(SRC))
DEPS    := $(subst .c,.d, $(SRC))

CC	:= $(CROSS)gcc

VPATH   := ../zforth
CFLAGS	+= -I. -I../zforth

CFLAGS  += -Os -g -ansi
CFLAGS  += -Wall -Wextra -Werror -Wno-unused-parameter -Wno-clobbered -Wno-unused-result
LDFLAGS	+= -g 

LIBS += -lreadline -lm

$(BIN): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $(OBJS) $(LIBS)

%.o: %.c Makefile src/zforth.h
	$(CC) $(CFLAGS) -MMD -c $<

clean:
	rm -f $(BIN) $(OBJS) $(DEPS)

lint:
	lint -i /opt/flint/supp/lnt -i src -w2 co-gcc.lnt \
		-e537 -e451 -e524 -e534 -e641 -e661 -e64 \
		$(SRC)

-include $(DEPS)
