#SDL_draw lib installer makefile

TARGET = installer

OBJS = main.o

$(TARGET):$(OBJS)
	$(CXX) -o $@ $(OBJS)

main.o:main.cpp
	$(CXX) -DMDIR=\"$(MDIR)\" -c main.cpp

.PHONY:clean

clean:
	-rm $(TARGET) $(OBJS)