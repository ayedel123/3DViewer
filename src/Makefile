CC = gcc -std=c11
CFLAGS = -Wall -Wextra -Werror -std=c11
BUILD_PATH = .
BUILD_PATH_SRC = $(BUILD_PATH)/viewModel
TEST_DIR = tests
GCOV_FLAGS = -fprofile-arcs -ftest-coverage
SOURCES = $(BUILD_PATH_SRC)/parser.c $(BUILD_PATH_SRC)/s21_model.c $(BUILD_PATH_SRC)/affine/affine.c $(BUILD_PATH_SRC)/affine/matrix/matrix.c
TESTS_SOURCES =$(TEST_DIR)/backTests.c \
	$(TEST_DIR)/parser_tests/analyzeFileTest.c \
	$(TEST_DIR)/parser_tests/coolGetLineTest.c \
	$(TEST_DIR)/parser_tests/parseVertexesTest.c \
  	$(TEST_DIR)/parser_tests/countVertexesTest.c \
	$(TEST_DIR)/parser_tests/parseFacesTest.c \
	$(TEST_DIR)/parser_tests/readModelTest.c \
	$(TEST_DIR)/affine_tests/matrixTest.c \
	$(TEST_DIR)/affine_tests/translatefTest.c \
	$(TEST_DIR)/affine_tests/rotatefTest.c \
	$(TEST_DIR)/affine_tests/scaleTest.c 

CPP_SOURCES = 

OBJECT = $(patsubst %*.c, %*.o, $(SOURCES))
OS = $(shell uname -s)

DIST_DIR = ../3DViewer_by_bebra

ifeq ($(OS), Linux)
  CFLAGS += -D OS_LINUX
  CHECK_FLAGS = -lpthread -lcheck -pthread -lrt -lm -lsubunit
endif
ifeq ($(OS), Darwin)
  CFLAGS += -D OS_MAC
  CHECK_FLAGS = -lcheck
endif

all: clean dist test edges_counter_test install gcov_report run

run:
	build/3DViewer_by_bebra

open_app: run

build_test:
	$(CC) $(CFLAGS) $(TESTS_SOURCES) $(SOURCES) $(CHECK_FLAGS) -o test.out


test: build_test edges_counter_test
	./test.out


edges_counter_test_build:
	cmake -DCMAKE_BUILD_TYPE=Release -B build .
	cmake --build build -- count_edges_test

edges_counter_test: edges_counter_test_build
	build/count_edges_test


gcov_report: 
	$(CC) $(CFLAGS) $(GCOV_FLAGS) $(TESTS_SOURCES) $(SOURCES) $(CHECK_FLAGS) -o GcovReport
	@./GcovReport
	@lcov -t "GcovReport" -o GcovReport.info -c -d .
	@genhtml -o report GcovReport.info
	@open ./report/index-sort-f.html
	@rm -rf ./*.gcno ./*gcda ./GcovReport.*

install: libgif.a
	cmake -DCMAKE_BUILD_TYPE=Release -B build .
	cmake --build build -- 3DViewer_by_bebra


uninstall: clean

dist: clean clean_dist
	mkdir ${DIST_DIR}
	cp -rf . ${DIST_DIR}
	tar -zcvf ../archive.tar.gz ${DIST_DIR}



libgif.a:
	cmake -DCMAKE_BUILD_TYPE=Release -B gifRecorder/gifEncoder/build gifRecorder/gifEncoder/
	cmake --build gifRecorder/gifEncoder/build -- egif


clean_dist:
	rm -rf ${DIST_DIR}
	rm -rf ../archive.tar
	rm -rf ../archive.tar.gz

dvi:
	open readme.md

leaks: test
	leaks -atExit -- ./test

clang:
	@cp ../materials/linters/.clang-format .clang-format
	find  ../src -type f -name '*.cpp' -o -name '*.h' -o -name '*.c' | xargs clang-format -i
	@rm .clang-format



clean: clean_cmake clean_libgif clean_dist
	rm -rf ./a.out ./*.o ./*.a ./test ./GcovReport ./report ./*.info ./*.gcno ./*gcda ./*.gch  */*.gch tests/.out ./*.out SavingFile.h.gch


clean_cmake:
	rm -rf src/build build

clean_libgif:
	rm -rf gifRecorder/gifEncoder/build
	rm -rf libegif.a
