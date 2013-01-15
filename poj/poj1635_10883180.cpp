#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<vector>
#include<string>
using namespace std;

string MinTreeRep(string tree)
{
    if(tree=="01")
        return tree;
	tree=tree.substr(1,tree.size()-2);

	vector<string> v;

	int size=tree.size();
	int last=0;
	int tmp=0;
	for(int i=0;i<size;i++)
	{
		if(tree[i]=='0')
			tmp++;
		if(tree[i]=='1')
			tmp--;
		if(tmp==0)
		{
			v.push_back(MinTreeRep(tree.substr(last,i-last+1)));
			last=i+1;
		}
	}
	sort(v.begin(),v.end());
	tree="";
	size=v.size();
	for(int i=0;i<size;i++)
        tree=tree+v[i];

	return "0"+tree+"1";
}
char str[3333];
int main()
{
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	string tree1,tree2;
	int t;
	scanf("%d\n",&t);
	while(t--)
	{
//		cin>>tree1>>tree2;
        gets(str);
        tree1=str;
        tree1="0"+tree1+"1";

		tree1=MinTreeRep(tree1);
        gets(str);
        tree2=str;
		tree2="0"+tree2+"1";

		tree2=MinTreeRep(tree2);
		if(tree1==tree2)
			puts("same");
		else
			puts("different");
	}
	return 0;
}
