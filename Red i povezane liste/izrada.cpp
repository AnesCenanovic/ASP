#include <iostream>
#include <stdexcept>
#include <memory>
using namespace std;
template <typename T>
class islam{
    private:
    void operator =(const islam&);
    islam(const islam&);
  public:
    islam(){}
    virtual ~islam(){}
    virtual int brojElemenata()const=0;
    virtual T skini()=0;
    virtual const T& celo()=0;
    virtual void stavi(const T&)=0;
    virtual void brisi()=0;
};
template <typename T>
class Red:public islam<T>{
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
    while(p!=0){
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
void IzmjeniStek(Stek<int> &stek,Red<int> &red,int pocetnaDuzinaReda){
    int temp=stek.brojElemenata();
    while(!stek.empty()){
        red.stavi(stek.vrh());
        stek.skini();
    }
for(int i=0;i<pocetnaDuzinaReda;i++){
        stek.stavi(red.skini());
    }
for(int i=0;i<pocetnaDuzinaReda;i++){
        red.stavi(stek.skini());
    }
while(!red.empty()){
    stek.stavi(red.skini());
}

while(!stek.empty()){
    red.stavi(stek.skini());
}

while(!red.empty()){
    stek.stavi(red.skini());
}
stek.Ispisi();
std::cout<<stek.vrh();
}
int main(){
    int average=0;
    int temp;
    Red<int> red;
    for (int i(1); i<=5; i++)
	red.stavi(i);
    red.Ispisi();
    for(int i=0;i<red.brojElemenata();i++){
        temp=red.skini();
        average+=temp;
        red.stavi(temp);
    }
    std::cout<<average/red.brojElemenata()<<std::endl;
    red.Ispisi();
    for(int i=0;i<red.brojElemenata();i++){
        temp=red.skini();
        if(temp<average/red.brojElemenata())
        continue;
        else red.stavi(temp);
    }
      red.Ispisi();
      Red<int> red2;
    for (int i(1); i<=4; i++)
	red2.stavi(i);
    Stek<int> stek;
    for (int i(5); i<=8; i++)
	stek.stavi(i);
    red2.Ispisi();
    std::cout<<red2.celo()<<std::endl;
    stek.Ispisi();
    std::cout<<stek.vrh()<<std::endl;
    IzmjeniStek(stek, red2,4);
    return 0;
}