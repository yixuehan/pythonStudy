// Created by cgo - DO NOT EDIT

//line cgo.go:1
package main

/*
#include <stdio.h>
static void SayHello(const char* s) {
puts(s);
}
*/
import _ "unsafe"

func main() {
	(_Cfunc_SayHello)((_Cfunc_CString)("Hello, World\n"))
}
