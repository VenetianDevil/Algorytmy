# Algorytmy i Struktury Danych

## Introduction
Programy na zajęcia "Algorytmy i Struktury danych" z drugiego roku UJ. Programy wymagane przez (dwoje różnych) prowadzących do zaliczenia.

## Table of contents
* [Technologies](#technologies)
* [Setup](#setup)
* [Folders & Files](#folders/files)
* [Status](#status)

## Technologies
* c++11

## Setup
Każdy plik można skompilować w terminalu z użyciem standartu c++11:
```
g++ -std=c++11 -o prog nazwa_pliku.cpp -Wall -O
./prog
```
## Folders/Files
*1 - zajęcia 1 sem III
    *binary_search.cpp
    *fibonacci.cpp
    *silnia.cpp
    *pot.cpp - liczenie dowolnej potęgi
    *srednia.cpp - liczenie średniej z podawanych n liczb
    *osnadz.cpp - przeliczanie systemu ósemkowego na dziesiętny
    *wysz_bin_iter.cpp - iteracyjne wyszukiwanie binarne
*2 - Listy sem III
    *lista.cpp - lista z usuwaniem duplikatów
*listy - listy sem III
    *list_wskaz.cpp - wskaźnikowa jednokierunkowa
    *list_wskaz_dwu.cpp - wskaźnikowa dwukierunkowa
    *lista_osoby.cpp - dwukierunkowa z elementami typu Osoba{imie, nazwisko}
    *Stos.cpp - Stos na podstawie listy wskaźnikowej jednokierunkowej
    *Kolejka.cpp - Kolejka na podstawie listy jednokierunkowej z ogonem
*sort - algorytmy sortowania sem III
    *sort_selekcja.cpp - Selection Sort
    *sort_wstawiania.cpp - Insertion Sort
    *sort_bombelkowy.cpp - Bubble Sort
    *pliki png podsumowujące złożoność zaimplementowanych algorytmów
    *sort_kopiec.cpp - sortowanie Kopca(Stogu)
    *quickSort.cpp - Quick Sort
*zaliczenie - sem III
    *notacja.cpp - zamiana notacji ONP na inifiksową i na odwrót, z wykorzystaniem stosu

*3 - zajęcia sem IV
    *set.cpp - implementacja działań na zbiorach
    *min.cpp - Kolejka priorytetowa w postacji kopca, gdzie najmniejszy klucz znajduje sie w korzeniu
*graf - zadania z grafami sem IV
    *graf_3.cpp - Graf: macierz sąsiedztwa, lista sąsiedztwa, czy jest dwudzielny, uporządkowanie topologiczne wierzchołków
    *graf_4.cpp - Wykaz mostów w grafie i punktów artykulacji, hierarchia klas, własna koncepcja implementacji grafu
    *pdf z wyjaśnieniem zadania do programu graf_4
*impl5 - zadanie sem IV
    *miasta.cpp - wersja nieudana?
    *miasta2.cpp - wersja ostateczna
    *pdf z wyjaśnieniem treści zadania
*dodatkowe - zadania dodatkowe sem IV
    *Kruskal.cpp - Implementacja algorytmu Kruskala
    *Prim.cpp - niekompletny algorytm Prima

## Status
Zakończone
