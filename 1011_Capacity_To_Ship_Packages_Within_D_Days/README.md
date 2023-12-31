## Решение задачи [1011. Capacity To Ship Packages Within D Days](https://leetcode.com/problems/capacity-to-ship-packages-within-d-days/)

Существует конвейер с контейнерами, которые требуется отправить в другой порт в течение `days` дней в той последовательности, в которой они расположены на конвейере. Пусть порядковым номером контейнера на конвейере будет `i` от 0 до `n`. Нам дан массив `weights` длины `n`, где `weights[i]` - вес контейнера с номером `i`. На корабль одновременно можно погрузить несколько контейнеров так, чтобы их суммарный вес не превышал максимально допустимого для данного корабля. Нас просят найти **минимальную** грузоподъемность корабля достаточную для транспортировки всех контейнеров в течение `days` дней. Корабль делает **один** рейс в день.

То есть, нужно представить себе, что у нас есть **один** корабль, который последовательно перевезет контейнеры различного веса в порядке их нумерации. Контейнеры могут перевозиться группами, суммарный вес которрых не превышает грузоподъемности корабля. Группы могут формироваться только из **последовательно** снятых с конвейера контейнеров. Нам дана возможность сформировать максимально `days` групп для перевозки всех контейнеров.

Здесь можно заметить, что если грузоподъемности корабля **не хватает**, чтобы перевезти весь груз за указанное количество рейсов, то и для **меньшей** грузоподъемности ответ также будет отрицательный: корабль не справится за указанный срок. С другой стороны, если грузоподъемность **достаточна** для выполнения работы, то и дальнейшее ее **увеличение** приведет также к успешному выполнению миссии. Напишем функцию, проверяющую все доступные нам значения грузоподъемности корабля для перевозки в течение `days` дней, отвечающую на вопрос будут ли перевезены все контейнеры. 

Я назвал функцию `Check(max_weight, days)`. Она просто последовательно суммирует вес контейнеров пока результат не превышает `max_weight`, затем уменьшает счетчик `days` на единицу, и продолжает перебирать контейнеры, повторяя тот же алгоритм, пока либо контейнеры не закончатся - результат `true`, либо дни - результат `false`, если остались необработанные контейнеры.

В качестве минимального значения грузоподъемности удобно взять вес самого легкого контейнера. А максимумом пусть будет суммарный вес всех контейнеров. Представим, что мы последовательно посчитали результат функции `Check()` от минимума до максимума для данного количества дней. Если расположить результаты слева направо, слева будут отрицательные значения, а с какого-то момента результат станет положительным, и правее все результаты также будут положительными. То есть при движении слева направо возможен только переход из отрицательных значений в положительные, а при движении справа налево - из положительных в отрицательные. Это свойство расположения данных называется **монотонностью**. Для поиска границы перехода отлично подходит **бинарный поиск**. Нам нужно найти **минимальное** значение `max_weight`, дающее **положительный** результат. То есть **левую** границу положительных значений.

Мой код, отвечающий за бинарный поиск левой границы положительных значений выглядит так:

```
while (min < max) {
    int mid = min + ((max - min) >> 1);
    if (Check(weights, mid, days)) {
        max = mid;
    } else {
        min = mid + 1;
    }
}
```

Берем середину диапазона возможной предельной грузоподъемности `mid = min + ((max - min) >> 1)`, проверяем в какой части множества результатов находится ответ `Check(mid, days)`. Если в положительной - сдвигаем влево правую границу, цель левее. Если в отрицательной - сдвигаем вправо левую границу, цель правее. Есть еще вариан, что цель непосредственно `mid`. В любом случае, это значение не потеряется, а когда границы `min` и `max` сойдутся, ответ будет равен любой из них.

Полностью мое решение находится [здесь](solution.cpp).