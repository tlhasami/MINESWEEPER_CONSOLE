#include<iostream>
#include<cstdlib>
#include<iomanip>
#include<ctime>
#define MAX 100
using namespace std;

void tracker(char box[MAX][MAX],char screen_show[MAX][MAX],int size,int x,int y){
    if(x<0){
        return ;
    }
    if(y<0){
        return ;
    }
    if(y==size){
        return ;
    }
    if(x==size){
        return ;
    }
    if(screen_show[x][y]==' '){
        return;
    }
    
    if(box[x][y]==' '){
        screen_show[x][y]=' ';
        tracker(box,screen_show,size,x-1,y-1);
        tracker(box,screen_show,size,x-1,y);
        tracker(box,screen_show,size,x-1,y+1);
        tracker(box,screen_show,size,x,y-1);
        tracker(box,screen_show,size,x,y+1);
        tracker(box,screen_show,size,x+1,y-1);
        tracker(box,screen_show,size,x+1,y);
        tracker(box,screen_show,size,x+1,y+1);
    }

    return;
}

bool gameover(char checker[MAX][MAX],char arr[MAX][MAX],int n){
    int x,y;
    cout<<"Enter your x and y index respectively : ";
    cin>>x>>y;
    while(!(x<n && y<n && x>=0 && y>=0) || arr[x][y]!='-'){
        cout<<"---Invalid Entry---"<<endl;
        cout<<"Enter your x and y index respectively : ";
        cin>>x>>y;   
    }
	cout<<"Index selected x: "<<x<<" y: "<<y<<endl;
    if(checker[x][y]=='*'){
        arr[x][y]=checker[x][y];
        return 1;
    }
    else if(checker[x][y]==' '){
        cout<<"tracker activated"<<endl;
        tracker(checker,arr,n,x,y);
    }
    else arr[x][y]=checker[x][y];

    return 0;
}

void bomb_generator(char bomb[MAX][MAX],int n){
    int bombs;
    if(n==8)bombs=8;
    if(n==17)bombs=17;
    if(n==30)bombs=30;
    for(int i=0;i<bombs;i++){
        int bombX=rand()%n;
        int bombY=rand()%n;
        while(bomb[bombX][bombY]=='*'){
            bombX=rand()%n;
            bombY=rand()%n;
        }
        bomb[bombX][bombY]='*';
    }

     for(int i=0;i<n;i++){
         for(int j=0;j<n;j++){
         int count=0;
             if(i>=0 && i<=n &&j>=0 && j<=n && bomb[i][j]!='*' && bomb[i-1][j-1]=='*') count ++;
            if(i>=0 && i<=n &&j>=0 && j<=n && bomb[i][j]!='*'&& bomb[i-1][j]=='*') count ++;
            if(i>=0 && i<=n &&j>=0 && j<=n && bomb[i][j]!='*'&& bomb[i-1][j+1]=='*') count ++;
            if(i>=0 && i<=n &&j>=0 && j<=n && bomb[i][j]!='*'&& bomb[i][j-1]=='*') count ++;
            if(i>=0 && i<=n &&j>=0 && j<=n && bomb[i][j]!='*'&& bomb[i][j+1]=='*') count ++;
            if(i>=0 && i<=n &&j>=0 && j<=n && bomb[i][j]!='*'&& bomb[i+1][j-1]=='*') count ++;
            if(i>=0 && i<=n &&j>=0 && j<=n && bomb[i][j]!='*'&& bomb[i+1][j]=='*') count ++;
            if(i>=0 && i<=n &&j>=0 && j<=n && bomb[i][j]!='*'&& bomb[i+1][j+1]=='*') count ++;
             if(count != 0) bomb[i][j]=count+'0';
         }
     }
    
}

void screen(char arr[MAX][MAX],int n){
    cout<<setw(6)<<" ";
    for(int i=0;i<n;i++)
            cout<<setw(5)<<i<<" ";
	cout<<endl<<endl;
    for(int i=0;i<n;i++){
        cout<<setw(5)<<i
			<<" ";
        for(int j=0;j<n;j++){
            cout<<setw(5)<<arr[i][j]<<" ";
        }
        cout<<"\n\n";
    }
    cout<<endl;
}

int main (){

	srand(time(0));
    int n;
    char lvl;
    cout<<"Enter"<<endl
    <<" (B-> Beginner)"<<endl
    <<" (M-> Medium)"<<endl
    <<" (H-> Hard)"<<endl<<" ";
    cin>>lvl;
    switch(lvl){
        case 'B': n=8; break;
        case 'M': n=17; break;
        case 'H': n=30; break;
    }

    char box[MAX][MAX];
    char show_screen[MAX][MAX];

    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            box[i][j]=' ';
            show_screen[i][j]='-';
        }
    }
    bomb_generator(box,n);
    int safe_turn=0;
    while(1){
    	cout<<endl;
        screen(show_screen,n);
        cout<<endl;
        
        if(gameover(box,show_screen,n)){
            system("cls");
            cout<<"\n";
            screen(box,n);
            cout<<" LOST!";
            break;
        }
        else{
            safe_turn++;
            if(safe_turn==n*n-n){
                cout<<" CONGRATULATIONS !"<<endl;
                break;
            }
        }
        system("cls");
    }
    return 0;
}