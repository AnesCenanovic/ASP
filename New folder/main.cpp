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

template <typename TipKljuca, typename TipVrijednosti>
class AVLStabloMapa : public Mapa<TipKljuca, TipVrijednosti> {
private:
    struct AVLCvor{
    std::pair<TipKljuca,TipVrijednosti> pair;
    AVLCvor(){left=right=parent=0;}
    AVLCvor(const std::pair<TipKljuca,TipVrijednosti> &p){
        pair=p; left=0; right=0; parent=0,h=1;
    }
    AVLCvor *left,*right,*parent;
    int h;
};
   int len;
   AVLCvor *root;

   int height(AVLCvor *c){
       if(!c) return 0;
       return c->h;
   }
   int balance(AVLCvor *c){
       if(!c) return 0;
       return height(c->left)-height(c->right);
   }

   void azurirajVisinu(AVLCvor *c){
       c->h=max(height(c->left),height(c->right)+1);
   }

   AVLCvor *azurirajBalans(AVLCvor *c){
       azurirajVisinu(c);
       int bal=balance(c);
       if(bal==2){
           if(balance(c->left)<0)
            c->left=leftRotation(c->left);
            return rightRotation(c);
       }
       else if(bal==-2){
           if(balance(c->right)>0)
            c->right=rightRotation(c->right);
            return leftRotation(c);
       }
       return c;
   }

   AVLCvor *leftRotation(AVLCvor *c){
       AVLCvor *temp=c->right;
       c->right=temp->left;
       temp->left=c;
       azurirajVisinu(c);
       azurirajVisinu(temp);
       return temp;
   }

   AVLCvor *rightRotation(AVLCvor *c){
       AVLCvor *temp=c->left;
       c->left=temp->right;
       temp->right=c;
       azurirajVisinu(c);
       azurirajVisinu(temp);
       return temp;
   }
   
   AVLCvor *Umetni(AVLCvor* &c, std::pair<TipKljuca,TipVrijednosti> &par) {
    if(!c)
    return new AVLCvor(par);
    
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
    return azurirajBalans(c);
    } 

    AVLCvor *Trazi(AVLCvor* r, const TipKljuca& x) const {
        if(!r) return nullptr;
    if (x < r->pair.first)
        return Trazi(r->left, x);
    else if (x > r->pair.first)
        return Trazi(r->right, x);
    else
        return r;
    }

    AVLCvor *Copy(AVLCvor *r){
      if (!r)
      return nullptr;
      AVLCvor* new_root=new AVLCvor(r->pair);
      new_root->left=Copy(r->left);
      new_root->right=Copy(r->right);
      return new_root;
    }

    void Delete(AVLCvor *r){
      if(r==nullptr) return;
      Delete(r->left);
      Delete(r->right);
      delete r;
    }

public:
 AVLStabloMapa() {
    len = 0;
    root = 0;
  }
  AVLStabloMapa(const AVLStabloMapa<TipKljuca, TipVrijednosti> &mapa)
      : len(mapa.len),root(nullptr) {
    root = Copy(mapa.root);
  }
  AVLStabloMapa<TipKljuca, TipVrijednosti> &operator=(const AVLStabloMapa<TipKljuca, TipVrijednosti> &mapa) {
      if(&mapa!=this){
          Delete(root);
          root=Copy(mapa.root);
          len=mapa.len;
      }
    return *this;
  }
  ~AVLStabloMapa() {
    obrisi();
  }
  int brojElemenata() const override { return len; };
  void obrisi() override {
    Delete(root);
    root=nullptr;
    len = 0;
  }
  void obrisi(const TipKljuca &kljuc) override {
    AVLCvor *temp=Trazi(root,kljuc);
    temp->pair.second=TipVrijednosti();
    len--;
  }

  TipVrijednosti &operator[](TipKljuca kljuc) override {
     AVLCvor *temp=Trazi(root,kljuc);
     if(!temp){
         std::pair<TipKljuca,TipVrijednosti> par(kljuc,TipVrijednosti());
         root=Umetni(root,par);
         len++;
         temp = Trazi(root, kljuc);
     }
     return temp->pair.second;
  } 
  TipVrijednosti operator[](TipKljuca index) const override {
    AVLCvor *temp=Trazi(root,index);
     if(!temp){
         return TipVrijednosti();
     }
     return temp->pair.second;
  }
};


int main() {
    AVLStabloMapa <int,int> mapa1;
    BinStabloMapa <int,int> mapa2;
    clock_t vrijeme1=clock();
    for(int i=0;i<10000;i++)
    mapa1[i]=i;
    clock_t vrijeme2=clock();
    for(int i=0;i<10000;i++)
    mapa2[i]=i;
    clock_t vrijeme3=clock();
    cout<<"AVL Stablo performanse: "<<int(vrijeme2-vrijeme1) / (CLOCKS_PER_SEC/1000)<<" ms"<<endl;
    cout<<"Bin Stablo performanse: "<<int(vrijeme3-vrijeme2) / (CLOCKS_PER_SEC/1000)<<" ms"<<endl;
  return 0;
}