#include<stdio.h>
#include<stdlib.h>

#define RED 1
#define BLACK -1

#define RED_RULE 1
#define BLACK_RULE 0


int cusor_y =1;
int cusor_x = 1;

enum
{
    WIN,
    EQUEAL,
    CONTINUE
};

int rule=0;

void set_cusor( int x, int y )
{
    printf("\033[%d;%dH",y,x);
}

void init_five_chess( int (* parr)[20][20])
{
    int i,j;
    for(i=1;i<21;i++)
    {
        for(j=1;j<21;j++)
        {
            (*parr)[i][j]=0;
            set_cusor(i,j);
            printf("\033[47;47m \033[0m");
            
        }
    }
     set_cusor(1,1);
}

void print_five_chess(int (*parr)[20][20] )
{
    //system("clear");
    int i,j;
    for(i=1;i<21;i++)
    {
        for(j=1;j<21;j++)
        {
            if( (*parr)[i][j]==0 )
            {
                set_cusor(i,j);
                printf("\033[47;47m \033[0m");
            }
               // printf("\033[47m\033[%d;%dH \033[0m",j+1,i+1);
                //printf("\033[47m\033[%d;%dH \033[0m",j+1,i+1);
                
                //printf("\033[%d")
            else if( (*parr)[i][j]==-1 )
            {
                set_cusor(i,j);
                printf("\033[30;47m#\033[0m");
            }
               
                //printf("\033[47m\033[30m\033[%d;%dH#\033[0m",j+1,i+1);
            else if( (*parr)[i][j]==1 )
            {
                set_cusor(i,j);
                printf("\033[31;47m@\033[0m");
            }
                
                //printf("\033[47m\033[31m\033[%d;%dH@\033[0m",j+1,i+1);
                
        }
    }
    //set_cusor(1,1);
    

}

// 
int judge_win( int (*parr)[20][20] )
{
    
    //横向
    int i = 1,j = 1;
    int m = 0, sum = 0;
    for (j =1; j<21; j++)
    {   for( i=1; i<17; i++)
        {
            sum = 0;
            for (m = 0; m<5; m++)
            {
                sum += (*parr)[j][i+m];
            }
            if (sum==-5||sum==5)
             {
                printf("111");
                return WIN;
            }
        }
        
    }
    
    //纵向
    //sum = 0;
    for (j =1; j<21; j++)
    {   for( i=1; i<17; i++)
        {   sum = 0;
            for (m = 0; m<5; m++)
            {
                sum += (*parr)[i+m][j];
            }
            if (sum==-5||sum==5)
            {
                printf("2222");
                return WIN;
            }
        }
        
    }
    //左上到右下
    //sum = 0;
    for (j =1; j<17; j++)
    {   for( i=1; i<17; i++)
        {
            sum = 0;
            for (m = 0; m<5; m++)
            {
                sum += (*parr)[i+m][j+m];
            }
            if (sum==-5||sum==5)
            {
                printf("3333");
                return WIN;
            }
        }
        
    }
    //sum = 0;
    for (j =5; j<21; j++)
    {   for( i=5; i<21; i++)
        {
            sum = 0;
            for (m = 0; m<5; m++)
            {
                sum += (*parr)[i-m][j-m];
            }
            if (sum==-5||sum==5)
            {
                printf("4444");
              return WIN;
            }
        }
        
    }

    return CONTINUE;
}

void action_five_chess( int (*parr)[20][20] )
{
    //int cusor_x=0,cusor_y=0;
    char ch;
    int result;
    while('q' != (ch=getchar() ) )
    {
        if( ch=='a' )
        {   
            if( cusor_x>1 )
            {
                cusor_x--;
                printf("\033[1D");
            }
            
        }
        if( ch=='d')
        {
            if( cusor_x<20 )
            {
                cusor_x++;
               printf("\033[1C");
            }
             
        }
         if( ch=='w')
        {
            if( cusor_y>1 )
            {
                cusor_y--;
                printf("\033[1A");
            }
            
        }
        if( ch=='s')
        {
            if( cusor_y<20 )
            {
                cusor_y++;
                printf("\033[1B");
            }
            
        }
        if( ch==' ' )//表示有落子动作
        {
            if( (*parr)[cusor_x][cusor_y] )
                continue;
            if( rule == RED_RULE )
            {
                (*parr)[cusor_x][cusor_y]=RED;
                printf("\033[30;47m#\033[0m");
            }
            else
            {
                (*parr)[cusor_x][cusor_y]=BLACK;
                printf("\033[30;47m@\033[0m");
            }
            //print_five_chess(parr);//打印棋盘
           // xcusor=cusor_x;
            //ycusor=cusor_y;
            set_cusor( cusor_x,cusor_y );
            
            result = judge_win(parr);
            if( result == WIN )
            {
                printf("%s\n",rule?"红方胜出":"白方胜出");
                break;
            }
            else if( result == EQUEAL )
            {
                printf("平局\n");
            }
            rule =!rule;
        }
    }
}

int main(void)
{
    int arr[20][20] ={0};
    system("stty -echo"); 
    system("stty raw"); 
    system("clear");
   
    init_five_chess( &arr );
    //print_five_chess( &arr );
    //printf("\033[0:0H");
    
    action_five_chess( &arr );
    //printf("\033[30;47m@@@@@\033[0m");


    system("stty cooked");
    system("stty echo");
    return 0;
}
