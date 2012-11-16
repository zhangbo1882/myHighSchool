MACRO := DEBUGALL
CFLAGS := -g -w -D$(MACRO)
EXE	= hadump
SOURCES = $(wildcard *.c)
OBJS = $(patsubst %.c, %.o,$(SOURCES))  
CC = gcc
$(EXE): $(OBJS)
	@echo "source files:" $(SOURCES)
	@echo "object files:" $(OBJS)
	$(CC) $(OBJS)  -D$(MACRO) $(CFLAGS) -o $(EXE)   
sinclude $(SOURCES:.c=.d)
%d: %c
	@echo "create depend"
	$(CC) -MM $(CFLAGS) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ ,g' < $@.$$$$ > $@; \
	$(RM) $@.$$$$
	
clean:
	rm -rf $(OBJS)

	rm -f $(EXE)
