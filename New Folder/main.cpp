#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
using namespace std;




template <typename TipKljuca, typename TipVrijednosti> class Mapa {
private:
  void operator=(const Mapa &);
  Mapa(const Mapa &);

public:
  Mapa() {}
  virtual ~Mapa() {}
  virtual int brojElemenata() const = 0;
  virtual void obrisi() = 0;
  virtual void obrisi(const TipKljuca &kljuc) = 0;
  virtual TipVrijednosti &operator[](TipKljuca kljuc)  = 0;
  virtual TipVrijednosti operator[](TipKljuca index) const = 0;
};
template <typename TipKljuca, typename TipVrijednosti>
class NizMapa : public Mapa<TipKljuca, TipVrijednosti> {
private:
   int cap;
   int len;
   std::pair<TipKljuca, TipVrijednosti> **M;
public:
  NizMapa(int size = 100000) {
    cap = size;
    len = 0;
    M = new std::pair<TipKljuca, TipVrijednosti> *[cap] {};
  }
  NizMapa(const NizMapa<TipKljuca, TipVrijednosti> &mapa)
      : cap(mapa.cap), len(mapa.len) {
    M = new std::pair<TipKljuca, TipVrijednosti> *[mapa.cap] {};
    for (int i = 0; i < len; i++)
      M[i] = new std::pair<TipKljuca, TipVrijednosti>(*mapa.M[i]);
  }
  NizMapa<TipKljuca, TipVrijednosti> operator=(const NizMapa<TipKljuca, TipVrijednosti> &mapa) {
      if(&mapa!=this){
          obrisi();
          cap = mapa.cap;
    len = mapa.len;
    for (int i = 0; i < len; i++)
      M[i] = new std::pair<TipKljuca, TipVrijednosti>(*mapa.M[i]);
      }
    return *this;
  }
  ~NizMapa() {
    obrisi();
    delete[] M;
  }
  int brojElemenata() const override { return len; };
  void obrisi() override {
    for (int i = 0; i < len; i++) {
      delete M[i];
    }
    len = 0;
  }
  void obrisi(const TipKljuca &kljuc) override {
    for (int x = 0; x < len; x++) {
      if (M[x]->first == kljuc) {
        delete M[x];
        for(int j=x;j<len-1;j++){
            M[j]=M[j+1];
        }
        len--;
        break;
      }
      
    }
  }
  void Ispisi() {
    if (len == 0)
      throw std::logic_error("Mapa prazna!");
    for (int i = 0; i < len; i++) {
      std::cout << M[i]->first << " " << M[i]->second << std::endl;
    }
  }
  TipVrijednosti &operator[](TipKljuca kljuc) override {
      bool flag=false;
      for(int i=0;i<len;i++){
          if(M[i]->first==kljuc){
              flag=true;
              return M[i]->second;
          }
      }
          if(!flag){
             M[len] = new std::pair<TipKljuca, TipVrijednosti>(kljuc,TipVrijednosti());
             len++;
          }
      
    return M[len - 1]->second;
  }
  TipVrijednosti operator[](TipKljuca index) const override {
      for(int i=0;i<len;i++){
          if(M[i]->first==index){
              return M[i]->second;
          }
      }
      return TipVrijednosti();
  }
};


//-----------------------------------------------------------------------------------------------------


template <typename TipKljuca, typename TipVrijednosti>
class HashMapa : public Mapa<TipKljuca, TipVrijednosti> {
private:
   unsigned int(*hash_funkcija)(TipKljuca input ,unsigned int output);
   int cap;
   int len;
   std::pair<TipKljuca,TipVrijednosti> **M;
public:

  void definisiHashFunkciju(unsigned int(*hash)(TipKljuca input ,unsigned int output)){
      hash_funkcija=hash;
  }

  HashMapa(int size = 10000) : M(nullptr), len(0), cap(size), hash_funkcija(nullptr) {
    M = new std::pair<TipKljuca, TipVrijednosti> *[cap] {};
  }
  HashMapa(const HashMapa<TipKljuca, TipVrijednosti> &mapa)
      : cap(mapa.cap), len(mapa.len) {
           hash_funkcija=mapa.hash_funkcija;
    M = new std::pair<TipKljuca, TipVrijednosti> *[mapa.cap] {};
    for(int i=0;i<mapa.cap;i++){
        if(mapa.M[i]!=nullptr) M[i]= new std::pair<TipVrijednosti,TipKljuca>(*mapa.M[i]);
    }
      }
  HashMapa<TipKljuca, TipVrijednosti> operator=(const HashMapa<TipKljuca, TipVrijednosti> &mapa) {
      if(&mapa!=this){
          obrisi();
          cap = mapa.cap;
    len = mapa.len;
     hash_funkcija=mapa.hash_funkcija;
    for(int i=0;i<mapa.cap;i++){
        if(mapa.M[i]!=nullptr) M[i]= new std::pair<TipVrijednosti,TipKljuca>(*mapa.M[i]);
    }
      }
    return *this;
  }
  ~HashMapa() {
    obrisi();
    delete[] M;
  }
  int brojElemenata() const override { return len; };
  void obrisi() override {
    for (int i = 0; i < cap; i++) {
        if(M[i]!=nullptr){
            delete M[i];
            M[i]=nullptr;
        }
    }
    len = 0;
  }
  void obrisi(const TipKljuca &kljuc) override {
       unsigned int indeks=hash_funkcija(kljuc,cap);
      for(int i=indeks;i<cap;i++){
          if(i==indeks-1)break;
          if(M[i]!=nullptr && M[i]->first==kljuc){
              delete M[i];
              len--;
              M[i]=nullptr;
              break;
          }
           if(i==cap-1) i=0;
      }
  }
 
  TipVrijednosti &operator[](TipKljuca kljuc) override {
       if(!hash_funkcija)  throw "Hash funkcija nije definisana";
       unsigned int indeks=hash_funkcija(kljuc,cap);
     if(indeks < cap && M[indeks]!=nullptr && M[indeks]->first==kljuc){
              return M[indeks]->second;
      }
      for(int i=indeks;i<cap;i++){
          if(i==indeks-1)break;
          if(M[i]!=nullptr && M[i]->first==kljuc)
           return M[i]->second;
           if(i==cap-1) i=0;
      }
      for(int i=indeks;i<cap;i++){
          if(i==indeks-1)break;
          if(M[i]==nullptr){
             M[i] = new std::pair<TipKljuca, TipVrijednosti>(kljuc,TipVrijednosti());
              len++;
              return M[i]->second;
          }
           if(i==cap-1) i=0;
      }
    return M[indeks]->second;
  }
  TipVrijednosti operator[](TipKljuca index) const override {
     if(!hash_funkcija)  throw "Hash funkcija nije definisana";
      unsigned int indeks=hash_funkcija(index,cap);
      if(indeks < cap && M[indeks]!=nullptr && M[indeks]->first==index){
              return M[indeks]->second;
      }
      return TipVrijednosti();
  }
};

// Testiranje klase


void Test1(){
    NizMapa<std::string,std::string> m;
    m["Sarajevo"] = "BiH";
    m["Zagreb"] = "Hrvatska";
    if(m.brojElemenata()==2) cout<<"Tačno!";
}
void Test2(){    
    NizMapa<std::string,std::string> m;
    m["Sarajevo"] = "BiH";
    m["Zagreb"] = "Hrvatska";
    m.obrisi("Zagreb");
    if(m.brojElemenata()==1) cout<<"Tačno!";
}
void Test3(){  
    NizMapa<std::string,std::string> m;
    m["Sarajevo"] = "BiH";
    m["Zagreb"] = "Hrvatska";
    m.obrisi();
    if(m.brojElemenata()==0) cout<<"Tačno!";
}
void Test4(){   
    NizMapa<std::string,std::string> m;
    m["Sarajevo"] = "BiH";
    m["Zagreb"] = "Hrvatska";
    cout<<m["Zagreb"];
}
void Test5(){
    NizMapa<std::string,std::string> m;
    m["Sarajevo"] = "BiH";
    m["Zagreb"] = "Hrvatska";
    cout<<m["Sarajevo"];
}

int main() {
HashMapa<std::string,std::string> m;
// Nije definisana hash funkcija!
std::string s1("Sarajevo"), s2("Zagreb");
m[s1] = "BiH";
m[s2] = "Hrvatska";
std::cout << m.brojElemenata() << " " << m[s2];
  return 0;
}