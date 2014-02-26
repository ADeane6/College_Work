# #####################################################################
# http://www.gnu.org/software/make/manual/html_node

.PHONY: build clean

CC     = $(CXX)
SRC    = $(wildcard *.cc)
TARGET = $(basename $(SRC))

build: $(TARGET)
	@true

clean:
	$(RM) $(TARGET) *.o *.d

DEPS = $(patsubst %.cc, %.d, $(SRC))
%.d: %.cc
	g++ -MM $< -MF $@

include $(DEPS)