TARGET = udc2_freq_set
all: $(TARGET)
.PHONY: all

LIBS =  /usr2/fs/clib/clib.a /usr2/fs/rtelb/rtelb.a
OBJECTS = udc2_freq_set.o

$(TARGET): $(OBJECTS) $(LIBS)

#use install as oper
.PHONY: install
install: $(TARGET)
	cp -f udc2_freq_set /usr2/oper/bin
