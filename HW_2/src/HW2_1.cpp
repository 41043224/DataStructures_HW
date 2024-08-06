#include <iostream>
#include <vector>
#include <stdexcept>
#include <cmath> 

using namespace std;

class Polynomial; 


class Term {
    friend class Polynomial; // �N Polynomial �]���ͤ����O�A�Ϩ����X�� Term ���p������
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

    // �K�[�@����h������
    void AddTerm(float coef, int exp);
    // �C�X�h����
    void Print() const;

private:
    Term* termArray; // �s�x�h��������
    int capacity;    // �e�q
    int terms;       // ��e�����ƶq
};

// Polynomial ���O���c�y��ơA��l�Ʈe�q�M����
Polynomial::Polynomial(int cap) : capacity(cap), terms(0) {
    termArray = new Term[capacity]; // �ʺA���t�s�x�Ŷ�
}

// �V�h�������K�[�@��
void Polynomial::AddTerm(float coef, int exp) {
    if (terms >= capacity) {
        throw overflow_error("error"); // ��W�L�e�q�ɩߥX���`
    }
    termArray[terms++] = Term(coef, exp); // �K�[�s����Ʋդ�
}

// �h�����[�k
Polynomial Polynomial::Add(const Polynomial& other) const {
    Polynomial c;
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

    return c;
}

// �h�������k
Polynomial Polynomial::Mult(const Polynomial& other) const {
    Polynomial result; 


    for (int i = 0; i < terms; i++) {
        for (int j = 0; j < other.terms; j++) {
            float coef = termArray[i].coef * other.termArray[j].coef; // �t�Ƭۭ�
            int exp = termArray[i].exp + other.termArray[j].exp; // ���Ƭۥ[
            result.AddTerm(coef, exp); // �K�[���n��
        }
    }

    return result;
}

// �h�����D��
float Polynomial::Eval(float x) const {
    float result = 0.0;

    // �p��h�����b x �B����
    for (int i = 0; i < terms; i++) {
        result += termArray[i].coef * pow(x, termArray[i].exp); // �ھڤ����p��
    }

    return result;
}

// �C�X�h����
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
