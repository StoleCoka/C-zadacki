//Да се дефинира класа IceCream во која се чуваат податоци за:
//
//име (динамичка низа од знаци),
//состав (низа од знаци, најмногу 100)
//цена (децимален број),
//попуст (цел број, изразен во проценти) иницијална вредност 0.
//За потребите на класата да се имплементираат:
//
//соодветни конструктори и деструктор (да се погледнат повиците во функцијата main)
//оператор << за печатење на податоците за сладоледот во следниов формат:
//име: состав цена [цена на попуст]
//
//делот „цена на попуст“ се печати само ако за сладоледот се нуди попуст (вредноста на попустот е поголема од нула)
//
//оператор ++ во префикс нотација за зголемување на попустот за 5
//оператор + - за собирање на објект од класата IceCream со низа од знаци. Собирањето се реализира на начин што името на новиот сладолед се добива со спојување на името на сладоледот и низата од знаци одделени со „ + “. Цената на новиот сладолед се зголемува за 10, а попустот и составот на сладоледот остануваат исти.
//метод void setDiscount(int discount) со кој може да се смени вредноста на попустот. Дозволените вредности на попустот се во интервалот [0,100]
//метод void setName(char* name) со кој се менува името на сладоледот.
//Да се креира класа IceCreamShop во која се чува:
//
//име на продавницата (низа од знаци, најмногу 50)
//динамички резервирано поле од објекти од класата IceCream
//број на сладоледи во полето (цел број).
//За оваа класа да се обезбедат:
//
//соодветни конструктори и деструктор (погледнете ги повиците во main функцијата)
//оператор += за додавање нов објект од класата IceCream во полето
//        оператор << за печатење на листа од сите сладоледи во продавницата. Прво се печати името на продавницата, а потоа се печатат податоците за сите сладоледи одделени со нов ред.
#include <iostream>
#include <cstring>

using namespace std;

class IceCream {
private:
    char *name;
    char ingr[100];
    float price;
    int discount = 0;
public:
    IceCream(char *name = (char *) "", char *ingr = "", float price = 0.0, int discount = 0) {
        this->name = new char[strlen(name) + 1];
        strcpy(this->name, name);
        strcpy(this->ingr, ingr);
        this->price = price;
        this->discount = discount;
    }

    IceCream(const IceCream &ic) {
        this->name = new char[strlen(ic.name) + 1];
        strcpy(this->name, ic.name);
        strcpy(this->ingr, ic.ingr);
        this->price = ic.price;
        this->discount = ic.discount;
    }

    IceCream &operator=(const IceCream &ic) {
        if (this != &ic) {
            delete[]name;
            this->name = new char[strlen(ic.name) + 1];
            strcpy(this->name,ic.name);
            strcpy(this->ingr, ic.ingr);
            this->price = ic.price;
            this->discount = ic.discount;
        }
        return *this;
    }

    ~IceCream() {
        delete[]name;
    }

    void setDiscount(int d) {
        if (d >= 0 && d <= 100)
            this->discount = d;
    }

    friend ostream &operator<<(ostream &os, const IceCream &cream) {
        os << cream.name << ": " << cream.ingr << " " << cream.price;
        if (cream.discount > 0) {
            os  << " ("  << cream.price * (float)(100 - cream.discount) / 100 << ")";
        }
        return os;
    }

    //TODO
    IceCream &operator++() {
        discount += 5;
        return *this;
    }
    IceCream operator+(const char *extra) {

        char* newName = new char[strlen(name) + strlen(extra) + 4];
        strcat(newName, name);
        strcat(newName, " + ");
        strcat(newName, extra);

        IceCream res(newName, ingr, price + 10);
        res.setDiscount(discount);
        return res;
    }

    char *getName() const {
        return name;
    }

    void setName(char *n) {
        this->name = new char[strlen(n) + 1];
        strcpy(this->name, n);
    }

};

class IceCreamShop {
private:
    char name[50];
    IceCream *icecream;
    int broj;
public:
    IceCreamShop(char *name = "", IceCream *icecream = NULL, int broj = 0) {
        strcpy(this->name, name);
        this->broj = broj;
        icecream = new IceCream[broj];
        for (int i = 0; i < broj; ++i) {
            this->icecream[i] = icecream[i];
        }

    }

    IceCreamShop(const IceCreamShop &ic) {
        strcpy(this->name, ic.name);
        icecream = ic.icecream;
        this->broj = ic.broj;
        icecream = new IceCream[ic.broj];
        for (int i = 0; i < ic.broj; ++i) {
            this->icecream[i] = ic.icecream[i];
        }
    }

    IceCreamShop &operator=(const IceCreamShop &ic) {
        if (this != &ic) {
            delete[]icecream;
            strcpy(this->name, ic.name);
            icecream = ic.icecream;
            this->broj = ic.broj;
            icecream = new IceCream[ic.broj];
            for (int i = 0; i < ic.broj; ++i) {
                this->icecream[i] = ic.icecream[i];
            }
        }
        return *this;
    }

    friend ostream &operator<<(ostream &os, const IceCreamShop &shop) {
        os << shop.name << endl;
        for (int i = 0; i < shop.broj; ++i) {
            os << shop.icecream[i] << endl;
        }
        return os;
    }

    IceCreamShop &operator+=(const IceCream &ic) {
        IceCream *tmp = icecream;
        icecream = new IceCream[broj + 1];
        for (int i = 0; i < broj; i++) {
            icecream[i] = tmp[i];
        }
        icecream[broj] = ic;
        icecream[broj].setName(ic.getName());
        broj++;
        delete[] tmp;
        return *this;
//        IceCream * temp = icecream;
//        icecream= new IceCream[broj +1];
//        for (int i = 0; i < broj; ++i) {
//            this->icecream[i]=temp[i];
//        }
//        icecream[broj]=ic;
//        broj++;
//        delete[]temp;
//        return * this;
    }

    ~IceCreamShop() {
        delete[]icecream;
    }
};
// vashiot kod ovde

// zabraneto e menuvanje na main funkcijata

int main() {
    char name[100];
    char ingr[100];
    float price;
    int discount;

    int testCase;

    cin >> testCase;
    cin.get();
    if (testCase == 1) {
        cout << "====== TESTING IceCream CLASS ======" << endl;
        cin.getline(name, 100);
        cin.getline(ingr, 100);
        cin >> price;
        cin >> discount;
        cout << "CONSTRUCTOR" << endl;
        IceCream ic1(name, ingr, price);
        ic1.setDiscount(discount);
        cin.get();
        cin.getline(name, 100);
        cin.getline(ingr, 100);
        cin >> price;
        cin >> discount;
        IceCream ic2(name, ingr, price);
        ic2.setDiscount(discount);
        cout << "OPERATOR <<" << endl;
        cout << ic1 << endl;
        cout << ic2 << endl;
        cout << "OPERATOR ++" << endl;
        ++ic1;
        cout << ic1 << endl;
        cout << "OPERATOR +" << endl;
        IceCream ic3 = ic2 + "chocolate";
        cout << ic3 << endl;
    } else if (testCase == 2) {
        cout << "====== TESTING IceCream CONSTRUCTORS ======" << endl;
        cin.getline(name, 100);
        cin.getline(ingr, 100);
        cin >> price;
        cout << "CONSTRUCTOR" << endl;
        IceCream ic1(name, ingr, price);
        cout << ic1 << endl;
        cout << "COPY CONSTRUCTOR" << endl;
        IceCream ic2(ic1);
        cin.get();
        cin.getline(name, 100);
        ic2.setName(name);
        cout << ic1 << endl;
        cout << ic2 << endl;
        cout << "OPERATOR =" << endl;
        ic1 = ic2;
        cin.getline(name, 100);
        ic2.setName(name);
        cout << ic1 << endl;
        cout << ic2 << endl;

        cin >> discount;
        ic1.setDiscount(discount);


    } else if (testCase == 3) {
        cout << "====== TESTING IceCreamShop ======" << endl;
        char icsName[50];
        cin.getline(icsName, 100);
        cout << "CONSTRUCTOR" << endl;
        IceCreamShop ics(icsName);
        int n;
        cin >> n;
        cout << "OPERATOR +=" << endl;
        for (int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name, 100);
            cin.getline(ingr, 100);
            cin >> price;
            IceCream ic(name, ingr, price);
            ics += ic;
        }
        cout << ics;
    } else if (testCase == 4) {
        cout << "====== TESTING IceCreamShop CONSTRUCTORS ======" << endl;
        char icsName[50];
        cin.getline(icsName, 100);
        IceCreamShop ics(icsName);
        int n;
        cin >> n;
        for (int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name, 100);
            cin.getline(ingr, 100);
            cin >> price;
            IceCream ic(name, ingr, price);
            ics += ic;
        }
        IceCream x("FINKI fruits", "strawberry ice cream, raspberry ice cream, blueberry ice cream", 60);
        IceCreamShop icp = ics;
        ics += x;
        cout << ics << endl;
        cout << icp << endl;
    }


    return 0;
}