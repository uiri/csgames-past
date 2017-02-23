if args.length < 2 then
	print "Usage: ./test_gen mat_sz out_file"
	exit 1
end
var iters = args[0].to_i
var out = new FileWriter.open(args[1])
out.write(args[0])
out.write "\n"
var bf = new FlatBuffer.with_capacity(iters + iters - 1)
for i in [0 .. iters[ do
	for j in [0 .. iters[ do
		var rnd = 5.rand
		if rnd >= 3 then
			bf.add 2.rand.to_c
		else
			bf.add '0'
		end
	end
	out.write bf
	out.write "\n"
	bf.clear
end
out.close
