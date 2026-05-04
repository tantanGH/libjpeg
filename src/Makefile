# elf2x68k インストールパス
ifndef ELF2X68K_DIR
	ELF2X68K_DIR=/opt/homebrew/Cellar/elf2x68k/20260331
endif

# デフォルトサフィックスを削除
.SUFFIXES:

# 各種コマンド短縮名
CC = m68k-xelf-gcc
AS = m68k-xelf-as
AR = m68k-xelf-ar

# 出力アーカイブファイル名(picojpeg版)
TARGET_FILE = ../lib/libjpeg.a

# 出力アーカイブファイル名(stb_image版・要ハイメモリ・MPUタイプ別)
TARGET_FILE_STB_000 = ../lib/libjpegstb.a
TARGET_FILE_STB_030 = ../lib/libjpegstb030.a
TARGET_FILE_STB_060 = ../lib/libjpegstb060.a

# ヘッダ検索パス
INCLUDE_FLAGS = -I${ELF2X68K_DIR}/lib/gcc/m68k-elf/13.4.0/include \
				-I${ELF2X68K_DIR}/m68k-elf/include \
				-I./libs/libhimem/include \
				-I../include

# コンパイルフラグ
COMMON_FLAGS = -m68000 -O2 $(INCLUDE_FLAGS)
CFLAGS = $(COMMON_FLAGS) -fno-defer-pop -D__USE_PICOJPEG__

COMMON_FLAGS_STB_000 = -m68000 -O2 $(INCLUDE_FLAGS)
CFLAGS_STB_000 = $(COMMON_FLAGS_STB_000) -fno-defer-pop -D__USE_STB_IMAGE__

COMMON_FLAGS_STB_030 = -m68030 -O2 $(INCLUDE_FLAGS)
CFLAGS_STB_030 = $(COMMON_FLAGS_STB_030) -fno-defer-pop -D__USE_STB_IMAGE__

COMMON_FLAGS_STB_060 = -m68060 -O2 $(INCLUDE_FLAGS)
CFLAGS_STB_060 = $(COMMON_FLAGS_STB_060) -fno-defer-pop -D__USE_STB_IMAGE__

# *.c ソースファイル (picojpeg版)
C_SRCS = picojpeg.c jpeg.c

# *.c ソースファイル (stb_image版)
C_SRCS_STB = jpeg.c

# *.s ソースファイル
ASM_SRCS =

# *.h ヘッダーファイル (picojpeg版)
HEADER_SRCS = ../include/jpeg.h

# *.h ヘッダーファイル (stb_image版)
HEADER_SRCS_STB = ../include/jpeg.h stb_image.h

# リンク対象のライブラリファイル
LIBS =

# 中間ファイル生成用ディレクトリ (picojpeg版)
INTERMEDIATE_DIR = _build/elf2x68k

# 中間ファイル生成用ディレクトリ (stb_image版)
INTERMEDIATE_DIR_STB_000 = _build000/elf2x68k
INTERMEDIATE_DIR_STB_030 = _build030/elf2x68k
INTERMEDIATE_DIR_STB_060 = _build060/elf2x68k

# オブジェクトファイル (picojpeg版)
OBJS =	$(addprefix $(INTERMEDIATE_DIR)/,$(patsubst %.c,%.o,$(C_SRCS))) \
	    $(addprefix $(INTERMEDIATE_DIR)/,$(patsubst %.s,%.o,$(ASM_SRCS)))

# オブジェクトファイル (stb_image版)
OBJS_STB_000 = $(addprefix $(INTERMEDIATE_DIR_STB_000)/,$(patsubst %.c,%.o,$(C_SRCS_STB))) \
	           $(addprefix $(INTERMEDIATE_DIR_STB_000)/,$(patsubst %.s,%.o,$(ASM_SRCS)))
OBJS_STB_030 = $(addprefix $(INTERMEDIATE_DIR_STB_030)/,$(patsubst %.c,%.o,$(C_SRCS_STB))) \
	           $(addprefix $(INTERMEDIATE_DIR_STB_030)/,$(patsubst %.s,%.o,$(ASM_SRCS)))
OBJS_STB_060 = $(addprefix $(INTERMEDIATE_DIR_STB_060)/,$(patsubst %.c,%.o,$(C_SRCS_STB))) \
	           $(addprefix $(INTERMEDIATE_DIR_STB_060)/,$(patsubst %.s,%.o,$(ASM_SRCS)))

# デフォルトのターゲット
all : $(TARGET_FILE) $(TARGET_FILE_STB_000) $(TARGET_FILE_STB_030) $(TARGET_FILE_STB_060)

# 中間生成物の削除
clean : 
	rm -f $(TARGET_FILE) $(TARGET_FILE_STB_000) $(TARGET_FILE_STB_030) $(TARGET_FILE_STB_060)
	rm -rf $(INTERMEDIATE_DIR)
	rm -rf $(INTERMEDIATE_DIR_STB_000)
	rm -rf $(INTERMEDIATE_DIR_STB_030)
	rm -rf $(INTERMEDIATE_DIR_STB_060)

# アーカイブファイルの生成 (picojpeg版)
$(TARGET_FILE) : $(OBJS)
	$(AR) -rs ${TARGET_FILE} $(OBJS)

# アーカイブファイルの生成 (stb_image版)
$(TARGET_FILE_STB_000) : $(OBJS_STB_000)
	$(AR) -rs ${TARGET_FILE_STB_000} $(OBJS_STB_000)
$(TARGET_FILE_STB_030) : $(OBJS_STB_030)
	$(AR) -rs ${TARGET_FILE_STB_030} $(OBJS_STB_030)
$(TARGET_FILE_STB_060) : $(OBJS_STB_060)
	$(AR) -rs ${TARGET_FILE_STB_060} $(OBJS_STB_060)

# *.c ソースのコンパイル (picojpeg版)
$(INTERMEDIATE_DIR)/%.o : %.c Makefile $(HEADER_SRCS)
	mkdir -p $(INTERMEDIATE_DIR)
	$(CC) $(CFLAGS) -c $*.c -o $(INTERMEDIATE_DIR)/$*.o

# *.c ソースのコンパイル (stb_image版)
$(INTERMEDIATE_DIR_STB_000)/%.o : %.c Makefile $(HEADER_SRCS_STB)
	mkdir -p $(INTERMEDIATE_DIR_STB_000)
	$(CC) $(CFLAGS_STB_000) -c $*.c -o $(INTERMEDIATE_DIR_STB_000)/$*.o
$(INTERMEDIATE_DIR_STB_030)/%.o : %.c Makefile $(HEADER_SRCS_STB)
	mkdir -p $(INTERMEDIATE_DIR_STB_030)
	$(CC) $(CFLAGS_STB_030) -c $*.c -o $(INTERMEDIATE_DIR_STB_030)/$*.o
$(INTERMEDIATE_DIR_STB_060)/%.o : %.c Makefile $(HEADER_SRCS_STB)
	mkdir -p $(INTERMEDIATE_DIR_STB_060)
	$(CC) $(CFLAGS_STB_060) -c $*.c -o $(INTERMEDIATE_DIR_STB_060)/$*.o		