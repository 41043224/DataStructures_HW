#include <iostream>
#include <stdexcept>
#include <cmath> // �Ω� pow ���

using namespace std;

class Polynomial; // �e�V�ŧi

class Term {
    friend class Polynomial; // �N Polynomial �]���ͤ����O�A�Ϩ����X�� Term ���p������
    friend ostream& operator<<(ostream& os, const Polynomial& p); // �ͤ���ơA�Ω��X
    friend istream& operator>>(istream& is, Polynomial& p); // �ͤ���ơA�Ω��J
private:
    float coef; // �t��
    int exp;    // ����

public:
    Term(float c = 0, int e = 0) : coef(c), exp(e) {}
};

class Polynomial {
public:
    Polynomial(int capacity = 10); // �c�y���
    Polynomial Add(const Polynomial& other) const; // �h�����[�k
    Polynomial Mult(const Polynomial& other) const; // �h�������k
    float Eval(float x) const; // �D��

    void AddTerm(float coef, int exp); // �K�[�@��

    // ���� << �B��šA�Ω��X�h����
    friend ostream& operator<<(ostream& os, const Polynomial& p);

    // ���� >> �B��šA�Ω��J�h����
    friend istream& operator>>(istream& is, Polynomial& p);

private:
    Term* termArray; // �s�x�h��������
    int capacity;    // �e�q
    int terms;       // ��e�����ƶq
};

Polynomial::Polynomial(int cap) : capacity(cap), terms(0) {
    termArray = new Term[capacity]; // �ʺA���t�s�x�Ŷ�
}

void Polynomial::AddTerm(float coef, int exp) {
    if (terms >= capacity) {
        throw overflow_error("Polynomial capacity exceeded"); // ��W�L�e�q�ɩߥX���`
    }
    termArray[terms++] = Term(coef, exp); // �K�[�s����Ʋդ�
}

Polynomial Polynomial::Add(const Polynomial& other) const {
    Polynomial c(capacity + other.capacity); // ���G�h����
    int aPos = 0, bPos = 0; // ��Ӧh��������e��m

    // �X�֨�Ӧh����
    while (aPos < terms && bPos < other.terms) {
        if (termArray[aPos].exp == other.termArray[bPos].exp) {
            // �p�G���ƬۦP�A�t�Ƭۥ[
            c.AddTerm(termArray[aPos].coef + other.termArray[bPos].coef, termArray[aPos].exp);
            aPos++;
            bPos++;
        }
        else if (termArray[aPos].exp > other.termArray[bPos].exp) {
            // �p�G��e�������Ƹ��j�A�K�[�쵲�G�h������
            c.AddTerm(termArray[aPos].coef, termArray[aPos].exp);
            aPos++;
        }
        else {
            // �_�h�K�[�t�@�Ӧh��������e��
            c.AddTerm(other.termArray[bPos].coef, other.termArray[bPos].exp);
            bPos++;
        }
    }

    // �K�[�Ѿl��
    while (aPos < terms) {
        c.AddTerm(termArray[aPos].coef, termArray[aPos].exp);
        aPos++;
    }

    while (bPos < other.terms) {
        c.AddTerm(other.termArray[bPos].coef, other.termArray[bPos].exp);
        bPos++;
    }

    return c; // ��^���G�h����
}

Polynomial Polynomial::Mult(const Polynomial& other) const {
    Polynomial result(capacity * other.capacity); // ���G�h����

    // �i�歼�k�ާ@
    for (int i = 0; i < terms; i++) {
        for (int j = 0; j < other.terms; j++) {
            float coef = termArray[i].coef * other.termArray[j].coef; // �t�Ƭۭ�
            int exp = termArray[i].exp + other.termArray[j].exp; // ���Ƭۥ[
            result.AddTerm(coef, exp); // �K�[���n��
        }
    }

    return result; // ��^���G�h����
}

float Polynomial::Eval(float x) const {
    float result = 0.0;

    // �p��h�����b x �B����
    for (int i = 0; i < terms; i++) {
        result += termArray[i].coef * pow(x, termArray[i].exp); // �ھڤ����p��
    }

    return result; // ��^���G
}

// ���� << �B��šA�Ω��X�h����
ostream& operator<<(ostream& os, const Polynomial& p) {
    for (int i = 0; i < p.terms; i++) {
        os << p.termArray[i].coef << "x^" << p.termArray[i].exp;
        if (i < p.terms - 1) {
            os << " + ";
        }
    }
    return os;
}

// ���� >> �B��šA�Ω��J�h����
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
