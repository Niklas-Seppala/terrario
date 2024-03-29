
OBJ_DIR:=../obj/
OUT_DIR:=../out/
SRC_DIR:=../src/
TEST_DIR:=./

CC=gcc
HEADERS=-I../include
RAYLIB=-lraylib -lGL -lm -lpthread -ldl -lrt -lX11
TEST=-lcheck -lm -lpthread -lrt -lsubunit

##################### DEBUG ####################
DEBUG=-g -DDEBUG
################################################

##################### TEST ####################
TEST_CONFIGS=-DHOOKS_SC=2 -DHOOKS_CG=2
################################################

CC_WARN=-Wall -Wshadow -Werror -Wextra -Wformat=2 -Wpedantic -fmax-errors=1 -Wno-unknown-pragmas -Wno-unused-function -Wno-unused-parameter
CC_FLAGS=${CC_WARN} -O0 -std=gnu99 ${DEBUG} ${TEST_CONFIGS}
PROJECT_NAME=Terrario
BUILD=0.0.1
EXE_NAME=${PROJECT_NAME}-${BUILD}
TEST_NAME=${EXE_NAME}-tests

SRC_FILES=$(shell find ../src -type f \( -iname "*.c" ! -iname "main.c" \))

SRC := $(SRC_FILES:${SRC_DIR}%=%)
OBJS := $(SRC:%.c=${OBJ_DIR}%.o)
BINS := $(SRC:%.c=%)

COMPLETE_PRINT=\033[1;32mBUILD SUCCESS\033[0m ✅ - \033[1mBinary location: ${OUT_DIR}${TEST_NAME}\033[0m

suite:
	${CC} -c ${CC_FLAGS} ${HEADERS} test_input.c -o ${OBJ_DIR}test_input.o
	${CC} -c ${CC_FLAGS} ${HEADERS} test_hooks.c -o ${OBJ_DIR}test_hooks.o
	${CC} -c ${CC_FLAGS} ${HEADERS} test_algorithm.c -o ${OBJ_DIR}test_algorithm.o
	${CC} -c ${CC_FLAGS} ${HEADERS} test.c -o ${OBJ_DIR}test.o


build: suite ${BINS}
	@echo ----------------------------------------------------------------------
	@echo "🔗 \033[1;36mLINKING\033[0m"
	${CC} ${OBJS} ${OBJ_DIR}test.o ${OBJ_DIR}test_hooks.o ${OBJ_DIR}test_input.o ${OBJ_DIR}test_algorithm.o ${RAYLIB} ${TEST} -o ${OUT_DIR}${TEST_NAME}
	@echo ----------------------------------------------------------------------
	@echo "$(COMPLETE_PRINT)"
	@echo ----------------------------------------------------------------------
	@echo "\n"

%: %.o
	
%.o: ${SRC_DIR}%.c
	${CC} -c ${CC_FLAGS} ${HEADERS} $< -o ${OBJ_DIR}$@

test: build
	@${OUT_DIR}${TEST_NAME}

memcheck: build
	@valgrind --leak-check=full --show-leak-kinds=all --log-file=memcheck.log ${OUT_DIR}${TEST_NAME}
	@echo "\n\n------------------------ test forks ------------------------"
	@grep "ERROR SUMMARY:" memcheck.log
	@echo "\n\n------------------------ test.c ------------------------"
	@tail memcheck.log
	@echo "\n\n"

clean:
	@rm $(OBJ_DIR)* $(OUT_DIR)* *.o 2>/dev/null || true