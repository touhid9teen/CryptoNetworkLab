// RSA (Rivest-Shamir-Adleman) public-key cryptosystem



#include <bits/stdc++.h>
using namespace std;
int n;

// Function to calculate (a^b) mod n
int power(int a, int b)
{
    int res = 1;
    // Loop until b becomes 0
    while (b)
    {
        // If b is odd, multiply res by a
        if (b % 2 == 1)
            res = (a * res) % n;
        // Square a
        a = (a * a) % n;
        // Divide b by 2
        b /= 2;
    }
    // Return the result
    return res % n;
}

// Function to calculate the greatest common divisor of a and b
int gcd(int a, int b)
{
    // If b is 0, return a
    if (b == 0)
        return a;
    // Otherwise, recursively call gcd with b and the remainder of a divided by b
    return gcd(b, a % b);
}

// Function to find an integer e such that 1 < e < tf and gcd(e, tf) == 1
int findE(int tf)
{
    int e = 2;
    // Loop until e is not coprime with tf or e equals tf
    while (gcd(e, tf) != 1 && e < tf)
        e++;
    // Return the result
    return e;
}

// Function to find an integer d such that (d * e) % tf == 1
int findD(int e, int tf)
{
    int d = 1;
    // Loop until (d * e) % tf equals 1
    while ((d * e) % tf != 1)
        d++;
    // Return the result
    return d;
}

// Start of the main function
int main()
{
    // Prompt the user to enter a message
    cout << "Enter the message: ";
    string s;
    // Read the message from the user
    getline(cin, s);

    // Define the prime numbers p and q
    int p = 11, q = 13;
    // Calculate n = p * q
    n = p * q;
    // Calculate the totient function tf = (p - 1) * (q - 1)
    int tf = (p - 1) * (q - 1);

    // Find an integer e such that 1 < e < tf and gcd(e, tf) == 1
    int e = findE(tf);
    // Print the public key {e, n}
    cout << "Public Key: {" << e << ", " << n << "}" << endl;

    // Find an integer d such that (d * e) % tf == 1
    int d = findD(e, tf);
    // Print the private key {d, n}
    cout << "Private Key: {" << d << ", " << n << "}" << endl;

    // Create a vector to store the encrypted message
    vector<int> a;

    // For each character in the message
    for (int i = 0; i < s.size(); i++)
    {
        // Convert the character to an integer x by subtracting the ASCII value of ' '
        int x = s[i] - ' ';
        // Encrypt x using the public key and add the result to the encrypted message
        int c = power(x, e) % n;
        a.push_back(c);
    }

    // Print the encrypted message
    cout << endl
         << "Encrypted Message: ";
    for (auto x : a)
        cout << x;

    // Create a string to store the decrypted message
    string ms = "";

    // For each integer in the encrypted message
    for (auto x : a)
    {
        // Decrypt x using the private key and add the result to the decrypted message
        int m = power(x, d);
        char c = m + ' ';
        ms += c;
    }

    // Print the decrypted message
    cout << endl
         << "Decrypted Message: ";
    cout << ms << endl;
}
