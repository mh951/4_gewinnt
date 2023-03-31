CC = gcc
CFLAGS = --std=c11 -pedantic
HEADERS = $(wildcard *.h)
PROGRAMS= 4 artificial_intelligence_test checking_test players_test

compile: $(PROGRAMS)

.PHONY: all clean compile test checkstyle all

all: compile test

clean:
	rm -f $(PROGRAMS) *.o

4: main_4.o
	$(CC) $(CFLAGS) main_4.o artificial_intelligence.c checking.c players.c -o 4 $(HEADERS)

artificial_intelligence_test: artificial_intelligence_test.o
	$(CC) $(CFLAGS) artificial_intelligence_test.o artificial_intelligence.c checking.c players.c -o artificial_intelligence_test $(HEADERS)

checking_test: checking_test.o
	$(CC) $(CFLAGS) checking_test.o checking.c -o checking_test $(HEADERS)

players_test: players_test.o
	$(CC) $(CFLAGS) players_test.o players.c checking.c -o players_test $(HEADERS)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

test:
	./artificial_intelligence_test
	./checking_test
	./players_test

checkstyle:
	python cpplint.py --repository=. --filter='-runtime/int,-readability/casting,-runtime/threadsafe_fn,-build/include_subdir,-runtime/printf,-build/include_what_you_use' *.c *.h
