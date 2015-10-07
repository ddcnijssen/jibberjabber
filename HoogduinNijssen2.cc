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
    if(kar == 97 || kar == 101 || kar == 105 || 
       kar == 111 || kar == 117 || kar == 121){
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

char genereerkar(bool & klinker, int & ktel){
  int kar = (rand() % 94);
  if (kar == 0) 
    kar = 10;
  else 
    kar += 31;
  administratie(kar, klinker, ktel);
  return kar;
}

int maakgetal(char kar, int getal){
  getal *= 10;
  getal += kar - '0';
  return getal;
}

int draaiom(int getal){
  int tempgetal = getal;
  int omgedraaid;
  
  while(getal != 0){
    if(INT_MAX / 10 < omgedraaid) //kijken of dit ook anders gechecked kan worden
      return 0;
    omgedraaid *= 10;
    omgedraaid += tempgetal % 10;
    tempgetal /= 10;
  }
  return omgedraaid;
}//draaiom

void lycheck(int getal){
  int i = 1;
  int tempgetal = getal;
  int omgedraaid = draaiom(getal); 
   
  if(getal/10 == 0)
    return;
  
  if(omgedraaid == 0){
    cout << getal << "(" << i << ";overflow)" << endl;
    return;
  }
  
  while(tempgetal != omgedraaid){
    i++;
    tempgetal += omgedraaid;
    omgedraaid = draaiom(tempgetal);
    if(INT_MAX - omgedraaid < tempgetal){
      cout << getal << "(" << i << ";overflow)" << endl;
      return;
    }//if
  }//while
  cout << getal << "(" << i << ")" << endl;
}

void verwerkgetal(int getal, int & max, int & min, int & gem){
  
  lycheck(getal);
  
  gem += (getal - gem) / telgetal;
  if(telgetal > 1){
    if(getal > max)
      max = getal;
    else if(getal < min)
      min = getal;
  }//if
  else{
  max = getal;
  min = getal;
  }//else
}

void ontcijferen(char kar, ifstream & invoer){
  int ktel;
  int getal = 0, telgetal = 0;
  int max = 0, min = 0, gem = 0;
  bool klinker = true;
  char prkar;
  
  while (! invoer.eof()){     
    if(ktel == key){
      cout << kar;
      ktel = 0;
      if(kar >= '0' && kar <= '9')
        getal = maakgetal(kar, getal);
      else
        if(prkar >= '0' && prkar <= '9')
          telgetal++
          verwerkgetal(getal, max, min, gem);
    }//if
    else{
      administratie(kar, klinker, ktel);
    }//else
  prkar = kar;
  kar = invoer.get();
  }//while 
  cout << endl;
  
  //lychrel getallen controleren
  //boodschap eindigd niet op een cijfer
  //afdrukken grootste kleinste getal en gemiddelde
}//ontcijferen

void coderen(char kar, ifstream & invoer, ofstream & uitvoer){
  int ktel;
  bool klinker = true;
  
  while (! invoer.eof()){     
    if(ktel == key){
      uitvoer.put(kar);      
      ktel = 0;
      prkar = kar;
      kar = invoer.get();
    }//if
    else{
      uitvoer.put(genereerkar(klinker, ktel));
    }//else
  }//while
}//coderen

int main(){

  ifstream invoer;
  ofstream uitvoer;
  
  char doel;    //Doel waarmee het programma gerund wordt, C of O
                //C voor Coderen, O voor Ontcijferen
  char kar;     //Karakter om invoer te lezen en mee te werken        
  int key;      //Key om mee te Coderen of Ontcijferen
  srand(time(NULL)); //seed random
  
  coderenOntcijferen(doel);
  filenames(invoer, uitvoer, doel);
  
  key = setKey(doel);
  
  eersteKar(kar, invoer);
  
  //zet invoer en uitvoer op goede plek
    
  if(doel == 'O')
    ontcijferen(kar, invoer);
  if(doel == 'C')
    coderen(kar, invoer, uitvoer);
  
  invoer.close ();
  uitvoer.close ();
  return 0;
}
