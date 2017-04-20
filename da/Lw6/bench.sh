make
python tests_generator.py $1

for i in `seq 5`;
    do ./Lw6 < 0${i}.t > answer ;
    echo "$i\t" ;
    grep time answer
    python3 benchmark.py < 0${i}.t > answerPy ;
    grep time answerPy
done