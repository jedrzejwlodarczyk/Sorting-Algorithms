#include <iostream>
#include <algorithm>

using namespace std;

//dziala prawie jak bąbelkowe tylko sprawdzane są elementy oddalone od siebie o h a nie sąsiednie
//przyrost sadgewicka( przeskok o h, gdzie h=n/2 -> h=h/2 -> ... dopoki h>1) 
void shell_sort(int data[], int n) { 
    int temp=0;
    //pierwsza pętla - ustawiamy przyrost, druga - dla kazdego "i" mieszczacego sie w tablicy wliczajac przyrost sprawdzamy czy poprzednie wartosci sa mniejsze od niego
    //(jesli data[i-h] <= data[i] <= data[i+h] to data[i] jest dobrze ustawiona w danym momencie)
    for (int h=n/2; h>0; h/=2) {
        for (int i=0; i<n-h+1; i++) {
            //musimy jeszcze sprawdzic o przyrost w druga strone czy i-h jest mniejsze
            int temp=data[i],j=i;
            while(j>=h && data[j-h]>temp){
                data[j]=data[j-h];
                j-=h;
            }
            data[j]=temp;
      }
    }
  }


//szukamy najmniejszego elementu z calej tablicy, zmieniamy element najmniejszy z pierwszym nieposortowanym elementem
void selection_sort(int data[], int n) {
    int temp=0,min=0;
    for(int i=0; i<n-1; i++){
        min=i;
        for(int j=i+1; j<n; j++){
            if(data[j]<data[min]){
                min=j;
            }
        }
            if(min!=i){
                temp=data[min];
                data[min]=data[i];
                data[i]=temp;
        }
    }
}

//heapsort
//funkcja dla danego i(rodzica) sprawdza czy jego dzieci są większe (jesli tak to zamienia), prostymi spami naprawia kopiec
void remake_heap(int data[], int n, int i) {
    int temp=0,parent,l_child,r_child;
    while(true){
        parent=i;
        l_child=2*parent+1;
        r_child=2*parent+2;
        if(l_child<n && data[l_child]>data[parent]){
            parent=l_child;
            }
        if(r_child<n && data[r_child]>data[parent]){
            parent=r_child;
            }
        //sprawdzenie czy rodzic mial dzieci wieksze od niego, jesli tak jest to nastepuje zamiana 
        if(parent!=i){
            temp=data[parent];
            data[parent]=data[i];
            data[i]=temp;
            i=parent;
            }
        else{
            break;
            }
    }
}

//tworzymy kopiec z danych wejsciowych (petla iteruje od n/2-1 dlatego ze kopiec od indeksow n/2 do n-1 nie ma dzieci[tylko liscie])
void build_heap(int data[],int n){
    for (int i=n/2-1; i>=0; i--) {
        remake_heap(data, n, i);
  }


}

//glowna funkcja, wywolujemy budowe kopca, zamieniamy elementy zgodnie ze struktura kopca(pierwszy element najwiekszy), zmniejszamy kopiec(i=n-1) i wywolujemy naprawe kopca
void heap_sort(int data[], int n) {
    int temp=0;
    build_heap(data,n);
    for(int i=n-1; i>=0; i--){
        temp=data[0];
        data[0]=data[i];
        data[i]=temp;
        remake_heap(data,i,0);
    }
}
// porównujemy 'klucz' z poprzedzającymi go elementami i przesuwając je odpowiednio w prawo ustawiamy na swoim miejscu
void insertion_sort(int data[], int n){
    int j,key;
    for(int i=1; i<n; i++){ 
        key = data[i];
        j = i-1;
        while(j>=0 && data[j] > key){ 
            data[j+1] = data[j]; 
            j = j-1;
        }
        data[j+1] = key;
    }
}

int partition(int data[], int p, int q)
{
    int pivot = data[p];
    int i = p + 1; //bo pivot to pierwszy element
    int j = q;

    while (true)
    {
        while (i <= j && data[i] <= pivot){
            i++;
        }
        
        while (i <= j && data[j] >= pivot){
            j--;
        }
        if (i <= j){
            swap(data[i], data[j]);
        }
        else{
            break;
        }
    }
    swap(data[p],data[j]);
    return j; //pivot index
}
 
int partition_random(int data[], int p, int q){
    srand(time(0));
    int random_index = p + rand() % (q - p);
    swap(data[random_index],data[q]);

    int pivot = data[q];
    int i = p;
    int j = q-1;

    while (true)
    {
        while (i <= j && data[i] <= pivot){
            i++;
        }
        while (i <= j && data[j] >= pivot){
            j--;
        }
        if (i <= j){
            swap(data[i], data[j]);
        }
        else{
            break;
        }
    }
    swap(data[q],data[i]);
    return i;


}


void quick_sort_left_pivot(int data[], int p, int q){
    if (p < q) {
        int index = partition(data, p, q);
 
        quick_sort_left_pivot(data, p, index - 1);
        quick_sort_left_pivot(data, index + 1, q);
    }
}

void quick_sort_random_pivot(int data[], int p, int q){
    if (p < q) {
        int index = partition_random(data, p, q);
 
        quick_sort_random_pivot(data, p, index - 1);
        quick_sort_random_pivot(data, index + 1, q);
    }
}


// Funkcja sortująca używając odpowiedniego algorytmu
void sort_using_algorithm(int data[], int size, int algorithm) {
    switch (algorithm)
    {
    case 1:
        insertion_sort(data,size);
        break;
    case 2:
        shell_sort(data, size);
        break;
    case 3:
        selection_sort(data,size);
        break;
    case 4:
        heap_sort(data,size);
        break;
    case 5:
        quick_sort_left_pivot(data,0,size-1);
        break;
    case 6:
        quick_sort_random_pivot(data,0,size-1);
        break;
    default:
        cout << "Unknown algorithm" << endl;
        exit(0);
        break;
    }
}

int main(int argc, char* argv[]) {
    // Sprawdzenie poprawności argumentów wiersza poleceń
    if (argc != 3 || string(argv[1]) != "--algorithm") {
        cout << "Użycie: " << argv[0] << " --algorithm <numer_algorytmu>" << endl;
        return 1;
    }

    int algorithm_number = stoi(argv[2]);

    // Wczytanie danych wejściowych ze standardowego wejścia
    //implementacja dynamicznej tablicy (nie wiadomo ile elementow bedziemy musieli posortowac)
    int* data = nullptr;
    int capacity = 0;
    int size = 0;
    int value;
    while (cin >> value) {
        if (size >= capacity) {
            // Zwiększenie pojemności tablicy
            int new_capacity = (capacity == 0) ? 1 : 2 * capacity;
            int* new_data = new int[new_capacity];
            // Skopiowanie danych do nowej tablicy
            for (int i = 0; i < size; ++i) {
                new_data[i] = data[i];
            }
            // Zwolnienie pamięci starej tablicy i przypisanie nowej tablicy
            delete[] data;
            data = new_data;
            capacity = new_capacity;
        }
        data[size++] = value;
    }

    // Wykonanie sortowania zgodnie z wybranym algorytmem
    sort_using_algorithm(data, size, algorithm_number);

    // Wyświetlenie posortowanych danych
    cout << "Posortowane dane:";
    for (int i = 0; i < min(25, size); ++i) {
        cout << " " << data[i];
    }
    cout << endl;

    // Zwolnienie zaalokowanej pamięci
    delete[] data;

    return 0;
}