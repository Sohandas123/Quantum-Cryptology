#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double Pr_win(double, double, double, double); // to calculate  Pr(win) = Pr_win(theta1, theta2, Phi1, Phi2)

#define PI 3.14159

int main()
{
    double dtr = PI / 180;                             // dtr = degree to radian conversion constant
    double theta1, theta2, phi1, phi2, inc = 0.05, pr; // inc stands for increment in each step.  2*theta increaments 0.1, so theta should increaments 0.05.

    FILE *fp = fopen("winning_probability.txt", "w");
    if (fp == NULL)
    {
        printf("Error!");
        exit(1);
    }
    fprintf(fp, "\n Sl       Theta1       Theta2       Phi1       Phi2             Pr(win)");
    fprintf(fp, "\n-------------------------------------------------------------------------");
    long long int count = 0, iter = 0;
    double t = 0.0, q = 0.0, r = 0.0,s = 0.0 ;

    /* here we are varying theta & phi from [0, PI/4], but actually we took 2*theta & 2*phi initially for simplicity in calcualation
     so in actual setup  2*theta and 2*phi are varying from [0, PI/2] */

    theta1 = t;
    while (theta1 <= (45 * dtr)) // thetas and phis are in [0 , PI/4]
    {
        for (theta2 = q; theta2 <= (45 * dtr); theta2 += inc)
        {
            for (phi1 = r; phi1 <= (45 * dtr); phi1 += inc) // phis are in [-PI/4 , PI/4]
            {
                for (phi2 = s; phi2 <= (45 * dtr); phi2 += inc)
                {
                    iter++;
                    pr = Pr_win(theta1, theta2, phi1, phi2); // returns (1/4)*[cos^2(theta1-phi1) + cos^2(theta1-phi2) + cos^2(theta2-phi1) + sin^2(theta2-phi2)]
                    if(pr > 0.75){
                        count++;
                        fprintf(fp, "\n %lld.     %.2lf    %.2lf    %.2lf    %.2lf    -    %.10lf   <----* winning probablity is more than  0.75", iter, 2 * theta1, 2 * theta2, 2 * phi1, 2 * phi2, pr);
                        continue;
                    }
                    fprintf(fp, "\n %lld.     %.2lf    %.2lf    %.2lf    %.2lf    -    %.10lf", iter, 2 * theta1, 2 * theta2, 2 * phi1, 2 * phi2, pr);               
                }
                s = 0;
                fprintf(fp, "\n -----------------------------------------------------------------------------------------------------");
            }
            r = 0;
        }
        q = 0;
     theta1 += inc;
    }
    fclose(fp);
    printf("\n For  %lld  many cases we are winnig probability greater than  0.75", count);
    return 0;
}

// returns (1/4)*[cos^2(theta1-phi1) + cos^2(theta1-phi2) + cos^2(theta2-phi1) + sin^2(theta2-phi2)]

double Pr_win(double x, double y, double z, double t) // to calculate Pr(win) = Pr_win(theta1, theta2, Phi1, Phi2)
{
    double r = 0.25 * (cos(x - z) * cos(x - z) + cos(x - t) * cos(x - t) + cos(y - z) * cos(y - z) + sin(y - t) * sin(y - t));
    return r; 
}
