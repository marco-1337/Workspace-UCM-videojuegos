#include <iostream>

#include "pair.h"
#include "myvector.h"

using namespace std;

int main(int, char**){
    
    /* Templates 37

    Pair<int,int> x(1,2);
    Pair<int,int> y(x);
    Pair<double,string> z(1.2,"Hola");
    if ( x == y )
    cout << "They are equal!" << endl;
    cout << x.getFirst() << " " << x.getSecond() << endl;
    cout << y.getFirst() << " " << y.getSecond() << endl;
    cout << z.getFirst() << " " << z.getSecond() << endl;

    */

    ///* Templates 39
   
    MyVector<int> v;
    v.push_back(11);
    v.push_back(15);
    v.push_back(17);
    cout << v.size() << endl;
    cout << v[0] << " " << v[1] << " " << v[2] << endl;
    v[1] = 4;
    cout << v[0] << " " << v[1] << " " << v[2] << endl;

    //*/

    return 0;
}
