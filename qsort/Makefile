CC = gcc
CFLAGS = -g -Wall -fopenmp

# pattern rule for object files
%.o: %.c
	$(CC) -c $< -o $@

all: qsort r

qsort: qsort.o
	$(CC) -o qsort qsort.o $(CFLAGS)
	$(RM) *.o

r: qsort.Rmd make.R
	Rscript make.R
	$(RM) *.md *.Rout