make:
	make main.x

%.x: %.o quicksort.o mergesort.o insertionsort.o heapsort.o tester.o
	g++ -std=c++11 quicksort.o mergesort.o insertionsort.o heapsort.o tester.o $< -o $@
	rm -f *.o

%.o: %.cpp
	g++ -std=c++11 -c $< -o $@

clean:
	rm -f *.o *.x

cleanRes:
	rm -f Risultati/*/*.txt