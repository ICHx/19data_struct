#!/bin/sh
clang -S -emit-llvm prj2-nov.c
lli prj2-nov.s
