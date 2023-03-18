program:
	g++ main.cpp CPU.cpp -g --std=c++11 -I/opt/homebrew/Cellar/sfml/2.5.1_2/include/ -o test -L/opt/homebrew/Cellar/sfml/2.5.1_2/lib -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system -lstdc++
