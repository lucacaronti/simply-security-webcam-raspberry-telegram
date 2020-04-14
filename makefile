TARGET=securityCamera
PROJECT=securityCamera
OPENCV_FLAGS=`(pkg-config --cflags --libs opencv4)`

$(PROJECT): $(PROJECT).o
	g++ $(PROJECT).o -o $(TARGET) $(OPENCV_FLAGS)
$(PROJECT).o: $(PROJECT).cpp
	g++ -c $(PROJECT).cpp $(OPENCV_FLAGS)
clean:
	rm $(TARGET) $(PROJECT).o
