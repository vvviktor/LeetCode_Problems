## Решение задачи [37. Sudoku Solver](https://leetcode.com/problems/sudoku-solver/)

Как и следует из названия задачи, нам предлагают решить головоломку **Sudoku**, вернее, один из ее популярных вариантов.

![](Img/Sudoku-by-L2G-20050714.svg.png)

На вход поступает двумерный массив `char` размера 9 х 9, где пустые клетки обозначены символом ``` `.` ```.

Правила такие:
- В каждой строке числа от `1 - 9` встречаются строго по одному разу.
- В каждом столбце числа от `1 - 9` встречаются строго по одному разу.
- Это же правило касается каждого квадрата 3 х 3, которых на поле 9.

Решать задачу будем методом подбора, как и положено решать подобные головоломки. Продвигаясь слева направо сверху вниз, на каждом шаге будем пытаться поставить в свободную клетку число, которое не встречается ни в текущем ряду, ни в текущем столбце, ни в текущем квадрате. Если такого числа на этом шаге нет, откатимся на шаг назад, и для того шага попробуем следующее подходящее число, если оно есть. Если нет - еще на шаг назад, пока не удастся продолжить движение вперед. И таким образом дойдем до последней клетки с годным решением. 

Для этого нужно на каждом шаге точно знать какие числа уже использованы для каждого ряда, строки и квадрата. Я использую массивы целых чисел - 9 чисел для рядов, 9 - для столбцов, 9 - для квадратов - в которых с помощью битовых операторов включаю нужные биты, обозначая, что число "занято", то есть выставить его на клетку в соответствующем столбце, ряду и квадрате мы не можем.

Перед тем как приступить к решению потребуется составить карту уже присутствующих на поле чисел. То есть выставить нужные биты в рядах, столбцах и квадратах. Для этого использую метод `FillBoard()`, который, в свою очередь, вызывает метод `ToggleBit(y, x, k)`, переключающий бит из 0 в 1 и обратно оператором `^` или **XOR**. Для перевода координат в индексы служебных массивов, и для удобного доступа по индексам реализован метод `GetPtrs(y, x)`.

Непосредственно решением занимается метод `Solve(y, x)`, формирующий цепь рекурсивных вызовов, где каждый такой вызов - шаг вперед. Для проверки доступности очередного числа реализован метод `CanPut(y, x, k)`. Если нет доступных чисел, вызов завершается, происходит обратный ход рекурсии до момента, когда появляется возможность продвинуться вперед с другим числом. Успешным завершением всей цепи вызовов будет базовый случай - вызов `Solve(y, x)` для `y == 9, x == 0`, что означает выход на позицию следующюю после обработки правой нижней позиции.

Мое решение лежит [здесь](solution.cpp).