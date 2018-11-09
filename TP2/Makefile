
CFLAGS += -Wall -Wextra -Wno-sign-compare -Werror=implicit-function-declaration -pipe -I.
CFLAGS += -g -O2
# CFLAGS += -O2 -Os
# CFLAGS += -fPIC -fstack-protector-strong

DEPDIR := .dep
OBJDIR := .obj
$(shell mkdir -p $(DEPDIR) $(OBJDIR) >/dev/null)

objfile = $(addprefix $(OBJDIR)/,$(subst /,!,$1))

DEPFLAGS = -MT $@ -MMD -MP -MF $(DEPDIR)/$(notdir $*).Td

compile = $(CC) $(DEPFLAGS) $(CFLAGS)
link = $(CC) $(LDFLAGS) -o $1 $(call objfile,$2)
postcompile = @mv -f $(DEPDIR)/$(notdir $*).Td $(DEPDIR)/$(notdir $*).d && touch $(call objfile,$@)

ALGS := $(patsubst %.c,%.alg,$(subst algs/,,$(wildcard algs/*.c)))
TARGETS := $(ALGS) .generate-data

.PHONY: all clean re

all: $(TARGETS)

clean:
	@rm -f $(TARGETS) $(shell find -iname "*.o")

re: clean all

.generate-data: mtrand.o generator.o
	$(call link,$@,$^)

%.alg: algs/main_%.o common.o algs/%.o
	$(call link,$@,$^)

algs/main_%.o: main.c  
	$(compile) -DRALG=$* -o $(call objfile,$@) -c $^
	$(postcompile)

%.o: %.c
	$(compile) -o $(call objfile,$@) -c $^
	$(postcompile)

$(DEPDIR)/%.d: ;
.PRECIOUS: $(DEPDIR)/%.d

include $(wildcard $(patsubst %,$(DEPDIR)/%.d,$(basename $(SRCS))))

