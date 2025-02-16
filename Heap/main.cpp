#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;



void Zamjeni (int i, int j,vector<int> &a) {
 int tmp(a[i]);
 a[i]=a[j];
 a[j]=tmp; 
} 

 int LijevoDijete(int i) { 
 return 2*i+1;
 }
 int DesnoDijete(int i)  { 
 return 2*i+2;
 }
 int Roditelj(int i)  { 
 return (i-1)/2;
 } 


void PopraviDolje(vector<int> &a,int velicina,int i) {
 int najveci=i;
 int ld=LijevoDijete(i);
 int dd=DesnoDijete(i);
   
    if (ld < velicina && a.at(ld) > a.at(najveci))
       najveci=ld;
 
    
    if (dd < velicina && a.at(dd) > a.at(najveci))
       najveci=dd;
 
    
    if (najveci != i) {
       swap(a[i],a[najveci]);
        PopraviDolje(a,velicina,najveci);
 }
}

void StvoriGomilu(vector<int> &a,int velicina = -1) {
     if(velicina <=0) velicina=a.size();
    for (int i=velicina/2-1; i>=0; i--)
    PopraviDolje(a,velicina,i);
}




int getMax(vector<int> &a){
    int max=a.at(0);
    for(int i=0;i<a.size();i++){
        if(a.at(i)>max)
        max=a.at(i);
    }
    return max;
}

void count(vector<int> &a,int exp){
    vector<int> b(a.size(),0);
    vector<int> count(10,0);


    for(int i=0;i<a.size();i++)
        count[(a[i]/exp)%10]++;

    for(int i=1;i<10;i++)
        count[i]+=count[i-1];

    for(int i=a.size()-1;i>=0;i--){
        b.at(count.at((a.at(i)/exp)%10)-1)=a[i];
        count[(a[i]/exp)%10]--;
    }
    for(int i=0;i<a.size();i++)
        a.at(i)=b.at(i);
}
void radixSort(vector<int> &a){
    int n=getMax(a);
    for(int exp=1;n/exp>0;exp*=10)
    count(a,exp);
}

void stvoriGomilu(vector<int> &a,int velicina=-1){
   
   StvoriGomilu(a,velicina);
}

void umetniUGomilu(vector<int> &a,int umetnuti,int &velicina){
    a.push_back(umetnuti);
    velicina++;
   StvoriGomilu(a,velicina);
}

void izbaciPrvi(vector<int> &a, int &velicina) {
    if(velicina==0) throw std::logic_error ("Heap prazan");
    swap(a[0],a[--velicina]);
    stvoriGomilu(a,velicina);
} 

void gomilaSort(vector<int> &a){
    stvoriGomilu(a,a.size());
    sort(a.begin(),a.end());
}



int main(){
   vector<int> a;
    int velicina = 0;
    umetniUGomilu(a,546,velicina);
    umetniUGomilu(a,435435,velicina);
    umetniUGomilu(a,12,velicina);
    umetniUGomilu(a,546,velicina);
    umetniUGomilu(a,675767,velicina);
    umetniUGomilu(a,33,velicina);
    umetniUGomilu(a,555,velicina);
    umetniUGomilu(a,1,velicina);
    izbaciPrvi(a,velicina);
    izbaciPrvi(a,velicina);
    izbaciPrvi(a,velicina);
    izbaciPrvi(a,velicina);
    izbaciPrvi(a,velicina);
    izbaciPrvi(a,velicina);
    izbaciPrvi(a,velicina);
    izbaciPrvi(a,velicina);
    for(int i(0);i<a.size();i++){
        cout<<a[i]<<velicina;
    }    
}