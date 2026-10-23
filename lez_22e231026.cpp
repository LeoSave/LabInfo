/*
> ricorsioni: imoortanti nei codici
> poi ha spiegato il quicksort 
> IMPORTANTE: il quicksort deterministico al caso pessimo (il numero a dx è già il piu grande) costa n^2;
per questo si usa il quicksort random, che con alta probabilità mi dà il miglior caso possibile O(nlogn)
*/
#include<iostream>
#include<vector>
#include <string>
#include <algorithm>
#include <random>

using namespace std;

// FATTORIALE
long fatt(long n) { // long: an integer type that is at least 32 bits, typically 4 bytes on 32‑bit systems, è come scrivere int32
    if (n<= 1) return 1;
    return n * fatt(n-1);
} 

/*
PARTE SULLA SERIE DI FIBONACCI: (non completa)

long Fib(long n) { // mi dà l'ennesimo termine della serie
    if (n<= 1) return 1;
    return Fib(n-1) + Fib(n-2);
} 
// oppure (è O(n), ma esiste amche una versione O(logn))
long Fib(long n) { // mi crea tutto il vettore
    vector<long> F(n+1);
    F[0] = F[1] = 1;
    //for (long)
    // e continua (e-learning)
}
// ogni volta che usa le due chiamate prima per definire la n esima, poi quando va avanti
// e passa alle altre, il computer si è dimenticato di averle già risolte prima (a lungo andare molto costoso)
// (guardare pag37 dispense)
*/

// UTILITY 

int random(int a, int b){ // restituisce un numero random in [a..b]
static random_device rd; // per inizializzare il generatore
static mt19937 gen(rd()); // static evita di creare ogni volta il generatore a ogni chiamata
uniform_int_distribution<int> dist(a, b);

return dist(gen);
}

vector<int> generaArrayCasuale(int n, int minVal = -100, int maxVal = 100){ // accetta solo n > 0 oppure tutti gli argomenti
vector<int> A(n); // vettore di n interi da riempire
for (auto i = 0; i < n; i++){
A[i] = random(minVal,maxVal);
}
return A; // non fa la copia!
}

void printArray(const vector<int>& B){
for (auto x : B){
cout << x << " ";
}
cout << endl;
}

int Distribuzione(vector<int>& A, int sx, int px, int dx){
    if (px!=dx){
        swap(A[px], A[dx]); // swap scambia due elementi di un array. non serve se px=dx
    }
    int i=sx;
    int j=dx-1; //-1 è dovuto al fatto che a dx c'ho appoggiato il pivot
    while (i<=j){ //meglio mettere <= perche se ho un array di due elementi con < e basta il ciclo non parte
        while (i<=j && A[i] < A[dx]) i++; // avanza fintanto che abbiamo 0
        while (i<=j && A[j] >= A[dx]) j--; // retrocede fintanto che abbiamo 1
        if(i<j){
            swap(A[i],A[j]);
            i++;
            j--;
        }
    }
    swap(A[i],A[dx]); // tanto ormai i + grandi sono stati divisi dai + piccoli, quindi scambio il pivot col primo dei piu grandi e la divisione rimane vera
    return i; // ci dovrei mettere il rango in realtà

} // se non metto che deve anche essere i<j, le i e j proseguono all'infinito e mi escono dall'array

void QuickSort(vector<int>& A,int sx, int dx){
    if(sx<dx) {
        int pivot = dx; // può essere qualunque valore in [sx ... dx]
        int rango = Distribuzione(A, sx, pivot, dx);
        QuickSort(A,sx,rango - 1);
        QuickSort(A, rango + 1, dx);
    }

} // questo è deterministico in quanto gli dico io come prendere il pivot (non è sempre la cosa migliore) c'è anche un algoritmo per mettere il pivot randomico
// PER IL CODICE IN CUI USA SIA IL DETERMINISTICO CHE IL RANDOM, GUARDO E LEARNING

int main(){
constexpr auto N = 12;
vector<int> A = generaArrayCasuale(N);
//vector<int> A={2,-1}; // lui è qua pk la forma senza alcuni dettaglietti andava bene tranne quando l'array aveva solo due elementi 
printArray(A); // questo è l'array non ordinato
Distribuzione(A, 0, A.size()-1, A.size()-1); // attenzione: questa riga NON è necessaria, ce l'ho messa solo per capire che fa Distribuzione
printArray(A); // questo è l'array con la roba messa a sx/dx se minore/maggiore del pivot
QuickSort(A, 0, A.size()-1);
printArray(A); // questo è l'array ordinato finale 
return 0;
}
