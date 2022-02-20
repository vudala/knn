
CC=gcc
FLAGS=-Wall -O3
LIBS=-fopenmp -lm
SRC=$(wildcard *.c)
OBJS=$(subst .c,.o,$(SRC))
OUTPUT=knn
RM=rm -f

all: $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -o $(OUTPUT) $(LIBS)

%.o: %.c
	$(CC) -c $(FLAGS) $< $(LIBS)

run: 
	./$(OUTPUT) train_samples.txt test_samples.txt 3

clean:
	@$(RM) $(OBJS)

purge: clean
	@$(RM) $(OUTPUT)
