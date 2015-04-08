all: clean main.o
	./main.o

test: clean make_tests
	rm -rf results.log
	rm -rf ../tests
	mkdir ../tests
	mv *.tst ../tests
	../tests/point.tst --log_level=test_suite >> results.log
	../tests/method.tst --log_level=test_suite >> results.log
	../tests/individual.tst --log_level=test_suite >> results.log
	../tests/strategy.tst --log_level=test_suite >> results.log
	mv results.log ../tests/

make_tests: point.tst individual.tst method.tst strategy.tst

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

method.tst: method.o point.o 
	g++ method.o point.o method_test.cpp -lboost_unit_test_framework -o method.tst
    
method.o: method.cpp method.h
	g++ -c -g method.cpp -o method.o

strategy.tst: method.o point.o mipluslambdastrategy.o milambdastrategy.o individual.o
	g++ method.o point.o mipluslambdastrategy.o milambdastrategy.o individual.o strategy_test.cpp -lboost_unit_test_framework -o strategy.tst

mipluslambdastrategy.o: mipluslambdastrategy.cpp mipluslambdastrategy.h
	g++ -c -g mipluslambdastrategy.cpp -o mipluslambdastrategy.o

milambdastrategy.o: milambdastrategy.cpp milambdastrategy.h
	g++ -c -g milambdastrategy.cpp -o milambdastrategy.o

main.o: method.o point.o mipluslambdastrategy.o milambdastrategy.o individual.o
	g++ method.o point.o mipluslambdastrategy.o milambdastrategy.o individual.o main.cpp -o main.o

