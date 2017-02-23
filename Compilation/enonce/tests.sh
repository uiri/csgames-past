test -d out || mkdir out

for source in "$@"; do
	bn=`basename "$source" .m`
	input=programs_inputs/"$bn".input
	test -e "$input" || input=/dev/null
	output=out/"$bn".output
	sav=programs_output/"$bn".output
	echo "* $source"
	java -classpath bin Interpret "$source" < "$input" > "$output"
	if diff "$output" "$sav"; then
		:
	else
		echo "  -> failed $source"
	fi
done
