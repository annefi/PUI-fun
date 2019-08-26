/* stlvec -- example of using STL vectors
   from: http://www.cs.rpi.edu/~musser/stl-examples/vector1.html

   26Mar2001
 */ 

#include <vector.h>
#include <algo.h>

void pause()
{
    char c;
    cout << "\n\nPress return to continue: ";
    cin.get(c);
    cout << "\n\n";
}

int main() 
{
    vector<int> v(10,0);
    ostream_iterator<int> out(cout, " ");
    copy(v.begin(), v.end(), out);
    pause();

    vector<int>::iterator i = v.begin();
    i += 4;
    *i++ = 7;  // or v[4] = 7;
    *i = 9;    // or v[5] = 9;
    copy(v.begin(), v.end(), out);
    pause();
    
    vector<int>::iterator where = find(v.begin(), v.end(), 9);

    copy(where, v.end(), out);
    pause();

    where = v.insert(where, 8);
    copy(v.begin(), v.end(), out);
    pause();

    where += 3;

    where = v.insert(where, 4);
    copy(v.begin(), v.end(), out);
    pause();

    where -= 6;
    where = v.insert(where, 11);
    copy(v.begin(), v.end(), out);
    pause();

    v.erase(where+2);
    copy(v.begin(), v.end(), out);
    pause();

    sort(v.begin(), v.end());
    copy(v.begin(), v.end(), out);
    pause();

    if (binary_search(v.begin(), v.end(), 8))
         cout << "Yes, 8 occurs in vector v.";
    else
         cout << "No, didn't find 8 in vector v.";
    pause();

    if (binary_search(v.begin(), v.end(), 12))
         cout << "Yes, 12 occurs in vector v.";
    else
         cout << "No, didn't find 12 in vector v.";
    pause();

    where = lower_bound(v.begin(), v.end(), 8);
    copy(where, v.end(), out);
    pause();

    where = lower_bound(v.begin(), v.end(), 0);
    copy(where, v.end(), out);
    pause();

    where = upper_bound(v.begin(), v.end(), 0);
    copy(where, v.end(), out);
    pause();

    vector<int> w(v);

    if (v == w)
       cout << "v and w have the same contents";
    else
       cout << "v and w have different contents";
    pause();


    w[5] = 17;
    if (v == w)
       cout << "v and w have the same contents";
    else
       cout << "v and w have different contents";
    pause();

    v[5] = 17;
    if (v == w)
       cout << "v and w have the same contents";
    else
       cout << "v and w have different contents";
    pause();

    return 0;

}
