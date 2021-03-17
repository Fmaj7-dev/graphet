EMCC=emcc
CC=clang++
RMCMD=rm -Rf

FLAGS=-std=c++11
FRAMEWORKS=-framework GLUT -framework OpenGl

OBJ_LOCAL=$(CPPSOURCES:.cpp=.o)
DEPENDS := $(patsubst %.cpp,%.d,$(CPPSOURCES))
BUILD_DIR=../build

OBJ=$(addprefix $(BASE)/$(BUILD_DIR)/,$(OBJ_LOCAL))

ifeq ($(TYPE), static)
	DIR_LIB=$(BASE)/$(BUILD_DIR)
	TARGET=$(DIR_LIB)/$(PROJECT).a
else ifeq ($(TYPE), executable)
	DIR_BIN=$(BASE)/$(BUILD_DIR)
	TARGET=$(DIR_BIN)/$(PROJECT)
endif

.PHONY: all clean 

# all
all: $(TARGET)

$(BASE)/$(BUILD_DIR)/%.o: %.cpp Makefile
	$(CC) $(FLAGS) -o $@ -c $< $(INCLUDE) $(DEFS) $(ATTRIBS)

$(TARGET): $(OBJ)
ifeq ($(TYPE), static)
	ar -rv $(TARGET) $(OBJ)
else ifeq ($(TYPE), executable)
	$(CC) $(OBJ) $(FRAMEWORKS) -L$(BASE)/$(BUILD_DIR) $(LIBS) -o$(TARGET)
endif	

clean:
	$(RMCMD) $(OBJ) $(TARGET)

info:
	@echo "TYPE: "$(TYPE)
	@echo "CONFIGURATION: "$(CONFIGURATION)

	@echo "OBJ: "$(OBJ)
	@echo "CPPSOURCES: "$(CPPSOURCES)
	@echo "TARGET: "$(TARGET)