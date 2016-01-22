#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<stdbool.h>

int compare(int ans, int computerguess,int P);
int cg(int,int,int);
int mypow(int);

bool finish = false;

int main(int argc,char *argv[])
{
	int gtimes;
	printf("\033c");
	srand((unsigned)time(NULL)); //generate random seed with time
	if(argc != 3) //check user input
	{
		printf("\n%s%s%s\n%s\n%s\n\n","Usage:",argv[0]," N P","N is the number of intergers to play with.","P is the number of positions.");
		exit(1);
	}
	int N = atoi(argv[1]);
	int P = atoi(argv[2]);
	if((N > 9 || N < 1) || (P > 9 || P < 1)) //check if N and P are legal
	{
		printf("\n%s\n\n","N and P should be between one to nine.");
		exit(1);
	}
	if(N < P)
	{
		printf("\n%s\n\n","The answer will not have the same interger twice,please input N >= P.");
		exit(1);
	}
	int i,j;
	int tempans[P];
	int ans = 0;
	for(i = 0;i < P;i++) //generate random number
	{
		tempans[i] = (rand() % N) + 1;
		for(j = i - 1;j >= 0;j--)
		{
			if(tempans[i] == tempans[j])
			{
				i--;
				break;
			}
		}
	}
	for(i = 0;i < P;i++)
	{
		ans += mypow(P - i - 1) * tempans[i];
	}
	printf("%s%d\n","The answer is:",ans);
	printf("\n%s\n","Computer start guessing.");
	while(!finish)
		gtimes = cg(N,P,ans);
	printf("Times guessed:%d\n\n",gtimes);
	return 0;
}

int compare(int ans, int computerguess, int P)
{
	int H = 0,X = 0, k, j;
	int guessarray[P],ansarray[P];
	for(k = 0;k < P;k++)
	{
		guessarray[k] = computerguess / mypow(P - 1 - k);
		computerguess -= mypow(P - 1 - k) * guessarray[k];
		ansarray[k] = ans / mypow(P - 1 - k);
		ans -= mypow(P - 1 - k) * ansarray[k];
	}
	for(k = 0;k < P;k++)
	{
		for(j = 0;j < P;j++)
		{
			if(ansarray[k] == guessarray[j] && k == j)
				H++;
			if(ansarray[k] == guessarray[j] && k != j)
				X++;
		}
	}
	return H * 10 + X;
}

int cg(int N,int P,int ans)
{
	static int i = 0;
	int j,k,rtemp = 0;
	static int possibleans[30];
	static int HXresult[30];
	bool ok = true;
	int tg[P],temp = 0;

	possibleans[i] = 0;
	HXresult[i] = 0;
	for(j = 0;j < P;j++) //generate random number
	{
		tg[j] = (rand() % N) + 1;
		for(k = j - 1;k >= 0;k--)
		{
			if(tg[j] == tg[k])
			{
				j--;
				break;
			}
		}
	}
	for(j = 0;j < P;j++)
	{
		temp += mypow(P - j - 1) * tg[j];
	}
	for(j = 0;j < i;j++)
	{
		if(HXresult[j] != compare(possibleans[j],temp,P))//compare with possible answers,not with true answer,so no need to show result.
		{
			ok = false;
			break;
		}
	}

	if(ok)
	{
		rtemp = compare(ans,temp,P);//compare with true answer and show the result.
		printf("%d %dH%dX\n", temp, rtemp / 10, rtemp % 10);
		possibleans[i] = temp;
		HXresult[i] = rtemp;
		i++;
	}
	if(rtemp == P * 10)
		finish = true;
	return i;
}

//function to calculate 10 power a,same as pow(10,a) in math.h.
int mypow(int a)
{
	if(a == 0)
		return 1;
	else
		return 10 * mypow(a - 1);//recursive here.
}
