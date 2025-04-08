#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <ctime>
#include <unordered_map>

using namespace std;

unordered_map<int,string>kisiler(const string &dosyaAdi){
    unordered_map<int,string>kisilerMap;
    ifstream dosya(dosyaAdi);
    if (!dosya.is_open())
    {
        cerr<<"kisiler.csv dosyasi acilamadi: "<<dosyaAdi<<endl;
        return kisilerMap;
    }

    string satir;
    getline(dosya,satir);

    while (getline(dosya,satir))                                                                                                                    
    {
        stringstream ss(satir);
        string parca;
        int isbn;
        string kisiIsmi;
        getline(ss, parca, ',');
        isbn = stoi(parca);
        getline(ss, kisiIsmi, ',');
        kisilerMap[isbn] = kisiIsmi;

    }
    dosya.close();
    return kisilerMap;
}

string bugununTarihi(){                                                                                                                             //gptden yardim alindi
    time_t t=time(0);
    tm* now=localtime(&t);
    return to_string(now->tm_year + 1900) + "-" + to_string(now->tm_mon + 1) + "-" + to_string(now->tm_mday);
}
string geriVerilmesiGerekenTarih(int gunEkle){                                                                                                      //gptden yardim alindi
    time_t t=time(0)+(gunEkle*86400);
    tm* now=localtime(&t);
    return to_string(now->tm_year + 1900)+"-"+to_string(now->tm_mon + 1)+"-"+to_string(now->tm_mday);
}

struct kitap{
    string kitapAdi;
    int ISBN;
    string yazar;
    int yayinYili;
    bool durumu;
    string alinmaTarihi;
    string geriVermeTarihi;

    void goster(){
        cout<<"Kitap Adi: "          <<kitapAdi<<endl;
        cout<<"ISBN Numarasi: "      <<ISBN<<endl;
        cout<<"Kitap Yazari: "       <<yazar<<endl;
        cout<<"Kitabin Yayin Yili: " <<yayinYili<<endl;
        cout<<"Durumu: "             <<(durumu ? "Odunc Alindi":"Mevcut")<<endl;
        if(!alinmaTarihi.empty()){
            cout<<"Alinma Tarihi: "     <<alinmaTarihi<<endl;
            cout<<"Geri verme Tarihi: " <<geriVermeTarihi<<endl;
        }
    }

    void oduncAl(){
        int almak;
        if(durumu){
            cout<<"Bu kitap su an elimizde yok.."<<endl;
            return;
        }

        cout<<"Kitabi odunc almak istiyor musunuz? (Evet: 1 / Hayir: 0): "; cin>>almak;

        while(almak!=0 && almak!=1){
            cout<<"Lutfen gecerli bir sayi giriniz!! (1/0): ";cin>>almak;
        }

        if (almak==1){
            alinmaTarihi=bugununTarihi();
            int gun;
            while(true){
                cout<<"Kitabi kac gunlugune almayi planliyorsunuz? (Min1 - Max31): "; cin>>gun;
                if(gun>=1 && gun<=31) break;
                cout<<"Lutfen gecerli bir aralik giriniz!! (1-31): "<<endl;
            }

            geriVermeTarihi=geriVerilmesiGerekenTarih(gun);
            cout<<"Kitap basariyla odunc alindi. Geri verme tarihi: "<<geriVermeTarihi<<endl;
            durumu=1;
        }
        else if (almak==0){
            cout<<"Kitabi odunc almadiniz. "<<endl;
        }
        
    }
    void geriVer(){
        if (durumu==0){
            cout<<"Bu kitap zaten kutuphanede!"<<endl;
            return;
        }
        durumu=0;
        alinmaTarihi="";
        geriVermeTarihi="";
        cout<<"Kitap basariyla geri verildi. "<<endl;
    }
};

vector<kitap>veriOku(const string &dosyaAdi){                                                                                                       
    vector<kitap>kitaplar;
    ifstream dosya(dosyaAdi);
    if(!dosya.is_open()){
        cerr<<"Dosya acilmadi: "<<dosyaAdi<<endl;
        return kitaplar;
    }
    string satir;
    getline(dosya,satir);

    while(getline(dosya,satir)){                                                                                                //gptden yardim
        stringstream ss(satir);
        string parca;
        kitap k;

        getline(ss, k.kitapAdi, ',');
        getline(ss, parca, ',');k.ISBN=stoi(parca);
        getline(ss, k.yazar, ',');
        getline(ss, parca, ',');k.yayinYili=stoi(parca);
        getline(ss, parca, ',');k.durumu=(stoi(parca)==1);
        getline(ss, k.alinmaTarihi, ',');
        getline(ss, k.geriVermeTarihi, ',');

        kitaplar.push_back(k);
    }
    dosya.close();
    return kitaplar;
}
void dosyayaKitapYaz(const string &dosyaAdi,const vector<kitap> &kitaplar){
    ofstream dosya(dosyaAdi);
    if(!dosya.is_open()){
        cerr<<"Dosya yazma islemi icin acialamadi!!! "<<dosyaAdi<<endl;
        return;
    }

    dosya<<"kitapadi,ISBN,yazar,yayinYili,durumu,alinmaTarihi,geriVermeTarihi\n";
    for (size_t i = 0; i < kitaplar.size(); i++)
    {
        dosya<<kitaplar[i].kitapAdi<<','
             <<kitaplar[i].ISBN<<','   
             <<kitaplar[i].yazar<<','
             <<kitaplar[i].yayinYili<<','
             <<(kitaplar[i].durumu? 1 : 0 )<<','
             <<kitaplar[i].alinmaTarihi<<','
             <<kitaplar[i].geriVermeTarihi<<"\n";
    }
    dosya.close();
}

struct kutuphane
{
    vector<kitap>kitaplar;

    void listeGoster(){
        cout<<"\nKutphanedeki kitaplarin listesi\n";
        for (size_t i = 0; i < kitaplar.size(); i++)
        {
            cout<<i+1<<": "<<kitaplar[i].kitapAdi
                         <<" - "<<(kitaplar[i].durumu?"Odunc Alindi":"Mevcut")
                         <<endl;
        }
        cout<<endl;
    }

    void islemYap(){
        int x;
        cout<<"Islem yapmak istediginiz kitabin numarasini girin(1 - "<<kitaplar.size()<<"): ";cin>>x;
        if(x-1<1||x-1>=kitaplar.size()){
            cout<<"Gecersiz numara!"<<endl;
            return;
        }
        kitaplar[x-1].goster();

        cout<<"Islem yapmak ister misiniz? Secenekler:\n";
        cout<<"1: Odunc al\n";
        cout<<"2: Geri ver\n";
        cout<<"3: Islem yapma (Iptal) \n";
        cout<<"Seciminiz: ";
        int secim;
        cin>>secim;
        switch (secim)
        {
        case 1:
            kitaplar[x-1].oduncAl();
            break;
        case 2:
            kitaplar[x-1].geriVer();
            break;
        case 3:
            cout<<"Islem iptal edildi. "<<endl;
            break;
        default:
            cout<<"Gecersiz secim!! "<<endl;
        }
    }
};

// kisiler.csv ekleyemedim 3.04.2025

int main(){
    kutuphane ktphn;
    ktphn.kitaplar=veriOku("kitaplar.csv");
    int temp=1;
    ktphn.listeGoster();
    while (temp)
    {
        ktphn.islemYap();

        cout<<"Islem yapamya devam etmek istiyor musunuz? (Evet:1 / Hayir:0): ";cin>>temp;
        while (temp!=0 && temp!=1)
        {
            cout<<"Gecersiz Secim!! (1/0): ";cin>>temp;
        }
        
    }
    
    cout<<"Guncellenmis Son Durum: "<<endl;
    ktphn.listeGoster();

    dosyayaKitapYaz("kitaplar.csv", ktphn.kitaplar);
    return 0;
}