#include <iostream>
#include <stdexcept>
#include <memory>
template <typename T>
class Lista{
    private:
    void operator =(const Lista&);
    Lista(const Lista&);
  public:
    Lista(){}
    virtual ~Lista(){}
    virtual int brojElemenata()const=0;
    virtual T &trenutni()const=0;
    virtual bool sljedeci()=0;
    virtual bool prethodni()=0;
    virtual void pocetak()=0;
    virtual void kraj()=0;
    virtual void obrisi()=0;
    virtual void dodajIspred(const T& el)=0;
    virtual void dodajIza(const T& el)=0;
    virtual T &operator [](int i) = 0;
    virtual T operator [](int i) const = 0;
};
template <typename T>
class NizLista: public Lista<T>{
  protected:
  mutable int cap;
  mutable int len;
  mutable int cur;
  mutable T **L;
  public:
    NizLista(int size=10000){
        cap=size;
        len=cur=0;
        L=new T*[cap]{};
    }
    NizLista(const NizLista<T> &lista): cap(lista.cap),len(lista.len),cur(lista.cur){
        L=new T*[cap]{};
        for(int i=0;i<len;i++)
        L[i]=new T(*lista.L[i]);
    }
    void operator =(const NizLista<T> &lista){
        cap=lista.cap;
        len=lista.len;
        cur=lista.cur;
        for(int i=0;i<len;i++)
        L[i]=new T(*lista.L[i]);
    }
     ~NizLista(){
        for(int i=0;i<len;i++){
            delete L[i];
        }
        delete[] L;
    }
    int brojElemenata()const override {return len;};
    T &trenutni()const override{
        if(len<=0) throw std::logic_error("Lista prazna!");
        return *L[cur];};
    bool sljedeci()override{
        if(len<=0) throw std::logic_error("Lista prazna!");
        if(cur<len-1) {
            cur++;
            return true;
        }
            return false;
    };
    bool prethodni()override{
        if(len<=0) throw std::logic_error("Lista prazna!");
         if(cur!=0){
            cur--;
            return true;
        }
        return false;
    };
    void pocetak()override{
        if(len<=0) throw std::logic_error("Lista prazna!");
        cur=0;
    };
    void kraj()override{
        if(len<=0) throw std::logic_error("Lista prazna!");
        cur=len-1;
    };
    void obrisi()override{
        if(len<=0) throw std::logic_error("Lista prazna!");
        delete L[cur];
            for(int i=cur;i<len-1;i++)
            L[i]=L[i+1];
            if(cur==len-1){
            cur=len-2;
        }
        len--;
        
    };
    void dodajIspred(const T& el)override{
        if(len<cap){
              if(len==0){
                  cur=0;
         L[cur]=new T(el);
     }
     else{
         for(int i=len;i>cur;i--)
            L[i]=L[i-1];
            L[cur]=new T(el);
            cur++;
     }
     len++;
    }
    };
    void dodajIza(const T& el)override{
    if(len<cap){
              if(len==0){
                  cur=0;
         L[cur]=new T(el);
     }
     else{
         for(int i=len;i>cur;i--)
            L[i]=L[i-1];
            L[cur+1]=new T(el);
     }
        len++;
        }
    };
    void Ispisi(){
         if(len==0) throw std::logic_error("Lista prazna!");
        for(int i=0;i<len;i++){
            std::cout<<*L[i]<<" ";
        }
        std::cout<<std::endl;
    }
    T &operator [](int i)override{
        if(i<0 || i>=len)std::domain_error("Neispravan index!");
        return *L[i];
    };
    T operator [](int i) const override{
        if(i<0 || i>=len)std::domain_error("Neispravan index!");
        return *L[i];
    };
};


template <typename T>
class JednostrukaLista: public Lista<T>{
  private:
    struct Cvor{
        T info;
        Cvor*next;
        Cvor(const T &element,Cvor* sljedeci):info(element),next(sljedeci){}
    };
  mutable int dlen,llen;
  mutable Cvor* begin;
  mutable Cvor* end;
  mutable Cvor* cur;
  public:
    JednostrukaLista(): begin(nullptr), end(nullptr), cur(nullptr),llen(0),dlen(0){}
    JednostrukaLista(const JednostrukaLista<T> &lista): begin(nullptr), end(nullptr), cur(nullptr),llen(0),dlen(0){
        for(auto i=lista.begin;i!=nullptr;i=i->next){
            dodajIspred(i->info);
        }
    }
    void operator =(const JednostrukaLista<T> &lista){
        for(auto i=lista.begin;i!=nullptr;i=i->next){
            dodajIspred(i->info);
        }
    }
     ~JednostrukaLista(){
        for(auto i=begin;i!=nullptr;){
            auto j=i->next;
            delete i;
            i=j;
        }
    }
    int DajDesnuDuzinu()const {return dlen;};
    int DajLijevuDuzinu()const {return llen;};
    int brojElemenata()const override {return dlen+llen;};
    T &trenutni()const override{
        if(llen+dlen<=0) throw std::logic_error("Lista prazna!");
        return cur->info;
        }
    bool sljedeci()override{
        if(llen+dlen<=0) throw std::logic_error("Lista prazna!");
        if(cur!=end){
            cur=cur->next;
            llen++;
            dlen--;
            return true;
            }
            return false;
        }
    bool prethodni()override{
        if(llen+dlen<=0) throw std::logic_error("Lista prazna!");
         if(cur!=begin){
             auto x=begin;
             for(auto y=begin;y!=cur;y=y->next)
                x=y;
             cur=x;
             llen--;
             dlen++;
             return true;
         }
         return false;
    };
    void pocetak()override{
        if(llen+dlen<=0) throw std::logic_error("Lista prazna!");
        cur=begin;
        dlen+=llen;
        llen=0;
    };
    void kraj()override{
         if(llen+dlen<=0) throw std::logic_error("Lista prazna!");
        cur=end;
        llen+=dlen;
        dlen=0;
    };
    void obrisi()override{
        if(dlen<=0) throw std::logic_error("Nema se šta izbaciti!");
        Cvor *p=begin;
            if(llen==0){
                p=begin;
                begin=p->next;
                cur=begin;
            }
            else{
                if(dlen!=1){
                    for(auto x=begin;x!=cur;x=x->next){
                        p=x;
                    }
                    p->next=cur->next;
                }
                p=cur;
                cur=p->next;
            }
            if(dlen==1){
                if(brojElemenata()!=1){
                    for(auto y=begin;y!=cur;y=y->next)
                    p=y;
                    cur=p;
                    p=cur->next;
                    dlen++;
                    llen--;
                }
                end=cur;
            }
            delete p;
            dlen--;
    };
    void dodajIspred(const T& el)override{
        Cvor *novi=new Cvor(el,nullptr);
        if(llen+dlen==0){
        cur=begin=end=novi;
        dlen++;
     }
     else{
         Cvor *x=begin;
          for(auto y=begin;y!=cur;y=y->next){
                        x=y;
                    }
            if(x==begin && brojElemenata()==1){
                begin=novi;
                novi->next=cur;
            }
            else{
                novi->next=cur;
                x->next=novi;
            }
            llen++;
     }
    }
    void dodajIza(const T& el)override{
         Cvor *novi=new Cvor(el,nullptr);
        if(llen+dlen==0){
        cur=begin=end=novi;
     }
     else{
            if(cur->next==nullptr){
                end=novi;
                cur->next=novi;
            }
            else{
                novi->next=cur->next;
                cur->next=novi;
            }
     }
     dlen++;
    };

    T &operator [](int i)override{
        if(i<0 || i>=llen+dlen)std::domain_error("Neispravan index!");
        auto temp=begin;
        for(int j=0;j<i;j++){
            temp=temp->next;
        }
        return temp->info;
    };
    T operator [](int i) const override{
       if(i<0 || i>=llen+dlen)std::domain_error("Neispravan index!");
        auto temp=begin;
        for(int j=0;j<i;j++){
            temp=temp->next;
        }
        return temp->info;
    };
};


int main()
{
JednostrukaLista<int> a;
NizLista<int> b;
JednostrukaLista<int> c(a);
NizLista<int> d(b);
a.dodajIspred(1);
b.dodajIspred(2);
std::cout<<a.trenutni()<<" "<<b.trenutni()<<std::endl;
for(int i=0;i<50;i++)
c.dodajIspred(i+1);
for(int i=0;i<50;i++)
d.dodajIspred(i+1);
std::cout<<c.trenutni()<<" "<<d.trenutni()<<std::endl;
c.pocetak();
d.kraj();
std::cout<<c.trenutni()<<" "<<d.trenutni()<<std::endl;
a.dodajIspred(3);
b.dodajIspred(4);
a.dodajIspred(5);
b.dodajIspred(6);
a.dodajIspred(7);
b.dodajIspred(8);
a.prethodni();
b.prethodni();
a.obrisi();
b.obrisi();
std::cout<<a.trenutni()<<" "<<b.trenutni()<<std::endl;
std::cout<<a.brojElemenata()<<" "<<b.brojElemenata()<<std::endl;
c.dodajIza(3);
d.kraj();
d.dodajIza(23);
std::cout<<a[2]<<" "<<c[10]<<std::endl;
d[4]=5;
    return 0;
}