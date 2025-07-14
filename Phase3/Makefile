CXX = g++

CXXFLAGS = -std=c++20 -I./header

SRC_DIRS = src server utils
OBJ_DIR = obj
BIN_DIR = bin

TARGET = utms.out

SRCS = $(wildcard $(addsuffix /*.cpp, $(SRC_DIRS)))

OBJS = $(SRCS:%.cpp=$(OBJ_DIR)/%.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: %.cpp $(wildcard $(SRC_DIRS)/*.hpp)
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)/$(TARGET)