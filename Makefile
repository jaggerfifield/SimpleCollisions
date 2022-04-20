
TARGET = code

IPATH = .\SDL2-2.0.20\x86_64-w64-mingw32\include\SDL2
LPATH = .\SDL2-2.0.20\x86_64-w64-mingw32\lib

LINK = -lmingw32 -lSDL2main -lSDL2 -lSDL2_image # -lSDL2_ttf -lSDL2_mixer

all : $(TARGET).o
	gcc $(TARGET).o -I$(IPATH) -L$(LPATH) -std=c99 -Wall -O $(LINK) -o a
	./a.exe
	
debug : $(TARGET).o
	gcc $(TARGET).o -I$(IPATH) -L$(LPATH) -std=c99 -Wall -O $(LINK) -o debug

release : $(TARGET).o
	gcc $(TARGET).o -I$(IPATH) -L$(LPATH) -std=c99 -Wl,-subsystem,windows $(LINK) -o release
	
# Generate the object file
$(TARGET).o : $(TARGET).c
	gcc $(TARGET).c -I$(IPATH) -L$(LPATH) -c -std=c99 -Wall -O $(LINK)
