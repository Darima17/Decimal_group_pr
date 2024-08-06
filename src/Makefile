PROJECT := s21_decimal

.PHONY: all clean $(PROJECT).a test gcov_report leaks_check linter linter_check

CC := gcc
STD := -std=c11
CFLAGS := -Werror -Wextra -Wall
LIBFLAG := -l$(PROJECT)
COVERAGE_FLAG :=
LEAKS_CALL :=
LINTER := clang-format -style=Google -i
LINTER_CHECK := clang-format -style=Google -n

OS := $(shell uname -s)
ifeq ($(OS), Darwin)
LIBCHECK_FLAGS := -lcheck
LEAKS := leaks --at-exit --
endif
ifeq ($(OS),Linux)
LIBCHECK_FLAGS := -lcheck -lcheck_pic -pthread -lrt -lm -lsubunit
LEAKS := valgrind --leak-check=full --show-leak-kinds=all --
endif

DIR_CHECK = @mkdir -p $(@D)

SRC_DIR := .
BUILD_DIR := build
UTILS_DIR := $(SRC_DIR)/utils
UTILS_BUILD_DIR := $(BUILD_DIR)/utils
TEST_DIR := unit_test
TEST_BUILD_DIR := $(BUILD_DIR)/$(TEST_DIR)
TEST_COMP_DIR := $(TEST_BUILD_DIR)/compilated
COVERAGE_DIR := gcov_report

SRC := $(wildcard $(SRC_DIR)/*.c)
OBJ := $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRC))
UTILS := $(wildcard $(UTILS_DIR)/*.c)
UTILS_OBJ := $(patsubst $(UTILS_DIR)/%.c, $(UTILS_BUILD_DIR)/%.o, $(UTILS))
TEST_C := $(patsubst $(SRC_DIR)/%.c, $(TEST_BUILD_DIR)/test_%.c, $(SRC))
TEST_COMPILATED := $(patsubst $(SRC_DIR)/%.c, $(TEST_COMP_DIR)/test_%.out, $(SRC))

all: gcov_report

### Leaks
leaks_check: LEAKS_CALL += $(LEAKS)
leaks_check: test

### Build with gcov report
gcov_report: COVERAGE_FLAG += --coverage
gcov_report: test
	@mkdir -p $(COVERAGE_DIR)
	@rm -f build/unit_test/compilated/*.gcno build/unit_test/compilated/*.gcda build/utils/*.gcno build/utils/*.gcda
	@gcov -f build/*.gcno
	@gcovr -r . --html-details --html-self-contained -o $(COVERAGE_DIR)/report.html
	@rm -f *.gcov


### Build test
test: $(PROJECT).a test_comp
test_comp: $(TEST_COMPILATED)

$(TEST_COMP_DIR)/test_%.out: $(TEST_BUILD_DIR)/test_%.c
	$(DIR_CHECK)
	@$(CC) $(STD) $(CFLAGS) $^ -g -o $@ $(LIBCHECK_FLAGS) $(PROJECT).a $(COVERAGE_FLAG)
	$(LEAKS_CALL) ./$@

$(TEST_BUILD_DIR)/test_%.c: $(SRC_DIR)/$(TEST_DIR)/%.check
	$(DIR_CHECK)
	@checkmk clean_mode=1 $^ > $@
	@$(LINTER) $@

### Library build
$(PROJECT).a: $(UTILS_OBJ) $(OBJ)
	@ar -rsc $@ $^

$(BUILD_DIR)/$(UTILS_DIR)/%.o: $(SRC_DIR)/$(UTILS_DIR)/%.c
	$(DIR_CHECK)
	@$(CC) $(STD) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(DIR_CHECK)
	@$(CC) $(STD) $(FLAGS) -c -g $< -o $@ $(COVERAGE_FLAG)

### Linters
linter:
	@$(LINTER) $(SRC) $(UTILS)

linter_check:
	$(LINTER_CHECK) $(SRC) $(UTILS)

clean:
	@rm -rf *.a *.out $(BUILD_DIR) *.gcov $(COVERAGE_DIR)

example:
	@echo $(wildcard *.c)
	@echo 
	@echo $(wildcard unit_test/*.check)
