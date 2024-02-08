compilar:
	gcc wizwor.c `pkg-config --cflags --libs sdl2` -o wizwor -lSDL2_image -lSDL2_ttf
	./wizwor
