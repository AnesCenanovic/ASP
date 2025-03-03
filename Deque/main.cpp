#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <memory>
using namespace std;
template <typename T>
class Red{
    private:
    void operator =(const Red&); //
    Red(const Red&); //
  public:
    Red(){} //
    virtual ~Red(){}
    virtual int brojElemenata()const=0; //
    virtual T skiniSaVrha()=0; //
    virtual T skiniSaCela()=0; //
    virtual void staviNaVrh(const T&)=0; //
    virtual void brisi()=0;
    virtual void staviNaCelo(const T&)=0; //
    virtual const T& vrh()=0; //
    virtual const T& celo()=0; //
};
template <typename T>
class DvostraniRed:public Red<T>{
    private:
     struct Cvor {
    T info;
    Cvor *next;
    Cvor *prev;
     Cvor(const T &element, Cvor *sljedeci, Cvor *prethodni)
        : info(element), next(sljedeci), prev(prethodni) {
            if(prev!=0) prev->next=this;
            if(next!=0) next->prev=this;
        }
        Cvor (Cvor *prethodni=0,Cvor *sljedeci=0):prev(prethodni),next(sljedeci){
             if(prev!=0) prev->next=this;
            if(next!=0) next->prev=this;
        }
    };
    mutable Cvor* top;
    mutable Cvor* bot;
    mutable int size;
    void kopiraj(const DvostraniRed &s);
    public:
    void brisi()override;
    DvostraniRed() : top(nullptr),bot(nullptr),size(0) {} 
    DvostraniRed(const DvostraniRed &s){
        top = bot = nullptr; size = 0; 
        kopiraj(s);}
    ~DvostraniRed(){brisi();}
    DvostraniRed &operator =(const DvostraniRed &s);
    void staviNaVrh(const T &info) override {
        Cvor *n=new Cvor(info,0,0);
        if(top==0)
        top=bot=n;
        else{
            bot->next=n;
            n->prev=bot;
            bot=bot->next;
        }
        size++;
        
         }
    void staviNaCelo(const T &info) override {
        Cvor *n(new Cvor(info,0,0));
        if(top==0)
        top=bot=n;
        else{
            top->prev=n;
            n->next=top;
            top=top->prev;
        }
        size++;
         } 
    T skiniSaVrha()override;
    T skiniSaCela()override;
    T& vrh() override{
        if(size<=0) throw std::logic_error("Prazan stek!");
        return bot->info;
    }
    T& celo() override{
        if(size<=0) throw std::logic_error("Prazan stek!");
        return top->info;
    }
    int brojElemenata()const override {return size;}
    bool empty()const {return top==0;};
    void Ispisi()const;
};
template <typename T>
void DvostraniRed<T>::kopiraj(const DvostraniRed& s){
    Cvor *p(s.top);
    while(p!=nullptr){
        staviNaVrh(p->info);
        p=p->next;
    }
}
template <typename T>
DvostraniRed<T> &DvostraniRed<T>::operator =(const DvostraniRed &s){
    if(&s==this) return *this;
    brisi();
    kopiraj(s);
    return *this;
}
template <typename T>
T DvostraniRed<T>::skiniSaVrha(){
   if(size<=0) throw std::logic_error("Prazan stek!");
   T element(bot->info);
   Cvor *p=bot;
   if(top==bot)
   top=bot=0;
   else bot=bot->prev;
   delete p;
   size--;
   return element;
}
template <typename T>
T DvostraniRed<T>::skiniSaCela(){
   if(size<=0) throw std::logic_error("Prazan stek!");
   T element(top->info);
   Cvor *p=top;
   if(bot==top)
   top=bot=0;
   else
   top=top->next;
   delete p;
   size--;
   return element;
}
template <typename T>
void DvostraniRed<T>::brisi(){
    while(!empty())
    skiniSaCela();
}
template <typename T>
void DvostraniRed<T>::Ispisi()const{
    Cvor *p(top);
    while(p!=0){
        std::cout<<p->info<<" ";
        p=p->next;
    }
    std::cout<<std::endl;
}

// Funckije testiranja metoda
void Test1(){
    DvostraniRed<int> dr;
     for(int i(1); i <= 5; i++)
        dr.staviNaCelo(i);
        dr.skiniSaCela();
        std::cout << dr.celo() << std::endl;
}
void Test2(){
    DvostraniRed<int> dr;
     for(int i(1); i <= 5; i++)
        dr.staviNaVrh(i);
        dr.skiniSaVrha();
        std::cout << dr.vrh() << std::endl;
}
void Test3(){
    Test1();
}
void Test4(){
    Test2();
}
void Test5(){
    Test1();
}
void Test6(){
    Test2();
}
void Test7() {
    DvostraniRed<int> dr;
    for(int i(1); i <= 5; i++)
        dr.staviNaVrh(i);
    std::cout << dr.brojElemenata() << std::endl;
}
bool Test8() {
    DvostraniRed<int> dr;
    for(int i(1); i <= 5; i++)
        dr.staviNaVrh(i);
    dr.brisi();
    if(dr.brojElemenata() == 0) return true;
    return false;
}
int main(){
    Test1();
    Test2();
    Test3();
    Test4();
    Test5();
    Test6();
    Test7();
    Test8();
    return 0;
}
    