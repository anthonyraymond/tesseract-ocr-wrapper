CC = g++

DEBUG = true

CPPFLAGS = -Wall -Wextra -std=gnu++11

ifeq ($(DEBUG), true)
	CPPFLAGS += -g
else
	CPPFLAGS += -Wpadded -O2
endif

SRCS= src/ocr.cpp src/overridedrenderer.cpp
LIB = -ltesseract -llept
INC = -I include

OBJS = $(patsubst src/%,obj/%,$(SRCS:.cpp=.o))

MAIN = ocr


.PHONY: clean

re: clean all

all : $(MAIN)
	@echo Compiled succefully

$(MAIN): $(OBJS)
	$(CC) $(CPPFLAGS) -o $@ $(OBJS) $(LIB)

obj/%.o: src/%.cpp
	@mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) $(INC) -c $< -o $@

clean:
	rm -rf $(OBJS) $(MAIN)
