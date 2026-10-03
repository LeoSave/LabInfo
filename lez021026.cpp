#include <iostream>
#include <vector>
#include <ctime>

// ho disabilitato il copilot ai al momento, se voglio riabilitarlo cerco copilot sulle estensioni

using namespace std;

int SommaMassima1(vector<int> B){ // O(n^3) , questi tre cicli for sono come una tripla sommatoria
    auto maxs = 0; // il masssimo migliore "al momento"
    auto n = B.size(); // numero di interi presenti in B

    for(auto i=0; i<n; ++i){
        for(auto j=i; j<n; ++j){ // da i a n pk j è il secondo indice (deve essere +grande)
            auto somma = 0;
            for(auto k=i; k<= j; ++k){ // k invece è l'indice che si muove tra i e j per sommare le caselle
                somma += B[k]; // somma = somma B[k]

            }
            if (somma > maxs){ // questo if mi trova il "vincitore" ad ogni iterazione, chi arriva in fondo è segmax
                               
            maxs = somma;
            }
        }
    
    }
        
return maxs;

}

int SommaMassima2(vector<int> B){ // O(n^2), ora sono due sommatorie
    auto maxs=0;
    auto n=B.size();
    for(auto i=0; i<n; i++){
        auto somma = 0; // sta volta somma lo definisco per ogni i e sommo già a partire dalle j, mettendo anche l'if lì dentro
        for(auto j=i; j<n; j++){ 
            somma += B[j];
            if(somma>maxs){
                maxs=somma;
            }
        }
    }
    return maxs;
} // concettualmente è simile a quello su, ma una volta definito l'i, sommo già indice per indice e 
  //man mano che trovo un segmento maggiore di quello prima lo sovrascrivo

  
  int SommaMassima3(vector<int> B){ // O(n), ora è una sommatoria col ragionamento dei massimali
    auto maxs = 0;
    auto somma = 0;
    // Si itera solo su tutti gli indici j}
    for (auto j = 0; j < B.size(); j++){
        if (somma > 0){ 
            somma += B[j];
        }
        else {
        somma = B[j];
        }  //quindi qua gli sto dicendo "se la somma è diventata negativa, passa al prossimo indice e continua a sommare"
        if (somma > maxs){ // qui invece gli sto dicendo "se la somma è cui sono arrivato è la più grande finora, sovrascrivi maxs"
        maxs = somma;
        } 
    }
    return maxs;   
 }
  

int random(int a, int b){ // restituisce numero random casuale tra a e b inclusi
    return a + rand() % (b-a+1); // % è il modulo
}

vector<int> generaArrayCasuale(int n, int minVal = -100, int maxVal = 100){
    vector<int> A(n); //vettore di n interi da riempire, dichiaro n così il programma sa quante caselle riempire, se non lo so a priori posso usare una funzione chiamata pushback
    for (auto i=0; i<n; i++){
        A[i] = random(minVal,maxVal);


    }
    return A;
    

}

// qui printo l'array, void vuol dire che la funziona non aspetta gli sia ritornato qualcosa
void printArray(vector<int> A){
    //for (auto i=0; i<A.size(); ++i){ cout << A[i]<< " ";}
    for(auto x : A){
        cout << x << " ";
    }
    cout << endl;
}

int main(){
    srand(time(NULL)); // srand è la funzione che dà il seed (seme) che avvia il processo con cui rand crea un numero casuale
     //vector<int> A = {4, -6, 3, 5, -2, 1, -4, 6, -3};
     vector<int> A = generaArrayCasuale(1000);
     printArray(A);

    auto maxSegmentSum1 = SommaMassima1(A);
    auto maxSegmentSum2 = SommaMassima2(A);
    auto maxSegmentSum3 = SommaMassima3(A);
    cout << "Il segmento di somma massima dell' array è: " << maxSegmentSum1 << endl;
    cout << "Il segmento di somma massima dell' array è: " << maxSegmentSum2 << endl;
    cout << "Il segmento di somma massima dell' array è: " << maxSegmentSum3 << endl;
    return 0;
}



/*

COMMENTI VARI:
> c'è un power point su teams che spiega anche la parte piu teorica che c'è dietro
> 'auto' come dichiarazione di una variabile non specifica il tipo, è il programma che lo riconosce, 
in questo caso comunque sono tutte 'int' o vettori le variabili
> per salvare immediatamente posso pigiare ctrl+s
> alla fine è la stessa roba già scritta anche ieri
> per il committ:
git add -a (a tutti), sennò git add nomefile
git commit -m "discorso"
git push
manca da fare il commit qando va bene tutto, l'eseguibile non va messo, si scrive git rm segmax
 (o come si chia,a il file) e anche commit push
*/