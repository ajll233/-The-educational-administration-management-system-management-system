CC=gcc
BIN=sch_man_sys.bin
OBJ=admin.o main.o student.o teacher.o tools.o sys.o
FLAG=-Wall -Werror
STD=-std=gnu99

all:$(OBJ)
	$(CC) -o $(BIN) $(OBJ) && ./$(BIN)

main.o:main.c
	$(CC) $(STD) $(FLAG) -c main.c

admin.o:admin.c admin.h tools.h sys.h
	$(CC) $(STD) $(FLAG) -c admin.c

student.o:student.c student.h tools.h sys.h
	$(CC) $(STD) $(FLAG) -c student.c

teacher.o:teacher.c teacher.h tools.h
	$(CC) $(STD) $(FLAG) -c teacher.c

tools.o:tools.c tools.h
	$(CC) $(STD) $(FLAG) -c tools.c

sys.o:sys.c sys.h student.h teacher.h admin.h tools.h
	$(CC) $(STD) $(FLAG) -c sys.c

clean:
	rm -rf $(BIN) $(OBJ)
