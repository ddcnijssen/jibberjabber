#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

//Vraagt gebruiker of deze een bestand wil coderen of ontcijferen
//input moet C of O zijn.
void coderenOntcijferen(char & input){
  cout << "Wilt U een boodschap coderen of ontcijferen?" << endl
       << "Antwoord C voor coderen of O voor ontcijferen: ";
  cin >> input;
  
  if(input != 'C' && input != 'O'){ //fout bij input
    cout << "\nError, verkeerde input. (geen C of O)" << endl;
    exit(1); //programma afsluiten
  }//if niet C of O
}//coderenOntcijferen

//Print bericht dat de file niet goed geopend is en stop programma
//naam is de naam van de te openen file
void nietOpen(string naam) {
  cout << "Error: file '" << naam << "' niet kunnen openen." << endl;
  exit(1); //programma afsluiten
}//nietopen

//Vraagt gebruiker welke bestanden geopend moeten worden
//invoer moet gebruikt worden, uitvoer alleen bij coderen
void filenames(ifstream & invoer, ofstream & uitvoer, char doel){
  string naam; //naam voor in en output files
  
  if(doel == 'O'){ //men wil een boodschap ontcijferen
    cout << "\nWelk bestand wilt U ontcijferen? bv. 'iets.txt'" << endl;
    cin >> naam;
    invoer.open(naam.c_str());
    if (! invoer.is_open()) nietopen(naam);
  }//if O
  if(doel == 'C'){ //men wil een boodschap coderen
    cout << "\nWelke boodschap wilt U coderen? bv. 'iets.txt'" << endl;
    cin >> naam;
    invoer.open(naam.c_str());
    if (! invoer.is_open()) nietopen(naam);
    cout << "Waar wilt U de gecodeerde boodschap opslaan?"
         << "bv. 'geheim.txt'" << endl;
    cin >> naam;
    uitvoer.open(naam.c_str());
    if (! uitvoer.is_open()) nietopen(naam);
  }//if C 
}//filenames

//Maakt een random key als er gecodeerd wordt
//Vraagt gebruiker om een key als er ontcijferd wordt
//doel geeft aan of er ontcijferd of gecodeerd wordt
int setKey(char doel){
  int key;
  if(doel == 'O'){ //wanneer ontcijferd wordt
    cout << "Geef aub de key gebruikt tijdens het coderen." << endl;
    cin >> key;
    if(key < 1 || key > 20){ //key controleren
      cout << "Key moet minstens 1 en maximaal 20 zijn." << endl;
      exit(1); //programma afsluiten
    }//if 20<k<1
  }//if O
  if(doel == 'C'){ //wanneer gecodeerd wordt
    key = (rand(time(NULL)) % 19) + 1; //genereert key tussen 1 en 20
    cout << "Deze key wordt gebruikt om uw boodschap te coderen: " 
         << key << endl;
  }//if C
  return key;
}//setKey

void eersteKar(char & kar, ifstream & invoer){
  kar = invoer.get ();

  if(invoer.eof()){ //controleert of het invoer bestand leeg is
    cout << "Leeg bestand" << endl;
    exit(1); //programma afsluiten
  }//if
}//eerstekar

schrijfweg()

int soortKar(char kar){
  if(kar == '%')
    return 0;
  if(kar == 10)
    return 1;  
  if(kar > 47 && kar < 58)
    return 2;
  if(kar > 96 && kar < 123)
    return 3;
}//soortKar

verwerkGetal(){
  
}

verwerkLetter(){
  
}

int main(){

  ifstream invoer;
  ofstream uitvoer;
  char doel;    //Doel waarmee het programma gerund wordt, C of O
                //C voor Coderen, O voor Ontcijferen
  char kar;     //Karakter om invoer te lezen en mee te werken 
  char prkar;   //Vorige karakter        
  int key;      //Key om mee te Coderen of Ontcijferen
  int ktel = 0; //Telt aantal klinkers of niet klinkers
  int soort;    //Om het soort karakter door te geven
  int n1, n2, n3, n4;
  int mingetal, maxgetal; //Onthoud grootste en kleinste getal
  bool klinker = true;    //Telt klinkers of niet klinkers
  
  coderenOntcijferen(doel);
  filenames(invoer, uitvoer, doel);
  
  key = setKey(doel);
  
  eersteKar(kar, invoer);
  
  //zet invoer en uitvoer op goede plek
    
  while (! invoer.eof()){       
    if(doel == 'C'){
      schrijfweg(kar, doel);
      //karakters invoeren bij coderen max 4 cijfers   
    }//coderen 
    else{
      soort = soortKar(kar);
    
      switch(soort){
        case 0:
          klinker = !klinker;
        case 1:
          ktel = 0;
          break;
        case 2:
          verwerkGetal();
          checkGetal(); //adfasdfasdf
          break;
        case 3:
          verwerkLetter();
          break;
      }//switch
    //ga na lychrel print getal en iteraties
    //onthoud grootste en kleinste
    }//ontcijferen
    prkar = kar;
    kar = invoer.get ();
  }//while
  
  //boodschap eindigd niet op een cijfer
  //afdrukken grootste kleinste getal en gemiddelde

  invoer.close ();
  uitvoer.close ();
  return 0;
}
