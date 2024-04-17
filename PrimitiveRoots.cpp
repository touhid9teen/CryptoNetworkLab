// Primitive roots of a number



#include <bits/stdc++.h>
using namespace std;

// Function to calculate (n^p) mod mod using binary exponentiation
long long bexpm(long long n, long long p, long long mod)
{
    long long res = 1;
    n %= mod; // Reduce n modulo mod
    while (p) // While p is not zero
    {
        if (p & 1)
            res = res * n % mod; // If p is odd, multiply res by n modulo mod
        p >>= 1;                 // Right shift p by 1 (equivalent to dividing p by 2)
        n = n * n % mod;         // Square n modulo mod
    }
    return res; // Return the result
}

// Start of the main function
int main()
{
    while (1)
    {
        // Prompt the user to enter a number n
        cout << "Enter value of n: ";
        int n;
        cin >> n;

        if (n == 1)
            cout << "Primitive roots of n: 0 \n";
        if (n == 2)
            cout << "Primitive roots of n: 1 \n";
        if (n < 3)
            continue;

        // Create a set to store the numbers that are coprime with n
        set<int> coprime, tmp;
        for (int i = 1; i < n; i++)
        {
            // If i is coprime with n, add it to the set
            if (__gcd(i, n) == 1)
                coprime.insert(i);
        }

        // Create a vector to store the primitive roots of n
        vector<int> primitive_roots;
        for (int x = 2; x < n; x++)
        {
            // Copy the set of numbers that are coprime with n
            tmp = coprime;
            for (int i = 1; i < n; i++)
            {
                // Calculate x^i modulo n
                int val = bexpm(x, i, n);
                // If val is in the set, remove it
                if (tmp.find(val) != tmp.end())
                    tmp.erase(val);
            }
            // If the set is empty, x is a primitive root of n
            if (tmp.empty())
                primitive_roots.push_back(x);
        }
        // Print the primitive roots of n
        cout << "Primitive roots of n: ";
        if(primitive_roots.size() == 0)
            cout << "None" << endl;
        else
        {
            for (int x : primitive_roots)
                cout << x << " ";
            cout << endl;
        }
    }
}
