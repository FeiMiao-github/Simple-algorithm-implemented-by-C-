src := src
bin := bin
inc := inc
cxx := g++
cflags := -lpthread -Wall -W -g -O3 -I$(inc)
A := @

SUFFIX:=.c .cc .h .hpp
SLASH:=/
DOT:=.

totarget=$(addprefix $(bin)$(SLASH),$(subst $(SLASH),$(DOT),$(1)))
tofiles=$(wildcard $(addprefix $(1),$(foreach p,$(SUFFIX),$(SLASH)*$(p))))

# create_target(cc,file,[cflags])
define do_create_target
$(call totarget,$(2)) : $(call tofiles,$(2))
	$(A) echo + cc $$^
	$(A) $(1) $$^ -o $$@ $(3)
endef

# do_create_dir(dir)
define do_create_dir
$(1):
	$(A) mkdir -p $(1)
endef

# create_target(src/dirs)
create_target=$(foreach p,$(1),$(eval $(call do_create_target,$(cxx),$(p),$(cflags))))
# create_dir(dir)
create_dir=$(foreach p,$(1),$(eval $(call do_create_dir,$(p))))

srcdirs := $(wildcard $(addsuffix $(SLASH)*,$(src)))

targets := $(foreach p,$(srcdirs),$(call totarget,$(p)))
tempdirs := $(sort $(dir $(targets)))

all: $(tempdirs) $(targets)

$(call create_dir,$(dir $(sort $(dir $(targets)))))
$(call create_target,$(srcdirs))

.PHONY: clean
clean:
	$(A) echo clean $(tempdirs)
	$(A) -rm -rf $(tempdirs)