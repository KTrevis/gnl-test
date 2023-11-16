GNL_PATH = ../gnl

all:
ifdef b
	cc -D BUFFER_SIZE=$(b) main.c $(GNL_PATH)/get_next_line.c $(GNL_PATH)/get_next_line_utils.c -I $(GNL_PATH) && ./a.out
else
	@echo "BUFFER_SIZE NOT DEFINED"
endif
