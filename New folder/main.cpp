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
    virtual const T& skiniSaCela()=0; //
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
    Cvor* top;
    Cvor* bot;
    int size;
    void kopiraj(const DvostraniRed &s);
    public:
    void brisi()override;
    DvostraniRed() : top(nullptr),bot(nullptr),size(0) {} 
    DvostraniRed(const DvostraniRed &s){kopiraj(s);}
    ~DvostraniRed(){brisi();}
    DvostraniRed &operator =(const DvostraniRed &s);
    void staviNaCelo(const T &info) override {
        Cvor *n(new Cvor(info,0,0));
        if(top==0)
        top=bot=n;
        else{
            n->prev=top;
            top->next=n;
            top=n;
        }
        size++;
         }
    void staviNaVrh(const T &info) override {
        Cvor *n(new Cvor(info,0,0));
        if(bot==0)
        top=bot=n;
        else{
            bot->next=n;
            n->prev=bot;
            bot=n;
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
        staviNaCelo(p->info);
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
   T element(top->info);
   Cvor *p=top;
   if(top==bot)
   top=bot=0;
   else{
      top->next->prev=nullptr;
      top=top->next; 
   }
   delete p;
   size--;
   return element;
}
template <typename T>
T DvostraniRed<T>::skiniSaCela(){
   if(size<=0) throw std::logic_error("Prazan stek!");
   T element(bot->info);
   Cvor *p=bot;
   if(bot==top)
   top=bot=0;
   else{
      top->prev->next=nullptr;
      bot=bot->prev; 
   }
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
int main(){
    
    return 0;
}
    