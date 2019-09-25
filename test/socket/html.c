#include "html.h"

char html_buf1[300]=
"HTTP/1.1 200 OK \r\n  \
Server: MySocket Server\r\n\
Date: TEST\r\n\
Content-Type: text/html\r\n\
Content-Length: %d\r\n\
Connection: close\r\n\
Accept-Ranges: bytes\r\n\r\n\
";
char html_buf2[200]=
"<!DOCTYPE html><html><head><meta charset=\"utf-8\"><title>01234(runoob.com)</title></head><body><h1>1234</h1><p>4567890</p></body></html>";


