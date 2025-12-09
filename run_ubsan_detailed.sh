#!/bin/bash
# run_ubsan_detailed.sh

set -e

echo "=== Detailed UndefinedBehaviorSanitizer Test ==="

BUILD_DIR="ubsan_test"
rm -rf $BUILD_DIR
mkdir $BUILD_DIR
cd $BUILD_DIR

echo "Compiling with full UBSan checks..."

UBSAN_FLAGS="-fsanitize=undefined"
UBSAN_FLAGS+=" -fsanitize=null"              # Разыменование NULL
UBSAN_FLAGS+=" -fsanitize=alignment"         # Выравнивание
UBSAN_FLAGS+=" -fsanitize=bounds"            # Выход за границы массива
UBSAN_FLAGS+=" -fsanitize=object-size"       # Доступ к объекту некорректного размера
UBSAN_FLAGS+=" -fsanitize=float-divide-by-zero"  # Деление на ноль с плавающей точкой
UBSAN_FLAGS+=" -fsanitize=float-cast-overflow"   # Переполнение при приведении float
UBSAN_FLAGS+=" -fsanitize=nonnull-attribute" # Нарушение атрибутов nonnull
UBSAN_FLAGS+=" -fsanitize=returns-nonnull-attribute"
UBSAN_FLAGS+=" -fsanitize=bool"              # Загрузка значения не 0/1 в bool
UBSAN_FLAGS+=" -fsanitize=enum"              # Загрузка значения вне диапазона enum
UBSAN_FLAGS+=" -fsanitize=vla-bound"         # Неположительный размер VLA
UBSAN_FLAGS+=" -fsanitize=unreachable"       # Достижимость недостижимого кода
UBSAN_FLAGS+=" -fsanitize=shift"             # Неопределенные сдвиги
UBSAN_FLAGS+=" -fsanitize=signed-integer-overflow"  # Переполнение знаковых целых
UBSAN_FLAGS+=" -fno-sanitize-recover=all"    # Не пытаться восстанавливаться после ошибок
UBSAN_FLAGS+=" -fno-omit-frame-pointer"      # Для лучших стектрейсов

gcc $UBSAN_FLAGS \
    -g -O1 \
    -Wall -Wextra -std=c11 \
    ../test_stack.c ../stack.c \
    -o ubsan_test

echo "Compilation successful!"
echo ""
echo "Running tests with UBSan..."

echo "========================================"
./ubsan_test
TEST_EXIT_CODE=$?
echo "========================================"

if [ $TEST_EXIT_CODE -eq 0 ]; then
    echo "All tests passed with UBSan"
    echo "No undefined behavior detected"
else
    echo " Tests failed or undefined behavior detected"
    echo "Exit code: $TEST_EXIT_CODE"

    if [ $TEST_EXIT_CODE -eq 1 ]; then
        echo "This typically indicates sanitizer found an issue"
    fi
fi

echo ""
echo "Testing main program..."
gcc $UBSAN_FLAGS \
    -g -O1 \
    -Wall -Wextra -std=c11 \
    ../main.c ../stack.c \
    -o ubsan_main

echo "Running main program..."
echo "========================================"
./ubsan_main
MAIN_EXIT_CODE=$?
echo "========================================"

if [ $MAIN_EXIT_CODE -eq 0 ]; then
    echo "Main program passed UBSan checks"
else
    echo "Main program has issues"
fi

cd ..
echo ""
echo "=== UBSan testing completed ==="
