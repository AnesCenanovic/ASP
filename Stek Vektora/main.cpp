#include <iostream>
#include <stdexcept>
#include <memory>
#include <vector>
using namespace std;
template <typename T>
class lol{
    private:
    void operator =(const lol&);
    lol(const lol&);
  public:
    lol(){}
    virtual ~lol(){}
    virtual int brojElemenata()const=0;
    virtual T skini()=0;
    virtual const T& vrh()=0;
    virtual void stavi(const T&)=0;
    virtual void brisi()=0;
};
template <typename T>
class Stek:public lol<T>{
    private:
     struct Cvor{
        T info;
        Cvor*sljedeci;
        Cvor(const T &element,Cvor* sljedeci):info(element),sljedeci(sljedeci){}
    };
    Cvor* top;
    int size;
    void kopiraj(const Stek &s);
    public:
    Stek() : top(0),size(0) {} 
    Stek(const Stek &s){kopiraj(s);}
    ~Stek(){brisi();}
    Stek &operator =(const Stek &s);
    void stavi(const T &info) override {
        top = new Cvor(info, top); size++;
         } 
    T skini()override;
    T& vrh() override;
    void brisi() override;
    int brojElemenata()const override {return size;}
    bool empty()const {return top==0;};
    void Ispisi()const;
};
template <typename T>
void Stek<T>::kopiraj(const Stek &s){
    Cvor *q,*p(s.top);
    top=0;
    size=s.size;
    while(p!=0){
        Cvor *r(new Cvor(p->info,0));
        if(top==0)
        top=r;
        else
        q->sljedeci=r;
        p=p->sljedeci;
        q=r;
    }
}
template <typename T>
Stek<T> &Stek<T>::operator =(const Stek &s){
    if(&s==this) return *this;
    brisi();
    kopiraj(s);
    return *this;
}
template <typename T>
T Stek<T>::skini(){
   if(size<=0)  throw std::logic_error("Prazan stek!");
   T element(top->info);
   Cvor *p=top->sljedeci;
   delete top;
   top=p;
   size--;
   return element;
}
template <typename T>
 T &Stek<T>::vrh(){
    if(top==0)  throw std::logic_error("Prazan stek!");
    return top->info;
}
template <typename T>
void Stek<T>::brisi(){
    while(!empty())
    skini();
}
template <typename T>
void Stek<T>::Ispisi()const{
    Cvor *p(top);
    while(p!=0){
        std::cout<<p->info<<" ";
        p=p->sljedeci;
    }
    std::cout<<std::endl;
}

void pretraga(Stek<vector<int> >& s, int trazeni){
     bool flag=false;
     int br=0,index;
     std::vector<std::vector<int>> temp(s.brojElemenata());
     while(br<temp.size() && flag==false){
         temp[br]=s.skini();
         int a=0,v=temp[br].size()-1, mid;
         while(v>=a){
             mid=(v+a)/2;
             if(trazeni==temp[br][mid]){flag=true;index=mid;break;}
             else if(temp[br][mid]<trazeni) a=mid+1;
             else v=mid-1;
         }
         br++;
     }
     for(int i=br-1;i>=0;i--) s.stavi(temp[i]);
     if (flag) std::cout << index << " " << s.brojElemenata() - br;
     else std::cout << "Nema elementa";
}
// Funkcije za testiranje metoda
void Test1() {
    vector<int> a{1,2,3,4,5};
    vector<int> b{6,7,8};
    vector<int> c{9,10,11};
    Stek<vector<int>> s;
    s.stavi(a);
    s.stavi(b);
    s.stavi(c);
    pretraga(s,7);
}

void Test2() {
    vector<int> a{1,2,3,4,5};
    vector<int> b{6,7,8};
    vector<int> c{9,10,11};
    vector<int> d{12,13,14};
    Stek<vector<int>> s;
    s.stavi(a);
    s.stavi(b);
    s.stavi(c);
    s.stavi(d);
    pretraga(s,14);
}

void Test3() {
    vector<int> a{1,2,3,4,5};
    vector<int> b{6,7,8};
    vector<int> c{9,10,11};
    vector<int> d{12,13,14};
    vector<int> e{12,13,14,16,17,18};
    Stek<vector<int>> s;
    
    s.stavi(a);
    s.stavi(b);
    s.stavi(c);
    s.stavi(d);
    s.stavi(e);
    pretraga(s,19);
}
int main(){
    Test1();
    Test3();
    Test2();
    return 0;
}