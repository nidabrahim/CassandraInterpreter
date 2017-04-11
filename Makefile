zzc: lex.yy.o Cassandra.o
	gcc -o zzc lex.yy.o Cassandra.o fin.o -lfl
lex.yy.o: lex.yy.c
	gcc -c lex.yy.c
Cassandra.o: Cassandra.c
	gcc -c Cassandra.c
fin.o: fin.c
	gcc -c fin.c
clean:
	rm *.o zzc
