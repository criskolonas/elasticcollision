#include <graphics.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

#define radiusX 25
#define radiusY 25
//Struct that contains the attributes of the ball.
struct ball
{
    int x;
    int y;
    int c;
    int m;
    int r;
    int sx;
    int sy;
};
//Opens "input.txt" and reads the first line
int ballcount()
{
   FILE *fp;
    int n;
    fp=fopen("input.txt","r");
    if(fp==NULL)
    {
        puts("Can't open file");
        exit(2);
    }
    fscanf(fp,"%d",&n);
    fclose(fp);
    return n;
}
//Creates space for the array of structs
void allocateSpace(struct ball **balls,int n)
{

    *balls =(struct ball *) malloc(n*sizeof(struct ball));
    if(balls==NULL)
    {
        printf("Allocation failed \n");
        exit(1);
    }
    return;
}

/*Opens "input.txt" reads the first line and then
puts the values in each member of the struct of the array.
Informs if stats are out of bounds*/
void ballstats(struct ball *balls)
{

    int n,i;
    FILE *fp;
    fp=fopen("input.txt","r");
    if(fp==NULL)
    {
        puts("Can't open file");
        exit(2);
    }
    fscanf(fp,"%d",&n);
    printf("The balls are %d \n",n);
    for(i=0;i<n;i++)
    {
        fscanf(fp,"%d",&balls[i].x);
        if(balls[i].x < 0 || balls[i].x > 600 )
        {
            printf("%d ball x pos off limits",i+1);
            exit -1;
        }
        fscanf(fp,"%d",&balls[i].y);
        if(balls[i].y < 0 || balls[i].y > 400 )
        {
            printf("%d ball y pos off limits",i+1);
            exit -1;
        }
        fscanf(fp,"%d",&balls[i].c);
        if(balls[i].c < 0 || balls[i].c > 15 )
        {
            printf("%d ball color off limits");
            exit -1;
        }
        fscanf(fp,"%d",&balls[i].m);
        if(balls[i].m < 0 || balls[i].m > 100000 )
        {
            printf("%d ball mass off limits",i+1);
            exit -1;
        }
        fscanf(fp,"%d",&balls[i].r);
        if(balls[i].r < 1 || balls[i].r > 100 )
        {
            printf("%d ball x pos off limits",i+1);
            exit -1;
        }
        fscanf(fp,"%d",&balls[i].sx);
        if(balls[i].sx < -100 || balls[i].sx > 100 )
        {
            printf("%d ball x speed off limits",i+1);
            exit -1;
        }
        fscanf(fp,"%d",&balls[i].sy);
        if(balls[i].sy < -100 || balls[i].sy > 100 )
        {
            printf("%d ball y speed off limits",i+1);
            exit -1;
        }
        printf("%d %d %d %d %d %d %d \n",balls[i].x,balls[i].y,balls[i].c,balls[i].m,balls[i].r,balls[i].sx,balls[i].sy);
    }
    fclose(fp);
    return;
}



int main()
{
    clock_t start,finish, previous;
    double step;

    struct ball *balls;

    /* counters*/
    int i,j,ballnum;


    /* request autodetection */
    int gdriver = DETECT, gmode, errorcode;
    /* initialize graphics and local variables */
    initgraph(&gdriver, &gmode, "");
    /* read result of initialization */
    errorcode = graphresult();
    if (errorcode != grOk) {  /* an error occurred */
      printf("Graphics error: %s\n", grapherrormsg(errorcode));
      system ("pause");
      exit(1);               /* terminate with an error code */
    }

    ballnum=ballcount();
    allocateSpace(&balls,ballnum);
    ballstats(balls);

    start=clock();
    previous=start;

    do
    {
        finish = clock();
        step = (finish-previous)*1.0/CLOCKS_PER_SEC;

        if (step >= 0.03)
        {
            previous = finish;


            for(i=0;i<ballnum;i++)
            {
                setcolor(BLACK);
                setfillstyle(SOLID_FILL,BLACK);
                fillellipse(balls[i].x,balls[i].y,balls[i].r,balls[i].r);

                balls[i].x+= balls[i].sx*step;
                balls[i].y+= balls[i].sy*step;

                if (balls[i].x+balls[i].r>=getmaxx() ||  balls[i].x-balls[i].r<=0)
                {
                    balls[i].sx *= -1;
                }
                if (balls[i].y+balls[i].r>=getmaxy() ||  balls[i].y-balls[i].r<=0)
                {
                    balls[i].sy *= -1;
                }


                setcolor(balls[i].c);
                setfillstyle(SOLID_FILL,balls[i].c);
                fillellipse(balls[i].x,balls[i].y,balls[i].r,balls[i].r);
            }
                printf("%d   %d\n",balls[0].x,balls[1].x);
                  if (sqrt(pow(balls[1].y - balls[0].y,2)+pow(balls[1].x - balls[0].x,2))<pow(balls[0].r+balls[1].r,2))
                {
                    //balls[0].sx = ((2*balls[0].m/(balls[0].m +balls[1].m)*balls[0].sx) + ((balls[1].m - balls[0].m)/(balls[0].m + balls[1].m)*balls[1].sx));
                    //balls[1].sx = ((2*balls[1].m/(balls[1].m +balls[0].m)*balls[1].sx) + ((balls[0].m - balls[1].m)/(balls[1].m + balls[0].m)*balls[0].sx));
                    //balls[0].sy = ((2*balls[0].m/(balls[0].m +balls[1].m)*balls[0].sy) + ((balls[1].m - balls[0].m)/(balls[0].m + balls[1].m)*balls[1].sy));
                    //balls[1].sy = ((2*balls[1].m/(balls[1].m +balls[0].m)*balls[1].sy) + ((balls[0].m - balls[1].m)/(balls[1].m + balls[0].m)*balls[0].sy));

                }


        }
    }
    while (!kbhit());
    closegraph();
    printf("%d %d %d %d",balls[0].sx,balls[0].sy,balls[1].sx,balls[1].sy);

    free(balls); //frees allocated memory
    return 0;

}
