CC = gcc
CFLAGS = -g -Wall -fopenmp

# pattern rule for object files
%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

all: reduce r

reduce: reduce.o
	$(CC) -o reduce reduce.o $(CFLAGS)
	$(RM) *.o

r: reduce.Rmd make.R
	Rscript make.R
	$(RM) *.md *.Rout