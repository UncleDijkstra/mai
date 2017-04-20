# g++ -std=c++11 bigint.cpp
make
python tests_generator.py 10000

for i in `seq 6`;
    do ./Lw6 < 0${i}.t > answer ;
    status="Fail";
    if diff -u 0${i}.a answer ;
        then status="OK";
    fi;

echo "$i $status" ;
done