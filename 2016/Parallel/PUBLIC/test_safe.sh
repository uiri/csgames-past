mkdir -p out
if [ -f ./C/bin/GOL ]; then
	for i in tests/*.in; do
		bn=`basename $i .in`
		./C/bin/GOL $i 10 b > out/$bn.out
		diff out/$bn.out tests/$bn.res
	done
fi

if [ -f ./CPP/bin/GOL ]; then
	for i in tests/*.in; do
		bn=`basename $i .in`
		./CPP/bin/GOL $i 10 b > out/$bn.out
		diff out/$bn.out tests/$bn.res
	done
fi
