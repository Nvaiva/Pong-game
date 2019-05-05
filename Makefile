CXXFLAGS = -Isdl2/32bit/include/SDL2 -std=c++0x

LXXFLAGS = -Lsdl2/32bit/lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image


main: Source.o ball.o game.o loadImage.o objects.o wall.o
	g++ Source.o ball.o game.o loadImage.o objects.o wall.o -o main $(LXXFLAGS)

	

Source.o: Source.cpp
	g++ Source.cpp -c $(FXXFLAGS)

	

game.o: game.cpp game.h
	g++ game.cpp -c $(FXXFLAGS)
	


ball.o: ball.cpp ball.h

	g++ ball.cpp -c $(FXXFLAGS)
	

laodImage.o: loadImage.cpp loadImage.h	
	g++ loadImage.cpp -c $(FXXFLAGS)

objects.o: objects.cpp objects.h
	g++ objects.cpp -c $(FXXFLAGS)

wall.o: wall.cpp wall.h
	g++ wall.cpp -c $(FXXFLAGS)