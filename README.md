

# Dokumentacja projektowa aplikacji: **Monopoli**
## Przedmiot: Programowanie w C++
Instytut Informatyki
Kolegium Nauk Przyrodniczych
Uniwersytet Rzeszowski




### Wykonali:
* Adrian Gajewski
* Kamil Bania
* Wojciech Gałka

_Prowadzący: mgr inż. Dawid Kosior_
Rzeszów 2019
## Temat projektu i nazwa aplikacji
Temat projektu: Stworzenie gry w języku C++ na podstawie gry planszowej monopoly
Nazwa aplikacji: **Monopoli**
## Cel i opis projektu
Celem projektu jest praktyczne zastosowanie języka C++ poprzez stworzenie gry. Gra będzie oparta 
o zasady monopoly. 
* Plansza składa się z 40 pól
    * Pole start
    * Więzienie
    * “Idziesz do więzienia”
    * Darmowy parking
    * 22 pola nieruchomości - miasta
    * 4 pola linii kolejowych
    * 1 pole elektrowni atomowej
    * 1 pole sieci wodociągowej
    * 6 pól szansy
    * 3 x niebieska szansa
    * 3 x czerwona szansa
    * 1 płatny parking (income tax)
    * 1 pole podatek od wzbogacenia (luxury tax)
* Każdy gracz rzuca 2 kostkami do gry
* Każda nieruchomość posiada akt własności
* Na planszy znajdują się 2 zestawy kart szans (niebieski i czerwony)

1.  Przygotowanie:
    * Wszyscy gracze rozpoczynają rozgrywkę na polu start
    * Każdy z graczy otrzymuje na start 1500$
    * Kolejność ustalana jest przez rzut kośćmi -  gracz z największą ilością zaczyna pierwszy.

2. Rozgrywka:
    * W trakcie swojej tury gracz rzuca kostkami i porusza się do przodu liczbę pól wyrzuconą w kostkach
    * Jeżeli gracz stanie na nieruchomości bez właściciela to może ją kupić, za co otrzyma kartę własności
    * Jeżeli gracz stanie na nieruchomości innego gracza, płaci mu czynsz 
    * Jeżeli gracz stanie na własnej nieruchomości może ją rozbudować o ile jest właścicielem pozostałych pól w danym kolorze.
    * Jeśli gracz stanie na polu podatek od wzbogacenia (luxury tax) to płaci 100$
    * Jeśli gracz stanie na polu płatny parking (income tax) to płaci 200$
    * Jeśli gracz stanie na polu szansy, to bierze on kartę z odpowiedniego zestawu
     i wykonuje instrukcję z karty
    * Jeżeli gracz stanie na polu więzienia to nic się nie dzieje
    * Jeżeli gracz stanie na polu “Idziesz do więzienia” to wtedy gracz jest umieszczony 
    w więzieniu
    * Gdy gracz staje na lub przechodzi przez pole start otrzymuje 200$
    * Można sprzedawać domki z powrotem bankowi za połowę ceny
    * Gracze nie mogą pożyczać gotówki między sobą
    * Bank może pożyczać pieniądze graczom:
        * pożyczając 500$
    * W przypadku pożyczki 500$ od banku, gracz po przejściu przez pole start otrzymuje jedynie 100$, i musi przynajmniej raz przejść przez pole start przed oddaniem pożyczki
    * Gracz może mieć “aktywną” tylko 1 pożyczkę

3. Debel:
    * Gdy gracz wyrzuci debla, wykonuje ruch normalnie, po czym wykonuje jeszcze jeden, dodatkowy rzut
    * Jeżeli gracz wyrzuci 3 deble pod rząd, nie może kupić nieruchomości i idzie do więzienia
    * Aby wyjść z więzienia:
        * gracz musi wyrzucić debla
        * gracz może użyć karty “wyjście z więzienia”
        * zapłacić 50$, rzucić kostkami i przesunąć się o wyrzuconą ilość

4. Nieruchomości, domki, hotele:
    * Gdy gracz posiada wszystkie nieruchomości danego koloru, może kupować domki lub hotele za cenę odpowiednią dla danej nieruchomości
    * Każdy domek zwiększa wartość kwoty jaką płacą gracze stając na to pole
    * Po wybudowaniu hotelu pole osiąga wartość maksymalną a dalszy rozwój nie jest możliwy.

5. Bankructwo:
    * Gracz który nie może zapłacić należności zostaje bankrutem i jest wyeliminowany 
    z gry
    * Jeżeli gracz posiada długi w banku to oddaje mu wszystkie swoje nieruchomości (Nieruchomości gracza są niczyje i można je znów kupić).
    * Jeżeli gracz bankrutuje na polu innego gracza to oddaje mu swoje wszystkie nieruchomości
    * Gracz nie może wybrać czy chce zbankrutować. Jeżeli jest możliwość spłaty należności to ten musi to zrobić
    * Zwycięża gracz który doprowadzi pozostałych do bankructwa

Cele szczegółowe
* Rzut kostkami
* Losowanie kolejności graczy
* Inicjalizacja planszy
* Kupno i sprzedaż nieruchomości
* Tasowanie i losowanie kart specjalnych
* Akcje dla poszczególnych kart
* Zmiana stanów pól i graczy
* Wyświetlanie planszy
* Prosty gracz AI
## Technologie
C++
## GUI
Po uruchomieniu gry, pyta nas ona o liczbę graczy która bierze udział w rozgrywce.

   ![Main activity](/images/Przechwytywanie1.PNG)

Kolejnym krokiem jest automatyczne wylosowanie kolejnosci oraz wypisanie początkowego stanu każdego gracza.

   ![Main activity](/images/Przechwytywanie2.PNG)

Menu gracza. Wraz z przebiegiem rozgrywki jest wzbogacane o nowe opcje.

   ![Main activity](/images/Przechwytywanie3.PNG)

Ruchy graczy AI.

   ![Main activity](/images/Przechwytywanie4AI.PNG)

Wypisanie aktualnego stanu planszy przez gracza.

   ![Main activity](/images/Przechwytywanie5board.PNG)

Pożyczka 500$ z banku.

   ![Main activity](/images/Przechwytywanie6pozyczka.PNG)

Spłata pożyczki.

   ![Main activity](/images/Przechwytywanie7splata.PNG)

Menu gdy gracz jest w więzieniu.

   ![Main activity](/images/Przechwytywanie8Jail.PNG)
   
Rozbudowane menu.
   
   ![Main activity](/images/Przechwytywanie9buyhouse.PNG)
   
Kupno domku na polu.
   
   ![Main activity](/images/Przechwytywanie10buyhouse2.PNG)
   
Sprzedaż domku.
   
   ![Main activity](/images/Przechwytywanie11sellhouse.PNG)
   
Gracz staną na polu szansa.
   
   ![Main activity](/images/Przechwytywanie12card.PNG)



## Diagramy
1. Pętla główna aplikacji

   ![Main activity](/images/diagrammonopoly1.png)

2. Wybór akcji gracza zależny od stanu w jakim się znajduje

   ![Player action](/images/diagrammonopoly2.png)
   
3. Pole nieruchomości

   ![Property field](/images/diagrammonopoly3.png)
   
4. Jesteś w więzieniu

   ![Player in jail](/images/diagrammonopoly4.png)

5. Pole szansy

   ![Chance field](/images/diagrammonopoly5.png)

