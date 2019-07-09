# Questions

## What's `stdint.h`?

Library that allow you to declare well defined types.

## What's the point of using `uint8_t`, `uint32_t`, `int32_t`, and `uint16_t` in a program?

It allow us to work with this variables in the way it is intended to by bmp standart

## How many bytes is a `BYTE`, a `DWORD`, a `LONG`, and a `WORD`, respectively?

1,4,4,2

## What (in ASCII, decimal, or hexadecimal) must the first two bytes of any BMP file be? Leading bytes used to identify file formats (with high probability) are generally called "magic numbers."

BM

## What's the difference between `bfSize` and `biSize`?

https://docs.microsoft.com/en-us/windows/desktop/api/wingdi/ns-wingdi-tagbitmapfileheader
The size, in bytes, of the bitmap file.
vs
https://docs.microsoft.com/en-us/previous-versions//dd183376(v=vs.85)
The number of bytes required by the structure.

## What does it mean if `biHeight` is negative?

https://docs.microsoft.com/en-us/previous-versions//dd183376(v=vs.85)
bitmap is a top-down DIB and its origin is the upper-left corner.

## What field in `BITMAPINFOHEADER` specifies the BMP's color depth (i.e., bits per pixel)?

biBitCount

## Why might `fopen` return `NULL` in `copy.c`?

if there is no file with opening name

## Why is the third argument to `fread` always `1` in our code?

because there is only one read one data element with the size of sizeof(BITMAPINFOHEADER);

## What value does `copy.c` assign to `padding` if `bi.biWidth` is `3`?

3

## What does `fseek` do?

position to the special place in the stream

## What is `SEEK_CUR`?

set current position of the file pointer 
