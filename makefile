program:
	g++ main.cpp CPU.cpp --std=c++11 -I/opt/homebrew/Cellar/sfml/2.5.1_2/include/ -o test -L/opt/homebrew/Cellar/sfml/2.5.1_2/lib -lsfml-graphics -lsfml-window -lsfml-system -lstdc++
