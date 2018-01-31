CC	:= g++
INCS	:= include
CFLAGS	:= -I$(INCS) -I./

COBJS	:= test.o main.o
APP	:= main

ifdef VERBOSE
	V :=
	cmd =
else
	V :=@
	cmd = @echo "$(1) $(2) --> $(3)"
endif

all: $(APP)
	@echo "Build $@ done !"

$(APP): $(COBJS)
	$(V) $(CC) $(CFLAGS) -o $@ $^

%.o: %.cpp
	$(call cmd, "CC", $<, $@)
	$(V) $(CC) $(CFLAGS) -c $<

clean:
	rm -f $(COBJS) $(APP)
