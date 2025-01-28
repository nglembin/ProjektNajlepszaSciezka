/*


Nikodem Glembin, s32943 - Projekt PPRG -> T1. Najlepsza ścieżka. 


*/

#include <iostream>  // Obsługa wejścia i wyjścia (cin, cout)
#include <vector>    // Dynamiczna alokacja pamięci (tablice 2D)
#include <climits>   // Stała INT_MAX do reprezentowania nieskończoności Dzięki temu program poprawnie porównwuje i znajduje minimalne wartości.
#include <algorithm> // reverse() – odwracanie kolejności elementów. 
#include <cstdlib>   // Funkcja rand() do losowania liczb
#include <ctime>     // Inicjalizacja generatora losowego (time(0))

using namespace std;

// Funkcja do znalezienia najlepszej ścieżki w tablicy
pair<vector<int>, int> znajdzNajlepszaSciezke(const vector<vector<int>> &tablica) {
    int liczbaWierszy = tablica.size();   // Liczba wierszy
    int liczbaKolumn = tablica[0].size(); // Liczba kolumn

    // Macierz kosztów minimalnej ścieżki (wypełniamy dużymi wartościami)
    vector<vector<int>> koszty(liczbaWierszy, vector<int>(liczbaKolumn, INT_MAX));

    // Macierz przechowująca skąd przyszliśmy do danego pola
    vector<vector<int>> sciezka(liczbaWierszy, vector<int>(liczbaKolumn, -1));

    // Przepisanie pierwszej kolumny do kosztów (bo od niej zaczynamy)
    for (int i = 0; i < liczbaWierszy; i++) {
        koszty[i][0] = tablica[i][0]; // Koszt wejścia do pierwszej kolumny to jej wartość
    }

    // Dynamiczne wypełnianie tablicy kosztów od lewej do prawej
    for (int j = 1; j < liczbaKolumn; j++) { // Dla każdej kolumny (od 2 do końca)
        for (int i = 0; i < liczbaWierszy; i++) { // Dla każdego wiersza
            for (int di = -1; di <= 1; di++) { // Możliwe ruchy: góra (-1), wprost (0), dół (+1)
                int poprzedniWiersz = i + di; // Sprawdzamy skąd możemy przyjść
                if (poprzedniWiersz >= 0 && poprzedniWiersz < liczbaWierszy) { // Czy ruch jest w granicach
                    int koszt = koszty[poprzedniWiersz][j - 1] + tablica[i][j]; // Obliczamy nowy koszt dojścia
                    if (koszt < koszty[i][j]) { // Czy to lepszy koszt?
                        koszty[i][j] = koszt;   // Zapisujemy najlepszy koszt
                        sciezka[i][j] = poprzedniWiersz; // Zapisujemy skąd przyszliśmy
                    }
                }
            }
        }
    }

    // Znalezienie minimalnego kosztu w ostatniej kolumnie
    int minimalnyKoszt = INT_MAX;
    int ostatniWiersz = -1;
    for (int i = 0; i < liczbaWierszy; i++) {
        if (koszty[i][liczbaKolumn - 1] < minimalnyKoszt) {
            minimalnyKoszt = koszty[i][liczbaKolumn - 1];
            ostatniWiersz = i;
        }
    }

    // Odtwarzanie ścieżki od prawej kolumny do lewej
    vector<int> najlepszaSciezka;
    int kolumna = liczbaKolumn - 1;
    while (kolumna >= 0) {
        najlepszaSciezka.push_back(tablica[ostatniWiersz][kolumna]); // Dodajemy wartość pola do ścieżki
        ostatniWiersz = sciezka[ostatniWiersz][kolumna]; // Przechodzimy do poprzedniego pola
        kolumna--; // Przechodzimy do wcześniejszej kolumny
    }

    reverse(najlepszaSciezka.begin(), najlepszaSciezka.end()); // Odwracamy kolejność ścieżki

    return {najlepszaSciezka, minimalnyKoszt}; // Zwracamy najlepszą ścieżkę i jej sumę
}

int main() {
    int liczbaWierszy, liczbaKolumn;
    cout << "Podaj liczbe wierszy: ";
    cin >> liczbaWierszy;
    cout << "Podaj liczbe kolumn: ";
    cin >> liczbaKolumn;

    srand(time(0)); // Inicjalizacja generatora losowego

    // Tworzenie tablicy 2D i losowanie wartości
    vector<vector<int>> tablica(liczbaWierszy, vector<int>(liczbaKolumn));
    cout << "Generowanie losowej tablicy:" << endl;
    for (int i = 0; i < liczbaWierszy; i++) {
        for (int j = 0; j < liczbaKolumn; j++) {
            tablica[i][j] = rand() % 10 + 1; // Losowe liczby 1-10
            cout << tablica[i][j] << " ";
        }
        cout << endl;
    }

    // Znalezienie najlepszej ścieżki
    auto [najlepszaSciezka, suma] = znajdzNajlepszaSciezke(tablica);

/*

Zamiast structured bindings można użyć również tego:

    pair<vector<int>, int> wynik = znajdzNajlepszaSciezke(tablica);
    vector<int> najlepszaSciezka = wynik.first;
    int suma = wynik.second;

*/

    // Wypisanie wyniku
    cout << "Najlepsza sciezka prowadzi przez pola o wartosciach: ";
    for (int wartosc : najlepszaSciezka) {
        cout << wartosc << " ";
    }
    cout << "\nSuma pol: " << suma << endl;

    return 0;
}
