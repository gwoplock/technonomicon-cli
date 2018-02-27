OBJS =  src-serv src-client

.PHONY: all $(OBJS)

all: $(OBJS)

$(OBJS):
	@ make -C $@ all

clean:
	@ #TODO make better
	@ make -C src-serv clean
	@ make -C src-client clean