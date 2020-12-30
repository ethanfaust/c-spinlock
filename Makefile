CC       := gcc
CFLAGS   := -Wall -std=gnu99 -ggdb
LIBS     := -lpthread
PROGS    := test
INCLUDES := -I./
FLAGS    :=

test: test.o
	$(CC) -o $@ $^ $(LIBS)

%.o: %.c
	$(CC) $(INCLUDES) $(CFLAGS) $(FLAGS) -c $^ -o $@

clean:
	rm -f $(PROGS) *.o *~

all: $(PROGS)
