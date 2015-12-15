CC=gcc
CFLAGS=-O3 -w -I. -I./include
MYSQL=-lz -L/usr/lib64/mysql -lmysqlclient
PROG=./saac

OBJ=main.o recv.o util.o char.o db.o mail.o acfamily.o lock.o sasql.o saacproto_serv.o saacproto_util.o

package: $(OBJ)
	$(CC) $(CFLAGS) -o $(PROG) $(OBJ) $(MYSQL)

clean:
	rm -f $(PROG)
	rm -f $(OBJ)
