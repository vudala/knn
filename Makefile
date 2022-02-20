
CC=gcc
FLAGS=-Wall -g
SRC=$(wildcard *.c)
OBJS=$(subst .c,.o,$(SRC))
OUTPUT=knn
RM=rm -f

all: $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -o $(OUTPUT)

%.o: %.c
	$(CC) -c $(FLAGS) $<

run: 
	./$(OUTPUT) train_samples.txt test_samples.txt

clean:
	@$(RM) $(OBJS)

purge: clean
	@$(RM) $(OUTPUT)
