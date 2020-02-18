EXE = main
OBJS = main.o EditDistance.o

OBJS_DIR = .objs

all: $(EXE)

$(EXE): $(patsubst %.o, $(OBJS_DIR)/%.o, $(OBJS))
	g++ $^ -std=c++14 -o $@

$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)

$(OBJS_DIR)/%.o: %.cpp | $(OBJS_DIR)
	g++ -std=c++14 -O0 -g -c $< -o $@

clean:
	rm -rf $(EXE) $(OBJS_DIR) *.o *.d

tidy: clean
	rm -rf doc

.PHONY: all tidy clean