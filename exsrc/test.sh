for ((i=2;i<=20;++i))
do
	echo Running main
	./main -n $i >1.out --no-pic
	echo Running slow
	./slow -n $i >2.out
	diff 1.out 2.out
	if [ $? != 0 ]; then
		echo $i Error
		exit
	else
		echo $i SAME
		rm 1.out 2.out
	fi
done
