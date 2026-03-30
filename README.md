# libjpeg
A simple JPEG library for X68k

---

picojpeg - Public domain, Rich Geldreich <richgel99@gmail.com>

---

elf2x68k環境向けのJPEGデコードCライブラリです。
 - デコードエンジンとしてコンパクトなpicojpegを採用させて頂いています
 - 768x512, 65536色モードでの表示を想定
 - 任意サイズのスケーリングおよび自動フィット(長辺を512にあわせる)をサポート
 - テキストプレーン2を使ったマスク処理関数も提供

```
#include <jpeg.h>

void jpeg_set_crt_768x512_65536_mode();
void jpeg_fill_text_masks();
void jpeg_open_text_masks();
int32_t jpeg_open(JPEG* jpeg, int16_t brightness);
void jpeg_close(JPEG* jpeg);
int32_t jpeg_draw(JPEG* jpeg, uint8_t* buffer, size_t size, int16_t scale_mode);
```

使う時は、サブモジュールとして組み込むのが簡単です。例えばプロジェクト直下にて以下を実行します。

```
git submodule add https://github.com/tantanGH/libjpeg.git libs/libjpeg
```

以下のようなツリーとなります。

```
my_app/
├── .git/
├── .gitmodules
├── libs/
│   └── libjpeg/
│       ├── include/jpeg.h
│       └── lib/libjpeg.a
└── src/
    ├── main.c
    └── Makefile
```

ヘッダー検索パスとライブラリ検索パスをMakefile内で
```
-I../libs/libjpeg/include
-L../libs/libjpeg/lib
```
のように指定し、`-ljpeg` でリンクできます。