all: compile run

run:
	build/rocketjump.exe

compile:
	g++ -std=c++17 src/vecmath.cpp src/slime.cpp src/grid.cpp src/main.cpp -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system -o build/rocketjump
