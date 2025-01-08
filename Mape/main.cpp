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
  virtual TipVrijednosti &operator[](TipKljuca kljuc) = 0;
  virtual TipVrijednosti operator[](TipKljuca index) const = 0;
};
template <typename TipKljuca, typename TipVrijednosti>
class NizMapa : public Mapa<TipKljuca, TipVrijednosti> {
private:
   int cap;
   int len;
   std::pair<TipKljuca, TipVrijednosti> **M;
public:
  NizMapa(int size = 10000) {
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
    Test1();
    Test2();
    Test3();
    Test4();
    Test5();
  return 0;
}