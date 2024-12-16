#include <iostream>
#include <stdexcept>
#include <memory>
using namespace std;
template <typename T>
class Red{
    private:
    void operator =(const Red&);
    Red(const Red&);
  public:
    Red(){}
    virtual ~Red(){}
    virtual int brojElemenata()const=0;
    virtual T skiniSaVrha()=0;
    virtual const T& skiniSaCela()=0;
    virtual void staviNaVrh(const T&)=0;
    virtual void brisi()=0;
    staviNaCelo();
 vrh();
 celo();
};
template <typename T>
class DvostraniRed:public Red<T>{
    private:
     struct Cvor{
        T info;
        Cvor*sljedeci;
        Cvor(const T &element,Cvor* sljedeci):info(element),sljedeci(sljedeci){}
    };
    Cvor* top;
    Cvor* bot;
    int size;
    void kopiraj(const Red &s);
    public:
    void brisi()override;
    Red() : top(0),bot(0),size(0) {} 
    Red(const Red &s){kopiraj(s);}
    ~Red(){brisi();}
    Red &operator =(const Red &s);
    void stavi(const T &info) override {
        Cvor *n(new Cvor(info,0));
        if(top==0)
        top=bot=n;
        else{
            bot->sljedeci=n;
            bot=bot->sljedeci;
        }
        size++;
         } 
    T skini()override;
    T& celo() override{
        if(size<=0) throw std::logic_error("Prazan stek!");
        return top->info;
    }
    int brojElemenata()const override {return size;}
    bool empty()const {return top==0;};
    void Ispisi()const;
};
template <typename T>
void Red<T>::kopiraj(const Red&s){
    Cvor *p(s.top);
    while(p!=nullptr){
        stavi(p->info);
        p=p->sljedeci;
    }
}
template <typename T>
Red<T> &Red<T>::operator =(const Red &s){
    if(&s==this) return *this;
    brisi();
    kopiraj(s);
    return *this;
}
template <typename T>
T Red<T>::skini(){
   if(size<=0) throw std::logic_error("Prazan stek!");
   T element(top->info);
   Cvor *p=top;
   if(top==bot)
   top=bot=0;
   else 
   top=top->sljedeci;
   delete p;
   size--;
   return element;
}
template <typename T>
void Red<T>::brisi(){
    while(!empty())
    skini();
}
template <typename T>
void Red<T>::Ispisi()const{
    Cvor *p(top);
    while(p!=0){
        std::cout<<p->info<<" ";
        p=p->sljedeci;
    }
    std::cout<<std::endl;
}
int main(){
    Red<int> red;
    for(int i=0;i<10;i++)
    red.stavi(i);
    red.Ispisi();
    red.skini();
    red.Ispisi();
    std::cout<<red.celo();
    std::cout<<red.brojElemenata();
    Red<int> red2;
    red2=red;
    Red<int> red3(red2);
    for(int i=0;i<10;i++)
    red3.stavi(i);
    red3.Ispisi();
    red3.skini();
    red3.Ispisi();
    return 0;
}
    