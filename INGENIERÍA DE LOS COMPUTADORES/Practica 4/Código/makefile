all:
	mpic++ -o paralelizado main_paralelizado.cc
	g++ -o generaMatrix generaMatrix.cc
	g++ -o secuencial main_secuencial.cc
	./generaMatrix > matrices.txt
