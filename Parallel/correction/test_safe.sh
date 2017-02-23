mkdir -p out
for i in tests/*.txt; do
	bn=`basename $i .txt`
	./bin/gol $i 10 > out/$bn.out_seq
	./bin/gol_para $i 10 > out/$bn.out_para
	diff out/$bn.out_seq out/$bn.out_para
done
