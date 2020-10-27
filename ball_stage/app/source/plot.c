#include <stdio.h>
#include <stdlib.h>
#include <math.h>

 

int main(int argc, char **argv){
        if(argc != 3)
        {
                printf("error: need input x y\n");
                return 0;
        }
        int x= 0;
        int y= 0;
        x = atoi(argv[1]);
        y = atoi(argv[2]);

        if(x > 100 || y > 10000)
        {
                printf("error: x < 100 y < 10000\n");
                return 0;
        }
        FILE *pipe = popen("gnuplot", "w");
        printf("success\n");
        FILE *test = fopen("test.txt", "w");
        printf("success\n");
        int pointer = 0;
        fprintf(test, "%d %d\n", x, y);
        fclose(test);
        fprintf(pipe, "set title test\n");
        fprintf(pipe, "set terminal jpeg\n");
        fprintf(pipe, "set output 'test.jpeg'\n");
        fprintf(pipe, "set xrange [0:100]\n");
        fprintf(pipe, "set yrange [0:10000]\n");
        fprintf(pipe, "unset xtics\n");
        fprintf(pipe, "unset ytics\n");
        fprintf(pipe, "set key off\n");
        fprintf(pipe, "plot 'test.txt', './app/bascket.txt' with l\n");

        fprintf(pipe, "exit\n");
        pclose(pipe);
        system("convert -resize 128%x100% -resize 1024x600 test.jpeg test.bmp\n"
);
        system("./drv/bitmap ./test.bmp\n");
	system("rm test.txt\n");
	system("rm test.jpeg\n");
        system("rm test.bmp\n");
	exit(0);
	return 0;
 


}
