ConflictDetection:main.o Rule.o Status.o
	g++ -o ConflictDetection main.o Rule.o Status.o -l sqlite3
main.o:main.cpp Rule.h Status.h
	g++ -c main.cpp
Rule.o:Rule.cpp Rule.h Status.h
	g++ -c Rule.cpp
Status.o:Status.cpp Status.h
	g++ -c Status.cpp

clean:
	rm -f *.o ConflictDetection