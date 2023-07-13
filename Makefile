# 指定编译器(根据项目情况修改)
CC = gcc

# 指定生成的可执行文件名(根据项目情况修改)
TARGET = linu_timer_demo

# 指定源码顶层目录(根据项目情况修改)
SRC_TOP_DIR := .

# 指定输出文件存放路径(根据项目情况修改)
OUT_DIR := ./output

# 指定编译器参数(根据项目情况修改)
# -std=gnu99: 支持C99标准 这里不要使用-std=c99, 否则会报警告提示部分库函数未包含对应头文件
# -Wall: 打开所有警告信息
# -O0: 不优化代码
# -Werror: 警告报错误
CFLAGS := -std=gnu99 -Wall -O0 # -Werror

# 指定头文件路径(根据项目情况修改)
# 包含源码顶层目录和子目录下有.h文件的文件夹, 并且过滤隐藏文件夹
# -not -path: 基于完整的路径进行过滤
CFLAGS += $(addprefix -I,$(shell find $(SRC_TOP_DIR)  -type f -name "*.h" -not -path "*/.*" \
                           -exec dirname {} \; | sort -u))

# 指定链接时库文件路径(根据项目情况修改)
LDFLAGS :=

# 指定运行时库文件路径(根据项目情况修改)
# -Wl,-rpath: 指定运行时库文件路径
LDFLAGS +=

# 指定需要链接的库(根据项目情况修改)
LIBS := -lrt

# 获取源码顶层目录下的所有的.c文件列表(不需要修改)
TARGET_SRC = $(shell find $(SRC_TOP_DIR) -name "*.c")
TARGET_OBJS = $(patsubst %.c, %.o, $(TARGET_SRC))

# 以下为编译默认目标规则(不需要修改)
# Makefile的默认目标
$(TARGET):$(TARGET_OBJS)
	$(CC) $^ $(CFLAGS) $(LDFLAGS) $(LIBS) -o $(TARGET)
	@mkdir -p $(OUT_DIR)/bin
	@mkdir -p $(OUT_DIR)/objs
	@mv $(TARGET) $(OUT_DIR)/bin
	@mv $(TARGET_OBJS) $(OUT_DIR)/objs
	@echo "compile done, target file: $(TARGET)"

# 以下为清除规则(不需要修改)
# 清理目标设置为伪目标，防止外面有clean文件 阻止执行clean
.PHONY:clean
clean:
	@find $(SRC_TOP_DIR) -type f -name "*.o" -exec rm -r {} \;
	@rm $(OUT_DIR)/objs -rf
	@echo "clean object file done!"

# 清理目标设置为伪目标
.PHONY:distclean
distclean:
	@find $(SRC_TOP_DIR) -type f -name "*.o" -exec rm -r {} \;
	@rm $(OUT_DIR) -rf
	@echo "clean target and object file done!"
