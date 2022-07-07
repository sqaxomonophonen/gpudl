#!/usr/bin/env python3

import sys
if len(sys.argv) != 2:
	sys.stderr.write("Usage: %s <path/to/keysymdef.h>\n" % sys.argv[0])
	sys.stderr.write("/usr/include/X11/keysymdef.h on my end\n")
	sys.exit(1)

# source: /usr/include/X11/keysym.h
whitelist = set([
	"XK_MISCELLANY",
	"XK_XKB_KEYS",
	"XK_LATIN1",
	"XK_LATIN2",
	"XK_LATIN3",
	"XK_LATIN4",
	"XK_LATIN8",
	"XK_LATIN9",
	"XK_CAUCASUS",
	"XK_GREEK",
	"XK_KATAKANA",
	"XK_ARABIC",
	"XK_CYRILLIC",
	"XK_HEBREW",
	"XK_THAI",
	"XK_KOREAN",
	"XK_ARMENIAN",
	"XK_GEORGIAN",
	"XK_VIETNAMESE",
	"XK_CURRENCY",
	"XK_MATHEMATICAL",
	"XK_BRAILLE",
	"XK_SINHALA",
])

tabs=5*"\t"

print(tabs + "// auto-generated with `%s`" % (" ".join(sys.argv)))

with open(sys.argv[1]) as f:
	ps = []
	max_sym_length = 0
	seen = set()

	visstack = [True]

	for line in f.readlines():
		line = line.strip()

		if line.startswith("#ifdef "):
			xs = line.split()
			symbol = xs[1]
			visstack.append(symbol in whitelist)
			continue

		if line.startswith("#endif"):
			visstack.pop()
			continue

		if not visstack[-1]: continue # skip sections not #define'd

		if not line.startswith("#define XK_"): continue
		if not "U+" in line: continue

		ss = line.split()
		value = int(ss[2][2:],16)
		if value in seen: continue
		seen.add(value)
		sym = ss[1]
		i = line.find("U+")
		assert(i >= 0)
		cp = line[i+2:i+6].strip()
		i2 = line.find("*/")
		comment = ""
		if i2 != -1:
			comment = " / " + line[i+7:i2].strip()
		assert(len(cp) == 4)
		ps.append((sym,value,cp, comment))
		max_sym_length = max(max_sym_length, len(sym))

	for p in ps:
		sym, value, cp, comment = p[0], p[1], p[2], p[3]
		if int(cp,16) < 0x100: continue
		print(tabs + "case %s: ks = 0x%s; break; // %s%s" % (hex(value), cp, sym, comment))

