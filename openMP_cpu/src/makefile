all: clean porr.o porr_omp.o install

test: clean make_tests
	rm -rf results.log
	rm -rf ../tests
	mkdir ../tests
	mv *.tst ../tests
	../tests/point.tst --log_level=test_suite >> results.log
	../tests/individual.tst --log_level=test_suite >> results.log
	mv results.log ../tests/

make_tests: point.tst individual.tst

install:
	mkdir ../target
	mv *.o ../target

clean:
	rm -rf *.o 

point.tst: point.o
	g++ point.o point_test.cpp -lboost_unit_test_framework -o point.tst
    
point.o: point.cpp point.h
	g++ -c -g point.cpp -o point.o

individual.tst: individual.o point.o
	g++ point.o individual.o individual_test.cpp -lboost_unit_test_framework -o individual.tst
    
individual.o: individual.cpp individual.h
	g++ -c -g individual.cpp -o individual.o

