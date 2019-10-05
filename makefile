CC = gcc
CFLAGS = 
OUT_DIR = ./out
SOURCES = flv.c \
		flv_header.c \
		flv_tag.c \
		flv_tag_script.c \
		flv_tag_script_string.c \
		flv_tag_script_double.c \
		flv_tag_script_ecma.c \
		flv_tag_script_object.c \
		flv_tag_script_bool.c

all: $(OUT_DIR) $(SOURCES)
	$(CC) $(CFLAGS) $(SOURCES) -o $(OUT_DIR)/flv

$(OUT_DIR):
	mkdir $(OUT_DIR)

clean:
	rm -rf $(OUT_DIR)
