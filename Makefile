CC = g++

HDRDIR = hdr
OBJDIR = obj
SRCDIR = src

LINKEDLIBS =  

FLAGS = -Wall -Wextra -std=c++20 -O2 -ggdb -I$(HDRDIR)

_HDRFILES = AutomataControllers.hpp \
			AutomataModels.hpp \
			AutomataViews.hpp \
			Exceptions.hpp \

HDRFILES = $(patsubst %,$(HDRDIR)/%,$(_HDRFILES))

_OBJFILES = main.o \
			Automata1DModel.o \
			AutomataController.o \
			Automata1DConsoleWriter.o \
			Automata1DFileWriter.o \

OBJFILES = $(patsubst %,$(OBJDIR)/%,$(_OBJFILES))

main: $(OBJFILES)
	$(CC) -o $@ $^ $(FLAGS) $(LINKEDLIBS) 

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp $(HDRFILES)
	$(CC) -c -o $@ $< $(FLAGS)

.PHONY: run clean

# generic run command
run:
	@echo "Running program..."
	@./main
	@echo "Program finished"

# clean .o files and main binary 
clean:
	@rm $(OBJDIR)/*.o  > /dev/null 2>&1 && echo "Object files removed" || echo "No object files to remove"
	@rm main >/dev/null 2>&1 && echo "Binary removed" || echo "No binary to remove"
