## Решение задачи [1326. Minimum Number of Taps to Open to Water a Garden](https://leetcode.com/problems/minimum-number-of-taps-to-open-to-water-a-garden/description/)

Представьте себе одномерный сад длины `n`. Да, этого ходят от нас авторы задачи. Тут все просто: пусть будет не сад, а огород; допустим, что огород двумерный, и в нем на каждой позиции от `0` до `n - 1` включительно параллельно друг другу расположены грядки, длина которых нас не интересует. Мы видим огород сбоку так, чтобы видеть все грядки. С этого момента второе измерение нас не интересует - сад одномерный. 

В этом одномерном саду на каждой позиции расположены установки для полива. У каждой установки есть диапазон охвата, включающий позиции сада, которые она способна полить. Этот диапазон может быть равен `0`, в этом случае можно считать, что установка не работает. Эти диапазоны даны в виде **радиуса** охвата в массиве `ranges[]`, где `ranges[i]` - радиус охвата поливалки для позиции `i` от `0` до `n - 1`. Полным охватом установки будет диапазон `[i - ranges[i], i + ranges[i]]` включительно. Все грядки в этом диапазоне будут считаться политыми этой установкой.

![](Img/1685_example_1.png)

Требуется, используя информацию о существующих поливальных установках, найти минимальное их **количество**, достаточное для полива всего сада.

То есть диапазоны соседних включенных установок должны **пересекаться**, и начало полива следующей установки не должно быть больше окончания полива предыдущей. Эти диапазоны **не** пересекаются: `[-3, 3], [4, 10], [12, 14]`, а эти - **пересекаются**: `[-8, 8], [-9, 9], [9, 11], [0, 10], [-1, 13]`.

Если нам попалось условие, при котором невозможно перекрыть весь сад пересекающимися диапазонами, программа должна вернуть `-1`.

Что говорит интуиция? Из всего множества пересекающихся диапазонов нужно выбрать те, последовательное расположение которых слева направо, позволит нам достичь правой границы за минимальное количество шагов. 

Создадим массив диапазонов в виде пар `[l, r]` где `l` левая включающая граница диапазона, а `r` - правая включающая. Отсортируем его по левой границе в неубывающем порядке. Заведем две переменные `curr_end` и `next_end`. В `curr_end` будет храниться правая включающая граница уже политого сада, в `next_end` - самая дальняя правая граница уже рассмотренных диапазонов. Понадобится также счетчик включенных установок `cnt`. 

- Для хранения отсортированных диапазонов я использую приоритетную очередь `q`.
- Инициализируем `curr_end = 0` и `next_end = 0`. Счетчик `cnt = 1`, так как на первой итерации `next_end` станет равен правой границе первого диапазона. То есть сад мы уже начали поливать.
- В цикле по отсортированным диапазонам, будем пытаться максимально отодвинуть вправо `next_end` рассматривая правую границу очередного диапазона, а `curr_end` будем обновлять на актуальный `next_end` в случае, если левая граница очередного рассматриваемого диапазона больше `curr_end`. Также в последнем случае нужно будет увеличить `cnt` на единицу.
- Если очередной диапазон разрывает уже сложившуюся непересекающуюся последовательность, то есть его левая граница больше `next_end`, завершаем программу, возвращаем `-1`.

Идеоматически такое решение относится к [жадным алгоритмам](https://ru.wikipedia.org/wiki/Жадный_алгоритм).

Мое решение с сортировкой [здесь](sort_solution.cpp). 