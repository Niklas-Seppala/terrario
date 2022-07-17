COMPLETE_PRINT=\033[1;32mSuccess\033[0m:\033[1m ${OUT_DIR}${EXE_NAME}\033[0m

OBJ_DIR:=./obj/
OUT_DIR:=./out/
SRC_DIR:=src/

CC=gcc
RAYLIB=-lraylib -lGL -lm -lpthread -ldl -lrt -lX11

##################### DEBUG ####################
DEBUG=-g -DDEBUG
################################################

#################### LOGGING ###################
#LOG_FILE=-DLOG_FILE
#LOG_PERSIST=-DLOG_PERSIST
#LOG_EXT_TERMINAL=-DLOG_EXT_TERMINAL

LOG_CONF=${LOG_PERSIST} ${LOG_FILE} ${LOG_EXT_TERMINAL}
################################################

RT_NULL_CHECKS = -DRT_NULL_CHECKS -DRT_NULL_KILLS
CC_WARN=-Wall -Wshadow -Werror -Wextra -Wformat=2 -Wpedantic -fmax-errors=2 -Wno-unknown-pragmas
CC_FLAGS=${CC_WARN} -O0 -std=c99 ${DEBUG} ${RT_NULL_CHECKS} ${LOG_CONF}
PROJECT_NAME=Terrario
BUILD=0.0.1
EXE_NAME=${PROJECT_NAME}-${BUILD}

SRC_FILES=$(shell find src -type f -iname '*.c')
SRC := $(SRC_FILES:${SRC_DIR}%=%)
OBJS := $(SRC:%.c=%.o)
BINS := $(SRC:%.c=%)


build: ${BINS}
	@echo ----------------------------------------------------------------------
	@echo "🔗 \033[1mLinking\033[0m"
	${CC} ${OBJS} ${RAYLIB} -o ${OUT_DIR}${EXE_NAME}
	@echo ----------------------------------------------------------------------
	@mv ./*.o ${OBJ_DIR}
	@echo "$(COMPLETE_PRINT)"
	@echo ----------------------------------------------------------------------
	@echo "\n"

%.o: ${SRC_DIR}%.c
	${CC} -Iinclude ${CC_FLAGS} ${CONFIG_FLAGS} -c $< -o $@

%: %.o
	

run: build
	@${OUT_DIR}${EXE_NAME} ${RUN_ARGS}


clean:
	@rm $(OBJ_DIR)* $(OUT_DIR)* *.o 2>/dev/null || true