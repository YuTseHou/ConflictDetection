ConflictDetection:main.o Rule.o
	g++ -o ConflictDetection main.o Rule.o
main.o:main.cpp Rule.h
	g++ -c main.cpp
Rule.o:Rule.cpp Rule.h
	g++ -c Rule.cpp

clean:
	rm -f *.o ConflictDetection