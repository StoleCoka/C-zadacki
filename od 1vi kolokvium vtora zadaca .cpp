//Да се дефинира класа Book, која репрезентира една книга. За класата Book се чуваат:
//
//Наслов (текстуална низа од 30 знаци)
//Сериски број (цел број)
//Тип на книга (енумерациски тип, стручна литература или роман)
//цена (децимален број)
//Серискиот број е единствен за секоја книга, неговата почетна вредност е 777550. Да се обезбеди секвенцијално генерирање на овој број, така што првата сметка ќе има идентификациски број 777551, втората 777552, третата 777553 итн. (5 поени)
//
//За оваа класа да се обезбедат потребните конструктори, set и get методи. (5 поени).
//
//Да се имплементира оператор за печатење << со кој ќе се печатат информациите за секој објект во формат: [сериски број]-[наслов] [тип] [цена] (5 поени).
//
//Да се имплементира оператор += кој како аргумент ќе прима реален број, што ќе ја означува маржата од дадена книга и ќе се додаде на цената на книгата. (5 поени).
//
//Потоа да се дефинира класа BookStore, во која се чуваат информации за:
//
//Име (текстуална низа од 20 знаци)
//Листа од книги (динамички алоцирана низа објекти од класата Book)
//Број на сметки (број на елементи во низата од книги, иницијално е 0)
//За оваа класа да се дефинираат потребните конструктори, деструктор, set и get методи. (5 поени).
//
//Оператор за печатење << во формат [име] и сите книги поединечно (види формат во тест примерите). (5 поени).
//
//Oператор += за додавање нова книга во продавницата. Во продавницата книгите се менаџираат според нивниот сериски број кој е уникатен. Во продавницата не смее да се дозволи додавање нова книга со сериски број кој веќе постои во продавницата. (10 поени).
//
//Оператор > кој споредува продавници според бројот на книги во продавницата. (5 поени).
//
//Да се дефинира метод void createMarketPrice() - со кој продавницата генерира продажни цени на сите книги. Продажните цени се пресметуваат во зависност од тоа за каков тип на литература станува збор. За стручна литература на цената на книгата се додава 5% од цената, а за романи се додава 3%. (10 поени).
//
//Да се дефинира глобален метод best() - кој прима низа од објекти од класатa BookStore и бројот на продавници, а ја враќа онаа продавница која има најмногу книги. Доколку повеќе продавници имаат ист број на книги се враќа онаа која е прва најдена. (5 поени)

#include <iostream>
#include <cstring>
using namespace std;

enum Tip{
    person, company
};
class Account{
private:
    char ime[30];
    int id;
    Tip tip;
    float balans;
    static int totalAccounts;
    void copy(const Account &a){
        strcpy(this->ime,a.ime);
        this->id=a.id;
        this->tip=a.tip;
        this->balans=a.balans;
    }
public:
    Account(){}
    Account(char *ime, int tip, float balans){
        strcpy(this->ime,ime);
        this->tip=(Tip)tip;
        this->balans=balans;
        this->id=1+totalAccounts;
        incT();
    }
    Account(const Account &a){
        copy(a);
    }
    static void incT(){
        totalAccounts++;
    }
    void tipToS(Tip tip){
        switch (tip) {
            case person:
                cout<<"person"<<endl;
                break;
            case company:
                cout<<"company"<<endl;
                break;
        }
    }
    float getBalans(){
        return balans;
    }
    int getID(){
        return id;
    }
    Account &operator-=(float danok){
        this->balans-=danok;
        return *this;
    }
    void print(){
        cout<<ime<<" "<<id<<" "<<balans<<" ";
        tipToS(tip);
    }
    Tip getTip(){
        return tip;
    }
    void setBalans(float balans){
        this->balans=balans;
    }

};
int Account::totalAccounts = 11110;

class Bank{
private:
    char ime[30];
    Account *smetki;
    int n;
    void copy(const Bank &b){
        strcpy(this->ime,b.ime);
        this->n=b.n;
        this->smetki = new Account [n];
        for (int i = 0; i < n; ++i) {
            this->smetki[i]=b.smetki[i];
        }
    }
public:
    Bank(char *ime=""){
        strcpy(this->ime,ime);
        this->n=0;
        this->smetki = new Account [0];
    }
    Bank(const Bank &b){
        copy(b);
    }
    Bank &operator=(const Bank &b){
        if(this!=&b){
            delete [] smetki;
            copy(b);
        }
        return *this;
    }
    ~Bank(){
        delete [] smetki;
    }
    void print(){
        cout<<ime<<endl;
        for (int i = 0; i < n; ++i) {
            smetki[i].print();
        }
    }
    Bank &operator+=(Account &nov){
        int flag=0;
        for (int i = 0; i < n; ++i) {
            if(smetki[i].getID()==nov.getID()){
                flag++;
            }
        }
        if(!flag){
            Account *tmp = new Account[n+1];
            for (int i = 0; i < n; ++i) {
                tmp[i]=smetki[i];
            }
            tmp[n++]=nov;
            delete [] smetki;
            smetki = tmp;
        }
        return *this;
    }
    void danok(){
        for (int i = 0; i < n; ++i) {
            if(smetki[i].getTip()==person){
                float danok = smetki[i].getBalans()*0.008;
                float novBalans=smetki[i].getBalans()-danok;
                smetki[i].setBalans(novBalans);
            }
            else{
                float danok = smetki[i].getBalans()*0.15;
                float novBalans=smetki[i].getBalans()-danok;
                smetki[i].setBalans(novBalans);
            }
        }
    }
    int getN(){
        return n;
    }
    Bank &operator+(const Bank &druga){
        Account *novi = new Account[n+druga.n];
        for (int i = 0; i < n; ++i) {
            novi[i]=smetki[i];
        }
        int j=0;
        for (int i = n; i < druga.n+n; ++i) {
            novi[i]=druga.smetki[j++];
        }
        delete [] smetki;
        delete [] druga.smetki;
        smetki = novi;
        n+=druga.n;
        return *this;
    }
};

float &operator+=(float balans, Account &a){
    float novbalans=balans+a.getBalans();
    return novbalans;
}
Bank liquid(Bank *banki, int n){
    Bank min=banki[0];
    for (int i = 1; i < n; ++i) {
        if(banki[i].getN()<min.getN()){
            min=banki[i];
        }
    }
    return min;
}

int main(){
    Account a("Stevo",0,30000);
    Account b("Josif",0,150000);
    Account c("AMC",1,35000);

    Account d("Marko",0,30000);
    Account e("Ivo",0,150000);
    Account f("SETEK",1,35000);

    Bank banka("Stopanska");
    Bank banka1("Halk");
    a-=3000;
    3000+=a;
    banka+=a;
    banka+=b;
    banka+=c;
    banka1+=d;
    banka1+=e;
    banka1+=f;
    banka1.danok();
    banka+banka1;
    banka.print();
}