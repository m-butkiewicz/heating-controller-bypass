# Awaryjne obejście sterowania pompy c.o.

## Zasada działania

Celem utworzenia projektu było ominięcie układu wadliwego sterownika pieca c.o. i przejęcie sterowania pompą. 

Oryginalny sterownik pieca z nieznanych przyczyn co pewien nieregularny czas przestawał prawidłowo funkcjonować. Efektem był brak sterowania pompą i doprowadzenie do wrzenia wody w układzie grzewczym.

Wykonany układ posiada oddzielny czujnik ([LM35][lm]) mierzący temperaturę wody w układzie. Gdy ta temperatura przekroczy minimalną zaprogramowaną wartość 35&deg;C i nie zostanie wykryte działanie oryginalnego sterownika, układ samoistnie załączy pompę. Zapobiegnie to przegrzaniu się wody.

## Obsługa i dodatkowe uwagi

Układ działa automatycznie po poprawnym podłączeniu. Aktualną temperaturę można odczytać 7-segmentowego wyświetlacza LED. Na obudowie znajdują się dodatkowe diody LED sygnalizujące obecność zasilania, pracę sterownika, pracę układu oraz wystąpienie awaryjnego załączenia.

Elementem wykonawczym jest procesor 8-bitowy [ATtiny26][at].

 * [Schemat elektroniczny układu][schelec]
 * [Schemat połączeń][schconn]

[lm]: <http://www.ti.com/product/LM35>
[at]: <https://www.microchip.com/wwwproducts/en/ATTINY26>
[schelec]: <elecrical-schematic.pdf>
[schconn]: <connection-schematic.pdf>
