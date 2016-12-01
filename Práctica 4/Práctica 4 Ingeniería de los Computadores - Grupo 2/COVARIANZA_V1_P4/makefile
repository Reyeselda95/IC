all:
	mpic++ -o paralelizado main_paralelizado.cc
	g++ -o generaMatrix generaMatrix.cc
	g++ -o secuencial main_secuencial.cc
	./generaMatrix > matrices1.txt
    ./generaMatrix > matrices2.txt
    ./generaMatrix > matrices3.txt
    ./generaMatrix > matrices4.txt
