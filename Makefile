
# C++ compiler
CCXX = g++

# C compiler
CC = gcc

# C compile option
CFLAGS = -Wall -Wextra -Werror -O2

# C++ compile option
CXXFLAGS = -Wall -Wextra -Werror -O2

# linking option
LDFLAGS = -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl -L./lib/ft_math -lftmath

# path to the headers
INCLUDE = -Iinclude -Ilib

# dir for src file
SRC_DIR = ./src

# dir for obj file
OBJ_DIR = ./obj

# name of executable
TARGET = ft_scop

# Math Library
FT_MATH_LIB = ./lib/ft_math/libftmath.a
FT_MATH_DIR = ./lib/ft_math

# source files to Make
# use wildcard to extract certain source file from SRC_DIR
# get file names only by using notdir.
SRCS_CXX = $(notdir $(wildcard $(SRC_DIR)/*.cc))
SRCS_C = $(notdir $(wildcard $(SRC_DIR)/*.c))
SRCS = $(SRCS_CXX) $(SRCS_C)


# 각각의 파일 확장자에 맞게 오브젝트 파일 변환
OBJS_CXX = $(SRCS_CXX:.cc=.o)
OBJS_C = $(SRCS_C:.c=.o)
OBJS = $(OBJS_CXX) $(OBJS_C)
OBJECTS = $(patsubst %.o,$(OBJ_DIR)/%.o,$(OBJS))
DEPS = $(OBJECTS:.o=.d)

# rule for all
all: $(TARGET)

# compile C++
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cc
	$(CCXX) $(CXXFLAGS) $(INCLUDE) -c $< -o $@ -MD

# compile C
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@ -MD

# link together
$(TARGET): $(OBJ_DIR) $(OBJECTS)
	$(MAKE) -C $(FT_MATH_DIR)
	$(CCXX) $(CXXFLAGS) $(OBJECTS) -o $(TARGET) $(LDFLAGS)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	$(MAKE) -C $(FT_MATH_DIR) clean
	rm -rf $(OBJECTS) $(DEPS) $(OBJ_DIR)

fclean: clean
	$(MAKE) -C $(FT_MATH_DIR) fclean
	rm -f $(TARGET)

re: fclean all

.PHONY: clean fclean all re

-include $(DEPS)
