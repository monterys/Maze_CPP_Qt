CC = g++
CFLAGS = -Wall -Wextra -Werror  -std=c++17
LDFLAGS = -lstdc++ -lm -lgtest -lpthread
GCOVFLAGS = -fprofile-arcs -ftest-coverage
GENINFOFLAGS = --no-external .

PROJECTNAME := maze
PRO_FILE = Maze/Maze.pro
SRCMODEL := maze.cc
EXECUTABLE = $(addprefix test_, $(PROJECTNAME))

README := dvi.html

SRC_DIRS := ./
OBJ_DIR = build
SRC := $(wildcard $(SRC_DIRS)/*.cc)
SRC_TEST = $(wildcard $(SRC_DIRS)/test_*.cc)
SRCH := $(wildcard $(SRC_DIRS)/*.h)

OBJS = $(addsuffix .o,$(basename $(SRC)))

OS := $(shell uname)

ifeq ($(OS),Darwin)
	GENINFOFLAGS += --ignore-errors mismatch
	GENINFOFLAGS += --ignore-errors usage,usage
endif

GCOV_HTML_DIR = report
COVERAGE_INFO = $(addsuffix .info, $(PROJECTNAME))
GENINFOFLAGS += --output-file $(GCOV_HTML_DIR)/$(COVERAGE_INFO)

all: tests install start

install: uninstall
	@echo "Installing..."
	qmake6 -o $(OBJ_DIR)/Makefile $(PRO_FILE)
	cd $(OBJ_DIR) && make -j6

uninstall: clean
	@echo "Uninstalling..."
	rm -rf $(OBJ_DIR)

start:
ifeq ($(OS),Darwin)
	$(OBJ_DIR)/$(PROJECTNAME).app/Contents/MacOS/$(PROJECTNAME)
else
	$(OBJ_DIR)/$(PROJECTNAME)
endif

clean:
	@echo "Cleaning up..."
	rm -rf $(OBJS) ${EXECUTABLE} $(GCOV_HTML_DIR)
	rm -rf *.gc* *.user *.app *.info *.dSYM .DS_Store maze_test_write maze_generated*

dvi: 
	open $(README)

dist: install 
	cd .. && tar -czf $(PROJECTNAME).tgz src
	@mv ../$(PROJECTNAME).tgz .

tests: clean ${EXECUTABLE}
	@echo "Running tests..."
	./${EXECUTABLE}

gcov_report: tests
	@echo "Generating HTML coverage report..."
	@mkdir -p $(GCOV_HTML_DIR)
	geninfo . $(GENINFOFLAGS) --exclude "test*"
	genhtml $(GCOV_HTML_DIR)/$(COVERAGE_INFO) -o $(GCOV_HTML_DIR)
	open $(GCOV_HTML_DIR)/index.html

%.o: %.cc
	$(CC) $(CFLAGS) -c -o $@ $<

$(EXECUTABLE): $(SRC_TEST) $(SRCMODEL)
	@echo "Linking..."
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS) $(GCOVFLAGS)

style:
	@echo "Checking styles..."
	clang-format -n -style=Google *.cc *.h */*.cc */*.h

format_style:
	@echo "Formatting styles..."
	clang-format -i -style=Google *.cc *.h */*.cc */*.h

valgrind: tests
	@echo "Checking by valgrind..."
	valgrind ./$(EXECUTABLE) --check-full

leaks: tests
	@echo "Checking leaks..."
	CK_FORK=no leaks -quiet --atExit -- ./$(EXECUTABLE)

.PHONY: all install uninstall start clean dvi dist tests gcov_report style format_style valgrind leaks