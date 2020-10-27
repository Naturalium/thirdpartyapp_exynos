#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
int rgyro()
{
        char a[15];
        char b[15];
        int i = 0;
        FILE* gy = popen("./drv/readGyrotest.sh", "r");
        fscanf(gy, "%s", a);
        while(a[i] != ',')
                i++;
        i++;
        while(a[i] != ',')
                i++;
        i++;
        sprintf(b, "%s", &a[i]);
        return atoi(b);
}

int main()
{
	pid_t pid;
	
        char var[29] = "./app/plot ";
        char a[29];
        int gyro, egyro;
	int count, status;
        int x, y;
        int ex, ey;
        FILE* p = popen("./drv/readGyrotest.sh", "r");
        char add[15] = "50 6000\n";

        ex = 5;
        ey = 5000;
	status = 0;
	count = 30;
        x = ex;
        y = ey;
	pid = fork();
	if(pid == -1)
	{
		printf("error : no fork\n");
		exit(0);
	}
	if(pid == 0)				/////child start
	{
	// start game
        sprintf(add, "%d %d", x, y);
        sprintf(a, "%s", var);
        strcat(var, add);
        system(var);
        egyro = rgyro();
        while(1)
       	{
                gyro = rgyro();
                if(gyro > egyro + 20)

                {
                        if(y > 0)
                        y = y - 1000;
                }
                else if(gyro < egyro - 20)
                {
                        if(y < 10000)
                        y = y + 1000;
                }
                sprintf(add, "%d %d", x, y);
                sprintf(var, "%s", a);
                strcat(var, add);
                system(var);
		if(x == 95 && y == 9000)
			break;
		else if(x == 95)
			x = 5;
		else
			x = x + 5;
        }
	// end game
	exit(0);
	}			/////// child end
	else			/////// parent process
	{
		sprintf(var, "./drv/fndtest s ");
		
		while(!(waitpid(pid, &status, WNOHANG) || count == 0))
		{
			sprintf(var, "./drv/fndtest s ");
			system("./drv/buzzertest 1\n");
			usleep(500000);
			system("./drv/buzzertest 0\n");
			usleep(500000);
			count--;
			sprintf(add, "%d", count);
			strcat(var, add);
			system(var);
		}
		system("rm ./app/score.txt");
		FILE* score = fopen("./app/score.txt", "w");
		fprintf(score, "%d\n", count);
		pclose(score);
		kill(pid, SIGKILL);
	}
	if(count == 0)
	{
		system("./drv/bitmap ./app/bmp/gameover.bmp\n");
		exit(0);
	}
	else
	{
		system("./drv/bitmap ./app/bmp/gameclear.bmp\n");
		exit(1);
	}
        pclose(p);
	return 0;
}
