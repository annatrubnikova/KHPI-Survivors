BIN := endgame


BIN_TARGET := ENDGAME

LIBS :=   -lSDL2 -lSDL2_image \
          -lSDL2_mixer -lSDL2_ttf -lSDL2_gfx -lm
  

.PHONY = all clean uninstall reinstall

CC = clang -std=c11  -Wall -Wextra -Werror -Wpedantic #compiler -std=c11

SOURCE := $(wildcard src/*.c)

HEAD := $(wildcard inc/*.h)

OBJECTS = $(addprefix obj/,$(notdir $(SOURCE:.c=.o)))

all: $(OBJECTS) $(BIN_TARGET) 

$(BIN_TARGET): $(SOURCE) $(OBJECTS) $(HEAD)
#mkdir -p obj 
# $(CC) -c  $(SOURCE) 
#mv $(OBJECTS) ./obj
	@$(CC) -o $(BIN) $(OBJECTS) $(LIBS)

obj/%.o: src/%.c $(HEAD)
	@mkdir -p obj 
	@$(CC) -c $< -o $@

uninstall: clean
	rm -f $(BIN)

clean:
	rm -drf obj
	rm -f $(wildcard *.o)

reinstall: $(BIN_TARGET)
