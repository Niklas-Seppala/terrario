COMPLETE_PRINT=\033[1;32mBUILD SUCCESS\033[0m ✅ - \033[1mBinary location: ${OUT_DIR}${TEST_NAME}\033[0m

OBJ_DIR:=../obj/
OUT_DIR:=../out/
SRC_DIR:=../src/

CC=gcc
HEADERS=-I../include
RAYLIB=-lraylib -lGL -lm -lpthread -ldl -lrt -lX11
TEST=-lcheck -lm -lpthread -lrt -lsubunit

##################### DEBUG ####################
DEBUG=-g -DDEBUG
################################################


CC_WARN=-Wall -Wshadow -Werror -Wextra -Wformat=2 -Wpedantic -fmax-errors=1
CC_FLAGS=${CC_WARN} -std=gnu99 ${DEBUG} 
PROJECT_NAME=Terrario
BUILD=0.0.1
EXE_NAME=${PROJECT_NAME}-${BUILD}
TEST_NAME=${EXE_NAME}-tests


SRC_FILES=$(shell find ../src -type f -iname '[!main]*.c')
SRC := $(SRC_FILES:${SRC_DIR}%=%)
OBJS := $(SRC:%.c=${OBJ_DIR}%.o)
BINS := $(SRC:%.c=%)

suite:
	@echo ----------------------------------------------------------------------
	@echo "🎯 \033[1mtest.c\033[0m"
	${CC} -c ${CC_FLAGS} ${HEADERS} test.c -o ${OBJ_DIR}test.o

build: suite ${BINS} 
	@echo ----------------------------------------------------------------------
	@echo "🔗 \033[1;36mLINKING\033[0m"
	${CC} ${OBJS} ${OBJ_DIR}test.o ${RAYLIB} ${TEST} -o ${OUT_DIR}${TEST_NAME}
	@echo ----------------------------------------------------------------------
	@echo "$(COMPLETE_PRINT)"
	@echo ----------------------------------------------------------------------
	@echo "\n"

%: %.o
	
%.o: ${SRC_DIR}%.c
	@echo ----------------------------------------------------------------------
	@echo "🎯 \033[1m$<\033[0m"
	${CC} -c ${CC_FLAGS} ${HEADERS} $< -o ${OBJ_DIR}$@

test: build
	@${OUT_DIR}${TEST_NAME}

clean:
	@rm $(OBJ_DIR)* $(OUT_DIR)* *.o 2>/dev/null || true