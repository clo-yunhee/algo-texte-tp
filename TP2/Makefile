ALGS:=$(patsubst %.c,%.alg,$(subst algs/,,$(wildcard algs/*.c)))

all: $(ALGS) genset

genset: mtrand.c genset.c

%.alg: main.c common.c algs/%.c
	gcc $^ -o $@ $(CFLAGS) -DRALG=$(patsubst %.alg,%,$@)

clean:
	@rm -f $(ALGS) genset

