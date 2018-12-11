/*
ID: silxikys
LANG: C++11
TASK: charrec
*/
#include<stdio.h>

int target[1200];
int character[27][21];

int visit[1200],pre[1200],minsum[1200],out[1200];

char table[]={" abcdefghijklmnopqrstuvwxyz"};

int total;

FILE *fout;

void initial()
{
	FILE *fin;
	int i,j,k,result;
	char tmp[32];
	fin=fopen ("font.in", "r");
	fscanf(fin,"%d",&total);
	for(i=0;i<27;i++)
	{
		for(j=1;j<=20;j++)
		{
			fscanf(fin,"%s",tmp);
			for(k=result=0;k<20;k++)
			{
				result<<=1;
				if(tmp[k]=='1')
					result+=1;
			}
			character[i][j]=result;
		}
	}
	for(i=0;i<19;i++)
	{
		visit[i]=1;
		minsum[i]=-1;
	}
	pre[0]=-1;
	minsum[0]=0;
	fclose(fin);
	fin=fopen ("charrec.in", "r");
	fscanf(fin,"%d",&total);
	for(i=1;i<=total;i++)
	{
		fscanf(fin,"%s",tmp);
		for(j=result=0;j<20;j++)
		{
			result<<=1;
			if(tmp[j]=='1')
				result+=1;
		}
		target[i]=result;
	}
	fclose(fin);
	fout = fopen ("charrec.out", "w");
}

int pop(unsigned x)
{
	x=x-((x>>1)&0x55555555);
	x=(x&0x33333333)+((x>>2)&0x33333333);
	x=(x+((x>>4)&0x0f0f0f0f))&0x0f0f0f0f;
	x=x+(x>>8);
	return ((x+(x>>16))&0x3f);
}

int match19(int level)
{
	int h,l,max,i,j,k1,k2,sum;
	h=l=-1;
	max=120;
	for(i=0;i<27;i++)
	{
		for(j=1;j<=20;j++)
		{
			sum=0;
			for(k1=k2=1;k2<=20;)
			{
				if(k2==j)
				{
					k2++;
					continue;
				}
				sum+=pop(character[i][k2]^target[level-19+k1]);
				if(sum>=max)
					break;
				k1++;
				k2++;
			}
			if(sum<max)
			{
				h=i;
				l=max=sum;
			}
		}
	}
	return (h<<16)|l;
}
int match20(int level)
{
	int h,l,max,i,j,sum;
	h=l=-1;
	max=120;
	for(i=0;i<27;i++)
	{	
		sum=0;
		for(j=1;j<=20;j++)
		{
			sum+=pop(character[i][j]^target[level-20+j]);
			if(sum>=max)
				break;
		}
		if(sum<max)
		{
			h=i;
			l=max=sum;
		}
	}
	return (h<<16)|l;
}
int match21(int level)
{
	int h,l,max,i,j,k1,k2,sum;
	h=l=-1;
	max=120;
	for(i=0;i<27;i++)
	{
		for(j=1;j<=21;j++)
		{
			sum=0;
			for(k1=k2=1;k2<=21;)
			{
				if(k2==j)
				{
					k2++;
					continue;
				}
				sum+=pop(character[i][k1]^target[level-21+k2]);
				if(sum>=max)
					break;
				k1++;
				k2++;
			}
			if(sum<max)
			{
				h=i;
				l=max=sum;
			}
		}
	}
	return (h<<16)|l;
}

int DP(int level)
{
	int tmp,max,result;
	max=0x7fffffff;
	if(level<0)
		return -1;
	if(visit[level])
		return minsum[level];
	tmp=DP(level-19);
	if(tmp!=-1)
	{
		result=match19(level);
		if((result&0xffff0000)!=0xffff0000&&(result&0xffff)+tmp<max)
		{
			max=(result&0xffff)+tmp;
			pre[level]=level-19;
			out[level]=(result&0xffff0000)>>16;
		}
	}
	tmp=DP(level-20);
	if(tmp!=-1)
	{
		result=match20(level);
		if((result&0xffff0000)!=0xffff0000&&(result&0xffff)+tmp<max)
		{
			max=(result&0xffff)+tmp;
			pre[level]=level-20;
			out[level]=(result&0xffff0000)>>16;
		}
	}
	tmp=DP(level-21);
	if(tmp!=-1)
	{
		result=match21(level);
		if((result&0xffff0000)!=0xffff0000&&(result&0xffff)+tmp<max)
		{
			max=(result&0xffff)+tmp;
			pre[level]=level-21;
			out[level]=(result&0xffff0000)>>16;
		}
	}
	visit[level]=1;
	minsum[level]=max==0x7fffffff?-1:max;
	return minsum[level];
}

void print(int i)
{
	if(i!=0)
		print(pre[i]);
	else
		return;
	fprintf(fout,"%c",table[out[i]]);
}

int main()
{
	int i;
	initial();
	DP(total);
	i=total;
	print(i);
	fprintf(fout,"\n");
	fclose(fout);
	return 0;
}