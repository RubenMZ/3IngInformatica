/*Basic Gaussian elimination with pivoting*/

/* DESCRIPTION:
    - Algorithm for solving system of n linear equations
       with n unknowns (x1,x2,...,xn)
    - Gaussian elimination is algorithm for solving
    system of linear equations. This method can be
    used to calculate determinant, inverse matrix or
    find inverse matrix.
   Author: Ervin B,
   May 2013
*/

#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

using namespace std;

void PrintMatrix( vector<vector<double> > &A)
{
    for ( int i = 0; i < A.size(); i++)
    {
        for ( int j = 0; j < A[i].size(); j++)
            cout << setiosflags(ios::showpoint | ios::fixed | ios::right)
                 << setprecision(4)
                 << setw(8) << A[i][j];
        cout << endl;
    }
}

vector<double> SystemSolution(vector<vector<double> > &A,vector<double> b)
{
    //Determine and test size of a matrix
    int n = A.size();
    for(int i = 0; i < n; i++)
        if(n != A[i].size())
            throw "Error! Number of rows and columns of matrix must be equal!";

    vector<double> x (b.size());
 //vector x is a vector of solutions (x1,x2,x3...xn)



    for(int i = 0; i < n - 1; i++)
    {
        for(int j = i+1; j < n; j++)
        {
            //Finding pivot
            double pivot = A[i][i];
            int index = i;
            for(int k = i+1; k < n; k++)
            {
                if(pivot > abs(A[k][i]))
                {
                    index = k;
                    pivot = A[k][i];
                }
            }

            //Row exchange
            for(int k = 0; k < n; k++)
            {
                double tmp = A[i][k];
                A[i][k] = A[index][k];
                A[index][k] = tmp;
            }

            //Elimination
            double coefficient = -(A[j][i]/A[i][i]);
            for(int k = i; k < n; k++)
            {
                A[j][k] += coefficient*A[i][k];
            }

            b[j] += coefficient*b[i];
        }
    }

    PrintMatrix(A);

    //Back-substitution
    x[n-1] = b[n-1]/A[n-1][n-1];
    for(int i = n-2; i>=0; i--)
    {
        double sum = 0;
        for(int j = i; j < n; j++)
        {
            sum += x[j]*A[i][j];
        }
        x[i] = (b[i]-sum)/A[i][i];
    }

    return x;
}



void PrintVector(const vector<double> &b)
{
    for(int i = 0; i < b.size(); i++)
        cout << setiosflags(ios::showpoint | ios::fixed | ios::right)
        << setprecision(4)
        << setw(8) << b[i]<<endl;
}


int main()
{
    int n;
    cout<<"Enter number of equations:";
    cin>>n;
    vector<vector<double> > A (n,vector<double> (n));
    vector<double> b (n);

    cout<<"Enter matrix coefficients:"<<endl;
    for(int i=0;i<n;i++)
      for(int j=0;j<n;j++)
      {
         cout<<"A["<<i+1<<"|"<<j+1<<"]=";
         cin>>A[i][j];
      }
    cout<<"\nEnter vector b:"<<endl;
    for(int i=0;i<n;i++)
    {
         cout<<"B["<<i+1<<"]= ";
         cin>>b[i];
    }

    vector<double> x = SystemSolution(A,b);
    cout<<"- SOLUTIONS -"<<endl;
    cout<<"Matrix:"<<endl;
    PrintMatrix(A);
    cout<<"\nVector x:"<<endl;
    PrintVector(x);

    return 0;
}