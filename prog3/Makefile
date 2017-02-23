CC       = gcc
CFLAGS   = --W -Wall -ansi -pedantic -Werror -g3 -fPIC
NAME    :=  libwrap
SNAME   :=  $(NAME).a
DNAME   :=  $(NAME).so
OBJ 	:= 	wrapper.o
LDFLAGS :=  -L.
LDLIBS  :=  -l$(...)

.PHONY: all clean fclean re

all: $(SNAME) $(DNAME)

$(SNAME): $(OBJ)
    $(AR) $(ARFLAGS) $@ $^

$(DNAME): LDFLAGS += -shared
$(DNAME): $(OBJ)
    $(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@

clean:
    $(RM) $(OBJ)

fclean: clean
    $(RM) $(SNAME) $(DNAME)

re: fclean all
