# MicroMouse-2025
Robot for robo-maze on olymp robofinist

### Фото и описание робота
https://vk.com/wall381491469_557

### Робот был сконструирован для реализации следующих экспериментов:
1) Малая конструкция, которая легко перемещается в лабиринте (и эксперимент на полностью деревянной конструкции)
2) Использование лазерных дальномеров
3) Проверка контроллера Avocado Uno v0.2 (и периверии) в данной задаче
4) Реализация картографирования и одновременной деикстры, для максимально эффективного поиска пути к финишу

### Робофинист 2025.03.15
В результате дописывания на месте и тестов было выяснено:
1) Лазерные дальномеры в целом работают достаточно эффективно, можно выносить в отдельную библиотеку, но стоит добавить поправочные коэффициенты по формуле y=kx+b (зависимость визуально была линейная) или map, для более точных значений, и возможно автоматическую калибровку
2) Лазерные дальномеры для данного проекта очень медленные, из-за чего невозможно на больших скоростях управлять роботом
3) Все конкуренты использовали ИК датчики (дальномеры) для ориентирования в лабиринте https://robototehnika.ru/e-store/catalog/409/
4) Также некоторые использовали гироскопы, что упрощало ориентирование в лабиринте
5) Робот очень быстрый и в том числе из-за вышеперечисленных причин неуправляемый на большой скорости, из-за чего ездил на 20 процентах скорости, но косяки конструкции тоже имеют место
6) Робот очень массивный для этой номинации, но свои цели (а именно эксперименты датчиков, контроллера, питания алгоритмов) - полностью себя оправдал и дал необходимый опыт
7) В ExtraMazesolver было реализовано картографироание (как выяснилось метод exploreCell требует доработок) и поиски кратчайших путей на основе алгоритма левой руки и деикстры (в полной мере не оттестировано), но после доработок должно показывать хорошие результаты
8) С контроллером Avocado Uno v0.2 + моторшилд HNR-252 DCv0.1 + пара самодельных расширений - не подвело, все работало корректно и без сбоев в олимпиадных условиях
9) После доработок робот может справиться с выполнением своей задачи (доезд до финиша, максимально эффективным способом), но самым быстрым (в виду вышеперечисленных причин) в данной конфигурации стать не сможет

