#include <stdio.h>

void print_matrix(double matrix[][100], int m, int n,int zero_size)
{
    for (size_t i = 0; i < m; i++)
    {
        for (size_t j = 0; j < n; j++)
        {
            printf("%.*lf\t",zero_size, matrix[i][j]);
        }
        printf("\n");
    }
    printf("---------------------------------------\n");
}

void matrix_add(double f[][100], double s[][100], int m, int n)
{
    double add[100][100] = {0};
    for (size_t i = 0; i < m; i++)
    {
        for (size_t j = 0; j < n; j++)
        {
            add[i][j] = f[i][j] + s[i][j];
        }
    }
    print_matrix(add, m, n, 0);
}

void matrix_multiplicate(double f[][100], double s[][100], int m, int n)
{
    double multi[100][100] = {0};
    for (size_t i = 0; i < m; i++)
    {
        for (size_t j = 0; j < n; j++)
        {
            int size = 0;
            while (size < m)
            {
                multi[i][j] += f[i][size] * s[size][j];
                size++;
            }
        }
    }
    print_matrix(multi, m, n, 0);
}

void matrix_transform(double f[][100], int m, int n)
{
    double transform[100][100] = {0};
    for (size_t i = 0; i < m; i++)
    {
        for (size_t j = 0; j < n; j++)
        {
            transform[j][i] = f[i][j];
        }
    }
    print_matrix(transform, m, n, 0);
}

void matrix_invert(double f[][100])
{
    const int size = 2;
    float determine = 1/(f[0][0]*f[1][1]-f[0][1]*f[1][0]);
    double invert[100][100] = {0};
    for (size_t i = 0; i < size; i++)
    {
        for (size_t j = 0; j < size; j++)
        {
            if ((i + j) % 2)
            {
                invert[i][j] = -f[i][j]*determine;
            }
            else
            {
                if (i == 0)
                {
                    invert[1][1] = f[i][j]*determine;
                }
                else
                {
                    invert[0][0] = f[i][j]*determine;
                }
            }
        }
    }
    print_matrix(invert, size, size,6);
}

int main()
{
    double first[100][100] = {0}, second[100][100] = {0};
    int  m, n, choice,start=1;
    while (choice != 9)
    {
        printf("1.Read two matrices, A and B\n2.Store the result of A + B in a file\n3.Store the result of AB in a file (if legal)\n4.Store the content of AT in a file\n5.Store the content of A-1 in a file (if 2x2)\n9.Quit\n");
        scanf("%d",&choice);
        printf("\n");
        if(start){
            if(choice == 9){
                printf("quit!\n");
                continue;
            }
            if (choice==1){
                start=0;
            }else{
                printf("the matrix are empty!\n---------------------------------------\n");
                continue;
            }
        }
        switch (choice)
        {
            case 1:
                for (int i = 0; i < m; ++i) {
                    for (int j = 0; j < n; ++j) {
                        first[i][j] = 0;
                        second[i][j] = 0;
                    }
                }
                printf("m:");
                scanf("%d", &m);
                printf("n:");
                scanf("%d", &n);
                for (size_t i = 0; i < m; i++)
                {
                    for (size_t j = 0; j < n; j++)
                    {
                        scanf("%lf", &first[i][j]);
                    }
                }
                for (size_t i = 0; i < m; i++)
                {
                    for (size_t j = 0; j < n; j++)
                    {
                        scanf("%lf", &second[i][j]);
                    }
                }
                break;
            case 2:
                matrix_add(first,second,m,n);
                break;
            case 3:
                m == n ? matrix_multiplicate(first, second, m, n) : printf("can't multiplicate.\n---------------------------------------\n");
                break;
            case 4:
                matrix_transform(first,m,n);
                break;
            case 5:
                m == 2 && n == 2 ? matrix_invert(first) : printf("can't invert.\n---------------------------------------\n");
                break;
            case 9:
                printf("quit!\n");
                break;
            default:
                printf("please enter 1~5 or 9 to quit!\n---------------------------------------\n");
                break;
        }
    }
    return 0;
}