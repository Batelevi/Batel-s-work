VAR = fsq
VAR2 = singly_linked_list

CC = gcc
CFLAGS = -ansi -pedantic-errors -Wall -Wextra -g

IDIR = ../../include
TDIR = ../../test/
ODIR = ../../obj/
BDIR = ../../bin/
DEBDIR = ../../debug/
RELDIR = ../../release/

VPATH = $(IDIR) $(TDIR) $(ODIR) $(BDIR)

TARGET = $(BDIR)$(VAR).out
OBJ = $(VAR).o $(VAR)_test.o $(VAR2).o
DEPS = $(VAR).h
VERSION =


.PHONY = all
.PHONY = run
.PHONY = run_debug
.PHONY = run_release
.PHONY = mkdir
.PHONY = mkdir_debug
.PHONY = mkdir_release
.PHONY = create_template_test
.PHONY = open
.PHONY = vlg
.PHONY = cgdb
.PHONY = gitadd
.PHONY = debug
.PHONY = release
.PHONY = clean


all: mkdir $(VAR).out 


$(VAR).out: $(OBJ)
	$(CC) $(CFLAGS) -I$(IDIR) $(ODIR)$(VAR).o $(ODIR)$(VAR)_test.o  $(ODIR)$(VAR2).o -o$(TARGET)


$(VAR).o: $(VAR).c $(DEPS)
	$(CC) $(CFLAGS) -I$(IDIR) -c $< -o$(ODIR)$@


$(VAR)_test.o: $(VAR)_test.c $(DEPS)
	$(CC) $(CFLAGS) -I$(IDIR) -c $(TDIR)$(VAR)_test.c -o$(ODIR)$@


$(VAR2).o: ../$(VAR2)/$(VAR2).c $(VAR2).h
	cd ../$(VAR2) && make $(VERSION)


run: $(TARGET)
	$(TARGET)


run_debug: 
	@ $(DEBDIR)$(VAR).out


run_release:
	@ $(RELDIR)$(VAR).out


mkdir:
	@ mkdir -p $(ODIR)
	@ mkdir -p $(BDIR)

	
touch:
	touch $(VAR).c
	touch $(IDIR)/$(VAR).h
	touch $(TDIR)$(VAR)_test.c


create_template_src_test:
	cp -i $(IDIR)/$(VAR).h $(VAR).c
	cp -n $(TDIR)template_test.c $(TDIR)$(VAR)_test.c


open:
	code $(VAR).c
	code $(IDIR)/$(VAR).h
	code $(TDIR)$(VAR)_test.c


vlg:
	valgrind --leak-check=yes --track-origins=yes $(TARGET)
	

cgdb:
	cgdb $(TARGET)
	

gitadd:
	git add .
	git add ../../*$(VAR)*
	git status
		
	
debug: CFLAGS += -DEBUG
debug: mkdir_debug
debug: clean
debug: TARGET = $(DEBDIR)$(VAR).out
debug: VERSION = debug
debug: all


mkdir_debug:
	@ mkdir -p $(DEBDIR)


release: CFLAGS = -ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3
release: mkdir_release
release: clean
release: TARGET = $(RELDIR)$(VAR).out
release: VERSION = release
release: all


mkdir_release:
	@ mkdir -p $(RELDIR)


clean:
	rm -f $(TARGET) $(ODIR)$(VAR)*.o $(ODIR)$(VAR2).o $(BDIR)$(VAR).out $(DEBDIR)$(VAR).out $(RELDIR)$(VAR).out 
