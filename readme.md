## Instrukcja uruchomienia programu
Żeby zbudować program wystarczy użyć komendy make.\
Uruchomienie programu: ./main <number_of_philosophers>
## Problem jedzących filozofów
### Opis problemu
- N filozofów siedzi przy okrągłym stole
- Filozofowie mogą wykonywać jedną z dwóch czynności: jedzenie lub rozmyślanie
- Każdy filozof ma widelec po swojej lewej i prawej stronie (czyli pomiędzy każdą parą filozofów leży widelec)
- Filozof może korzystać tylko z widelców leżących bezpośrednio obok niego
### Wyjaśnienie analogii
Problem jedzących filozofów jest obrazowym przedstawieniem problemów występujących w programach wielowątkowych.
- Filozofowie są analogią dla współbieżnych procesów lub wątków. Każdy działa niezależnie, ale musi współdzielić zasoby z innymi.
- Widelce są analogią dla zasobów współdzielonych (np. pliki, pamięć drukarki etc.). Każdy filozof potrzebuje dostępu dla określonych zasobów, ale nie mogą być one zajęte przez inne procesy. 
### Rozwiązanie problemu
Poprawne rozwiązanie problemu powinno unikać zakleszczenia (ang. _deadlock_) oraz głodzenia wątków (ang. _starvation_).
#### Zakleszczenie
Zakleszczenie to sytuacja, w której dwa procesy czekają na siebie nawzajem, przez co żaden nie może się zakończyć./
W problemie zakleszczenie występuje wtedy, gdy dwaj filozofowie czekają na siebie nawzajem, przez co żaden nie może zacząć jeść. Przykładowo, jeżeli wszyscy filozofowie wezmą widelec po swojej lewej stronie i będą czekali na prawy, to żaden z wątków nigdy się nie rozpocznie.
#### Głodzenie
Głodzenie to sytuacja, w której dany proces nie jest w stanie zakończyć działania ze względu na brak dostępu do jakiegoś zasobu (procesora, pliku etc.)./
W problemie głodzenie występuje wtedy, gdy filozof przez długi czas nie uzyskuje dostępu do dwóch pałeczek i nie może jeść.
