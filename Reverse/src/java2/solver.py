import string
import sys

result = 1196601068455751604172765025142834742772692164339541821505998319783121
origin = 33
out = []


while True:
    found = False

    for c in string.ascii_letters + '{_}' + string.digits:
        print result - ord(c)

        if (result - ord(c)) % 97 == 0:
            found = True
            result -= ord(c)
            result /= 97
            out.append(c)
            print c

            if result == origin:
                print ''.join(out)[::-1]
                sys.exit()

            break 

    if not found:
        print "No password found"
        break
