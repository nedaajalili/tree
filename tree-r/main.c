#include <stdio.h>
#include <stdlib.h>
typedef struct node
{
    int key;
    struct node *left;
    struct node *right;
} node_t;
node_t *readF(char *name);
node_t *createnode(int key);
node_t *insert(node_t *root, node_t *tmp);
void show(node_t *root,int mode);
int longestpath(node_t *root,int cnt, int max);
node_t *findmin(node_t *);
int height(node_t *root);
int diameter(node_t *root);
void allpath(node_t *root, int h, node_t **vet, int level);
int nodenum(node_t *root);
int main(int argc,char *argv[])
{
    node_t *root, *minnode, **vet;
    int len,min,h,d,i,n;
    root=readF(argv[1]);

    //show(root,1);
    minnode=findmin(root);
    min=minnode->key;
    printf("min is %d\n",min);
    h=height(root);
    printf("height is %d\n",h);
    d=diameter(root);
    printf("diameter is %d\n",d);
    vet=(node_t **)malloc(h*sizeof(node_t *));
    for(i=0;i<h;i++){
        vet[i]=NULL;
    }
    allpath(root,h,vet,0);
    n=nodenum(root);
    printf("%d nodes\n",n);
    len=longestpath(root,0,0);
    printf("%d",len);
    return 0;
}
node_t *readF(char *name)
{
    node_t *root,*tmp;
    int key;
    FILE *fp;
    root=NULL;
    fp=fopen(name,"r");
    if(fp==NULL)
    {
        printf("error!");
        exit(0);
    }
    while(fscanf(fp,"%d",&key)!=EOF)
    {
        tmp=createnode(key);
        root=insert(root,tmp);
    }
    return root;
}
node_t *createnode(int key)
{
    node_t *tmp;
    tmp=(node_t *)malloc(sizeof(node_t));
    if(tmp==NULL)
    {
        printf("error!");
        exit(0);
    }
    tmp->key=key;
    tmp->left=NULL;
    tmp->right=NULL;
    return tmp;
}
node_t *insert(node_t *root, node_t *tmp)
{
    if(root==NULL)
    {
        return tmp;
    }
    if(root->key>tmp->key)
    {
        root->left=insert(root->left,tmp);
    }
    if(root->key<tmp->key)
    {
        root->right=insert(root->right,tmp);
    }
    return root;
}

void show(node_t *root,int mode)
{
    if(root==NULL)
    {
        return;
    }
    if(mode<0)
    {
        printf("%d\n",root->key);
    }
    show(root->left,mode);
    if(mode==0)
    {
        printf("%d\n",root->key);
    }
    show(root->right,mode);
    if(mode>0)
    {
        printf("%d\n",root->key);
    }
}

node_t *findmin(node_t *root){
    if(root==NULL || root->left==NULL){
        return root;
    }

    return (findmin(root->left));
}
int height(node_t *root){
    int l,r;
    if(root==NULL){
        return 0;
    }
    l=height(root->left);
    r=height(root->right);
    return (1+((l>r)?l:r));
}
int diameter(node_t *root){
    int hl,hr,d,ld,rd,h;
    if(root==NULL){
        return 0;
    }
    hl=height(root->left);
    hr=height(root->right);
    ld=diameter(root->left);
    rd=diameter(root->right);
    h=hl+hr+1;
    d=(ld>rd)?ld:rd;
    return((h>d)?h:d);
}
void allpath(node_t *root, int h, node_t **vet, int level){
    int i;
    if(root==NULL)
        return;
    if(root->left==NULL && root->right==NULL){
        for(i=0;i<h;i++){
            if(vet[i]!=NULL){
                printf("%d-",vet[i]->key);
            }
        }
        printf("%d",root->key);
        printf("\n");
    }
    vet[level]=root;
    allpath(root->left,h,vet,level+1);
    allpath(root->right,h,vet,level+1);
    vet[level]=NULL;
    return;
}
int nodenum(node_t *root){
    int cnt=1;
    if(root->left!=NULL){
        cnt+=nodenum(root->left);
    }
    if(root->right!=NULL){
        cnt+=nodenum(root->right);
    }
    return cnt;
}

int longestpath(node_t *root,int cnt, int max){
    int l,r;
    if(root==NULL || (root->key%2)!=0){
            if(cnt>max){
                max=cnt;
            }
        return cnt;
    }
    l=longestpath(root->left,cnt++,max);
    r=longestpath(root->right,cnt++,max);
    max=((l>r)?l:r);
    return max;
}

