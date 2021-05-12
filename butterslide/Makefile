
LIBS=-lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

all: thegame

State.o:
	g++ -c "src/butterslide.cpp" -o State.o

thegame: State.o
	@echo "** Building the game"
	g++ -o thegame State.o $(LIBS)

clean:
	@echo "** Removing object files and executable..."
	rm -f thegame *.o

install:
	@echo '** Installing...'
	cp thegame /usr/bin

uninstall:
	@echo '** Uninstalling...'
	rm -f /usr/bin/thegame