/*
> sapendo i vari algoritmi per il sort e sapendo usare chrono per i tempi, e avendo l'altro codice per 
confrontare in quali casi convenga un sort rispetto all'altro 
> domande da fare all'AI:
1) cosa fare se l'insertion sort trova un array quasi ordinato
2) cosa succede se modifico il quicksort cambiando il caso base? (cioè cosa succede se farmo l'array a n?)
NB va manteenuto un diario/log man mano delle modifiche (facendo i log man mano con sulla repo di git)
>OBBIETTIVO: 1) convincersi che quando l'array è quasi ordinato, l'InsertionSort non è niente male.
2) capire cosa succede nel quicksort quando fermo il QS al caso base con <= elementi. (caso base-> avviene quando
 sx>=dx, ossia quando L=1. ossia quando sx-dx < L-1, rpba che va messa dentro all'if al posto di sx<dx)
 chiaramente il L=1 è il classico QSL, dico all'intelligenza di non darmi la soluzione , ma aiutarmi acpire
*/




// facendo il sorting ibrido ho un algoritmo che è SEMPRE nlogn, non solo al caso migliore. 

// compila con:  g++ -std=c++17 sortalg.cpp -o sortalg
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

// per creare numeri casuali
#include <random>
// per misurare i tempi di esecuzione
#include <chrono>

using namespace std;

/* UTILITY */

int random(int a, int b){ // restituisce un numero random in [a..b]
    static random_device rd;  // per inizializzare il generatore
    static mt19937 gen(rd()); // static evita di creare ogni volta il generatore a ogni chiamata 
    uniform_int_distribution<int> dist(a, b);

    return dist(gen);
}

vector<int> generaArrayCasuale(int n, int minVal = -100, int maxVal = 100){  // accetta solo n > 0 oppure tutti gli argomenti
    vector<int> A(n); // vettore di n interi da riempire
    for (auto i = 0; i < n; i++){
        A[i] = random(minVal,maxVal);
    }
    return A;  // non fa la copia!
}

void printArray(const vector<int>& B){
    for (auto x : B){
        cout << x << " ";
    }
    cout << endl;
}

void stampaArray(const vector<int>& B, int sx, int dx){ 
    if (sx < 0) sx = 0;
    if (dx > B.size()-1) dx = B.size()-1;
    for (auto i = sx; i <= dx; ++i){
        cout << B[i] << " ";
    }
    cout << endl;
} // questa funzione è molto utile per fare debugging negli algoritmi ricorsivi come il QuickSort, 
  //per vedere su quale esatto frammento di array sta lavorando il programma in un determinato istante

bool verificaOrdinamento(const vector<int>& A){ // Theta(n)
    // A[i] <= A[i+1] per tutti i valori 0 ≤ i ≤ n-2
    // A[0] <= A[1] && A[1] <= A[2] && ... && A[n-2] <= A[n-1]
    bool risultato = true; // elemento neutro rispetto all'and logico &&
    for (auto i = 0; i + 1 < A.size(); ++i){
        risultato = risultato && A[i] <= A[i+1];
    }
    return risultato;    
}

bool verificaOrdinamento2(const vector<int>& A){ // O(n)
    for (auto i = 0; i + 1 < A.size(); ++i){
        if (A[i] > A[i+1]) return false;
    }
    return true;    
}

bool verificaOrdinamento3(const vector<int>& A){ // O(n)
    auto i = 0; 
    while (i + 1 < A.size() && A[i] <= A[i+1]) ++i;
    return i + 1 >= A.size();    
}

/* INSERTION SORT */

void insertionSort(vector<int>& A){
    for (auto i = 1; i < A.size(); ++i){
        auto t = A[i];
        auto j = i;
        while (j > 0 && A[j-1] > t){
            A[j] = A[j-1];
            --j;
        }
        A[j] = t;
    }
}

/* QUICKSORT */

int Distribuzione(vector<int>& A, int sx, int px, int dx) {
    if (px != dx)
        swap(A[px], A[dx]);
    int i = sx;
    int j = dx - 1;
    while (i <= j) {
        while (i <= j && A[i] <= A[dx])
            i++;
        while (i <= j && A[j] >= A[dx])
            j--;
        if (i < j)
            swap(A[i], A[j]);
    }
    if (i != dx)
        swap(A[i], A[dx]);
    return i;
}

void QuickSortTroncato(vector<int>& A, int sx, int dx, const int L) { // metto const a L tanto non cambia mai 
    if (dx - sx +1 > L) {
        int pivot = random(sx, dx); 
        // stampaArray(A, sx, dx);
        int rango = Distribuzione(A, sx, pivot, dx);
        // cout << "dopo: ";
        // stampaArray(A, sx, dx);
        QuickSortTroncato(A, sx, rango - 1, L); // magia dell'induzione/ricorsione
        QuickSortTroncato(A, rango + 1, dx, L);
    }
}

void QuickSortTroncato(vector<int>& A) { // giusto per dargli solo una variabile (+ veloce)
    int L=1;
    QuickSortTroncato(A, 0, A.size()-1, L); // costo medio O(nlogn)
}

/* SORT IBRIDO */

void SwagSort(vector<int>& A, int sx, int dx, int L){
    int L=1;
    if(dx - sx + 1 > L){ // man mano c'è un certo blocco da riordinare e non vogliamo che siano più di L
    QuickSortTroncato(A); // costo medio O(nlogn)
    insertionSort(A); // costo O(n L) al casoo pessimo

    }
}

/* MAIN */

int main()
{
    constexpr auto N = 1000;               // dimensione = numero di interi random
    vector<int> A = generaArrayCasuale(N); // vector<int> A = {4, -6, 3, 5, -2, 1, -4, 6, -3};
    if (N < 100)
        printArray(A); // questa chiamata ignorata se N è grande

    // array di puntatori a funzioni, evita di scrivere tre volte il codice per misurare i tempi
    using FuncPtr = void (*)(vector<int> &);
    const vector<FuncPtr> funzioni = {
        insertionSort,
        QuickSortTroncato,
        SwagSort
    };
    const vector<string> nomi = {
        "Insertion Sort",
        "QuickSort randomizzato",
        "QuickSort + InsertionSort"
    };
    const vector<string> complessita = {
        "insertion sort quadratico al caso pessimo",
        "quicksort randomizzato",
        "è sempre ordine nlogn"
    };

    auto ordinato = A;
    sort(ordinato.begin(), ordinato.end());
    auto inverso = ordinato;
    reverse(inverso.begin(), inverso.end());

    const vector<vector<int>> input = {A, ordinato, inverso};
    const vector<string> tipi = {"casuale", "ordinato", "inverso"};

    for (int j = 0; j < input.size(); ++j) {
        cout << "Input " << tipi[j] << ":" << endl;
        for (int i = 0; i < funzioni.size(); ++i) {
            auto B = input[j]; // copia dello stesso input per ogni algoritmo

                const auto f = funzioni[i]; // sort
            const auto & costo = complessita[i]; // usa il riferimento, evitiamo la copia della stringa con: auto costo = complessita[i]
        
            auto start = chrono::steady_clock::now();  // tempo d'inizio

            f(B); // eseguiamo uno dei sort a turno sulla copia (perché?)

            auto stop = chrono::steady_clock::now();    // tempo di fine
            auto durata = chrono::duration_cast<chrono::microseconds>(stop - start);

            // printArray(B);
            if (!verificaOrdinamento(B)) // fase di testing 
                cout << "Errore in " << nomi[i] << endl;

            cout << "\t" << costo << ": " << " [" << durata.count() << " microsecondi]" << endl;
        }
   
    }
    return 0;
}