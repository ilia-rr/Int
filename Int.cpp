#include <bits/stdc++.h>
using namespace std;

// number of blocks, block size, block digits;
const int32_t bn = 1e4, bs = 1e9, bd = 9; 

struct Int
{
    int32_t b[bn] = {}, bc;

    Int()
    {
        bc = 0;
    }

    Int(int32_t n)
    {
        *this = n;
    }

    Int(string n)
    {
        *this = n;
    }

    Int(const Int &n)
    {
        bc = n.bc;
        copy(n.b, n.b + n.bc, b);
    }
    
    inline void operator = (int32_t n)
    {
        bc = 1;
        b[0] = n;
    }

    inline void operator = (string n)
    {
        bc = 0;

        for (int32_t i = n.size() - 1; i >= 0; i -= bd)
        {
            for (int32_t j = max(0, i - bd + 1); j <= i; j++)
                b[bc] = 10 * b[bc] + n[j] - '0';
        
            bc++;
        }

        while (b[bc - 1] == 0)
            bc--;
    }
   
    inline Int operator + (Int n)
    {
        Int ans;
        
        int64_t c = 0;
        
        for (int mx = min(bc, n.bc); ans.bc < mx; ans.bc++, c /= bs)
        {
            c += 1ll * b[ans.bc] + n.b[ans.bc];
            ans.b[ans.bc] = c % bs;
        }

        for (; ans.bc < bc; ans.bc++, c /= bs)
        {
            c += b[ans.bc];
            ans.b[ans.bc] = c % bs;
        }

        for (; ans.bc < n.bc; ans.bc++, c /= bs)
        {
            c += n.b[ans.bc];
            ans.b[ans.bc] = c % bs;
        }

        if (c)
            ans.b[ans.bc++] = c;

        return ans;
    }

    inline Int operator - (Int n)
    {
        Int ans = *this;

        for (int32_t i = 0; i < n.bc; i++)
        {
            ans.b[i] -= n.b[i];
            
            if (ans.b[i] < 0)
            {
                ans.b[i + 1]--;

                ans.b[i] += bs;
            }
        }

        return ans;
    }   

    inline Int operator * (int32_t n)
    {
        Int ans;

        int64_t c = 0;

        for (; ans.bc < bc; ans.bc++, c /= bs)
        {
            c += 1ll * b[ans.bc] * n;
            ans.b[ans.bc] = c % bs;
        }

        if (c > 0)
            ans.b[ans.bc++] = c;

        return ans;
    }

    inline Int operator * (long long n)
    {
        if (n > bs)
            return *this * int32_t(n / bs) * bs + *this * int32_t(n % bs);

        return *this * int32_t(n);
    }

    inline Int Reverse()
    {
        stringstream strm;

        strm << *this;

        string s = strm.rdbuf()->str();

        reverse(s.begin(), s.end());

        return Int(s); 
    }

    friend ostream &operator << (ostream &st, Int n)
    {
        st << n.b[n.bc - 1] << setfill('0');
    
        for (int32_t i = n.bc - 2; i >= 0; i--)
            st << setw(bd) << n.b[i];

        st << setw(0);

        return st;
    }

    inline bool operator == (Int n)
    {
        if (bc != n.bc)
            return 0;

        for (int i = 0; i < bc; i++)
            if (b[i] != n.b[i])
                return 0;

        return 1;
    }
};

int32_t main()
{
    // example
    
    Int a, b = 12, c = Int("51");

    a = 30;

    cout << c + b << endl;
    cout << c - a << endl;
    cout << b * 1234 << endl;
    cout << c * 1000000000000ll << endl;
    cout << a.Reverse() << endl;
    cout << (Int("9876543210") == Int("9876543210")) << endl;
}
