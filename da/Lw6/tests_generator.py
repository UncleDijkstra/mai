# -*- coding: utf-8 -*-

import sys
import random

# Максимально возможное значение числа.
MAX_VALUE = 10 ** 50
MIN_VALUE = 1

def get_random_nums():
    return random.randint(MIN_VALUE, MAX_VALUE), random.randint(MIN_VALUE, MAX_VALUE)

def get_answer( num1, num2, operation ):
    if operation == "+":
        return str( num1 + num2 )
    elif operation == "-":
        if num1 >= num2:
            return str( num1 - num2 )
        else:
            return str( "Error" )
    elif operation == "*":
        return str( num1 * num2 )
    elif operation == "/":
        if num2 == 0:
            return str( "Error" )
        else:
            return str( num1 / num2 )
    elif operation == "<":
        # num1 < num2 вернёт True или False, чтобы
        # получить 1 или 0, то сначала необходимо
        # привести его к int'у, а потом уже в строку.
        return str("true" if num1 < num2 else "false")
    elif operation == "^":
        return str(num1 ** num2)

if __name__ == "__main__":
    # Ожидаем, что будет два аргумента: название программы и
    # количество тестов.
    if len( sys.argv ) != 2:
        print "Usage: %s <tests count>" % sys.argv[0]
        sys.exit(1)
    
    # Считываем количество тестов для каждой операции.
    tests_count = int( sys.argv[1] )

    # Пробегаемся по операция, для которых мы хотим
    # сгенерировать тесты.
    for enum, operation in enumerate( [ "+", "-" , "*", "/" , "<", "^" ] ):
        # Открываем файлы для записи самих тестов и ответов 
        # к ним.
        test_file = open( '%02d.t' % ( enum + 1 ), 'w' )
        answer_file = open( '%02d.a' % ( enum + 1 ), 'w' )

        for i in range(0, tests_count):
            # Генерируем рандомные числа.
            num1, num2 = get_random_nums()
            if operation == "^":
                num2 = random.randint(0, 100)
            # Записываем в файл получившийся тест.
            test_file.write( "%d\n%d\n%s\n" % ( num1, num2, operation ) )
            # Получаем ответ в виде строки и записываем его
            # в файл с ответами.
            answer = get_answer( num1, num2, operation )
            answer_file.write( "%s\n" % answer )
        test_file.close()
        answer_file.close()