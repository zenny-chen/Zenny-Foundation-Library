# -*- coding: utf-8 -*-

import sys
import os

# Fetch the current platform
platforms = ["linux", "win32", "cygwin", "freebsd", "darwin"]
currPlatform = sys.platform
foundPlatform = False
for p in platforms:
    if currPlatform.startswith(p):
        currPlatform = p
        foundPlatform = True

if not foundPlatform:
    currPlatform = "others"

print("Current platform: " + currPlatform)

# Specify C compiler
cc = "gcc"

# Specify compiling options
cflags = [
          # GNU C11 standard
          "-std=gnu11",
          
          # optimization option
          "-Os"
          ]

# For Apple platforms we just use Objective-C with Cocoa framework
if currPlatform == "darwin":
    cflags.append("-x objective-c -fmessage-length=0 -fmacro-backtrace-limit=0 -fobjc-weak -fmodules -gmodules -fmodules-prune-interval=86400 -fmodules-prune-after=345600 -fno-common -fno-objc-exceptions -fasm-blocks -fstrict-aliasing")


includes = [
            "./",
            "./zenny_foundation/",
            "./zenny_foundation/zf_sys/"
            ]

# sources
srcs = [
        "unix_main.c",
        "zenny_foundation/zenny_foundation.c",
        "zenny_foundation/zf_memory.c",
        "zenny_foundation/zf_number.c",
        "zenny_foundation/zf_single_link_table.c",
        
        "zenny_foundation/zf_sys/zf_atomic.c",
        "zenny_foundation/zf_sys/zf_sync.c",
        "zenny_foundation/zf_sys/zf_uchar.c",
        "zenny_foundation/zf_sys/zf_directory.c"
        ]

# For Apple platforms we just use Objective-C with Cocoa framework
if currPlatform == "darwin":
    appleSrcs = [
        "zenny_foundation/zf_sys/zf_directory_apple.m",
        "zenny_foundation/zf_sys/zf_uchar_apple.m"
    ]
    
    srcs.extend(appleSrcs)

# Compose the build shell coomand line
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

