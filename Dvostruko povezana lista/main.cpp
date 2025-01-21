#include <iostream>
#include <memory>
#include <stdexcept>

using namespace std;

template <typename T> class Iterator;

template <typename T> class Lista {
private:
  void operator=(const Lista &);
  Lista(const Lista &);

public:
  Lista() {}
  virtual ~Lista() {}
  virtual int brojElemenata() const = 0;
  virtual T &trenutni() const = 0;
  virtual bool sljedeci() = 0;
  virtual bool prethodni() = 0;
  virtual void pocetak() = 0;
  virtual void kraj() = 0;
  virtual void obrisi() = 0;
  virtual void dodajIspred(const T &el) = 0;
  virtual void dodajIza(const T &el) = 0;
  virtual T &operator[](int i) = 0;
  virtual T operator[](int i) const = 0;
  virtual void Ispisi() const = 0;
};
template <typename T> class DvostrukaLista : public Lista<T> {
private:
  struct Cvor {
    T info;
    Cvor *next;
    Cvor *prev;
    Cvor(const T &element, Cvor *sljedeci, Cvor *prethodni)
        : info(element), next(sljedeci), prev(prethodni) {}
  };
  mutable int dlen, llen;
  mutable Cvor *begin;
  mutable Cvor *end;
  mutable Cvor *current;

public:
  DvostrukaLista()
      : begin(nullptr), end(nullptr), current(nullptr), llen(0), dlen(0) {}
  DvostrukaLista(const DvostrukaLista<T> &lista)
      : begin(nullptr), end(nullptr), current(nullptr), llen(0), dlen(0) {
    for (auto i = lista.begin; i != nullptr; i = i->next) {
      dodajIza(i->info);
      if (brojElemenata() != 1)
        current = current->next;
    }
  }
  DvostrukaLista<T> operator=(const DvostrukaLista<T> &lista) {
    if (&lista != this) {
      for (auto i = lista.begin; i != nullptr; i = i->next) {
        dodajIza(i->info);
        if (brojElemenata() != 1)
          current = current->next;
      }
    }
    return *this;
  }
  ~DvostrukaLista() {
    for (auto i = begin; i != nullptr;) {
      auto j = i->next;
      if (i != nullptr)
        delete i;
      i = j;
    }
  }
  void Ispisi() const override {
    if (llen + dlen <= 0)
      throw std::logic_error("Lista prazna!");
    Cvor *p = begin->next;
    while (p != end) {
      std::cout << p->info << " ";
      p = p->next;
    }
    std::cout << std::endl;
  }
  int DajDesnuDuzinu() const { return dlen; };
  int DajLijevuDuzinu() const { return llen; };
  int brojElemenata() const override { return dlen + llen; };
  T &trenutni() const override {
    if (llen + dlen <= 0)
      throw std::logic_error("Lista prazna!");
    return current->info;
  }
  bool prethodni() override {
    if (llen + dlen <= 0)
      throw std::logic_error("Lista prazna!");
    if (current != begin) {
      current = current->prev;
      llen--;
      dlen++;
      return true;
    }
    if (current == begin && dlen != brojElemenata())
      llen--;
    dlen++;
    return false;
  }
  bool sljedeci() override {
    if (llen + dlen <= 0)
      throw std::logic_error("Lista prazna!");
    if (current != end) {
      current = current->next;
      llen++;
      dlen--;
      return true;
    }
    if (current == end && llen != brojElemenata())
      llen++;
    dlen--;
    return false;
  };
  void pocetak() override {
    if (llen + dlen <= 0)
      throw std::logic_error("Lista prazna!");
    current = begin;
    dlen += llen;
    llen = 0;
  };
  void kraj() override {
    if (llen + dlen <= 0)
      throw std::logic_error("Lista prazna!");
    current = end;
    llen += dlen;
    dlen = 0;
  };
  void obrisi() override {
    if (dlen <= 0)
      throw std::logic_error("Nema se šta izbaciti!");
    Cvor *p = begin;
    if (llen == 0) {
      p = begin;
      begin = p->next;
      current = begin;
    } else {
      p = current;
      current = p->next;
      if (dlen != 1) {
        p->prev->next = current;
        current->prev = p->prev;
      }
    }
    if (dlen == 1) {
      if (llen != 0) {
        current = p->prev;
        p->next = nullptr;
        dlen++;
        llen--;
      }
      end = current;
    }
    delete p;
    dlen--;
  };
  void dodajIspred(const T &el) override {
    Cvor *novi = new Cvor(el, nullptr, nullptr);
    if (llen + dlen == 0) {
      current = begin = end = novi;
      dlen++;
    } else {
      if (current == begin) {
        begin = novi;
        novi->next = current;
        current->prev = novi;
      } else {
        if (llen != 0)
          current->prev->next = novi;
        novi->prev = current->prev;
        novi->next = current;
        current->prev = novi;
      }
      llen++;
    }
  }
  void dodajIza(const T &el) override {
    Cvor *novi = new Cvor(el, nullptr, nullptr);
    if (llen + dlen == 0) {

      current = novi;
      end = novi;
      begin = novi;
    } else {
      if (current == end) {

        end = novi;
        novi->prev = current;
      } else {

        novi->next = current->next;
        novi->prev = current;
      }

      current->next = novi;
    }
    dlen++;
  }

  T &operator[](int i) override {
    if (i < 0 || i >= llen + dlen)
      std::domain_error("Neispravan index!");
    auto temp = begin;
    for (int j = 0; j < i; j++) {
      temp = temp->next;
    }
    return temp->info;
  }
  T operator[](int i) const override {
    if (i < 0 || i >= llen + dlen)
      std::domain_error("Neispravan index!");
    auto temp = begin;
    for (int j = 0; j < i; j++) {
      temp = temp->next;
    }
    return temp->info;
  }
  int LijevaDuzina() const { return llen; }
  int DesnaDuzina() const { return dlen; }
  template <typename T2> friend T2 dajMaksimum(const Lista<T2> &n);
  friend class Iterator<T>;
};
template <typename T> class Iterator {
  const DvostrukaLista<T> *lista;
  typename DvostrukaLista<T>::Cvor *current;

public:
  Iterator(const DvostrukaLista<T> &list)
      : lista(&list), current(lista->begin) {}
  T trenutni() const {
    if (lista->brojElemenata() == 0)
      throw "Prazna lista!";
    return current->info;
  }
  void pocetak() {
    if (lista->brojElemenata() == 0)
      throw "Prazna lista!";
    current = lista->begin;
  }
  void kraj() {
    if (lista->brojElemenata() == 0)
      throw "Prazna lista!";
    current = lista->end;
  }
  void sljedeci() {
    if (lista->brojElemenata() == 0)
      throw "Prazna lista!";
    if (current != lista->end)
      current = current->next;
  }
  void prethodni() {
    if (lista->brojElemenata() == 0)
      throw "Prazna lista!";
    if (current != lista->begin)
      current = current->prev;
  }
};
template <typename T> T dajMaksimum(const Lista<T> &lista) {
  Iterator<T> iter(dynamic_cast<const DvostrukaLista<T> &>(lista));
  T temp = iter.trenutni();

  iter.pocetak();
  for (int i = 0; i < lista.brojElemenata(); i++) {
    if (iter.trenutni() > temp)
      temp = iter.trenutni();
    iter.sljedeci();
  }
  return temp;
}
// funkcije testiranja metoda
bool Test1() {
  DvostrukaLista<int> lista;
  lista.dodajIza(21);
  if (lista.brojElemenata() == 1)
    return true;
  return false;
}
bool Test2() {
  DvostrukaLista<int> lista;
  for (int i(1); i <= 21; i++)
    lista.dodajIza(21);
  if (lista.trenutni() == 1)
    return true;
  return false;
}
bool Test3() {
  DvostrukaLista<int> lista;
  for (int i(1); i <= 21; i++)
    lista.dodajIza(21);
  lista.prethodni();
  if (lista.trenutni() == 21)
    return true;
  return false;
}
bool Test4() {
  DvostrukaLista<int> lista;
  for (int i(1); i <= 21; i++)
    lista.dodajIza(21);
  lista.sljedeci();
  if (lista.trenutni() == 21)
    return true;
  return false;
}
bool Test5() {
  DvostrukaLista<int> lista;
  for (int i(1); i <= 21; i++)
    lista.dodajIza(21);
  lista.pocetak();
  if (lista.trenutni() == 21)
    return true;
  return false;
}
bool Test6() {
  DvostrukaLista<int> lista;
  for (int i(1); i <= 21; i++)
    lista.dodajIza(21);
  lista.kraj();
  if (lista.trenutni() == 21)
    return true;
  return false;
}
bool Test7() {
  DvostrukaLista<int> lista;
  for (int i(1); i <= 21; i++)
    lista.dodajIza(21);
  lista.obrisi();
  if (lista.trenutni() == 21)
    return true;
  return false;
}
bool Test9() {
  DvostrukaLista<int> lista;
  for (int i(1); i <= 21; i++)
    lista.dodajIza(21);
  if (lista.trenutni() == 21)
    return true;
  return false;
}
bool Test10() {
  DvostrukaLista<int> lista;
  for (int i(1); i <= 21; i++)
    lista.dodajIspred(21);
  if (lista.trenutni() == 21)
    return true;
  return false;
}
bool Test11Max() {
  DvostrukaLista<int> lista;
  for (int i(1); i <= 21; i++)
    lista.dodajIza(21);
  if (dajMaksimum(lista) == 21)
    return true;
  return false;
}
int main() { return 0; }