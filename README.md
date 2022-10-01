# ttgen
Truth Table Generator Compiller. Генератор таблиц иситинности для формул в троично-симметричной системе счисления.

Программа поддерживает как работу с файлом, так и интерактивный режим. Для работы с файлом необходимо передать имя файла и ключом `-S`.

Вводимая формула имеет вид `<имя формулы>(<переменные через запятую>):=<непосредственно формула>`. Имеется поддержка комментирования строк через `//`.

Операции:

- коньюнкиция `x & y`;
- дизьюнкция `x | y`;
- импликация `x -> y`;
- импликация по Брусенцову `x +> y`;
- сложение `x + y`;
- умножение `x * y`;
- исключающее или `x # y`;
- вычитание `x - y`;
- разность `x / y`;
- инверсия `~x`;
- инкремент `++x`;
- декремент `--x`.

Пример формулы `f(x,y):= (x & y) -> --(~y -> ~x)`.
