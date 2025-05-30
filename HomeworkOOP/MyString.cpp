#include "MyString.h"
#include <iostream>
#include <cstring>

MyString::MyString() {
    this->length = 0;
    this->content = new char[1];
    this->content[0] = '\0';
}

MyString::MyString(size_t num) {
    size_t numCopy = num;

    int digitsOfNum = 0;
    do {
        numCopy /= 10;
        digitsOfNum++;
    } while (numCopy > 0);

    this->length = digitsOfNum;
    this->content = new char[this->length + 1];
    this->content[this->length] = '\0';
    for (size_t i = 0; i < length; i++) {
        this->content[i] = num % 10 + '0';
        num /= 10;
    }

    this->reverse();
}

MyString::MyString(int num) {
    this->length = 0;
    this->content = new char[1];
    this->content[0] = '\0';
    bool isNegative = false;

    if (num < 0) {
        isNegative = true;
        num *= -1;
    }
    size_t positiveNum = num;
    *this = MyString(positiveNum);

    if (isNegative) {
        *this = MyString("-") + *this;
    }
}

MyString::MyString(double num) {
    this->length = 0;
    this->content = new char[1];
    this->content[0] = '\0';

    bool isNegative = false;
    if (num < 0) {
        num *= -1;
        isNegative = true;
    }

    int integerPart = num;
    num -= integerPart;
    *this += MyString(integerPart);
    
    const int PRECISION = 10;

    int leadingZeroes = 0;
    double numCopy = num;
    while (numCopy < 0.1 && leadingZeroes < PRECISION) {
        numCopy *= 10;
        leadingZeroes++;
    }

    if (leadingZeroes < PRECISION) {
        *this += ".";
        for (size_t i = 0; i < leadingZeroes; i++) {
            *this += "0";
        }

        numCopy = num;
        for (size_t i = 0; i < PRECISION; i++) {
            numCopy *= 10;
        }

        size_t copyFirstSixDigits = numCopy;
        MyString afterDecimal(copyFirstSixDigits);
        size_t lastZeroIndex = afterDecimal.getLength();
        for (int i = afterDecimal.getLength() - 1; i >= 0; i--) {
            if (afterDecimal.content[i] != '0') {
                lastZeroIndex = i + 1;
                break;
            }
        }

        afterDecimal = afterDecimal.subStr(0, lastZeroIndex);
        *this += afterDecimal;
    }

    if (isNegative) {
        *this = MyString("-") + *this;
    }
}

MyString::MyString(const char* str) {
    if (str == nullptr) {
        this->length = 0;
        this->content = new char[1];
        this->content[0] = '\0';
        return;
    }

    this->length = strlen(str);
    this->content = new char[this->length + 1];
    strcpy_s(this->content, this->length + 1, str);
}

MyString::MyString(const MyString& other) {
    this->copyFrom(other);
}

MyString::MyString(MyString&& str) noexcept {
    this->length = str.length;
    this->content = str.content;
    str.content = nullptr;
    str.length = 0;
}

MyString& MyString::operator=(const MyString& other) {
    if (this != &other) {
        this->free();
        this->copyFrom(other);
    }

    return *this;
}

MyString& MyString::operator=(MyString&& other) noexcept {
    if (this != &other) {
        this->free();
        this->length = other.length;
        this->content = other.content;
        other.content = nullptr;
        other.length = 0;
    }

    return *this;
}

MyString::~MyString() {
    this->free();
}

void MyString::setString(const char* str) {
    if (str == nullptr) {
        return;
    }

    delete[] this->content;

    this->length = strlen(str);
    this->content = new char[this->length + 1];
    strcpy_s(this->content, this->length + 1, str);
}

void MyString::setString(const MyString& other) {
    this->setString(other.getCString());
}

const char* MyString::getCString() const {
    return this->content;
}

MyString MyString::subStr(size_t start, size_t end) const {
    if (start > this->length || end > this->length) {
        throw std::out_of_range("Index out of range");
    }

    char* newCString = new char[end - start + 1];

    for (size_t i = start, j = 0; i < end; i++, j++) {
        newCString[j] = this->content[i];
    }
    newCString[end - start] = '\0';

    MyString result(newCString);
    delete[] newCString;
    return result;
}

List<MyString> MyString::separate(char separator) const {
    List<MyString> result;

    size_t currentStart = 0;
    
    size_t i;
    for (i = 0; i < length; i++) {
        if (this->content[i] == separator) {
            if (i > currentStart) {
                result.add(this->subStr(currentStart, i));
            }
            currentStart = i + 1;
        }
    }

    if (i > currentStart) {
        result.add(this->subStr(currentStart, i));
    }


    return result;
}

size_t MyString::getLength() const {
    return this->length;
}

void MyString::serialize(std::ofstream& stream) const {
    if (!stream.is_open()) {
        return;
    }

    stream << this->length;
    stream << this->content;
}

bool MyString::operator==(const MyString& other) const {
    return strcmp(this->content, other.getCString()) == 0;
}

bool MyString::operator!=(const MyString& other) const {
    return strcmp(this->content, other.getCString()) != 0;
}

bool MyString::operator>(const MyString& other) const {
    return strcmp(this->content, other.getCString()) > 0;
}

bool MyString::operator<(const MyString& other) const {
    return strcmp(this->content, other.getCString()) < 0;
}

bool MyString::operator>=(const MyString& other) const {
    return strcmp(this->content, other.getCString()) > -1;
}

bool MyString::operator<=(const MyString& other) const {
    return strcmp(this->content, other.getCString()) < 1;
}

bool MyString::isDouble() const {
    size_t i = 0;

    while (i < this->length && this->content[i] == ' ') {
        i++;
    }


    if (i < this->length && (this->content[i] == '-' || this->content[i] == '+')) {
        i++;
    }

    bool hasDigitsBefore = false;

    while (i < this->length && this->content[i] != '.' && this->content[i] != ',') {
        if (this->content[i] < '0' || this->content[i] > '9') {
            return false;
        }
        hasDigitsBefore = true;
        i++;
    }

    bool hasDecimalPoint = false;
    if (i < this->length && (this->content[i] == '.' || this->content[i] == ',')) {
        hasDecimalPoint = true;
        i++;
    }

    bool hasDigitsAfter = false;
    while (i < this->length && this->content[i] != ' ') {
        if (this->content[i] < '0' || this->content[i] > '9') {
            return false;
        }
        hasDigitsAfter = true;
        i++;
    }

    while (i < this->length && this->content[i] == ' ') {
        i++;
    }
    
    return i == this->length && (hasDigitsBefore || (hasDecimalPoint && hasDigitsAfter));
}

double MyString::toDouble() const {
    if (!isDouble()) {
        throw std::invalid_argument("Couldn't convert to double");
    }

    size_t leftPart = 0;

    size_t i = 0;

    while (this->content[i] == ' ') {
        i++;
    }

    bool isNegative = false;
    if (this->content[i] == '-') {
        isNegative = true;
        i++;
    }
    else if (this->content[i] == '+') {
        i++;
    }

    while (i < this->length && this->content[i] != '.' && this->content[i] != ',') {
        if (this->content[i] < '0' || this->content[i] > '9') {
            throw std::invalid_argument("Couldn't convert to double");
        }

        leftPart *= 10;
        leftPart += this->content[i] - '0';
        i++;
    }

    if (i < this->length && (this->content[i] == '.' || this->content[i] == ',')) {
        i++;
    }

    size_t rightPart = 0;

    double divideBy = 1;
    while (i < this->length && this->content[i] != ' ') {
        if (this->content[i] < '0' || this->content[i] > '9') {
            throw std::invalid_argument("Couldn't convert to double");
        }
        
        rightPart *= 10;
        rightPart += this->content[i] - '0';
        divideBy *= 10;
        i++;
    }

    double result = leftPart + (rightPart / divideBy);

    if (isNegative) {
        result *= -1;
    }

    return result;
}

bool MyString::isSizeT() const {
    if (this->length == 0) {
        return false;
    }

    size_t prev = 0;
    size_t max = 1;
    while (max != prev) {
        prev = max;
        max <<= 1;
        max++;
    }

    MyString maxSizeTInMyString(max);
    if (this->length > maxSizeTInMyString.getLength()) {
        return false;
    }
    
    if(this->length == maxSizeTInMyString.length && *this > maxSizeTInMyString) {
        return false;
    }

    for (size_t i = 0; i < length; i++) {
        if (this->content[i] < '0' || this->content[i] > '9') {
            return false;
        }
    }

    return true;
}

size_t MyString::toSizeT() const {

    size_t result = 0;
    for (size_t i = 0; i < length; i++) {
        if (this->content[i] == ' ') {
            continue;
        }

        result *= 10;
        result += this->content[i] - '0';
    }

    return result;
}

MyString& MyString::concat(const MyString& str) {
    size_t newLength =  this->length + str.getLength();
    char* newContent = new char[newLength + 1];

    strcpy_s(newContent, newLength + 1, this->content);
    strcat_s(newContent, newLength + 1, str.getCString());

    delete[] this->content;
    this->length = newLength;
    this->content = newContent;
    return *this;
}

MyString& MyString::reverse() {
    char swap;
    for (size_t i = 0; i < length / 2; i++) {
        swap = this->content[i];
        this->content[i] = this->content[length - 1 - i];
        this->content[length - 1 - i] = swap;
    }

    return *this;
}

MyString MyString::operator+(const MyString& str) const {
    MyString result(*this);
    result.concat(str);
    return result;
}

MyString& MyString::operator+=(const MyString& str) {
    this->concat(str);
    return *this;
}

void MyString::copyFrom(const MyString& other) {
    this->length = other.getLength();
    this->content = new char[this->length + 1];
    strcpy_s(this->content, this->length + 1, other.getCString());
}

void MyString::free() {
    delete[] this->content;
    this->content = nullptr;
    this->length = 0;
}

std::ofstream& operator<<(std::ofstream& stream, const MyString& string) {
    if (!stream.is_open()) {
        return stream;
    }

    stream.write(reinterpret_cast<const char*>(&string.length), sizeof(size_t));
    stream.write(reinterpret_cast<const char*>(string.content), string.length + 1);

    return stream;
}

std::ifstream& operator>>(std::ifstream& stream, MyString& string) {
    if (!stream.is_open()) {
        return stream;
    }

    string.free();

    stream.read(reinterpret_cast<char*>(&string.length), sizeof(size_t));

    string.content = new char[string.length + 1];
    stream.read(reinterpret_cast<char*>(string.content), string.length + 1);

    return stream;
}

std::ostream& operator<<(std::ostream& stream, const MyString& string) {
    stream << string.content;
    return stream;
}

std::istream& operator>>(std::istream& stream, MyString& string) {
    const int MAXINPUTSIZE = 1024;
    char input[MAXINPUTSIZE];
    std::cin.getline(input, MAXINPUTSIZE);
    string.setString(input);

    return stream;
}
