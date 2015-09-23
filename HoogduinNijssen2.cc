#include <iostream>
#include <fstream>
using namespace std;

int main(){

 ifstream invoer;
 ofstream uitvoer;
 char kar;
 int karakters = 0, overgangen = 0;
 
 invoer.open ("invoer.txt");  
 uitvoer.open ("uitvoer.txt");
 
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
 return 0;
}
