MACRO := DEBUGALL
CFLAGS := -g -w -D$(MACRO)
SOURCES = $(wildcard *.c)
OBJS = $(patsubst %.c, %.o,$(SOURCES))  
CC = gcc
main: $(OBJS)
	@echo "source files:" $(SOURCES)
	@echo "object files:" $(OBJS)
	$(CC) $(OBJS)  -D$(MACRO) $(CFLAGS) -o main  
sinclude $(SOURCES:.c=.d)
%d: %c
	@echo "create depend"
	$(CC) -MM $(CFLAGS) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ ,g' < $@.$$$$ > $@; \
	$(RM) $@.$$$$
	
clean:
	rm -rf $(OBJS)

	rm -f main
