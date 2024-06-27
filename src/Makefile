CC=gcc
CFLAGS=-std=c11 -pedantic -Wall -Werror -Wextra
SANFLAG=#-fsanitize=address -g
COVFLAGS=-fprofile-arcs -ftest-coverage
ADDFLAGS=-lncurses

GAMENAME=GameLife.out
START_FILE=start1.txt

C_FILES = $(wildcard *.c)
O_FILES = $(subst .c,.o, $(C_FILES))
O_GCOVFILES = $(addsuffix .gcov, $(O_FILES))

# Для теста покрытия
TESTDIR=./tests/
OUT_TEST=$(TESTDIR)test.out

all: build

start:
	./$(GAMENAME) < $(TESTDIR)$(START_FILE)

build: $(O_FILES)
	$(CC) $(CFLAGS) $(SANFLAG) $(O_FILES) -o $(GAMENAME) $(ADDFLAGS)

test: $(O_GCOVFILES)
	$(CC) $(CFLAGS) $(SANFLAG) $(COVFLAGS) $(addprefix $(TESTDIR), $(O_GCOVFILES)) -o $(OUT_TEST) $(ADDFLAGS)
	$(OUT_TEST) < $(TESTDIR)$(START_FILE)

gcov_report: test
	(cd $(TESTDIR) && gcov *.o.gcov)
	@echo ""
	lcov -t "test" -o $(TESTDIR)report.info -c -d $(TESTDIR)
	genhtml -o $(TESTDIR)report $(TESTDIR)report.info

# Компилируем объектные файлы функций библиотеки
%.o: %.c
	$(CC) $(CFLAGS) -c $(SANFLAG) $< -o $@ $(ADDFLAGS)

# Компилируем объектные файлы функций библиотеки с профилир/покрытием
%.o.gcov: %.c
	$(CC) $(CFLAGS) -c $(SANFLAG) $(COVFLAGS) $< -o $(TESTDIR)$@ $(ADDFLAGS)

clean:
	rm -rf *.o* \
	$(TESTDIR)*.o* \
	$(TESTDIR)*.gc* \
	$(TESTDIR)*report*

clang:
	clang-format -i *.c

rebuild: clean build