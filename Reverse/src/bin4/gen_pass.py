import sys
s = "I_W1sh_I_H4d_IDA_inst4lled_But_Wh0_C4n_4ff0rd_Th4t"

xor = 0xd1
result = 0xd1


print "int xor_bytes[%d] = {" % len(s)

for i, c in enumerate(s):
    xor = result ^ ord(c)
    result ^= xor

    sys.stdout.write("0x{:02x}".format(xor) + ", ")

    if (i + 1) % 16 == 0:
        print ""

print ""
print "}"
