# -*- coding: utf-8 -*-

import sys
import os

# Specify C compiler
cc = "gcc"

# Specify compiling options
cflags = [
          # GNU C11 standard
          "-std=gnu11",
          
          # optimization option
          "-Os"
          ]


includes = [
            "./"
            ]

# sources
srcs = [
        "unix_main.c",
        "zenny_foundation/zenny_foundation.c",
        "zenny_foundation/zf_atomic.c",
        "zenny_foundation/zf_memory.c",
        "zenny_foundation/zf_number.c",
        "zenny_foundation/zf_single_link_table.c",
        "zenny_foundation/zf_uchar.c",
        
        "zenny_foundation/zf_sys/zf_directory.c"
        ]

build_shell = cc + ' '

# append cflags
for flag in cflags:
    build_shell += flag + ' '

# append includes
for include in includes:
    build_shell += '-I' + include + ' '

#append sources
for src in srcs:
    build_shell += src + ' '

# specify the output executable
build_shell += "-o zf-test"

os.system(build_shell)

