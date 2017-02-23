in = read byte

while in > 0 (
	if in != 10 (
		if 'A <= in <= 'Z print "Is a capital letter"
		else if 'a <= in <= 'z print "Is a small letter"
		else print "Is not a letter"
		print byte 10
	)
	in = read byte
)
