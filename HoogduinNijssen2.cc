/* Auteurs:  Richard Hoogduin, Desley Nijssen
 * Functie:  Bestand codeert of ontcijfert geheime boodschappen en gebruikt
 *           daarvoor een key. Om een bestand te ontcijferen moet een key
 *           gegeven worden, met coderen wordt een key gegenereert.
 * Datum:    2015-10-09
 * compiler: g++
 */

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <climits>
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
void nietopen(string naam) {
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
    if (! invoer.is_open()) nietopen(naam); //bestand niet gevonden
  }//if O
  if(doel == 'C'){ //men wil een boodschap coderen
    cout << "\nWelke boodschap wilt U coderen? bv. 'iets.txt'" << endl;
    cin >> naam;
    invoer.open(naam.c_str());
    if (! invoer.is_open()) nietopen(naam); //bestand niet gevonden
    cout << "\nWaar wilt U de gecodeerde boodschap opslaan?"
         << "bv. 'geheim.txt'" << endl;
    cin >> naam;
    uitvoer.open(naam.c_str());
    if (! uitvoer.is_open()) nietopen(naam); //bestand niet gevonden
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
    key = (rand() % 19) + 1; //genereert key tussen 1 en 20
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

//verwerkt karakters die niet in de boodschap terecht komen
void administratie(char kar, bool & klinker, int & ktel){ 
  if(kar > 96 && kar < 123){
    if(kar == 97 || kar == 101 || kar == 105 || kar == 111 || kar == 117){
      if(klinker) ktel++; 
    }//klinkers
    else 
      if(!klinker) ktel++; //medeklinkers
  }//kleine letters
  if(kar == '%'){
    klinker = !klinker;
    ktel = 0;    
  }//%
  if(kar == 10){
    klinker = true;
    ktel = 0;
  }//\n  
}//administratie

//Genereert een random karakter om tussen boodschap karakters te stoppen
char genereerkar(bool & klinker, int & ktel){
  int kar = (rand() % 95);//genereer karakters 0 t/m 94
  if (kar == 0) //karakter 0 wordt 10
    kar = 10;
  else //karakters 1 t/m 94 worden 32 t/m 125 
    kar += 31;
  administratie(kar, klinker, ktel);  //kijk of ktel geupdate wordt
  return kar;                         //of klinkers verandert wordt
}//genereerkar

//bouwt getal uit cijfers in geheime boodschap
int maakgetal(char kar, int getal){
  getal *= 10;
  getal += kar - '0';
  return getal;
}//maakgetal

//draait een getal om
int draaiom(int getal){
  int omgedraaid = 0; //wordt opgebouwt tot omgekeerde van getal
  
  while(getal != 0){
    omgedraaid *= 10;
    omgedraaid += getal % 10;
    getal /= 10;
  }//while
  return omgedraaid;
}//draaiom

//checkt of het omgedraaide getal > INT_MAX
//wanneer dit niet het geval is checkt hij of getal + het omgedraaide
//getal > INT_MAX
bool maxcheck(int getal){
  int groot = 100000000; //een groot getal: 10^8
  if(getal / (groot * 10) > 0){
    if(getal % 100 > 0)
      return true; //omgedraaide getal is groter dan INT_MAX
    if(((draaiom(getal / 100)) + (getal % groot)) > (INT_MAX % groot))
      return true; //omgedraaide getal is groter dan INT_MAX
  }//if getal >= 10^9
  if(INT_MAX - draaiom(getal) < getal)
    return true; //getal + omgedraaid getal is groter dan INT_MAX     
  return false; //getal + omgedraaid getal is niet groter dan INT_MAX
}//maxcheck

//checkt of het getal geen lychrel getal is
void lycheck(int getal){
  int i = 0; //iteraties
  
  if(maxcheck(getal)){ //overflow na een iteratie
    cout << "(" << i + 1 << ";overflow)";
    return;
  }//if

  while(getal != draaiom(getal)){
    i++; //houd aantal iteraties bij   
    getal += draaiom(getal);
    if(maxcheck(getal)){ //overflow na volgende iteratie
      cout << "(" << i + 1 << ";overflow)";
      return;
    }    
  }//while
  cout << "(" << i << ")";
}//lycheck

//verwerkt een getal, gevonden in de geheime boodschap
//bepaalt of het hoger is dan het maximum, lager dan het minimum
//een mogelijk lychrel getal en het gemiddelde van alle getallen
void verwerkgetal(int getal, int & max, int & min, double & gem, int tel){
  
  lycheck(getal);
  
  gem += (double)(getal - gem) / tel;
  if(tel > 1){
    if(getal > max)
      max = getal;
    else if(getal < min)
      min = getal;
  }//if
  else{
  max = getal;
  min = getal;
  }//else
}//verwerk getal

//Ontcijferd een boodschap
void ontcijferen(char kar, int key, ifstream & invoer){
  int ktel = 0;           //houdt aantal getelde (mede)klinkers bij
  int getal = 0;          //getal wordt opgebouwd uit losse cijfers
  int telgetal = 0;       //telt aantal getallin in boodschap
  int max = 0, min = 0;   //grootste en kleinste getal in boodschap
  double gem = 0;         //gemiddelde alle getallen in boodschap
  bool klinker = true;    //zoek naar klinkers of medeklinkers
  char prkar;             //vorige karakter in boodschap
  
  while (! invoer.eof()){     
    if(ktel == key){ //dit karakter hoort in de boodschap     
      if(kar >= '0' && kar <= '9') //is een cijfer
        getal = maakgetal(kar, getal);
      else //is geen cijfer
        if(prkar >= '0' && prkar <= '9'){ //einde getal
          telgetal++;
          verwerkgetal(getal, max, min, gem, telgetal);
          getal = 0;
        }//if
      ktel = 0;
      cout << kar;
      prkar = kar;                 
    }//if
    else{ //dit karakter hoort niet in de boodschap
      administratie(kar, klinker, ktel);
    }//else  
  kar = invoer.get();  
  }//while 
  cout << endl;
  
  cout << "Kleinste getal in boodschap: " << min << endl
       << "Gemiddelde van alle getallen: " << (int)((gem + 0.5)/1) << endl
       << "Grootste getal in boodschap: " << max << endl;
}//ontcijferen

//codeert een geheime boodschap
void coderen(char kar, int key, ifstream & invoer, ofstream & uitvoer){
  int ktel = 0;         //houdt aantal getelde (mede)klinkers bij
  bool klinker = true;  //zoek naar klinkers of medeklinkers
  
  while (! invoer.eof()){     
    if(ktel == key){ //stop een karakter uit de boodschap in de output
      uitvoer.put(kar);      
      ktel = 0;
      kar = invoer.get();
    }//if
    else{ //genereer een random karaktar voor de output
      uitvoer.put(genereerkar(klinker, ktel));
    }//else
  }//while
}//coderen

//maakt lijn van infoblok af
void infolijn(int karakters){
  int i;
  for(i = karakters; i < 74; i++)
    cout << ' ';
  cout << '*' << endl;
}//infolijn

//print infoblok
void infoblok(){
  int i;
  for(i = 0; i < 75; i++)
    cout << '*'; 
     
  cout << endl
       << "* Programma door Richard Hoogduin en Desley Nijssen";
  infolijn(51); //vult lijn en break
  cout << "* Beide begonnen met Informatica in 2015";
  infolijn(40); //vult lijn en break      
  cout << "* Geprogrammeerd op 2015-10-09";
  infolijn(30); //vult lijn en break
  cout << "* ";
  infolijn(2);  //vult lijn en break
  cout << "* Dit is programmeer opgave 2";
  infolijn(29); //vult lijn en break
  cout << "* Er wordt gevraagd of U een boodschap wilt coderen of"
       << " ontcijferen";
  infolijn(66); //vult lijn en break
  cout << "* Als U wilt ontcijferen wordt er een bestand naam en een"
       << " key gevraagt";
  infolijn(70); //vult lijn en break
  cout << "* Als U wilt coderen twee bestand namen en wordt Uw key"
       << " gegenereert";
  infolijn(67); //vult lijn en break
    
  for(i = 0; i < 75; i++)
    cout << '*';
  cout << endl;       
}//infoblok

int main(){
  infoblok();
  
  ifstream invoer;   //bestand voor input
  ofstream uitvoer;  //bestand voor output
  char doel;         //Doel waarmee het programma gerund wordt, C of O
                     //C voor Coderen, O voor Ontcijferen
  char kar;          //Karakter om invoer te lezen en mee te werken        
  int key;           //Key om mee te Coderen of Ontcijferen
  srand(time(NULL)); //seed random
  
  coderenOntcijferen(doel);         //bestand coderen of ontcijferen?
  filenames(invoer, uitvoer, doel); //namen van te gebruiken bestanden
  
  key = setKey(doel);               //wat is de key
  
  eersteKar(kar, invoer);           //pak het eerste karakter
  
  if(doel == 'O')   //ontcijfer het gegeven bestand
    ontcijferen(kar, key, invoer);
  if(doel == 'C')   //codeer het gegeven bestand
    coderen(kar, key, invoer, uitvoer);
  
  invoer.close ();  //sluit invoer
  uitvoer.close (); //sluit uitvoer
  return 0;
}//main
