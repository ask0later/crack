# HACKING
Этот проект показывает разные способы взлома программы оппонента.

## Программа
Программа написана на ассемблере. Она принимает от пользователя пароль. В случае если он верный, программа вызывает функцию предоставления доступа(которая просто пишет в консоль "доступ выдан"), иначе вызывает функцию, которая пишет в консоль "доступ отвергнут". После считывания пароля вычисляется его хеш через алгоритм GNU HASH и сравнивается с хешом настоящего пароля. 
В прорамме присутствует уязвимость, из-за которой может случится переполнение буффера через ввод пароля и, следовательно, неопределенное поведение.
[pic1]

## Взлом оппонента через переполнение
В нашем распоряжении исполняемый файл программы противника. Его программа имеет ту же уязвимость. При вводе пароля, не контролируется количество символов, поэтому буффер, выделенный под этот пароль, может закончится и тогда мы начнем изменять данные после буффера. В этом и заключается способ взламывания через переполнение. Анализируя программу через дизассемблер, можно, например, убрать условие проверки пароля, чтобы в любом случае вызывалась функция предоставления доступа.


## Взлом оппонента таблеткой
Чтобы не переписывать все байты программы от начала буффера пароля до места кода, где мы хотим поменять байт, можно взломать более простым способом. Заключается он в том, чтбы написать программу (например, на Си), которая заменяет в файле некоторые байты на другие. Для этого только требуется посчитать количество байтов от начала программы до нужного места.

