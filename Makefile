COMPLETE_PRINT=\033[1;32mSuccess\033[0m ✅ - \033[1mBinary location: ${OUT_DIR}${EXE_NAME}\033[0m\n

OBJ_DIR:=./obj/
OUT_DIR:=./out/
SRC_DIR:=src/

CC=gcc
HEADERS=-Iinclude
RAYLIB=-lraylib -lGL -lm -lpthread -ldl -lrt -lX11

##################### DEBUG ####################
DEBUG=-g -DDEBUG
################################################


#################### LOGGING ###################
#LOG_FILE=-DLOG_FILE
LOG_PERSIST=-DLOG_PERSIST
#LOG_EXT_TERMINAL=-DLOG_EXT_TERMINAL

LOG_CONF=${LOG_PERSIST} ${LOG_FILE} ${LOG_EXT_TERMINAL}
################################################


# CONFIGS= -DLOG_FILE -DLOG_PERSIST
CC_FLAGS=-Wall -Wshadow -std=gnu99 ${DEBUG} ${LOG_CONF}
PROJECT_NAME=Terrario
BUILD=0.0.1
EXE_NAME=${PROJECT_NAME}-${BUILD}


SRC_FILES=$(shell find src -type f -iname '*.c')
SRC := $(SRC_FILES:${SRC_DIR}%=%)
OBJS := $(SRC:%.c=%.o)
BINS := $(SRC:%.c=%)


build: ${BINS}
	@echo "\n🔗 \033[1mLinking\033[0m"
	${CC} ${OBJS} ${RAYLIB} -o ${OUT_DIR}${EXE_NAME}
	@mv ./*.o ${OBJ_DIR}
	@echo "\n$(COMPLETE_PRINT)"

%.o: ${SRC_DIR}%.c
	@echo "🎯 \033[1m$<\033[0m"
	${CC} -c ${CC_FLAGS} ${HEADERS} $< -o $@

%: %.o
	
run:
	@${OUT_DIR}${EXE_NAME} ${RUN_ARGS}

clean:
	@rm $(OBJ_DIR)* $(OUT_DIR)* *.o 2>/dev/null || true