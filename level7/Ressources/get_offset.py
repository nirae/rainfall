#!/usr/bin/env python3

import sys

if len(sys.argv) < 2:
    sys.exit()

arg = bytes.fromhex(sys.argv[1])
result = arg.decode("ASCII")
print("%s => offset = %d" % (result, (ord(result[0]) - 65) * 4))
