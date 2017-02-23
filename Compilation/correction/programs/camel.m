ca = -1
cb = read byte
cc = read byte
while cb >= 0 (
	o = cb

	if 'A <= o <= 'Z (
		o = o - 'A + 'a
		if 'a <= ca <= 'z print "_"
		else if 'A <= ca <= 'Z && 'a <= cc <= 'z print "_"
	)
	print byte o

	ca = cb
	cb = cc
	cc = read byte
)
