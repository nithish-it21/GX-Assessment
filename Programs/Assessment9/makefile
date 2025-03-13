cc = gcc

flags = -Wall -o

target = main
files = main.c
obj_file = $(files:.c=.o)

all: $(target)

$(target): $(obj_file)
	$(cc) $(flags) $@ $^


$(obj_file): $(files)
	$(cc) -c $^ -o $@


run: $(target)
	./$(target)


clean:
	rm -f $(obj_file) $(target)
