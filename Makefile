# Ustawienia kompilatora i flag
CXX := g++
CXXFLAGS := -std=c++14 -Wall -Iinclude -O2
AR := ar
ARFLAGS := rcs

# Katalogi
SRC_DIR := src
INCLUDE_DIR := include
TESTS_DIR := test
EXAMPLES_DIR := examples
BUILD_DIR := build

# Nazwy plików
LIB_NAME := libnumeryczna.a
LIB := $(BUILD_DIR)/$(LIB_NAME)

# Pliki Ÿród³owe i obiektowe
SRCS := $(wildcard $(SRC_DIR)/*.cpp)
OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRCS))

# Testy
TEST_SRCS := $(wildcard $(TESTS_DIR)/*.cpp)
TEST_OBJS := $(patsubst $(TESTS_DIR)/%.cpp,$(BUILD_DIR)/tests_%.o,$(TEST_SRCS))
TEST_BIN := $(BUILD_DIR)/run_tests

# Przyk³ady
EXAMPLE_SRCS := $(wildcard $(EXAMPLES_DIR)/*.cpp)
EXAMPLE_BINS := $(patsubst $(EXAMPLES_DIR)/%.cpp,$(BUILD_DIR)/example_%,$(EXAMPLE_SRCS))

.PHONY: all clean dirs test examples

all: dirs $(LIB) $(TEST_BIN) examples

dirs:
	mkdir -p $(BUILD_DIR)

# Budowanie biblioteki statycznej
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(LIB): $(OBJS)
	$(AR) $(ARFLAGS) $@ $^

# Budowanie testów
$(BUILD_DIR)/tests_%.o: $(TESTS_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(TEST_BIN): $(TEST_OBJS) $(LIB)
	$(CXX) $(CXXFLAGS) $^ -o $@

test: $(TEST_BIN)
	./$(TEST_BIN)

# Budowanie przyk³adów
$(BUILD_DIR)/example_%: $(EXAMPLES_DIR)/%.cpp $(LIB)
	$(CXX) $(CXXFLAGS) $< $(LIB) -o $@

examples: $(EXAMPLE_BINS)

clean:
	rm -rf $(BUILD_DIR)
