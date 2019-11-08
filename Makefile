SHELL = /bin/sh
CC=gcc
INCLUDE=include
SRC=src
TEST=tests
FLAGS=-I$(INCLUDE) -I$(TEST) -Wall -lcheck -g
COMMON_TEST=$(TEST)/test_runner.c

RESUME_TEST_SRC=$(COMMON_TEST) $(SRC)/resume.c
RESUME_TEST_INCLUDE=$(INCLUDE)/resume.h $(TEST)/resume_test.h
RESUME_TEST=$(RESUME_TEST_SRC) $(RESUME_TEST_INCLUDE)

CHECK_DEPS= $(RESUME_TEST)
check: $(CHECK_DEPS)
	$(CC) $(FLAGS) $(RESUME_TEST_SRC) -o check
