main.o:main.cpp cal.h
	g++ -c main.cpp

cal.o:cal.h cal.cpp
	g++ -c cal.cpp

census: main.o cal.o
	g++ -o census main.o cal.o
