objects = main.o command.o

sum : $(objects)
	gcc -o sum $(objects)

main.o : defs.h
command.o : defs.h

# order only dependency
a: b c | b d

.PHONY : clean
clean : 
	-rm sum $(objects)
