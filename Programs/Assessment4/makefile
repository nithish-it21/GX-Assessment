CC = gcc


SRC = main.c memory_allocation.h matrix_input.h memory_deallocation.h multiplication.h print_matrix.h


OBJ = $(SRC:.c=.o)


TARGET = my_program

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)


%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@


clean:
	rm -f $(OBJ) $(TARGET)

