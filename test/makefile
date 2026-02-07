TARGET = main

INCFOLDER = -I$(PREFIX)/include
LDFOLDER = -L$(PREFIX)/lib -ldl -lSDL2 -lSDL2_ttf


all:
	mkdir -p build
	$(CROSS_COMPILE)gcc $(TARGET).c -o build/$(TARGET) $(INCFOLDER) $(LDFOLDER)

clean:
	rm build/*
