# David's grand makefile, with unit testing and integration testing support
# Parameters

EXEC_NAME = mycompiler
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
UTESTS_DIR = unittests_src
UTESTS_OBJ_DIR = unittests_obj
UTESTS_BIN_DIR = unittests_bin
ITESTS_DIR = integrationtests

CC = gcc
# Remove the `-g` when finished debugging 
CC_FLAGS = -ansi -pedantic -Wall -g

# -------------

SOURCES := $(wildcard $(SRC_DIR)/*.c)
INCLUDES := $(wildcard $(SRC_DIR)/*.h)
OBJECTS := $(SOURCES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
TESTABLES := $(filter-out $(OBJ_DIR)/main.o, $(OBJECTS))
UTESTS := $(wildcard $(UTESTS_DIR)/*.c)
UTESTS_OBJ := $(UTESTS:$(UTESTS_DIR)/%.c=$(UTESTS_OBJ_DIR)/%.o)
UTESTS_BIN := $(UTESTS:$(UTESTS_DIR)/%.c=$(UTESTS_BIN_DIR)/%)

.PHONY: all
all: compile compiletests test

.PHONY: remake
remake: clean all

.PHONY: compile
compile: $(BIN_DIR)/$(EXEC_NAME)

.PHONY: test
test:
	@DID_FAIL_UNIT=0; \
	for f in $(UTESTS_BIN_DIR)/*; do \
		echo -n "\033[1;33mTesting $$f\033[0m"; \
		atime=$$(date +%s%N); \
		./"$$f"; \
		if [ $$? -ne 0 ]; then \
			echo " \033[1;31mFailed!\033[0m"; \
			DID_FAIL_UNIT=1; \
		fi; \
		btime=$$(($$(date +%s%N) - $$atime)); \
		printf " \033[1;37m[%.2f ms]\033[0m\n" "$$(echo "scale = 10; $$btime / 1000000" | bc)"; \
	done; \
	if [ $$DID_FAIL_UNIT -eq 1 ]; then \
		echo "\033[1;31mFailed unit test(s)!\033[0m"; \
		exit 1; \
	fi; \
	DID_FAIL_INTEG=0; \
	for f in $(ITESTS_DIR)/*.sh; do \
		echo -n "\033[1;33mTesting $$f\033[0m"; \
		atime=$$(date +%s%N); \
		./"$$f"; \
		if [ $$? -ne 0 ]; then \
			echo " \033[1;31mFailed!\033[0m"; \
			DID_FAIL_INTEG=1; \
		fi; \
		btime=$$(($$(date +%s%N) - $$atime)); \
		printf " \033[1;37m[%.2f ms]\033[0m\n" "$$(echo "scale = 10; $$btime / 1000000" | bc)"; \
	done; \
	if [ $$DID_FAIL_INTEG -eq 1 ]; then \
		echo "\033[1;31mFailed integration test(s)!\033[0m"; \
		exit 2; \
	fi; \
	echo "\033[1;32mSuccess!\033[0m";

# Main target - Link o files
$(BIN_DIR)/$(EXEC_NAME): $(OBJECTS) $(SOURCES) $(INCLUDES)
	@echo "\033[1;34mCompiling $(BIN_DIR)/$(EXEC_NAME)\033[0m"; \
	$(CC) $(OBJECTS) -o $(BIN_DIR)/$(EXEC_NAME)

# Compile program c files to o files
$(OBJECTS): $(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	@echo "\033[1;35mCompiling $@\033[0m"; \
	$(CC) $(CC_FLAGS) -c $< -o $@

# Compile all tests
.PHONY: compiletests
compiletests: $(UTESTS_BIN)

# Compile test c files to o files
$(UTESTS_OBJ): $(UTESTS_OBJ_DIR)/%.o : $(UTESTS_DIR)/%.c
	@echo "\033[1;35mCompiling $@ \033[1;37m[UNIT TEST]\033[0m"; \
	$(CC) $(CC_FLAGS) -c $< -o $@

# Link tests with program objects
$(UTESTS_BIN_DIR)/%: $(UTESTS_OBJ_DIR)/%.o $(TESTABLES)
	@echo "\033[1;34mCompiling $@ \033[1;37m[UNIT TEST]\033[0m"; \
	$(CC) $(TESTABLES) $< -o $@

# Remove generated files
.PHONY: clean
clean:
	@echo "\033[1;32mRemoving all but source files\033[0m"; \
	rm -f -v $(BIN_DIR)/* $(OBJ_DIR)/* $(UTESTS_BIN_DIR)/* $(UTESTS_OBJ_DIR)/* $(ITESTS_DIR)/temp/*.ob $(ITESTS_DIR)/temp/*.ent $(ITESTS_DIR)/temp/*.ext $(ITESTS_DIR)/temp/*.as \

.PHONY: setup-precommit
setup-precommit:
	@chmod +x pre-commit; \
	cp pre-commit .git/hooks/; \
	echo "\033[1;32mMade sure compilation and tests pass before you are able to commit.\033[0m"

.PHONY: unsetup-precommit
unsetup-precommit:
	@rm -f .git/hooks/pre-commit; \
	echo "\033[1;31mPre-commit script removed!\033[0m"
