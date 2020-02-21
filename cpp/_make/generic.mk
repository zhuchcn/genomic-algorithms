CXX = g++
LD = g++

STDVERSION = -std=c++14
WARNINGS = -Wall

CXXFLAG = $(STDVERSION) $(WARNINGS) -g -O0
LDFLAG = $(STDVERSION) $(WARNINGS) -g -O0

OBJS_DIR = .objs
CPP_TEST = $(wildcard tests/*.cpp)
OBJS_TEST += $(CPP_TEST:.cpp=.o)

all: main

main: $(patsubst %.o, $(OBJS_DIR)/%.o, $(OBJS))
	$(LD) $^ $(LDFLAG) -o $@

$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)
	@mkdir -p $(OBJS_DIR)/tests

$(OBJS_DIR)/%.o: %.cpp | $(OBJS_DIR)
	$(CXX) $(CXXFLAG) -O0 -g -c $< -o $@

test: $(patsubst %.o, $(OBJS_DIR)/%.o, $(OBJS_TEST))
	$(LD) $^ $(LDFLAG) -o $@

clean:
	rm -rf main test $(OBJS_DIR) *.o *.d

tidy: clean
	rm -rf doc

.PHONY: all tidy clean