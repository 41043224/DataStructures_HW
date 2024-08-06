#include <iostream>
#include <vector>
#include <stdexcept>
#include <cmath> 

using namespace std;

class Polynomial; 


class Term {
    friend class Polynomial; // 將 Polynomial 設為友元類別，使其能夠訪問 Term 的私有成員
private:
    float coef; 
    int exp;    

public:

    Term(float c = 0, int e = 0) : coef(c), exp(e) {}
};

class Polynomial {
public:
    Polynomial(int capacity = 10);
    Polynomial Add(const Polynomial& other) const;
    Polynomial Mult(const Polynomial& other) const;

    float Eval(float x) const;

    // 添加一項到多項式中
    void AddTerm(float coef, int exp);
    // 列出多項式
    void Print() const;

private:
    Term* termArray; // 存儲多項式的項
    int capacity;    // 容量
    int terms;       // 當前項的數量
};

// Polynomial 類別的構造函數，初始化容量和項數
Polynomial::Polynomial(int cap) : capacity(cap), terms(0) {
    termArray = new Term[capacity]; // 動態分配存儲空間
}

// 向多項式中添加一項
void Polynomial::AddTerm(float coef, int exp) {
    if (terms >= capacity) {
        throw overflow_error("error"); // 當超過容量時拋出異常
    }
    termArray[terms++] = Term(coef, exp); // 添加新項到數組中
}

// 多項式加法
Polynomial Polynomial::Add(const Polynomial& other) const {
    Polynomial c;
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

    return c;
}

// 多項式乘法
Polynomial Polynomial::Mult(const Polynomial& other) const {
    Polynomial result; 


    for (int i = 0; i < terms; i++) {
        for (int j = 0; j < other.terms; j++) {
            float coef = termArray[i].coef * other.termArray[j].coef; // 系數相乘
            int exp = termArray[i].exp + other.termArray[j].exp; // 指數相加
            result.AddTerm(coef, exp); // 添加乘積項
        }
    }

    return result;
}

// 多項式求值
float Polynomial::Eval(float x) const {
    float result = 0.0;

    // 計算多項式在 x 處的值
    for (int i = 0; i < terms; i++) {
        result += termArray[i].coef * pow(x, termArray[i].exp); // 根據公式計算
    }

    return result;
}

// 列出多項式
void Polynomial::Print() const {
    for (int i = 0; i < terms; i++) {
        cout << termArray[i].coef << "x^" << termArray[i].exp;
        if (i < terms - 1) {
            cout << " + ";
        }
    }
    cout << endl;
}

int main() {
    Polynomial p1;
    p1.AddTerm(3, 2); 
    p1.AddTerm(5, 1); 
    p1.AddTerm(6, 0); 

    Polynomial p2;
    p2.AddTerm(2, 1); 
    p2.AddTerm(1, 0); 

    Polynomial sum = p1.Add(p2);
    Polynomial product = p1.Mult(p2);

    cout << "Polynomial 1: ";
    p1.Print();

    cout << "Polynomial 2: ";
    p2.Print();

    cout << "Sum: ";
    sum.Print();

    cout << "Product: ";
    product.Print();

    float value = p1.Eval(2.0);
    cout << "Value of Polynomial 1 at x=2: " << value << endl;

    return 0;
}
