#LDFLAGS=-L/opt/homebrew/opt/ncurses/lib/ -lncursesw
LDFLAGS=-lncurses
sst-info-curses: sst-info-curses.cxx
	ESCDELAY=1 g++ -std=c++20 -o sst-info-curses sst-info-curses.cxx $(LDFLAGS)

