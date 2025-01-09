#include <iostream>
#include <cmath>
#include <string>
#include <cstdlib>
#include <stdexcept>
#include <fstream>
#include <ctime>
using namespace std;



void ucitaj(string filename, int*& niz, int &vel){
    ifstream file(filename);
    char znak ='*';
    niz=new int[vel];
    for(int i=0;i<vel;i++){
    file>>niz[i]>>znak;
    if(!file) break;
    }
    file.close();
}

void generisi(string filename, int vel){
         std::ofstream myfile(filename);
          srand(time(0));
    for(int index=0; index<vel; index++)
    {
        int random_integer = rand();
        myfile << random_integer << " ";
    }
    myfile.close();
}


//

template <typename Tip>
void bubble_sort(Tip* niz, int vel){
    for(int i=vel-1;i>=1;i--){
        for(int j=1;j<=i;j++){
            if(niz[j-1]>niz[j]){
                Tip temp=niz[j-1];
                niz[j-1]=niz[j];
                niz[j]=temp;
            }
        }
    }
}

//

template <typename Tip>
void selection_sort(Tip* niz, int vel){
    for(int i=0;i<=vel-2;i++){
        Tip min=niz[i];
        int pmin=i;
        for(int j=i+1;j<=vel-1;j++){
            if(niz[j]<min){
                min=niz[j];
                pmin=j;
            }
        }
        niz[pmin]=niz[i];
        niz[i]=min;
    }
}
template<typename Tip>
Tip particija(Tip* niz, Tip prvi,Tip zadnji){
    Tip pivot=niz[prvi];
    int p=prvi+1;
    while(p<=zadnji){
        if(niz[p]<=pivot)
        p++;
        else 
        break;
    }
    for(int i=p+1;i<=zadnji;i++){
        if(niz[i]<pivot){
            auto temp=niz[i];
            niz[i]=niz[p];
            niz[p]=temp;
            p++;
        }
    }
            auto temp=niz[prvi];
            niz[prvi]=niz[p-1];
            niz[p-1]=temp;
        return p-1;
    }

template <typename Tip>
void merge(Tip* niz,const int l,const int p,const int q,const int u){
    int i(0),j(q-l),k(l);
    Tip *B=new Tip[u-l+1];
    for(int m=0;m<=u-l;m++){
        B[m]=niz[l+m];
    }
    while(i<=p-l && j<=u-l){
        if(B[i]<B[j])
        niz[k]=B[i++];
        else 
        niz[k]=B[j++];
        k++;
    }
    while(i<=p-l)
    niz[k++]=B[i++];
    while(j<=u-l)
    niz[k++]=B[j++];
    delete[] B;
}

template <typename Tip>
void quick_sort2(Tip *niz,int prvi, int zadnji){
  if(prvi<=zadnji){
       Tip j=particija(niz,prvi,zadnji);
       quick_sort2(niz,prvi,j-1);
       quick_sort2(niz,j+1,zadnji);
   }
}

//
template <typename Tip>
 void merge_sort2(Tip* niz,int l,int u){
    if(u>l){
        int p=(l+u-1)/2;
        int q=p+1;
        merge_sort2(niz,l,p);
        merge_sort2(niz,q,u);
        merge(niz,l,p,q,u);
    }
 }

template <typename Tip>
void quick_sort(Tip* niz, int vel){
   quick_sort2(niz,0,vel-1);
}
template <typename Tip>
void merge_sort(Tip* niz, int vel){
    merge_sort2(niz,0,vel-1);
}


int main(){
    int* niz;
    int vel = 100000;
    generisi("lol.txt", vel);
    ucitaj("lol.txt", niz, vel);
    int izbor;
    std::cin>>izbor;
    if(izbor==1){
        std::cout<<"bubble sort";
        clock_t vrijeme1 = clock();
        bubble_sort(niz,vel);
        clock_t vrijeme2 = clock();
        int ukvrijeme = (vrijeme2 - vrijeme1) / (CLOCKS_PER_SEC / 1000);
        cout << "Vrijeme izvrsenja: " << ukvrijeme << " ms." << endl;
    }
     if(izbor==2){
        std::cout<<"selection sort";
        clock_t vrijeme1 = clock();
        selection_sort(niz,vel);
        clock_t vrijeme2 = clock();
        int ukvrijeme = (vrijeme2 - vrijeme1) / (CLOCKS_PER_SEC / 1000);
        cout << "Vrijeme izvrsenja: " << ukvrijeme << " ms." << endl;
    }
     if(izbor==3){
        std::cout<<"quick sort";
       clock_t vrijeme1 = clock();
        quick_sort(niz,vel);
        clock_t vrijeme2 = clock();
        int ukvrijeme = (vrijeme2 - vrijeme1) / (CLOCKS_PER_SEC / 1000);
        cout << "Vrijeme izvrsenja: " << ukvrijeme << " ms." << endl;
    }
     if(izbor==4){
        std::cout<<"merge sort";
        clock_t vrijeme1 = clock();
        merge_sort(niz,vel);
        clock_t vrijeme2 = clock();
        int ukvrijeme = (vrijeme2 - vrijeme1) / (CLOCKS_PER_SEC / 1000);
        cout << "Vrijeme izvrsenja: " << ukvrijeme << " ms." << endl;
    }
    /*
    for(int i=0;i<vel;i++)
    std::cout<<niz[i]<<std::endl;*/
}