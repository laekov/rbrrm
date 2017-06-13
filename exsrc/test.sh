for ((i=2;i<=40;++i))
do
	echo Running main
	./main -n $i -detail >testd/main$i\.out
	echo Running slow
	./slow -n $i >testd/slow$i\.out
done
exit
for ((i=2;i<=40;++i))
	diff 1.out 2.out
	if [ $? != 0 ]; then
		echo $i Error
		exit
	else
		echo $i SAME
		rm 1.out 2.out
	fi
done
