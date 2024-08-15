Примеры сообщений выводимых данной программой:

Этот файл не содержит ни одного из признаков ZIP-архива:
1) Сигнатура Local file headers "\x50\x4b\x03\x04" отсутствует.
2) Сигнатура Central directory file header "\x50\x4b\x01\x02" отсутствует.
3) Сигнатура End of central directory record "\x50\x4b\x05\x06" отсутствует.

Этот файл содержит два признака ZIP-архива:
1) Сигнатура Local file headers "\x50\x4b\x03\x04" присутствует.
2) Сигнатура Central directory file header "\x50\x4b\x01\x02" присутствует.
3) Сигнатура End of central directory record "\x50\x4b\x05\x06" отсутствует.

Т.к. Сигнатура End of central directory record "\x50\x4b\x05\x06" отсутствует то данный файл является сломанным или битым ZIP-архивом.