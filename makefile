OBJS =  src-serv src-client

.PHONY: all $(OBJS)

all: $(OBJS)

$(OBJS):
	 @ $(MAKE) -C $@ all

clean:
	@ #TODO make better
	@ $(MAKE) -C src-serv clean
	@ $(MAKE) -C src-client clean