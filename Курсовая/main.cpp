//
//  main.cpp
//  Курсовая
//
//  Created by Марк Голосков on 20.12.2017.
//  Copyright © 2017 Марк Голосков. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <fstream>
#include <random>
#include <ctime>
#include <chrono>
//#include "Searches.cpp"
using namespace std;

void Naive (const string &t, const string *p,vector <int> vector,int R)
{
   
    
    /*while (i <= n - m)
    {
        int j;
        
     
        for (j = 0; j < m; j++)
            if (t[i+j] != p[j])
                break;
        
        if (j == m)  // if pat[0...M-1] = txt[i, i+1, ...i+M-1]
        {
            //cout<<"Pattern found at index: "<<i<<endl;
            vector.push_back(i);
            i = i + m;
        }
        else if (j == 0)
            i = i + 1;
        else
            i = i + j; // slide the pattern by j
    }*/
    int n = t.length();
    for (int j=0;j<R;j++)
    {
        int m = p[j].length();
        
        for (int i = 0; i <= n - m; i++) {
            int k;
            for (k = 0; k < m; k++) {
                if (p[j][k] != t[i + k])
                    break;
            }
            if (k == m) {
                vector.push_back(i);
                //cout << i << endl;
            }
        }
    }

}


//==================================================================================================
void Rabin_Karp(const string &str, const string *substr, const int d, const int q, std::vector<int> vector, int R)
{
    int i, j;
    int p = 0;
    int t = 0;
    int h = 1;
    size_t N = str.length();
    for (int k=0; k<R;k++)
    {
        size_t M = substr[k].length();
       
        for (i = 0; i < M - 1; i++)
            h = (h * d) % q;
        for (i = 0; i < M; i++)
        {
            p = (d *p + substr[k][i]) % q;
            t = (d * t + str[i]) % q;
        }
        for (i = 0; i <= N - M; i++)
        {
            if (p == t)
            {
                for (j = 0; j < M; j++)
                {
                    if (str[i + j] != substr[k][j])
                        break;
                }
                if (j == M)
                {
                    //cout<<"Pattern found at index: "<<i<<endl;
                    vector.push_back(i);
                }
            }
            if (i < N - M)
            {
                t = (d * (t - str[i] * h) + str[i + M]) % q;
                if (t < 0)
                    t = (t + q);
            }
        }
    }
}

//=================================================================================
/*void KMP(const std::string& S, int begin, const std::string& pattern, std::vector<int> a)
{
    std::vector<int> pf (pattern.length());
    
    pf[0] = 0;
    for (int k = 0, i = 1; i < pattern.length(); ++i)
    {
        while ((k > 0) && (pattern[i] != pattern[k]))
            k = pf[k-1];
        
        if (pattern[i] == pattern[k])
            k++;
        
        pf[i] = k;
    }
    
    for (int k = 0, i = begin; i < S.length(); ++i)
    {
        while ((k > 0) && (pattern[k] != S[i]))
            k = pf[k-1];
        
        if (pattern[k] == S[i])
            k++;
        
        if (k == pattern.length())
            a.push_back(i - pattern.length() + 1); //либо продолжаем поиск следующих вхождений
        //cout << i - pattern.length() + 1 << endl;
    }
}*/

/*void KMP(string S, string K)
{
    
        vector<int> T(K.size() + 1, -1);
        vector<int> matches;
        
        if (K.size() == 0) {
            matches.push_back(0);
        }
        
        for (int i = 1; i <= K.size(); i++) {
            int pos = T[i - 1];
            while (pos != -1 && K[pos] != K[i - 1])
                pos = T[pos];
            T[i] = pos + 1;
        }
        
        int sp = 0;
        int kp = 0;
        while (sp < S.size()) {
            while (kp != -1 && (kp == K.size() || K[kp] != S[sp]))
                kp = T[kp];
            kp++;
            sp++;
            if (kp == K.size())
                matches.push_back(sp - K.size());
        }
    
}*/

void kmp(const string needle, const string haystack, vector<int> a)
{
   
    int m = needle.size();
    bool flag = true;
    vector<int> border(m + 1);
    border[0] = -1;
    for (int i = 0; i < m; ++i) {
        border[i + 1] = border[i];
        while (border[i + 1] > -1 && needle[border[i + 1]] != needle[i]) {
            border[i + 1] = border[border[i + 1]];
        }
        border[i + 1]++;
    }
    
    int n = haystack.size();
    int seen = 0;
    for (int i = 0; i < n; ++i) {
        while (seen > -1 && needle[seen] != haystack[i]) {
            seen = border[seen];
        }
        if (++seen == m) {
            flag = false;
            //cout << "KMP: " << i - m + 1 << endl;
            a.push_back(i-m+1);
            seen = border[m]; // There are no more characters in needle, so with the next input character let's try with the border of the whole needle.
        }
    }
}

/*void searchkmp(const string needle, const string haystack, int m, int n)
{
    
    vector <int> a;
    bool flag = true;
    vector<int> border(m + 1);
    border[0] = -1;
    for (int i = 0; i < m; ++i) {
        border[i + 1] = border[i];
        while (border[i + 1] > -1 && needle[border[i + 1]] != needle[i]) {
            border[i + 1] = border[border[i + 1]];
        }
        border[i + 1]++;
    }
    
    
    

    int seen = 0;
    for (int i = 0; i < n; ++i) {
        while (seen > -1 && needle[seen] != haystack[i]) {
            seen = border[seen];
        }
        if (++seen == m) {
            flag = false;
            //cout << "KMP: " << i - m + 1 << endl;
            a.push_back(i-m+1);
            seen = border[m]; // There are no more characters in needle, so with the next input character let's try with the border of the whole needle.
        }
    }
    
}*/









//=================================================================================================
#define NO_OF_CHARS 20

int getNextState(string P, int m, int state, int x)
{
    // If the character c is same as next character
    // in pattern,then simply increment state
    if (state < m && x == P[state])
        return state + 1;
    
    // ns stores the result which is next state
    int ns, i;
    
    // ns finally contains the longest prefix
    // which is also suffix in "pat[0..state-1]c"
    
    // Start from the largest possible value
    // and stop when you find a prefix which
    // is also suffix
    for (ns = state; ns > 0; ns--)
    {
        if (P[ns - 1] == x)
        {
            for (i = 0; i < ns - 1; i++)
                if (P[i] != P[state - ns + 1 + i])
                    break;
            if (i == ns - 1)
                return ns;
        }
    }
    
    return 0;
}



void computeTF(string P, int m, vector<vector <int>> TF)
{
    int state, x;
    for (state = 0; state <= m; ++state)
        for (x = 0; x < NO_OF_CHARS; ++x)
            TF.at(state).at(x) = getNextState(P, m, state, x);
}

int charToNum(char c)
{
    switch (c)
    {
        case '0':
            return 0;
        case '1':
            return 1;
        case '2':
            return 2;
        case '3':
            return 3;
        case '4':
            return 4;
        case '5':
            return 5;
        case '6':
            return 6;
        case '7':
            return 7;
        case '8':
            return 8;
        case '9':
            return 9;
        case 'q':
            return 0;
        case 'w':
            return 1;
        case 'e':
            return 2;
        case 'r':
            return 3;
        case 't':
            return 4;
        case 'y':
            return 5;
        case 'u':
            return 6;
        case 'i':
            return 7;
        case 'o':
            return 8;
        case 'p':
            return 9;
            default:
            return -1;
    }
}

void StateChart(string *P, string T, vector<int> a, int R)
{
    int n = T.length();// длина текста
    for (int k=0;k<R;k++)
    {
        int m = P[k].length();// длина подстроки
        
        vector<vector<int>> TF(m + 1);
        for (auto &it : TF)
        {
            it.resize(NO_OF_CHARS);
        }
        
        computeTF(P[k], m, TF);
        
        // Process txt over FA.
        int i, state = 0;
        for (i = 0; i < n; i++)
        {
            state = TF[state][charToNum(T[i])];
            if (state == m)
            {
                a.push_back(i-m+1);
                //cout << "Pattern found at index " << i - m + 1 << endl;
            }
        }
    }
}





 //int  ar[] ={1,2,3,4,5,6,7,8,9};
const char * ar[]={"0","1","2","3","4"/*,"5","6","7","8","9","q","w","e","r","t","y","u","i","o","p"*/};
//const char * ar[] = {"а", "б" ,"в", "г","д","е", "ё", "ж", "з", "и", "й", "к", "л", "м", "н", "о", "п", "р", "с", "т", "у", "ф", "х", "ц", "ч", "ш", "щ", "ъ", "ы", "ь", "э", "ю", "я","q", "w", "e", "r", "t" ,"y", "u", "i", "o", "p", "a", "s", "d", "f", "g", "h", "j", "k","l", "z", "x", "c", "v", "b", "n", "m","1"};

int main() {
    ofstream fout;
    vector <int> a;
    fout.open("t(n).txt");
    //Naive ("96745","45",a);
    //Rabin_Karp("2281428", "28", 10, 167,a);
    //kmp("28","2281428",a);
    //StateChart("ab", "babe",a);
    
    string str;
    string substr;
    int n;
    n=5000;
    int m=9;
    double Time[4];
    for (int k=0;k<200;k++)
    {
        for (int i=0; i<n;i++)
        {
            str+=ar[rand() % (sizeof ar/sizeof (char *))];
        }
        
        for (int i=0;i<m;i++)
        {
            substr+=ar[rand() % (sizeof ar/sizeof (char *))];
        }
        
        vector <int> a;
        auto start = chrono::high_resolution_clock::now();
            Naive(str, &substr, a,1);
        auto end = chrono::high_resolution_clock::now();
        //fout <<  chrono::duration_cast <chrono::microseconds> (end-start).count () <<endl;
        Time[0]+=chrono::duration_cast <chrono::microseconds> (end-start).count ();
        
        vector <int> b;
        auto start1 = chrono::high_resolution_clock::now();
        Rabin_Karp(str, &substr, 2, 67, b,1);
        auto end1 = chrono::high_resolution_clock::now();
        //fout <<  chrono::duration_cast <chrono::microseconds> (end1-start1).count () <<endl;
        Time[1]+=chrono::duration_cast <chrono::microseconds> (end1-start1).count ();
        
        vector <int> d;
        auto start2 = chrono::high_resolution_clock::now();
        kmp(substr,str, d);
        auto end2 = chrono::high_resolution_clock::now();
            //fout <<  chrono::duration_cast <chrono::microseconds> (end2-start2).count () <<endl;
        Time[2]+=chrono::duration_cast <chrono::microseconds> (end2-start2).count ();
        
        vector <int> c;
        auto start3 = chrono::high_resolution_clock::now();
        StateChart(&substr, str, c,1);
        auto end3 = chrono::high_resolution_clock::now();
        //fout <<  chrono::duration_cast <chrono::microseconds> (end3-start3).count () <<endl;
        Time[3]+=chrono::duration_cast <chrono::microseconds> (end3-start3).count ();
    
    
    
    }
    
    for (int i=0;i<4;i++)
    {
        Time[i]/=200;
        fout << Time[i] << endl;
    }

    return 0;
}
