all: clean porr.o porr_omp.o install

install:
	mkdir ../target
	mv *.o ../target

clean:
	rm -Rf ../target
	rm -rf *.o 

porr.o: main.o state.o strategy.o timer.o
	g++ main.o state.o strategy.o timer.o -o porr.o

porr_omp.o: main.o state.o strategy_omp.o timer.o
	g++ -fopenmp main.o state.o strategy_omp.o timer.o -o porr_omp.o

main.o: 
	g++ -c -g main.cpp

state.o: state.cpp state.h 
	g++ -c -g state.cpp 

strategy.o: strategy.cpp strategy.h state.h 
	g++ -c -g strategy.cpp

strategy_omp.o: strategy.cpp strategy.h state.h 
	g++ -fopenmp -c -g strategy.cpp -o strategy_omp.o

timer.o: timer.cpp timer.h
	g++ -c -g timer.cpp
