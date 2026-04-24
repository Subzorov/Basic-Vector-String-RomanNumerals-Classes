// 25L-0622 Muhammad Zubair Azam

#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;

class VectorType {
    double* x;
    double* y;
    double* z;

public:

    VectorType (double i = 1, double j = 1, double k = 1) 
    {
        this->x = new double {i};
        this->y = new double {j};
        this->z = new double {k};
    }
    VectorType (const VectorType& v) {
        this->x = new double (*(v.x));
        this->y = new double (*(v.y));
        this->z = new double (*(v.z));
    }
    ~VectorType () {
        delete x;
        delete y;
        delete z;
    }

    VectorType& operator = (const VectorType& v) {
        if (this != &v) {
            *this->x = *(v.x);
            *this->y = *(v.y);
            *this->z = *(v.z);
        }
        return *this;
    }
    double operator * (const VectorType& v) const {
        double res = (*this->x) * (*v.x) +  (*this->y) * (*v.y) +  (*this->z) * (*v.z);
        return res;
    }
    VectorType operator ^ (const VectorType& v) const {
        double x_component = (*this->y * *v.z) - (*this->z * *v.y);
        double y_component = (*this->z * *v.x) - (*this->x * *v.z);
        double z_component = (*this->x * *v.y) - (*this->y * *v.x);
        return {x_component, y_component, z_component};
    }
    VectorType operator + (const VectorType& v) const {
        return {(*this->x) + (*v.x), (*this->y) + (*v.y), (*this->z) + (*v.z)};
    }
    VectorType operator - (const VectorType& v) const {
        return {(*this->x) - (*v.x), (*this->y) - (*v.y), (*this->z) - (*v.z)};
    }
    VectorType& operator ++ () {
        ++(*this->x);
        ++(*this->y);
        ++(*this->z);
        return *this;
    }
    VectorType& operator -- () {
        --(*this->x);
        --(*this->y);
        --(*this->z);
        return *this;
    }
    VectorType operator ++ (int) {
        VectorType temp = *this;
        (*this->x)++;
        (*this->y)++;
        (*this->z)++;
        return temp;
    }
    VectorType operator -- (int) {
        VectorType temp = *this;
        (*this->x)--;
        (*this->y)--;
        (*this->z)--;
        return temp;
    }
    double length () const {
        double res = sqrt((*this->x) * (*this->x) + (*this->y) * (*this->y) + (*this->z) * (*this->z));
        return res;
    }

    friend bool operator == (const VectorType& v1, const VectorType& v2);
    friend bool operator != (const VectorType& v1, const VectorType& v2);
    friend ostream& operator << (ostream& out, const VectorType& v);
    friend istream& operator >> (istream& in, VectorType& v);
    friend double fractionCalc (const VectorType& v1, const VectorType& v2);
    friend double theta (const VectorType& v1, const VectorType& v2);
};

bool operator == (const VectorType& v1, const VectorType& v2) {
    if (*(v1.x) == *(v2.x) && *(v1.y) == *(v2.y) && *(v1.z) == *(v2.z)) { return true; }
    else { return false; }
}
bool operator != (const VectorType& v1, const VectorType& v2) {
    if (*(v1.x) != *(v2.x) || *(v1.y) != *(v2.y) || *(v1.z) != *(v2.z)) { return true; }
    else { return false; }
}
ostream& operator << (ostream& out, const VectorType& v) {
    out << *(v.x) << "i " << *(v.y) << "j " << *(v.z) << "k ";
    return out;
}
istream& operator >> (istream& in, VectorType& v) {
    cout << "Enter x: ";
    while (!(in >> *v.x)) {
        cout << "Invalid input! Enter a number for x: ";
        in.clear();
        in.ignore(1000, '\n');
    }

    cout << "Enter y: ";
    while (!(in >> *v.y)) {
        cout << "Invalid input! Enter a number for y: ";
        in.clear();
        in.ignore(1000, '\n');
    }

    cout << "Enter z: ";
    while (!(in >> *v.z)) {
        cout << "Invalid input! Enter a number for z: ";
        in.clear();
        in.ignore(1000, '\n');
    }
    return in;
}
double fractionCalc (const VectorType& v1, const VectorType& v2) {
    if (v1.length() * v2.length() != 0) {
        double numerator = v1 * v2;
        double denominator = v1.length() * v2.length();
        return ( numerator/denominator );
    }
    else { return 0; }
}
double theta(const VectorType& v1, const VectorType& v2) {
    double x = fractionCalc(v1, v2);
    double result = 3.141589/2 - (x + (x* x* x)/6  + (x*x*x*x*x)/40);
    return result;
}


class String {
    char* str;
    int size;
    bool errorIndex (int i1, int i2) {
        if (i1 > size || i2 > size || i1 < 0 || i2 < 0) { return true; }
        else { return false; }
    }
    int indexSubString (const char* s) {
        for (int i = 0; str[i] != '\0'; i++) {
            int j = 0;
            while (s[j] != '\0' && str[i+j] == s[j]) { j++; }
            if (s[j] == '\0') { return i; }
        }
        return -1;
    }
public:

    String(const char* s = "") { 
        if (s == nullptr) {
            size = 0;
            str = new char[1];
            str[0] = '\0';
        } 
        else {
            size = 0;
            while (s[size] != '\0') { size++; }
            str = new char[size + 1];
            for (int i = 0; i < size; i++) { str[i] = s[i]; }
            str[size] = '\0';
        }
    }
    ~String () { delete[] str; }
    String (const String& s) {
        this->size = s.size;
        this->str = new char [size + 1];
        this->str[size] = '\0';
        for (int i = 0; i < size; i++) { this->str[i] = s.str[i]; }
    }
    int length () { return size; }

    String upper () {
        String result(*this);
        for (int i = 0; result.str[i] != '\0'; i++) {
            if ( result.str[i] >= 'a' && result.str[i] <= 'z') { result.str[i] -= 32; }
        }
        return result;
    }
    String lower () {
        String result(*this);
        for (int i = 0; result.str[i] != '\0'; i++) {
            if ( result.str[i] >= 'A' && result.str[i] <= 'Z') { result.str[i] += 32; }
        }
        return result;
    }

    char& at (int index) { 
        if (index >= size || index < 0)  { 
            cout << "Invalid Index!" << endl;
            static char null = '\0';
            return null;
        }
        else { return str[index]; }
    }

    String substring (int i1, int i2) {

        if (!errorIndex(i1, i2) && i1 <= i2) {
            char* temp;
            int len = 0;
            for (int i = i1; i <= i2; i++) { len++; }
            temp = new char [len + 1];
            temp[len] = '\0';
            int count = 0;
            for (int i = i1; i <= i2; i++) { temp[count++] = str[i]; }
            String result(temp);
            delete[] temp;
            return result;
        }
        else { return String(""); }
    }

    int getSubStringIndex (const char* s) {
        if (indexSubString(s) != -1) { return indexSubString(s); }
        else { 
            cout << "Substring could not be found! " << endl;
            return -1;
        }
    }

    void compare (const String& s) const {
        if (*this > s) { cout << *this << " is greatert than " << s << endl; }
        if (*this < s) { cout << *this << " is smaller than " << s << endl; }
        if (*this == s) { cout << *this << " is equal to " << s << endl; }
    }

    void concat (const char* s) { *this = *this + s; }
    void concat (const String& s) { *this = *this + s; }
    void concat (const char c) { *this = *this + c; }
    void concat (const int x) { *this = *this + x; }
    void concat (const float x) { *this = *this + x; }
    void prepend (const String& s) { *this = s + *this; }
    void prepend (const char* s) { *this = s + *this; }
    void prepend (const char c) { *this = c + *this; }
    void prepend (const int x) { *this = x + *this; }
    void prepend (const float x) { *this = x + *this; }

    bool operator == (const String& s) const;
    bool operator != (const String& s) const;
    bool operator < (const String& s) const;
    bool operator > (const String& s) const;
    String& operator = (const String& s);
    char& operator [] (int index);
    friend String operator + (const char* s1,  const String& s2);
    friend String operator + (const String& s1, const String& s2);
    friend String operator + (const String& s, const char c);
    friend String operator + (const char c, const String& s);
    friend String operator + (const String& s, const int x);
    friend String operator + (const int x, const String& s);
    friend String operator + (const String& s, const float x);
    friend String operator + (const float x, const String& s);
    friend ostream& operator << (ostream& out, const String& s);
    friend istream& operator >> (istream& in, String& s);
};

bool String::operator == (const String& s) const {
    if (this->size != s.size) { return false; }
    else {
        for (int i = 0; i < size; i++) {
            if (this->str[i] != s.str[i]) { return false; }
        }
    }
    return true;
}

bool String::operator != (const String& s) const {
    if (this->size != s.size) { return true; }
    else {
        for (int i = 0; i < size; i++) {
            if (this->str[i] != s.str[i]) { return true; }
        }
    }
    return false;
}

bool String::operator < (const String& s) const {
    int min_size;
    if (this->size < s.size) { min_size = this->size; }
    else { min_size = s.size; }
    for (int i = 0; i < min_size; i++) {
        if (this->str[i] > s.str[i]) { return false; }
        if (this->str[i] < s.str[i]) { return true; }
    }
    return (this->size < s.size);
}

bool String::operator > (const String& s) const {
    int min_size;
    if (this->size < s.size) { min_size = this->size; }
    else { min_size = s.size; }
    for (int i = 0; i < min_size; i++) {
        if (this->str[i] > s.str[i]) { return true; }
        if (this->str[i] < s.str[i]) { return false; }
    }
    return (this->size > s.size);
}

String& String::operator = (const String& s) {
    if (this == &s) { return *this; }
    delete[] this->str;
    this->size = s.size;
    this->str = new char [size + 1];
    this->str[size] = '\0';
    for (int i = 0; i < size; i++) { this->str[i] = s.str[i]; }
    return *this;
}

String operator + (const char* s1,  const String& s2) { return String(s1) + s2; }

String operator + (const String& s1, const String& s2) {
    int total_size = s1.size + s2.size;
    char* temp = new char [total_size + 1];
    temp[total_size] = '\0';
    int count = 0;
    for (int i = 0; i < s1.size; i++) { temp[count++] = s1.str[i]; }
    for (int i = 0; i < s2.size; i++) { temp[count++] = s2.str[i]; }
    String result(temp);
    delete[] temp;
    return result;
}

String operator + (const String& s, const char c) {
    int total_size = s.size + 1;
    char* temp = new char [total_size + 1];
    temp[total_size] = '\0';
    for (int i = 0; i < total_size; i++) { temp[i] = s.str[i]; }
    temp[s.size] = c;
    String result(temp);
    delete[] temp;
    return result;
}

String operator + (const char c, const String& s) {
    int total_size = s.size + 1;
    char* temp = new char [total_size + 1];
    temp[total_size] = '\0';
    temp[0] = c;
    for (int i = 0; i < s.size; i++) { temp[i+1] = s.str[i]; }
    String result(temp);
    delete[] temp;
    return result;
}

String operator + (const String& s, const int x) {
    string x_string = to_string(x);
    char* temp;
    int temp_size = 0;
    for (int i = 0; x_string[i] != '\0'; i++) { temp_size++; }
    temp = new char [temp_size + 1];
    temp[temp_size] = '\0';
    for (int i = 0; i < temp_size; i++) { temp[i] = x_string[i]; }
    String result(temp);
    delete[] temp;
    return (s + result); 
}

String operator + (const String& s, const float x) {
    string x_string = to_string(x);
    char* temp;
    int temp_size = 0;
    for (int i = 0; x_string[i] != '\0'; i++) { temp_size++; }
    temp = new char [temp_size + 1];
    temp[temp_size] = '\0';
    for (int i = 0; i < temp_size; i++) { temp[i] = x_string[i]; }
    String result(temp);
    delete[] temp;
    return (s + result); 
}

String operator + (const int x, const String& s) {
    string x_string = to_string(x);
    char* temp;
    int temp_size = 0;
    for (int i = 0; x_string[i] != '\0'; i++) { temp_size++; }
    temp = new char [temp_size + 1];
    temp[temp_size] = '\0';
    for (int i = 0; i < temp_size; i++) { temp[i] = x_string[i]; }
    String result(temp);
    delete[] temp;
    return (result + s); 
}

String operator + (const float x, const String& s) {
    string x_string = to_string(x);
    char* temp;
    int temp_size = 0;
    for (int i = 0; x_string[i] != '\0'; i++) { temp_size++; }
    temp = new char [temp_size + 1];
    temp[temp_size] = '\0';
    for (int i = 0; i < temp_size; i++) { temp[i] = x_string[i]; }
    String result(temp);
    delete[] temp;
    return (result + s); 
}

char& String::operator [] (int index) { return at(index); }

ostream& operator << (ostream& out, const String& s) {
    out << s.str;
    return out;
}

istream& operator >> (istream& in, String& s) {
    char temp[3000];
    while (true) {
        in.getline(temp, 3000);
        if (temp[0] == '\0') { cout << "Empty string entered! Please try again: " << endl; }
        else { break; }
    }
    delete[] s.str;
    s.size = 0;
    for (int i = 0; temp[i] != '\0'; i++) { s.size++; }
    s.str = new char [s.size + 1];
    s.str[s.size] = '\0';
    for (int i = 0; i < s.size; i++) { s.str[i] = temp[i]; }
    return in;
}

class RomanNumerals {
private:
    string rom_num;

    bool Error (const int size) const {
        for (int i = 0; i < size; i++) {
            if (rom_num[i] != 'I' && rom_num[i] != 'V' && rom_num[i] != 'X' && rom_num[i] != 'L' && rom_num[i] != 'C' &&
            rom_num[i] != 'D' && rom_num[i] != 'M') 
            { return true; }
        }
        int counter = 1;
        for (int i = 0; i < size; i++) {
            if (counter == 4) { return true; }
            if (i < size-1 && rom_num[i] == rom_num[i+1]) { counter++; }
            else { counter = 1; }
        }
        for (int i = 0; i < size; i++) {
            if (rom_num[i] == 'V' || rom_num[i] == 'L' || rom_num[i] == 'D') {
                if (i < size - 1 && (rom_num[i] == rom_num[i+1])) { return true; }
            }
        }
        for (int i = 0; i < size - 1; i++) {
            int current_val = Convertor(rom_num[i]);
            int next_val = Convertor(rom_num[i+1]);

            if (current_val < next_val) {
            if (rom_num[i] == 'I' && (rom_num[i+1] != 'V' && rom_num[i+1] != 'X')) { return true; }
            if (rom_num[i] == 'X' && (rom_num[i+1] != 'L' && rom_num[i+1] != 'C')) { return true; }
            if (rom_num[i] == 'C' && (rom_num[i+1] != 'D' && rom_num[i+1] != 'M')) { return true; }
            if (rom_num[i] == 'V' || rom_num[i] == 'L' || rom_num[i] == 'D') { return true; }
            }
        }
        return false;
    }
    int Convertor (char c) const {
        if (c == 'I') { return 1; }
        else if (c == 'V') { return 5; }
        else if (c == 'X') { return 10; }
        else if (c == 'L') { return 50; }
        else if (c == 'C') { return 100; }
        else if (c == 'D') { return 500; }
        else if (c == 'M') { return 1000; }
        return 0;
    }

    int romToInt () const {
        int len = rom_num.length();
        int integer = 0;

        if (len == 1) { return Convertor(rom_num[0]); }
        else {
            if (len % 2 == 0) {
                for (int i = len-1; i >= 0; i-=2) {
                    int current = Convertor(rom_num[i]), next = Convertor(rom_num[i-1]);
                    if (current <= next) { integer  = integer + (current + next); }
                    else { integer = integer + (current - next); }
                }
            }
            else {
                for (int i = len-1; i >= 0; i-=2) {
                    if (i-1 < 0) {
                        integer = integer + Convertor(rom_num[i]);
                        break;
                    }
                    int current = Convertor(rom_num[i]), next = Convertor(rom_num[i-1]);
                    if (current <= next) { integer  = integer + (current + next); }
                    else { integer = integer + (current - next); }
                }
            }
        }
        return integer;
    }
    
    string intToRom (int number) const {
        string roman;
        char numerals[7] = {'M', 'D', 'C', 'L', 'X', 'V', 'I'};
        int i = 0;
        while (number != 0) {
            int temp = Convertor(numerals[i]);
            if (number == 4) {
                roman += "IV";
                break;
            }
            else if (number == 9) {
                roman += "IX";
                break;
            }
            if (number >= 40 && number <= 49) {
                roman += "XL";
                number -= 40;
            }
            else if (number >= 90 && number <= 99) {
                roman += "XC";
                number -= 90;
            }
            else if (number >= 400 && number <= 499) {
                roman += "CD";
                number -= 400;
            }
            else if (number >= 900 && number <= 999) {
                roman += "CM";
                number -= 900;
            }
            if (temp <= number) { 
                roman += numerals[i];
                number -= temp;
            }
            else { i++; }
        }

        return roman;
    }

public:
    RomanNumerals (string n = ""): rom_num(n) {};

    void setRomNum () { 
    cout << "Enter the Roman Numeral: ";
    while (true) {
        cin >> rom_num;
        if (Error(rom_num.length())) { 
            cout << "Invalid Roman Numeral! Enter it again: "; 
            continue; 
        }
        if (rom_num.empty()) { 
            cout << "Empty string entered! Please try again: "; 
            continue; 
        }
        break; 
    }
}
    RomanNumerals operator + (const RomanNumerals& r) const {
        int result = this->romToInt() + r.romToInt();
        if (result > 3999) {
            cout << "Number exceeded above the standard!" << endl;
            return RomanNumerals(); //this will return a blank object.
        }
        return intToRom(result); 
    }
    RomanNumerals operator - (const RomanNumerals& r) const {
        int result = this->romToInt() - r.romToInt();
        while (result <= 0) {
            cout << "Number below the standard!" << endl;
            return RomanNumerals();
        }
        return intToRom(result);
    }
    RomanNumerals operator * (const RomanNumerals& r) const {
        int result = this->romToInt() * r.romToInt();
        while (result > 3999) {
            cout << "Number exceeded above the standard!" << endl;
            return RomanNumerals();
        }
        return intToRom(result);
    }
    RomanNumerals operator / (const RomanNumerals& r) const {
        int result = this->romToInt() / r.romToInt();
        if (result == 0) { 
            cout << "Number cannot be represented in Roman Numerals! " << endl;
            return RomanNumerals();
        }
        return intToRom(result);
    }
    bool operator == (const RomanNumerals& r) const {
        if (this->rom_num == r.rom_num) { return true; }
        else { return false; }
    }
    bool operator != (const RomanNumerals& r) const {
        if (this->rom_num != r.rom_num) { return true; }
        else { return false; }
    }
    bool operator < (const RomanNumerals& r) const {
        if (romToInt() < r.romToInt()) { return true; }
        else { return false; }
    }
    bool operator > (const RomanNumerals& r) const {
        if (romToInt() > r.romToInt()) { return true; }
        else { return false; }
    }

    RomanNumerals& operator ++ () {
        int temp = romToInt();
        ++temp;
        if (temp > 3999) {
            cout << "Number has exceeded above the standard!" << endl;
            return *this; // I am returning the object by reference therefore I cannot do return RomanNumerals();
        }
        this->rom_num = intToRom(temp);
        return *this;
    }

    RomanNumerals operator ++ (int) {
        RomanNumerals original = *this;
        int temp = romToInt();
        temp++;
        if (temp > 3999) {
            cout << "Number has exceeded above the standard!" << endl;
            return RomanNumerals();
        }
        this->rom_num = intToRom(temp);
        return original;
    }
    RomanNumerals& operator -- () {
        int temp = romToInt();
        --temp;
        if (temp == 0) {
            cout << "Numeral cannot be evaluated!" << endl;
            return *this;
        }
        this->rom_num = intToRom(temp);
        return *this;
    }
    RomanNumerals operator -- (int) {
        RomanNumerals original = *this;
        int temp = romToInt();
        temp--;
        if (temp == 0) {
            cout << "Numeral cannot be evaluated!" << endl;
            return RomanNumerals();
        }
        this->rom_num = intToRom(temp);
        return original;
    }
    string getRoman(int x) { return intToRom(x); }
    int getInt () { return romToInt(); }
    friend ostream& operator << (ostream& out, RomanNumerals& r);
};

ostream& operator << (ostream& out, RomanNumerals& r) {
    out << r.rom_num;
    return out;
}


int main() {
    VectorType v1(-3, 4, 0), v2(1, -1, -1);
    VectorType v3 = v1 + v2;
    VectorType v4 = v1 - v2;
    double dot = v1 * v2;
    VectorType cross = v1 ^ v2;
    
    cout << "V1: " << v1 << endl;
    cout << "V2: " << v2 << endl;
    cout << "Sum: " << v3 << endl;
    cout << "Diff: " << v4 << endl;
    cout << "Dot: " << dot << endl;
    cout << "Cross: " << cross << endl;
    cout << "Length V1: " << v1.length() << endl;
    cout << "Angle: " << theta(v1, v2) << endl;

    v1 = v2;
    cout << "Assignment (V1=V2): " << v1 << endl;
    cout << "Equality: " << (v1 == v2) << endl;
    cout << "Inequality: " << (v1 != v3) << endl;

    ++v1;
    v1++;
    cout << "Increments: " << v1 << endl;
    --v1;
    v1--;
    cout << "Decrements: " << v1 << endl;

    String s1("My name is this");
    String s2("My name is Zubi");
    String s3 = s1 + " " + s2;
    String s4, s5;
    cout << "Enter the strings: " << endl;
    cin >> s4 >> s5;
    cout << "Printing using << operators: " << s4 << endl << s5 << endl;
    
    cout << "String: " << s3 << endl;
    cout << "Length: " << s3.length() << endl;
    cout << "Upper: " << s3.upper() << endl;
    cout << "Lower: " << s3.lower() << endl;
    cout << "Substring: " << s3.substring(0, 3) << endl;
    cout << "Index of 'TRU': " << s3.getSubStringIndex("tru") << endl;
    
    s1.concat(s2);
    s2.prepend("Super ");
    s4.concat(2.12313f); //f is necessary otherwise the compiler gets confused because a decimal number could be treated as a float, double etc
    s5.prepend(123412421);
    cout << "Concat s1: " << s1 << endl << " | Concat s4: " << s4 << endl;
    cout << "Prepend s2: " << s2 << endl << " | Prepend s5: " << s5 << endl;
    cout << "Comparison: " << (s1 > s2) << endl;
    cout << "At index 2: " << s1[2] << endl;
    
    RomanNumerals r1, r2;
    r1.setRomNum();
    r2.setRomNum();
    RomanNumerals r_sum = r1 + r2;
    cout << "Sum = " << r_sum << endl;
    r1.setRomNum();
    r2.setRomNum();
    RomanNumerals r_sub = r1 - r2;
    cout << "Difference = " << r_sub << endl;
    r1.setRomNum();
    r2.setRomNum();
    RomanNumerals r_mul = r1 * r2;
    cout << "Multiplication = " << r_mul << endl;
    r1.setRomNum();
    r2.setRomNum();
    RomanNumerals r_div = r1 / r2;
    cout << "Division = " << r_div << endl;
    
    ++r1;
    r2++;
    cout << "Prefix X: " << r1 << endl;
    cout << "Postfix V: " << r2 << endl;
    cout << "R1 > R2: " << (r1 > r2) << endl;
    cout << "Int value: " << r1.getInt() << endl;

    return 0;
}