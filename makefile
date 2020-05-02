INCDIRS = -I./ \
		-I./src \
		-I./src/interface \
		-I./module/PacketEthComm \
		-I./module/PacketEthComm/Client \
		-I./module/EnsembleCommon \
		-I./module/EnsembleCommand

OPENCV_CFLAG = `pkg-config opencv4 --cflags`
OPENCV_LIBS = `pkg-config opencv4 --libs`

CC = gcc
LD = gcc
AR = ar
		
TARGET = EnsembleAPI.so

CXXFLAGS  = -fPIC -g $(OPENCV_CFLAG) $(INCDIRS)
CXXFLAGS += -O3 -Wall -std=c++11 -fopenmp

LDFLAGS= -shared

#LIBS = -L$(BOOST_LIB_PATH) -Xlinker --start-group -lpthread -ldl -lm -lrt -lc -lstdc++ -lboost_system -lboost_thread -lboost_filesystem -lboost_regex -lboost_date_time -lgomp -lstdc++fs -Xlinker --end-group $(OPENCV_LIBS)
LIBS = -Xlinker --start-group -lpthread -ldl -lm -lrt -lc -lstdc++ -lboost_system -lboost_thread -lboost_filesystem -lboost_regex -lboost_date_time -lboost_program_options -lboost_python3 -lpython3.6m -lgomp -lstdc++fs -lzbar -Xlinker --end-group $(OPENCV_LIBS)

SRCDIRS		= ./ \
			./src \
			./src/interface \
			./module/PacketEthComm \
			./module/PacketEthComm/Client \
			./module/EnsembleCommon \
			./module/EnsembleCommand
			
VPATH = . $(SRCDIRS)

SRCS = $(foreach dir, . $(SRCDIRS),$(wildcard $(dir)/*.cpp))

OBJS = $(SRCS:.cpp=.o)
OBJS := $(notdir $(OBJS))

all: $(TARGET)

$(TARGET) : $(OBJS)
	-rm -f $(TARGET)
	gcc -o $(TARGET) $(OBJS) $(LDFLAGS)

clean:
	-rm -rf $(OBJS)
	-rm -f $(TARGET)
	-rm -f depend

depend: $(SRCS) 
	$(CC) -M $(CXXFLAGS) $^ > $@ 

-include depend

#depend: .depend
#
#.depend: $(SRCS) $(VERSIONNUM)
#	rm -f ./.depend
#	$(CC) $(CXXFLAGS) -MM $^ > $(notdir $@) -MF  ./.depend;
#	echo "HAHAHAH = " $(CC) $(CXXFLAGS) -MM $^ > $(notdir $@) -MF  ./.depend;
#	#$(CC) $(CFLAGS) -MM $^ -MF  ./.depend;
#
#-include .depend
