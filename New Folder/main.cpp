#include <iostream>
#include <memory>
#include <ctime>
#include <stdexcept>
#include <string>
#include <utility>

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
class BinStabloMapa : public Mapa<TipKljuca, TipVrijednosti> {
private:
    struct BSCvor{
    std::pair<TipKljuca,TipVrijednosti> pair;
    BSCvor(){left=right=parent=0;}
    BSCvor(const std::pair<TipKljuca,TipVrijednosti> &p){
        pair=p; left=0; right=0; parent=0;
    }
    BSCvor *left,*right,*parent;
};
   int len;
   BSCvor *root;
   
   BSCvor *Umetni(BSCvor* &c, std::pair<TipKljuca,TipVrijednosti> &par) {
    if(!c)
    return new BSCvor(par);
    
    if (par.first < c->pair.first){
      c->left = Umetni(c->left, par);
      c->left->parent = c; 
    }
    else if (par.first > c->pair.first){
      c->right = Umetni(c->right, par);
      c->right->parent = c;
    }
    else {
      c->pair.second=par.second;
    }
    return c;
    } 

    BSCvor *Trazi(BSCvor* r, const TipKljuca& x) const {
        if(!r) return nullptr;
    if (x < r->pair.first)
        return Trazi(r->left, x);
    else if (x > r->pair.first)
        return Trazi(r->right, x);
    else
        return r;
    }

    BSCvor *Copy(BSCvor *r){
      if (!r)
      return nullptr;
      BSCvor* new_root=new BSCvor(r->pair);
      new_root->left=Copy(r->left);
      new_root->right=Copy(r->right);
      return new_root;
    }

    void Delete(BSCvor *r){
      if(r==nullptr) return;
      Delete(r->left);
      Delete(r->right);
      delete r;
    }

public:
  BinStabloMapa() {
    len = 0;
    root = 0;
  }
  BinStabloMapa(const BinStabloMapa<TipKljuca, TipVrijednosti> &mapa)
      : len(mapa.len),root(nullptr) {
    root = Copy(mapa.root);
  }
  BinStabloMapa<TipKljuca, TipVrijednosti> &operator=(const BinStabloMapa<TipKljuca, TipVrijednosti> &mapa) {
      if(&mapa!=this){
          Delete(root);
          root=Copy(mapa.root);
          len=mapa.len;
      }
    return *this;
  }
  ~BinStabloMapa() {
    obrisi();
  }
  int brojElemenata() const override { return len; };
  void obrisi() override {
    Delete(root);
    root=nullptr;
    len = 0;
  }
  void obrisi(const TipKljuca &kljuc) override {
    BSCvor *temp=Trazi(root,kljuc);
    temp->pair.second=TipVrijednosti();
    len--;
  }

  TipVrijednosti &operator[](TipKljuca kljuc) override {
     BSCvor *temp=Trazi(root,kljuc);
     if(!temp){
         std::pair<TipKljuca,TipVrijednosti> par(kljuc,TipVrijednosti());
         root=Umetni(root,par);
         len++;
         temp = Trazi(root, kljuc);
     }
     return temp->pair.second;
  } 
  TipVrijednosti operator[](TipKljuca index) const override {
    BSCvor *temp=Trazi(root,index);
     if(!temp){
         return TipVrijednosti();
     }
     return temp->pair.second;
  }
};

//-----------------------------------------------------------------------------------------------------------

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

//------------------------------------------------------------------------------------------------------------------------------

// Testiranje klasa


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

//------------------------------------------------------------------------------------------------------------------------------

int main() {
   // Osnovni test funkcionalnosti BinStabloMapa
BinStabloMapa<std::string,std::string> m1;
NizMapa<std::string,std::string> m2;
clock_t vrijeme1 = clock();
for(int i=0;i<10000;i++){
    m1[std::string(to_string(i))] = i;
}
clock_t vrijeme2 = clock();
int ukvrijeme1 = (vrijeme2 - vrijeme1) / (CLOCKS_PER_SEC / 1000);
for(int i=0;i<10000;i++){
    m2[std::string(to_string(i))] = i;
}
clock_t vrijeme3 = clock();
int ukvrijeme2 = (vrijeme3 - vrijeme2) / (CLOCKS_PER_SEC / 1000);
cout << "Vrijeme izvrsenja NizMapa: " << ukvrijeme2 << " ms." << endl;
cout << "Vrijeme izvrsenja BinStabloMapa: " << ukvrijeme1 << " ms." << endl;

clock_t vrijeme4 = clock();
cout << m2["9999"] << endl;
clock_t vrijeme5 = clock();
int ukvrijeme3 = (vrijeme5 - vrijeme4) / (CLOCKS_PER_SEC / 1000);
cout << m1["9999"] << endl;
clock_t vrijeme6 = clock();
int ukvrijeme4 = (vrijeme6 - vrijeme5) / (CLOCKS_PER_SEC / 1000);
cout << "Vrijeme nalaženja NizMapa: " << ukvrijeme3 << "ms" << endl;
cout << "Vrijeme nalaženja BinStabloMapa: " << ukvrijeme4 << "ms" << endl;
  return 0;
}