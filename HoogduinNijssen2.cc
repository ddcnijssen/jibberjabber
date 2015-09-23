#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
using namespace std;

//print bericht dat de file niet goed geopend is en stop programma
//naam is de naam van de te openen file
void nietopen(string naam) {
  cout << "Error: file '" << naam << "' niet kunnen openen." << endl;
  exit(1);
}//nietopen

//Vraagt gebruiker of deze een boodschap wil ontcijferen of coderen
//en laad daarna de correcte bestanden.
//invoer moet gebruikt worden, uitvoer alleen bij coderen
void filenames(ifstream & invoer, ofstream & uitvoer){
  char ant; //gebruikt om input van de gebruiker te vragen
  string naam; //naam voor in en output files

  cout << "Wilt U een boodschap coderen of ontcijferen?" << endl
       << "Antwoord C voor coderen of O voor ontcijferen: ";
  cin >> ant;

  if(ant == 'O'){ //men wil een boodschap ontcijferen
    cout << "\nWelk bestand wilt U ontcijferen? bv. 'iets.txt'" << endl;
    cin >> naam;
    invoer.open(naam.c_str());
    if (! invoer.is_open()) nietopen(naam);
  }//if O
  if(ant == 'C'){ //men wil een boodschap coderen
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
  if(ant != 'O' && ant != 'C'){ //fout bij input
    cout << "\nError, verkeerde input. (geen O of C)" << endl;
    exit(1);
  }//if niet O of C
}//filenames

int main(){

 ifstream invoer;
 ofstream uitvoer;
 //char kar;

 filenames(invoer, uitvoer);

 /*
 kar = invoer.get ();

 if(invoer.eof()){
   cout << "Leeg bestand" << endl;
   return 0;
 }

 while ( ! invoer.eof ()) {
  uitvoer.put (kar);
  karakters++;
  if (kar == '\n') overgangen++;
  if (kar > 47 && kar < 58) cout << kar << " ";
  kar = invoer.get ();
 }

 invoer.close ();
 uitvoer.close ();
 cout << "\n karakters | overgangen   " << karakters << " | "
      << overgangen << endl;
 */
 return 0;
}
