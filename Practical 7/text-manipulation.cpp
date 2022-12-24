#include "text-manipulation.hpp"

char toLowerCase(char ch)
{
    if (ch >= 65 && ch <= 90)
        ch += 32;
    return ch;
}

size_t countCharacters(string &text)
{
    int i{0};
    int count{0};
    while (text[i++] != '\0')
    {
        if (text[i] == '\n')
            continue;
        count++;
    }
    return count;
}

size_t countCharacters(string &text, char ch)
{
    int i{0};
    int count{0};
    while (text[i++] != '\0')
    {
        if (text[i] == '\n' || text[i] == ' ')
            continue;
        count++;
    }
    return count;
}

size_t countWords(string &text)
{
    istringstream iss(text);
    string temp;
    int count{0};
    while (getline(iss, temp, ' '))
    {
        if (temp.find('\n') != string::npos)
        {
            istringstream iss1(temp);
            while (getline(iss1, temp))
            {
                if (temp != "")
                    count++;
            }
            continue;
        }
        count++;
    }
    return count;
}

size_t countParagraphs(string &text)
{
    string temp;
    istringstream iss(text);
    int count{0};
    while (getline(iss, temp))
    {
        if (temp == "")
            continue;
        count++;
    }
    return count;
}

size_t countSentences(string &text)
{
    string temp;
    istringstream iss(text);
    int count{0};
    while (getline(iss, temp, '.'))
    {
        if (temp.find('!') != string::npos)
        {
            string temp1;
            istringstream iss1(temp1);
            while (getline(iss1, temp1, '!'))
            {
                if (temp1 != "")
                    count++;
            }
            continue;
        }
        if (temp.find('?') != string::npos)
        {
            string temp1;
            istringstream iss1(temp1);
            while (getline(iss1, temp1, '?'))
            {
                if (temp1 != "")
                    count++;
            }
            continue;
        }
        count++;
    }
    return count;
}

string processWord(string word)
{
    string processed = "";
    for (size_t i{0}; word[i] != '\0'; i++)
    {
        if (!((word[i] >= 65 && word[i] <= 90) || (word[i] >= 97 && word[i] <= 122)))
            continue;
        if (word[i] >= 65 && word[i] <= 90)
            word[i] += 32;
        processed = processed + word[i];
    }
    return processed;
}

void wordMap(string &text)
{
    list *mapArray = new list[26];
    string temp;
    istringstream iss(text);
    while (getline(iss, temp, ' '))
    {
        if (temp.find('\n') != string::npos)
        {
            istringstream iss1(temp);
            while (getline(iss1, temp))
            {
                if (temp != "")
                {
                    temp = processWord(temp);
                    char ch = temp[0];
                    list &ptr = mapArray[ch - 97];
                    if (!ptr.start)
                        ptr.create(temp);
                    else
                        ptr.searchAndUp(temp);
                }
            }
            continue;
        }
        temp = processWord(temp);
        char ch = temp[0];
        list &ptr = mapArray[ch - 97];
        if (!ptr.start)
            ptr.create(temp);
    }
    for (size_t i{0}; i < 26; i++)
        mapArray[i].print();
}

void searchPattern(string text, string pattern)
{
    int found = text.find(pattern);
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    while (found != string::npos)
    {
        SetConsoleTextAttribute(hConsole, 15);
        cout << text.substr(0,found);
        text = text.substr(found+pattern.length());
        SetConsoleTextAttribute(hConsole, 224);
        cout<<pattern;
        found = text.find(pattern);
    }
    SetConsoleTextAttribute(hConsole, 15);
    cout << text.substr(0,found);
}