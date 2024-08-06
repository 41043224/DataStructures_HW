#include <iostream>
#include <stdexcept>
#include <cmath> // 用於 pow 函數

using namespace std;

class Polynomial; // 前向宣告

class Term {
    friend class Polynomial; // 將 Polynomial 設為友元類別，使其能夠訪問 Term 的私有成員
    friend ostream& operator<<(ostream& os, const Polynomial& p); // 友元函數，用於輸出
    friend istream& operator>>(istream& is, Polynomial& p); // 友元函數，用於輸入
private:
    float coef; // 系數
    int exp;    // 指數

public:
    Term(float c = 0, int e = 0) : coef(c), exp(e) {}
};

class Polynomial {
public:
    Polynomial(int capacity = 10); // 構造函數
    Polynomial Add(const Polynomial& other) const; // 多項式加法
    Polynomial Mult(const Polynomial& other) const; // 多項式乘法
    float Eval(float x) const; // 求值

    void AddTerm(float coef, int exp); // 添加一項

    // 重載 << 運算符，用於輸出多項式
    friend ostream& operator<<(ostream& os, const Polynomial& p);

    // 重載 >> 運算符，用於輸入多項式
    friend istream& operator>>(istream& is, Polynomial& p);

private:
    Term* termArray; // 存儲多項式的項
    int capacity;    // 容量
    int terms;       // 當前項的數量
};

Polynomial::Polynomial(int cap) : capacity(cap), terms(0) {
    termArray = new Term[capacity]; // 動態分配存儲空間
}

void Polynomial::AddTerm(float coef, int exp) {
    if (terms >= capacity) {
        throw overflow_error("Polynomial capacity exceeded"); // 當超過容量時拋出異常
    }
    termArray[terms++] = Term(coef, exp); // 添加新項到數組中
}

Polynomial Polynomial::Add(const Polynomial& other) const {
    Polynomial c(capacity + other.capacity); // 結果多項式
    int aPos = 0, bPos = 0; // 兩個多項式的當前位置

    // 合併兩個多項式
    while (aPos < terms && bPos < other.terms) {
        if (termArray[aPos].exp == other.termArray[bPos].exp) {
            // 如果指數相同，系數相加
            c.AddTerm(termArray[aPos].coef + other.termArray[bPos].coef, termArray[aPos].exp);
            aPos++;
            bPos++;
        }
        else if (termArray[aPos].exp > other.termArray[bPos].exp) {
            // 如果當前項的指數較大，添加到結果多項式中
            c.AddTerm(termArray[aPos].coef, termArray[aPos].exp);
            aPos++;
        }
        else {
            // 否則添加另一個多項式的當前項
            c.AddTerm(other.termArray[bPos].coef, other.termArray[bPos].exp);
            bPos++;
        }
    }

    // 添加剩餘項
    while (aPos < terms) {
        c.AddTerm(termArray[aPos].coef, termArray[aPos].exp);
        aPos++;
    }

    while (bPos < other.terms) {
        c.AddTerm(other.termArray[bPos].coef, other.termArray[bPos].exp);
        bPos++;
    }

    return c; // 返回結果多項式
}

Polynomial Polynomial::Mult(const Polynomial& other) const {
    Polynomial result(capacity * other.capacity); // 結果多項式

    // 進行乘法操作
    for (int i = 0; i < terms; i++) {
        for (int j = 0; j < other.terms; j++) {
            float coef = termArray[i].coef * other.termArray[j].coef; // 系數相乘
            int exp = termArray[i].exp + other.termArray[j].exp; // 指數相加
            result.AddTerm(coef, exp); // 添加乘積項
        }
    }

    return result; // 返回結果多項式
}

float Polynomial::Eval(float x) const {
    float result = 0.0;

    // 計算多項式在 x 處的值
    for (int i = 0; i < terms; i++) {
        result += termArray[i].coef * pow(x, termArray[i].exp); // 根據公式計算
    }

    return result; // 返回結果
}

// 重載 << 運算符，用於輸出多項式
ostream& operator<<(ostream& os, const Polynomial& p) {
    for (int i = 0; i < p.terms; i++) {
        os << p.termArray[i].coef << "x^" << p.termArray[i].exp;
        if (i < p.terms - 1) {
            os << " + ";
        }
    }
    return os;
}

// 重載 >> 運算符，用於輸入多項式
istream& operator>>(istream& is, Polynomial& p) {
    cout << "Enter the number of terms: ";
    is >> p.terms;
    if (p.terms > p.capacity) {
        throw overflow_error("Polynomial capacity exceeded");
    }
    for (int i = 0; i < p.terms; i++) {
        cout << "Enter coefficient and exponent for term " << i + 1 << ": ";
        is >> p.termArray[i].coef >> p.termArray[i].exp;
    }
    return is;
}

int main() {
    Polynomial p1, p2;

    cout << "Enter Polynomial 1:" << endl;
    cin >> p1;

    cout << "Enter Polynomial 2:" << endl;
    cin >> p2;

    Polynomial sum = p1.Add(p2);
    Polynomial product = p1.Mult(p2);

    cout << "Polynomial 1: " << p1 << endl;
    cout << "Polynomial 2: " << p2 << endl;
    cout << "Sum: " << sum << endl;
    cout << "Product: " << product << endl;

    float value = p1.Eval(2.0);
    cout << "Value of Polynomial 1 at x=2: " << value << endl;

    return 0;
}
