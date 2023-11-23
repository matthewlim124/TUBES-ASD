CC=gcc  #compiler
TARGET=test_lagu #target file name
SOURCE= ../../ADT/Word/word.c ../../ADT/MesinKarakter/mesinkarakter.c ../../ADT/MesinKata/mesinkata.c  test_lagu.c lagu.c -o test_lagu
all:
	$(CC) $(SOURCE) -o $(TARGET)
	@echo "Build finished. Run './$(TARGET)' to execute."
clean:
	rm $(TARGET)
