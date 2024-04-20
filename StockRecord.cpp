//За потребите на еден приватен банкар кој тргува со акции, потребно е да се направи модул за менаџирање со клиентски портфолија.
//
//За таа цел, треба да се креира класа StockRecord. Класата треба да содржи:
//
//ID, кој означува која е акцијата која се тргува (низа од 12 знаци)
//Име на компанијата која ја издала акцијата (низа од 50 знаци)
//Цена според која се купени акциите (реален број)
//Моментална цена на акцијата (реален број)
//Број на акции кои се купени (цел број)
//За класата да се дефинираат потребните конструктори и set метода за моменталната цена со потпис void setNewPrice(double c) (10 поени). Исто така, да се имплементираат методи double value() и double profit(). Првата треба да ја пресметува вредноста на акциите, а втората треба да го пресметува моменталниот профит од акциите. Пресметката се врши на следниот начин (5 поени):
//
//Вредност = број на акции * моментална цена
//Профит = број на акции * (моментална цена - цена по која се купени)
//Дополнително, да се преоптовари операторот << за печатење на објектот во следниот формат (5 поени): Компанија БројНаАкции КуповнаЦена МоменталнаЦена Профит
//
//        Да се креира класа Client која содржи:
//
//Име и презиме на клиентот (низа од 60 знаци)
//ID на сметка (цел број)
//Низа од компании кои ги поседува клиентот (динамичка низа од објекти од класата StockRecord)
//Број на објекти во низата (цел број)
//За класата Client да се дефинираат потребните конструктори, деструктор и метода double totalValue() која ќе ја пресметува моменталната вредност на акциите кои ги поседува клиентот. Таа се пресметува како збир од вредноста на сите акции од секоја компанија од кои е составено клиентското портфолио (15 поени). Дополнително, за класата да се преоптоварат операторите:
//
//+= за купување на нова компанија во портфолиото (додавање на нов објект од класата StockRecord во низата со компании) (10 поени)
//
//<< за печатење на информации за портфолиото на клиентот така што во првиот ред ќе бидат прикажани ID на сметката и моменталната вредност на портфолиото одделени со празно место, а во секој нареден ред ќе бидат прикажани компаниите од кои е составено портфолиото, секоја во посебен ред (5 поени)
//
//Комплетна функционанлост (5 поени)
#include <iostream>
#include <cstring>
using namespace std;

class StockRecord{
private:
    char ID[12];
    char companyName[50];
    double kupenaCena;
    double momentalnaCena;
    int brAkcii;
public:
          StockRecord() {
//        strcpy(ID, " ");
//        strcpy(companyName, " ");
//        kupenaCena = 0;
//        momentalnaCena = 0;
//        brAkcii = 0;
    }
    StockRecord(char *ID, char *companyName, double kupenaCena, int brAkcii){
        strcpy(this->ID, ID);
        strcpy(this->companyName, companyName);
        this->kupenaCena = kupenaCena;
        this->brAkcii = brAkcii;
    }

    StockRecord(const StockRecord & other){
        strcpy(this->ID, other.ID);
        strcpy(this->companyName, other.companyName);
        this->kupenaCena = other.kupenaCena;
        this->brAkcii = other.brAkcii;
    }
    StockRecord & operator =(const StockRecord & other){
        if(this!=&other){
            strcpy(this->ID, other.ID);
            strcpy(this->companyName, other.companyName);
            this->kupenaCena = other.kupenaCena;
            this->brAkcii = other.brAkcii;
        }
        return *this;
    }

    void setKupenaCena(double kupenaCena);

    void setMomentalnaCena(double momentalnaCena);

    void setBrAkcii(int brAkcii);

    void setNewPrice(double c){
        this->momentalnaCena = c;
    }
    double value(){
        return brAkcii * momentalnaCena;
    }
    double profit() const {
        return brAkcii * (momentalnaCena - kupenaCena);
    }

    friend ostream & operator << (ostream & o, const StockRecord & sr);

};
ostream & operator << (ostream & o, const StockRecord & sr){
    o << sr.companyName << " " << sr.brAkcii << " " << sr.kupenaCena << " " << sr.momentalnaCena << " ";
    cout << sr.profit() << endl;
}

void StockRecord::setKupenaCena(double kupenaCena) {
    StockRecord::kupenaCena = kupenaCena;
}

void StockRecord::setMomentalnaCena(double momentalnaCena) {
    StockRecord::momentalnaCena = momentalnaCena;
}

void StockRecord::setBrAkcii(int brAkcii) {
    StockRecord::brAkcii = brAkcii;
}

class Client{
private:
    char imePrezime[60];
    int IDsmetka;
    StockRecord *stockrecords;
    int n;
public:
    Client(char *imePrezime, int IDsmetka){
        strcpy(this->imePrezime, imePrezime);
        this->IDsmetka = IDsmetka;
        this->n = 0;
        this->stockrecords = new StockRecord[0];
    }
    double totalValue() const{
        double zbir = 0;
        for(int i = 0; i < n; i++){
            zbir += stockrecords[i].value();
        }
        return zbir;
    }

    Client & operator +=(const StockRecord & other){
        int i;
        StockRecord * tmp = new StockRecord[this->n+1];
        for(i = 0; i < this->n; i++){
            tmp[i] = stockrecords[i];
        }
        tmp[n++] = other;
        delete [] stockrecords;
        stockrecords = tmp;
        return *this;
    }
    Client & operator =(const Client & other){
        if(this!=&other){
            delete [] stockrecords;
            strcpy(this->imePrezime, other.imePrezime);
            this->IDsmetka = other.IDsmetka;
            this->n = other.n;
            this->stockrecords = new StockRecord[this->n];
            for(int i = 0; i < this->n; i++){
                stockrecords[i] = other.stockrecords[i];
            }
        }
        return *this;
    }
    friend ostream & operator << (ostream & o, const Client & c);

    ~Client(){
        if(n!= 0)
            delete [] stockrecords;
    }
};
ostream & operator << (ostream & o, const Client & c){
    o << c.IDsmetka << " ";
    o << c.totalValue() << endl;
    for(int i = 0; i < c.n; i++){
        o << c.stockrecords[i];
    }
}
int main(){
    int test;
    cin >> test;
    if(test == 1){
        char ID[12];
        char companyName[50];
        double kupenaCena;
        double momentalnaCena;
        int brAkcii;
     //   cin >> ID >> companyName >> kupenaCena >> momentalnaCena >> brAkcii;
    //    StockRecord sr[100];
     //   for(int i = 0; i < 100; i++){
            cin >> ID >> companyName >> kupenaCena >> momentalnaCena >> brAkcii;
            //sr[i] = (ID, companyName, kupenaCena, brAkcii);
      //  }

        StockRecord s1[100];
        s1[0].setBrAkcii(brAkcii);
        //s1.setNewPrice(momentalnaCena);
        cout << s1;
    }
    return 0;
}