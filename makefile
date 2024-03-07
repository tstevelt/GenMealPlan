
PROG = GenMealPlan
LIB = GenMealPlan.a

CFLAGS = -g -Wall -Wformat-truncation=0 -I../../include -I/usr/local/include -DHAVE_DATABASE

MYSQL_DIR = /usr/lib64

MYSQL_FLAGS = -lz -lcrypt -lm -lssl -lcrypto

XLIB = /usr/local/lib64/nutrilib.a /usr/local/lib64/dbylib.a /usr/local/lib64/shslib.a $(MYSQL_DIR)/libmysqlclient.so /usr/local/lib64/libxlsxwriter.a $(MYSQL_FLAGS)

DEF = /usr/local/include

WEBDIR = /usr/local/bin
PRG = $(WEBDIR)/$(PROG)

FILES = \
	$(LIB)(GenMealPlan.o)	\
	$(LIB)(getargs.o)		\
	$(LIB)(LoadFoods.o)		\
	$(LIB)(LoadProfile.o)	\
	$(LIB)(LoadFTD.o)		\
	$(LIB)(FindFood.o)		\
	$(LIB)(initpop.o)		\
	$(LIB)(cmpscore.o)		\
	$(LIB)(obj_func.o)		\
	$(LIB)(select_parents.o) \
	$(LIB)(crossover.o)		\
	$(LIB)(PrintFuncs.o)

.SILENT:

$(PRG): $(LIB) $(XLIB)
	echo "using gcc to load $(PRG)"
	gcc -o $(PRG) $(LIB) $(XLIB)

$(LIB): $(FILES)

$(FILES): GenMealPlan.h $(DEF)/nutrilib.h $(DEF)/filenutri.h $(DEF)/dbylib.h $(DEF)/shslib.h

clean:
	rm -f $(LIB)

all:
	make clean
	make

.PRECIOUS: $(LIB)

