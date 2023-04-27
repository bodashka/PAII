//Bahdan Shakh
//b.shakh@innopolis.university
#include <bits/stdc++.h>
using namespace std;

double mod(double x) {
    if (x >= 0) {
        return x;
    } else return -1*x;
}

class Matrix {
    protected:
        int n, m;
        vector <vector <double> > body;

    public:
        Matrix(int n, int m){
            this->n = n;
            this->m = m;
            body.resize(n);
            for (int i = 0; i < n; i++){
                body[i].resize(m);
            }
        }

        Matrix() : Matrix(0,0) {}

        Matrix(const vector <vector <double> > &a){
            this->n = a.size();
            this->m = 0;
            for (int i = 0; i < a.size(); i++){
                this->m = max(this->m, (int)a[i].size());
            }
            body.resize(n);
            for (int i = 0; i < this->n; i++){
                body[i].resize(m);
                for (int j = 0; j < this->m; j++){
                    if (a[i].size() <= j){
                        this->body[i][j] = 0;
                    } else this->body[i][j] = a[i][j];
                }
            }
        }

        Matrix operator=(const Matrix& other)
        {
            if (this == &other)
                return *this;

            this->n = other.n;
            this->m = other.m;
            this->body.resize(this->n);
            for (int i = 0; i < this->n; i++){
                this->body[i].resize(this->m);
                for (int j = 0; j < this->m; j++){
                    this->body[i][j] = other.body[i][j];
                }
            }

            return *this;
        }

        Matrix operator+(const Matrix& b)
        {
            Matrix temp(0,0);
            if (this->n != b.n || this->m!=b.m){
                return temp;
            }

            temp = *this;
            for (int i = 0; i < b.n; i++){
                for (int j = 0; j < b.m; j++){
                    temp.body[i][j] += b.body[i][j];
                }
            }

            return temp;
        }

        Matrix operator-(const Matrix& b)
        {
            Matrix temp(0,0);
            if (this->n != b.n || this->m!=b.m){
                return temp;
            }

            temp = *this;
            for (int i = 0; i < b.n; i++){
                for (int j = 0; j < b.m; j++){
                    temp.body[i][j] -= b.body[i][j];
                }
            }

            return temp;
        }

        Matrix operator*(const Matrix& b)
        {
            Matrix temp(0,0);
            if (this->m != b.n){
                return temp;
            }

            temp.n = this->n;
            temp.m = b.m;
            temp.body.resize(temp.n);
            for (int i = 0; i < this->n; i++){
                temp.body[i].resize(temp.m);
                for (int j = 0; j < b.m; j++){
                    temp.body[i][j] = 0;
                    for (int k = 0; k < b.n; k++){
                        temp.body[i][j] += this->body[i][k] * b.body[k][j];
                    }
                }
            }

            return temp;
        }

        Matrix transpose(){
            Matrix temp(this->m, this->n);
            for (int i = 0; i < this->n; i++){
                for (int j = 0; j < this->m; j++){
                    temp.body[j][i] = this->body[i][j];
                }
            }
            return temp;
        }

        friend istream& operator>>(istream& is, Matrix& obj)
        {
            int n, m;
            double x;
            is >> n;
            is >> m;
            obj.n = n;
            obj.body.resize(n);
            obj.m = m;
            for (int i = 0; i < n; i++){
                obj.body[i].resize(m);
                for (int j = 0; j < m; j++){
                    is >> x;
                    obj.body[i][j] = x;
                }
            }
            return is;
        }

        friend ostream& operator<<(ostream& os, const Matrix& obj)
        {
            for (int i = 0; i < obj.n-1; i++){
                for (int j = 0; j < obj.m; j++){
                    os << obj.body[i][j] <<' ';
                }
                os <<'\n';
            }
            for (int j = 0; j < obj.m; j++){
                os << obj.body[obj.n-1][j] <<' ';
            }

            return os;
        }

        bool isEmpty() {
            return this->n == 0 || this->m == 0;
        }

        int getN() const {
            return this->n;
        }

        int getM() const {
            return this->m;
        }

        vector <vector <double> > getBody() const {
            return this->body;
        }

        void rowDivide(double x, int i) {
            for (int j = 0; j < this->m; j++){
                this->body[i][j] = this->body[i][j] / x;
            }
        }

        void weirdMinusCheck() {
            for (int i = 0; i < this->n; i++){
                for (int j = 0; j < this->m; j++){
                    if (this->body[i][j] > -0.0000000001 && this->body[i][j] <= 0){
                        this->body[i][j] = 0;
                    }
                }
            }
        }

};

class AugmentedMatrix;
class PermutationMatrix;
class IdentityMatrix;
class SquareMatrix;
class EliminationMatrix;

class SquareMatrix : public Matrix {
    public:
        SquareMatrix(int n) : Matrix(n, n){}

        SquareMatrix() : Matrix(){}

        SquareMatrix(const vector <vector <double> > &a){
            this->n = a.size();
            this->m = a[0].size();
            body.resize(n);
            for (int i = 0; i < this->n; i++){
                body[i].resize(m);
                for (int j = 0; j < this->m; j++){
                    if (a[i].size() <= j){
                        this->body[i][j] = 0;
                    } else this->body[i][j] = a[i][j];
                }
            }
        }

        friend istream& operator>>(istream& is, SquareMatrix& obj)
        {
            int n;
            double x;
            is >> n;
            obj.n = n;
            obj.m = n;
            obj.body.resize(n);
            for (int i = 0; i < n; i++){
                obj.body[i].resize(n);
                for (int j = 0; j < n; j++){
                    is >> x;
                    obj.body[i][j] = x;
                }
            }
            return is;
        }

        Matrix inverse();
};

class ColumnVector : public Matrix {
    public:
        ColumnVector(int n) : Matrix(n, 1){}

        ColumnVector() : Matrix(){}

        ColumnVector(vector <double> a) {
            n = a.size();
            m = 1;
            body.resize(n);
            for (int i = 0; i < n; i++){
                body[i].push_back(a[i]);
            }
        }

        friend istream& operator>>(istream& is, ColumnVector& obj)
        {
            int n;
            is >> n;
            obj.n = n;
            obj.m = 1;
            obj.body.resize(n);
            for (int i = 0; i < n; i++){
                obj.body[i].resize(1);
                is >> obj.body[i][0];
            }
            return is;
        }

        void normalize() {
            double coef;
            Matrix length = this->transpose() * *this;
            coef = length.getBody()[0][0];
            for (int i = 0; i < this->n; i++){
                this->body[i][0] /= coef;
            }
        }
};

class IdentityMatrix : public SquareMatrix {
    public:
        IdentityMatrix(int n) : SquareMatrix(n) {
            for (int i = 0; i < n; i++) this->body[i][i] = 1;
        }

        IdentityMatrix() : SquareMatrix() {}
};

class PermutationMatrix : public IdentityMatrix {
    public:
        PermutationMatrix(int n, int i, int j) : IdentityMatrix(n) {
            this->body[i][i] = 0; this->body[j][j] = 0;
            this->body[i][j] = 1; this->body[j][i] = 1;
        }   

        PermutationMatrix() : IdentityMatrix() {}
};

class EliminationMatrix : public IdentityMatrix {
    public:
        EliminationMatrix(int n) : IdentityMatrix(n) {}
        EliminationMatrix() : IdentityMatrix() {}

        //Eliminate j from i
        double construct(Matrix& a, int i, int j) {
            double x = a.getBody()[i][j], y = a.getBody()[j][j];
            this->body[i][j] = x/(-y);
            if (this->body[i][j] == -0) this->body[i][j] = 0;
            return this->body[i][j];
        }
};

class AugmentedMatrix {
    public:
        Matrix* a;
        Matrix* b;

        AugmentedMatrix(Matrix* a, Matrix* b) {
            this->a = a;
            this->b = b;
        }
        
        AugmentedMatrix() {
            this->a = new IdentityMatrix();
            this->b = new IdentityMatrix();
        }

        friend ostream& operator<<(ostream& os, AugmentedMatrix& obj) {
            for (int i = 0; i < obj.a->getN(); i++){
                for (int j = 0; j < obj.a->getM(); j++){
                    os << obj.a->getBody()[i][j] <<' ';
                }
                for (int j = 0; j < obj.b->getM(); j++){
                    os << obj.b->getBody()[i][j] <<' ';
                }
                os <<'\n';
            }

            return os;
        }

        void rowDivide(double x, int i) {
            this->a->rowDivide(x, i);
            this->b->rowDivide(x, i);
        }
};

/*
C++ apparently does not support OOP in a way that Java does. I found this solution to work
*/
Matrix SquareMatrix::inverse() {
    SquareMatrix a = *this;
    int n = a.getN();

    AugmentedMatrix obj(&a, new IdentityMatrix(n) );

    for (int i = 0; i < n; i++) {
        //finding maximum element
        int max = i;
        for (int j = i+1; j < n; j++) {
            if (mod(obj.a->getBody()[j][i]) > mod(obj.a->getBody()[max][i])){
                max = j;
            }
        }
        if (max != i) {
            PermutationMatrix p(n, max, i);
            (*obj.a) = p * *(obj.a);
            (*obj.b) = p * *(obj.b);
        }

        //no instructions provided for dependent matrices
        /*if (a.getBody()[max][i] == 0) {
            break;
        }*/

        //elimination
        for (int j = i+1; j < n; j++) {
            if (obj.a->getBody()[j][i] != 0) {
                EliminationMatrix E(n);
                E.construct(a, j, i);
                (*obj.a) = E * *(obj.a);
                (*obj.b) = E * *(obj.b);
            }
        }

    }
    //"Way back:\n";
    for (int i = n-1; i >= 0; i--) {
        for (int j = i-1; j >= 0; j--) {
            if (obj.a->getBody()[j][i] != 0) {
                EliminationMatrix E(n);
                E.construct(a, j, i);
                (*obj.a) = E * *(obj.a);
                (*obj.b) = E * *(obj.b);
            }
        }
    }
    //"Diagonal normalization:\n";
    for (int i = 0; i < n; i++) {
        obj.rowDivide(obj.a->getBody()[i][i], i);
    }
    return (*obj.b);
}

#define GNUPLOT_NAME "C:\\gnuplot\\bin\\gnuplot -persist"

int main(){
    
    FILE* pipe = _popen(GNUPLOT_NAME, "w");

    Matrix a;
    ColumnVector b;
    int n = 10, deg = 3;
    vector <pair <double, double> > points = { {1,2}, {1.4, 2.6}, {2.33, 4.5}, {5.9, 1.6}, {3.14, 6.28}, {6.19, 4.56}, {4.5, 6.55}, 
    {1.34, 7.12}, {0, 0}, {2, 5} };
    //cin >> n;
    cout << setprecision(4) << fixed;
    vector <double> aNewVec(n);
    vector <vector <double> > aVec(n);
    vector <double> bVec(n);
    for (int i = 0; i < n; i++) {
        aNewVec[i] = points[i].first;
        bVec[i] = points[i].second;
    }
    //cin >> deg;
    for (int i = 0; i < n; i++) {
        aVec[i].resize(deg+1);
        aVec[i][0] = 1;
        for (int j = 1; j <= deg; j++) {
            aVec[i][j] = aVec[i][j-1] * aNewVec[i];
        }
    }
    a = Matrix(aVec);
    b = ColumnVector(bVec);
    /*cout << "A:\n" << a;
    cout << "\nA_T*A:\n";*/
    SquareMatrix step_two((a.transpose()*a).getBody() );
    /*cout << step_two;
    cout << "\n(A_T*A)^-1:\n";
    cout << step_two.inverse();
    cout << "\nA_T*b:\n";
    cout << a.transpose()*b;
    cout << "\nx~:\n";*/
    Matrix ans = step_two.inverse()*(a.transpose()*b);
    //cout << ans;

    fprintf(pipe, "plot [-5 : 10] [-30 : 30] %lf*x**3 + %lf*x**2 + %lf*x**1 + %lf*x**0 , '-' using 1:2 with points\n", ans.getBody()[3][0],
    ans.getBody()[2][0], ans.getBody()[1][0], ans.getBody()[0][0]);
    for (auto [x,y] : points) {
        fprintf(pipe, "%f\t%f\n", x, y);
    }
    fprintf(pipe, "e\n");
    fflush(pipe);

    _pclose(pipe);
    
}