#include <stdio.h>

int main() {
    int N, Q=2;
    char array_names[20];
    char array_options[100];
    char name[20];

    scanf("%d", &N);

    for (int i = 0; i < N; i++)
    {
        scanf("%s", &array_names[i]);
    }

    
    for (int x = 0; x < 9; x++)
    {
        for (int y = 0; y < N; y++)
        {
            printf("%d%s\n", x, array_names[y]);
        }
        
    }
    

    return 0;
}