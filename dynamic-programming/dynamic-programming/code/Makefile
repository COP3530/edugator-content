.PHONY: fibonacci 1d-bottom-up 1d-top-down 2d-bottom-up 2d-top-down clean

fibonacci: fibonacci.cpp
	g++ -std=c++14 -o bin/fibonacci fibonacci.cpp

1d-bottom-up: 1d-bottom-up.cpp
	g++ -std=c++14 -o bin/1d-bottom-up 1d-bottom-up.cpp

1d-top-down: 1d-top-down.cpp
	g++ -std=c++14 -o bin/1d-top-down 1d-top-down.cpp

2d-bottom-up: 2d-bottom-up.cpp
	g++ -std=c++14 -o bin/2d-bottom-up 2d-bottom-up.cpp

2d-top-down: 2d-top-down.cpp
	g++ -std=c++14 -o bin/2d-top-down 2d-top-down.cpp

clean:
	rm bin/*