import sys
s = "4nt1_D3bugg3rs_4r3nt_So_B4d_Aft3r_All_R1ght?"

xor_bytes = [0xd1, 0xee, 0xd9]

print "int xor_bytes[%d] = {" % len(s)

for i, c in enumerate(s):
    b = xor_bytes[i % len(xor_bytes)] ^ ord(c)
    sys.stdout.write("0x{:02x}".format(b) + ", ")

    if (i + 1) % 16 == 0:
        print ""

print ""
print "}"
