COMPILER ?= gcc
CFLAGS = -fsanitize=address -pedantic -pedantic-errors -Wall -Wextra -g
LIBS = -lcrypto

SRCDIR = src
BUILDDIR = build
COMMON_SRCS = $(SRCDIR)/cli_parser/cli_parser.c \
			#   $(SRCDIR)/algorithms/decrypt.c \
            #   $(SRCDIR)/algorithms/embed.c \
            #   $(SRCDIR)/algorithms/encrypt.c \
            #   $(SRCDIR)/algorithms/extract.c \
            #   $(SRCDIR)/algorithms/stego_algorithms.c \
            #   $(SRCDIR)/crypto_cfg/crypto_cfg.c \
            #   $(SRCDIR)/files/bmp.c \
            #   $(SRCDIR)/files/file.c \
            #   $(SRCDIR)/files/files.c \
            #   $(SRCDIR)/stego_cfg/stego_cfg.c
COMMON_OBJS = $(patsubst $(SRCDIR)/%.c,$(BUILDDIR)/%.o,$(COMMON_SRCS))
MAIN_SRC = $(SRCDIR)/main.c
MAIN_OBJ = $(patsubst $(SRCDIR)/%.c,$(BUILDDIR)/%.o,$(MAIN_SRC))
TARGET = stegobmp

all: $(TARGET)

$(BUILDDIR):
	@mkdir -p $(BUILDDIR)/algorithms
	@mkdir -p $(BUILDDIR)/cli_parser
	@mkdir -p $(BUILDDIR)/crypto_cfg
	@mkdir -p $(BUILDDIR)/files
	@mkdir -p $(BUILDDIR)/stego_cfg

$(BUILDDIR)/%.o: $(SRCDIR)/%.c
	$(COMPILER) $(CFLAGS) -c $< -o $@

$(TARGET): $(BUILDDIR) $(COMMON_OBJS) $(MAIN_OBJ)
	$(COMPILER) $(CFLAGS) -o $@ $(MAIN_OBJ) $(COMMON_OBJS) $(LIBS)

clean:
	@rm -rf $(BUILDDIR) $(TARGET)

.PHONY: all clean
