default:
	g++ main.cpp -o app -I include/ -L lib/ -lraylib -lopengl32 -lgdi32 -lwinmm