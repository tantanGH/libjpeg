# libjpeg
A simple JPEG library for X68k

---

 - picojpeg - Public domain, Rich Geldreich <richgel99@gmail.com>

 - stb_image - v2.30 - public domain image loader - http://nothings.org/stb

---

elf2x68k環境向けのJPEGデコードCライブラリです。
 - デコードエンジンとしてコンパクトで省メモリなpicojpeg、高速なstb_imageを採用させて頂いています
 - 768x512, 65536色モードでの表示を想定
 - 任意サイズのスケーリングおよび自動フィット(長辺を512にあわせる)をサポート
 - テキストプレーン2を使ったマスク処理関数も提供
 - プログレッシブJPEGはstb_image版のみ対応

```
#include <jpeg.h>

void jpeg_crtmod_768x512_65536();
void jpeg_fill_text_masks();
void jpeg_open_text_masks();
void jpeg_reset_text_masks();

int32_t jpeg_open(JPEG* jpeg, int16_t brightness);
int32_t jpeg_draw(JPEG* jpeg, uint8_t* buffer, size_t size, int16_t scale_mode);
void jpeg_close(JPEG* jpeg);
```

- JPEGデータは既にメモリ上にあることが前提です。
- scale_mode は1~100を指定するとその倍率でセンタークリップ、0を指定すると長辺が512に自動フィットします

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
│       ├── lib/libjpeg.a
│       ├── lib/libjpegstb000.a
│       ├── lib/libjpegstb030.a
│       └── lib/libjpegstb060.a
└── src/
    ├── main.c
    └── Makefile
```

ヘッダー検索パスとライブラリ検索パスをMakefile内で
```
-I../libs/libjpeg/include
-L../libs/libjpeg/lib
```
のように指定し、`-ljpeg` でリンクできます。この場合は省メモリのpicojpeg版となります。

高速なstb_image版を使う場合はハイメモリが必須となります。拙作 libhimem も必要となります。また、一部で数学関数を使うため `-lm` の指定も必要となります。
 * -ljpegstb000 -lhimem -lm
 * -ljpegstb030 -lhimem -lm
 * -ljpegstb060 -lhimem -lm

 といった形でリンクしてください。000は全機種対応、030は68030以上、060は68060専用です。 

--
//------------------------------------------------------------------------------
// picojpeg.c v1.1 - Public domain, Rich Geldreich <richgel99@gmail.com>
// Nov. 27, 2010 - Initial release
// Feb. 9, 2013 - Added H1V2/H2V1 support, cleaned up macros, signed shift fixes 
// Also integrated and tested changes from Chris Phoenix <cphoenix@gmail.com>.
//------------------------------------------------------------------------------

--

/*
------------------------------------------------------------------------------
This software is available under 2 licenses -- choose whichever you prefer.
------------------------------------------------------------------------------
ALTERNATIVE A - MIT License
Copyright (c) 2017 Sean Barrett
Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
of the Software, and to permit persons to whom the Software is furnished to do
so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
------------------------------------------------------------------------------
ALTERNATIVE B - Public Domain (www.unlicense.org)
This is free and unencumbered software released into the public domain.
Anyone is free to copy, modify, publish, use, compile, sell, or distribute this
software, either in source code form or as a compiled binary, for any purpose,
commercial or non-commercial, and by any means.
In jurisdictions that recognize copyright laws, the author or authors of this
software dedicate any and all copyright interest in the software to the public
domain. We make this dedication for the benefit of the public at large and to
the detriment of our heirs and successors. We intend this dedication to be an
overt act of relinquishment in perpetuity of all present and future rights to
this software under copyright law.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
------------------------------------------------------------------------------
*/
