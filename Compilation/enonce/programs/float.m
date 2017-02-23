lu = read byte
while lu >= 0 if lu = '. || '0 <= lu <= '9 (
	zs = 0
	while lu = '0 (
		zs = zs + 1
		lu = read byte
	)
	exp = 0
	incexp = 1
	if lu = '. (
		incexp = 0
		lu = read byte
		while lu = '0 (
			zs = zs + 1
			exp = exp - 1
			lu = read byte
		)
	)
	if '1 <= lu <= '9 (
		print "0."
		zs = 0
		stop = 0
		while stop = 0 (
			if lu = '. && incexp = 1 incexp = 0
			else if '1 <= lu <= '9 (
				while zs > 0 ( print "0" zs = zs - 1 )
				exp = exp + incexp
				print byte lu
			) else if lu = '0 (
				exp = exp + incexp
				zs = zs + 1
			) else stop = 1
			if stop = 0 lu = read byte
		)
		if exp != 0 ( print "e" print exp )
	) else if zs = 0 print "." else print "0"
) else (
	print byte lu
	lu = read byte
)
