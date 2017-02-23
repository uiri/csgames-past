goal = 42
print "Plus ou moins ? (hint la reponse est "
print goal
print ")"
println
lu = goal + 1
while lu != goal && lu >= 0 (
        print "Votre choix: "
        lu = read
        if lu > goal ( print "c'est plus petit." println )
        if lu < goal ( print "c'est plus grand." println )
)
if lu = goal print "C'est bon." else print "Abandon"

println
