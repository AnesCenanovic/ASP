#include <iostream>
#include <stdexcept>
#include <memory>
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
int main(){
    Stek<int> stek;
    for(int i=0;i<10;i++)
    stek.stavi(i);
    stek.Ispisi();
    stek.skini();
    stek.Ispisi();
    std::cout<<stek.vrh();
    std::cout<<stek.brojElemenata();
    Stek<int> stek2;
    stek2=stek;
    Stek<int> stek3(stek2);
    for(int i=0;i<10;i++)
    stek3.stavi(i);
    stek3.Ispisi();
    stek3.skini();
    stek3.Ispisi();
    return 0;
}