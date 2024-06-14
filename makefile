COMPILER ?= gcc
CFLAGS = -fsanitize=address -pedantic -pedantic-errors -Wall -Wextra -g
LIBS = -lcrypto

SRCDIR = src
BUILDDIR = build
COMMON_SRCS = $(SRCDIR)/cli_parser/cli_parser.c \
			$(SRCDIR)/stego_config/stego_config.c \
			$(SRCDIR)/crypto_config/crypto_config.c \
			$(SRCDIR)/algorithms/mode_algo.c \
			$(SRCDIR)/algorithms/lsb_algo.c \
			$(SRCDIR)/algorithms/crypto_algo.c \
			$(SRCDIR)/general_config/general_config.c \
			$(SRCDIR)/bmp_manager/bmp.c \

COMMON_OBJS = $(patsubst $(SRCDIR)/%.c,$(BUILDDIR)/%.o,$(COMMON_SRCS))
MAIN_SRC = $(SRCDIR)/main.c
MAIN_OBJ = $(patsubst $(SRCDIR)/%.c,$(BUILDDIR)/%.o,$(MAIN_SRC))
TARGET = stegobmp

all: $(TARGET)

$(BUILDDIR):
	@mkdir -p $(BUILDDIR)/algorithms
	@mkdir -p $(BUILDDIR)/cli_parser
	@mkdir -p $(BUILDDIR)/crypto_config
	@mkdir -p $(BUILDDIR)/general_config
	@mkdir -p $(BUILDDIR)/stego_config
	@mkdir -p $(BUILDDIR)/bmp_manager

$(BUILDDIR)/%.o: $(SRCDIR)/%.c
	$(COMPILER) $(CFLAGS) -c $< -o $@

$(TARGET): $(BUILDDIR) $(COMMON_OBJS) $(MAIN_OBJ)
	$(COMPILER) $(CFLAGS) -o $@ $(MAIN_OBJ) $(COMMON_OBJS) $(LIBS)

clean:
	@rm -rf $(BUILDDIR) $(TARGET)

.PHONY: all clean
