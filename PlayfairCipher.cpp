// Playfair Cipher

#include <bits/stdc++.h> 
using namespace std; 

char matrix[5][5]; // Declare a 5x5 matrix
map<char, pair<int, int>> charToIndex; // Map to store character indices

// Function to remove spaces from a string
string removeSpaces(string str)
{
    string temp; // Temporary string to store result
    for (int i = 0; i < str.size(); i++) // Loop through the string
    {
        if (str[i] != ' ') // If the character is not a space
            temp += str[i]; // Add it to the temporary string
    }
    return temp; // Return the temporary string
}

// Function to convert a string to uppercase
string makeUppercase(string str)
{
    string temp; // Temporary string to store result
    for (int i = 0; i < str.size(); i++) // Loop through the string
    {
        if (str[i] >= 'a' && str[i] <= 'z') // If the character is lowercase
            temp += char(str[i] - 32); // Convert it to uppercase and add it to the temporary string
        else
            temp += str[i]; // If it's not lowercase, just add it to the temporary string
    }
    return temp; // Return the temporary string
}

// Function to form the matrix used in the Playfair cipher
void matrixFormation(string key)
{
    int pointer[26] = {0}; // Array to keep track of which letters have been used

    // Fill the matrix with the key
    for (int i = 0; i < key.size(); i++)
    {
        if (key[i] == 'J') // If the character is 'J'
            key[i] = 'I'; // Replace it with 'I'
        if (pointer[key[i] - 'A'] == 0) // If the character has not been used yet
        {
            pointer[key[i] - 'A'] = 1; // Mark it as used
            matrix[i / 5][i % 5] = key[i]; // Add it to the matrix
            charToIndex[key[i]] = {i / 5, i % 5}; // Store its index
        }
    }
    int len = key.size(); // Length of the key

    // Fill the rest of the matrix with the remaining letters
    for (char i = 'A'; i <= 'Z'; i++)
    {
        if (i == 'J') // Skip 'J'
            continue;
        if (pointer[i - 'A'] == 0) // If the character has not been used yet
        {
            pointer[i - 'A'] = 1; // Mark it as used
            matrix[len / 5][len % 5] = i; // Add it to the matrix
            charToIndex[i] = {len / 5, len % 5}; // Store its index
            len++; // Increase the length
        }
    }

    // Print the matrix
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            cout << matrix[i][j] << " "; // Print each character
        }
        cout << endl; // Print a newline after each row
    }
}

// Function to encrypt a string using the Playfair cipher
string Encrypt(string str)
{
    string temp; // Temporary string to store the result
    for (int i = 0; i < str.size(); i += 2) // Loop through the string two characters at a time
    {
        int row1 = charToIndex[str[i]].first; // Get the row of the first character
        int col1 = charToIndex[str[i]].second; // Get the column of the first character
        int row2 = charToIndex[str[i + 1]].first; // Get the row of the second character
        int col2 = charToIndex[str[i + 1]].second; // Get the column of the second character

        if (row1 == row2) // If the characters are in the same row
        {
            temp += matrix[row1][(col1 + 1) % 5]; // Add the character to the right of the first character to the temporary string
            temp += matrix[row2][(col2 + 1) % 5]; // Add the character to the right of the second character to the temporary string
        }
        else if (col1 == col2) // If the characters are in the same column
        {
            temp += matrix[(row1 + 1) % 5][col1]; // Add the character below the first character to the temporary string
            temp += matrix[(row2 + 1) % 5][col2]; // Add the character below the second character to the temporary string
        }
        else // If the characters are in different rows and columns
        {
            temp += matrix[row1][col2]; // Add the character at the intersection of the first character's row and the second character's column to the temporary string
            temp += matrix[row2][col1]; // Add the character at the intersection of the second character's row and the first character's column to the temporary string
        }
    }
    return temp; // Return the temporary string
}

// Function to decrypt a string using the Playfair cipher
string Decrypet(string str)
{
    string temp; // Temporary string to store the result
    for (int i = 0; i < str.size(); i += 2) // Loop through the string two characters at a time
    {
        int row1 = charToIndex[str[i]].first; // Get the row of the first character
        int col1 = charToIndex[str[i]].second; // Get the column of the first character
        int row2 = charToIndex[str[i + 1]].first; // Get the row of the second character
        int col2 = charToIndex[str[i + 1]].second; // Get the column of the second character

        if (row1 == row2) // If the characters are in the same row
        {
            temp += matrix[row1][(col1 - 1 + 5) % 5]; // Add the character to the left of the first character to the temporary string
            temp += matrix[row2][(col2 - 1 + 5) % 5]; // Add the character to the left of the second character to the temporary string
        }
        else if (col1 == col2) // If the characters are in the same column
        {
            temp += matrix[(row1 - 1 + 5) % 5][col1]; // Add the character above the first character to the temporary string
            temp += matrix[(row2 - 1 + 5) % 5][col2]; // Add the character above the second character to the temporary string
        }
        else // If the characters are in different rows and columns
        {
            temp += matrix[row1][col2]; // Add the character at the intersection of the first character's row and the second character's column to the temporary string
            temp += matrix[row2][col1]; // Add the character at the intersection of the second character's row and the first character's column to the temporary string
        }
    }
    return temp; // Return the temporary string
}

// Main function
int main()
{
    while (1) // Infinite loop
    {
        string key, plaintext; // Declare the key and plaintext

        cout << "Enter the key: "; // Prompt the user to enter the key
        cin >> key; // Read the key

        cin.ignore(); // Ignore the newline character

        cout << "Enter the plaintext: "; // Prompt the user to enter the plaintext
        getline(cin, plaintext); // Read the plaintext

        // Remove spaces from the plaintext
        plaintext = removeSpaces(plaintext);

        // Make uppercase
        plaintext = makeUppercase(plaintext);
        key = makeUppercase(key);

        // Replace 'J' with 'I' in the key
        for (int i = 0; i < key.size(); i++)
        {
            if (key[i] == 'J')
                key[i] = 'I';
        }

        // Handle duplicate characters in the plaintext
        for (int i = 0; i < plaintext.size(); i += 2)
        {
            if (plaintext[i] == plaintext[i + 1] && plaintext[i] == 'X')
            {
                plaintext.insert(i + 1, "Y");
            }
            else if (plaintext[i] == plaintext[i + 1])
            {
                plaintext.insert(i + 1, "X");
            }
        }

        // Padding
        if (plaintext.size() % 2 != 0 && plaintext[plaintext.size() - 1] == 'X')
            plaintext += 'Y';
        if (plaintext.size() % 2 != 0)
            plaintext += 'X';

        cout << "Plaintext after handle duplicate and padding: ";
        
        // Print the plaintext after handling duplicates and padding
        for (int i = 0; i < plaintext.size(); i++)
        {
            cout << plaintext[i]; // Print each character
            if (i % 2)
                cout << " "; // Print a space after every second character
        }

        cout << endl; // Print a newline

        // Matrix formation
        matrixFormation(key);

        // Encrypt the plaintext
        string cypherText = Encrypt(plaintext);

        cout << "CypherText: " << cypherText << endl; // Print the ciphertext

        // Decrypt the ciphertext
        string decryptedText = Decrypet(cypherText);

        cout << "Decrypted Text: " << decryptedText << endl << endl; // Print the decrypted text
    }
    return 0; // End the program
