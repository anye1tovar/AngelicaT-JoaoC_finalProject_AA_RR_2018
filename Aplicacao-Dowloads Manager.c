#include<stdio.h>

void knapSack(int W, int wt[], int val[], int n)
{
do{
	printf("N: %d", n);
    int i, w;
    int K[n+1][W+1];
    int S[n+1][W+1];
    int X[n]; 
    
    for (i = 0; i <= n; i++)
    {
        for (w = 0; w <= W; w++)
        {
        	 S[i][w] = 0;
        }
    }
    
    // Construir tabela K[][] em bottom up
    for (i = 0; i <= n; i++)
    {
        for (w = 0; w <= W; w++)
        {
            if (i==0 || w==0)
                K[i][w] = 0;
            else if (wt[i-1] <= w)
            	if(val[i-1] + K[i-1][w-wt[i-1]] > K[i-1][w])
				{
            		K[i][w] = val[i-1] + K[i-1][w-wt[i-1]];
            		S[i][w] = i - 1;
				}
				else
				{
					K[i][w] = K[i-1][w];
					S[i][w] = -1; // significa que uso la posisión anterios i-1, w para asignar el valor de suma maxima a la matriz
				}
            else
            {
            	K[i][w] = K[i-1][w];
                S[i][w] = -1;
			}                
        }
    }
    int a = n;
    int b = W;
    
    printf("\nAs posicoes dos elementos utilizados foram:\n");
    int m = -1;
    while(a > 0 && b > 0)
	{
		if(S[a][b] > -1){
			m++;
			X[m] = S[a][b];
			a--;
			b = b - wt[a];
		}
		else
		{
			do{
				a--;
			}
			while(S[a][b] == -1);	
		}
	}
	int j;	
	for(j = 0; j<=m; j++){
		printf("Pos: %d - Peso: %d - Valor: %d\n", X[j], wt[X[j]], val[X[j]]);
		wt[X[j]] = -1;
	}

	printf("\nValor maximo: %d\n", K[n][W]);
	
	//eliminar posiciones del vector ya "descargadas"
		
	int k = 0;
	int l;
	int naoentro = 1;
	for(j = 0; j <= n; j++){
		if(naoentro == 1){
			k = j;
		}
		while(wt[j] == -1 && k != n-1){
			naoentro = 0;
			wt[j] = wt[k+1];
			val[j] = val[k+1];
			
			wt[k+1] = -1;
			val[k+1] = -1;

			k++;
		}
		if(k == n-1) break;
	}
	n = n - (m+1);
}
while(n>0);	
}

// Programa driver
int main()
{        
    int val[] = {1, 2, 1, 2, 3, 2, 3, 1, 2, 1, 3, 2, 1, 3, 1, 2, 2, 1, 3, 3, 3, 2, 1, 1, 2, 2, 3, 1};
    int wt[] = {1, 5, 7, 10, 5, 6, 2, 7, 3, 8, 6, 4, 7, 5, 9, 6, 4, 5, 1, 7, 6, 4, 6, 8, 2, 9, 1, 3};
    int W = 10;
    int n = sizeof(val)/sizeof(val[0]);
    int m = sizeof(wt)/sizeof(wt[0]);
    
    knapSack(W, wt, val, n);
	return 0;
}

