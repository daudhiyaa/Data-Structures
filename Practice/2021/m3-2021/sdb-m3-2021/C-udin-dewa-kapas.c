// @author Nadif Mustafa

#include <stdio.h>
#define ll long long
#define MAXN 1000000

int nyala[4][MAXN + 5],		// MA, MK, BB, BK
	prefix[4][MAXN + 5];	// MA, MK, BB, BK

int main(){
	ll n, m,
	   res = 0,
	   ct_overlap = 0;
	int i, j,
		a, b;
	scanf("%lld %lld", &n, &m);
	
	while(m--){
		scanf("%d %d", &a, &b);
		
		// BIRU
		if(a + b <= n){
			nyala[3][n + 2 - a - b] = 1;
			prefix[3][n + 2 - a - b] = 1;
		}
		else {
			nyala[2][a + b - n] = 1;
			prefix[2][a + b - n] = 1;
		}
		
		// MERAH
		if(a + n - b <= n){
			nyala[0][b - a + 1] = 1;
			prefix[0][b - a + 1] = 1;
		}
		else {
			nyala[1][a - b + 1] = 1;
			prefix[1][a - b + 1] = 1;
		}
	}
	for(i = 0; i < 4; i++){
		for(j = 2; j <= n; j++){
			prefix[i][j] += prefix[i][j - 2];
		}
	}
	for(i = 0; i < 4; i++){
		for(j = 1; j <= n; j++)
		{
			if(!nyala[i][j])
				continue;
			
			int ii = ((i/2 + 1) % 2) * 2,
				jj = n + 1 - j,
				serang = jj,
				overlap = prefix[ii][jj] + prefix[ii + 1][jj];
			
			serang -= overlap;
			res += serang;
			
			if(i < 2)
				ct_overlap += overlap;
		}
	}
	printf("%lld\n", res + ct_overlap);
	return 0;
}