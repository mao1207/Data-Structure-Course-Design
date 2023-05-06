CFLAGS   = -c -Wall -Werror
COMPILE  = g++
RM       = rm -f
OBJ      = linux
SOURCE   = 1_2053058_ë�迥.o
DEPEND   = 1_2053058_ë�迥.cpp 

build : $(SOURCE)
	$(COMPILE) $(SOURCE) -o $(OBJ)

%.o:%cpp $(DEPEND)
	$(COMPILE) $(CFLAGS) -o $@ $<

clean:
	$(RM) *.bak $(SOURCE) $(OBJ)
	touch *.*
