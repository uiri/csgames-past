c1 = -1
c2 = read byte
c3 = read byte
while c2 >= 0 (
	o = c2

	if 'A <= o <= 'Z (
		o = o - 'A + 'a
		if 'a <= c1 <= 'z print "_"
		else if 'A <= c1 <= 'Z && 'a <= c3 <= 'z print "_"
	)
	print byte o

	c1 = c2
	c2 = c3
	c3 = read byte
)
