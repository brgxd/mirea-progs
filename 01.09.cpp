#include <iostream>
#include <vector>
#include<list>
#include<map>
#include<set>

using namespace std;

bool compare_chars(char x, char y)
{
    x = x >= 'A' && x <= 'Z' ? x - 'A' : x - 'a';
    y = y >= 'A' && y <= 'Z' ? y - 'A' : y - 'a';
    return x < y;

    /*
    int num1 , num2;
    if(x > 'A' && x < 'Z')
        num1 = x - 'A';
    else
        num1 = x - 'a';
    if(y > 'A' && y < 'Z')
        num2 = y - 'A';
    else
        num2 = y - 'a';
    return num1 < num2;
    */
}

int main()
{
    /*vector<int> v;
    for (int i = 0; i < 20; i++)
        v.push_back;
   

    list<int> l;
    for (int i = 0; i < 20; i++)
        l.push_back(i);
    
    //for (list<int>::iterator it = l.begin(); it != l.end(); cout << *it++ << " ")

    list<int>::iterator it = l.end();


    while (it != l.begin()) {
        cout << *--it << " ";
    }*/

    

    list<char> l;
    for (int i = 0; i < 5; i++)
        l.push_back('A'+i);
    for (int i = 0; i < 5; i++)
        l.push_back('t' + i);
    for (int i = 0; i < 5; i++)
        l.push_back('a' + i);
    for (int i = 0; i < 5; i++)
        l.push_back('T' + i);
    for (list<char>::iterator it = l.begin(); it != l.end(); cout << *it++ << " ");
    l.sort(compare_chars);
    cout << "\n";
    for (list<char>::iterator it = l.begin(); it != l.end(); cout << *it++ << " ");

    map<string, int> marks;
    marks["ivanov"] = 3;
    marks["petrov"] = 4;
    marks["sidorov"] = 3;
    marks["pavlov"] = 4;
    marks["kuznetsov"] = 5;


    //for (map<string, int>::iterator it = marks.begin(); it != marks.end(); cout << it->first << ": " << it->second << "\n", it++); перебор при помощи итератора обычно реализуют через while

    //map<string, int>::iterator it = marks.begin();
    map<string, int>::iterator it = marks.find("petrov");
    cout << "\n";
    while (it != marks.end()) {
        cout << it->first << ": " << it->second << "\n";
        it++;
    }

    it = marks.find("popov");
    if(it!=marks.end())
        cout << it->first << ": " << it->second << "\n";

    set<int> s;
    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++)
            s.insert(j);

    set<int>::iterator it_set = s.begin();
    while (it_set != s.end())
        cout << *it_set++ << " ";

    return 0;
}