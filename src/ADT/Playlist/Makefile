CC=gcc  #compiler
TARGET=test_listlinier #target file name
SOURCE= tes_listlinier.c listlinier.c ../../ADT/Lagu/lagu.c ../../ADT/Word/Word.c
SOURCE2 = listlinier.c ../../ADT/Lagu/lagu.c ../../ADT/Word/Word.c playlist.c test_playlist.c 
TARGET2 = test_playlist
all:
	$(CC) $(SOURCE) -o $(TARGET)
	$(CC) $(SOURCE2) -o $(TARGET2)
	@echo "Build finished. Run './$(TARGET) dan ./$(TARGET2)' to execute."
clean:
	rm $(TARGET) $(TARGET2)
