#include <iostream>
#include <algorithm>
#include<cstdio>
using namespace std;

struct Cpost{
    int L,R;
};
Cpost posters[10100];  //存储海报
int x[20200];  //存储端点编号
int Hash[10000010];  //存储离散后的端点的编号,端点的大小为1QW，所以要大。

struct CNode{
    int L,R;
    bool BCovered;  //True表示被完全覆盖
    CNode *pLeft,*pRight;
};

CNode Tree[1000000];
int nNodeCount=0;

int  Mid(CNode *pRoot){
   return (pRoot->L+pRoot->R)/2;
}

void Create(CNode *pRoot,int L,int R){
       pRoot->L=L;
       pRoot->R=R;
       pRoot->BCovered=false;
       if(L==R)  return;
           nNodeCount++;
         pRoot->pLeft=Tree+nNodeCount;
           nNodeCount++;
         pRoot->pRight=Tree+nNodeCount;
         Create(pRoot->pLeft,L,Mid(pRoot));
         Create(pRoot->pRight,Mid(pRoot)+1,R);
}

bool Query(CNode* pRoot,int L,int R){  //返回true表示可见
     if(pRoot->BCovered) return false; //已被完全覆盖
      
     //没有被完全覆盖
     if(pRoot->R==R && pRoot->L==L){
          pRoot->BCovered=true;
            return true;
     }

       bool bResult;
        if(L>=Mid(pRoot)+1){
           bResult=Query(pRoot->pRight,L,R);
        }
        else if(R<=Mid(pRoot)){
           bResult=Query(pRoot->pLeft,L,R);
        }
        else{
           bool b1=Query(pRoot->pLeft,L,Mid(pRoot)); 
           bool b2=Query(pRoot->pRight,Mid(pRoot)+1,R);
           bResult=b1||b2;
        }
      
        //需要更新根节点的覆盖情况
    if(pRoot->pLeft->BCovered && pRoot->pRight->BCovered)
        pRoot->BCovered=true;
     return bResult;
}

int main(){
    int c,n;
    scanf("%d",&c);
    while(c--){
       int nCount=0;
       scanf("%d",&n);
       for(int i=0;i<n;i++){
           scanf("%d%d",&posters[i].L,&posters[i].R);
           x[nCount++]=posters[i].L;
           x[nCount++]=posters[i].R;
       }
     sort(x,x+nCount);
     nCount=unique(x,x+nCount)-x;//unique返回的是去除重复后的，不重复那部分的最后一个位置
     //离散化
     int nInterval=0;
     for(int j=0;j<nCount;j++){
         //Hash[x[j]]=nInterval;
         /*if( i < nCount -1) {
             if( x[i+1] -x[i] == 1)
                 nInterval++;
             else
                 nInterval+=2;
         }*/
          Hash[x[j]]=nInterval;
          nInterval++;
     }
     Create(Tree,0,nInterval); //从零开始
     int Sum=0;
     for(int k=n-1;k>=0;k--){  //从最外面的开始
         if(Query(Tree,Hash[posters[k].L],Hash[posters[k].R]))
             Sum++;
     }
      printf("%d\n",Sum);
    }
    return 0;
}
