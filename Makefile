CC=g++

HDRDIR = hdr
OBJDIR = obj
SRCDIR = src

LINKEDLIBS =  

FLAGS = -Wall -Wextra -std=c++20 -O2 -g -I$(HDRDIR)

_HDRFILES = \

HDRFILES = $(patsubst %,$(HDRDIR)/%,$(_HDRFILES))

_OBJFILES = main.o \

OBJFILES = $(patsubst %,$(OBJDIR)/%,$(_OBJFILES))

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp $(HDRFILES)
	$(CC) -c -o $@ $< $(FLAGS)

main: $(OBJFILES)
	$(CC) -o $@ $^ $(FLAGS) $(LINKEDLIBS) 

.PHONY: run clean

run:
	@echo "Running program..."
	@./main
	@echo "Program finished"

clean:
	@rm $(OBJDIR)/*.o  > /dev/null 2>&1 && echo "Object files removed" || echo "No object files to remove"
	@rm main >/dev/null 2>&1 && echo "Binary removed" || echo "No binary to remove"
	@rm *.txt>/dev/null 2>&1 && echo "Result files removed" || echo "No result files to remove"
