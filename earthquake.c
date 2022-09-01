#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#define N 100

/*global variables*/

const int N = 100;

// struct for eqdb data
struct seismic_event
{
    char datestr[9]; // one extra char for the null character at the end
    char timestr[9];
    double latitude;
    double longitude;
    double depth;
    double magnitude;
};
typedef struct seismic_event SeismicEvent;

// function prototype

void load_array(SeismicEvent data[], FILE *infp);
void print_array(SeismicEvent data[]);
double ave_mag();
double ave_depth();

int main(int argc, char *argv[])
{

    // to read from a file, file pointer needed - from stdio.h

    // infp: input file pointer
    FILE *infp;
    SeismicEvent data[N];

    printf("Earthquake Program\n");
    // check for correct CLI arguments

    if (argc != 2)
    {
        printf("Usage: %s file\n", argv[0]);
    }
    else
    {
        // open file
        infp = fopen(argv[1], "r");

        // processing

        load_array(data, infp);
        print_array(data);
        printf("Average Magnitude = %lf\n", ave_mag(data));
        printf("Average Depth = %lf\n", ave_depth(data));

        // close file
        fclose(infp);
    }

    return (0);
}

// load array function

void load_array(SeismicEvent data[], FILE *infp)
{

    // local variables
    char hdrstr[80];
    int ii;
    char d[9];
    char t[9];
    char lat[16];
    char lgtd[16];
    char dpth[16];
    char mag[16];

    // read the header string

    // fgets = file get string
    fgets(hdrstr, 80, infp);
    printf("%s", hdrstr);

    // read the data

    for (ii = 0; ii < N; ii++)
    {
        fscanf(infp, "%s %s %s %s %s %s", d, t, lat, lgtd, dpth, mag);
        // printf(infp, "%s %s %s %s %s", d, t, lat, lgtd, dpth, mag);

        // copy each piece of data into the struct
        strcpy(data[ii].datestr, d);
        strcpy(data[ii].timestr, t);
        data[ii].latitude = atof(lat);
        data[ii].longitude = atof(lgtd);
        data[ii].depth = atof(dpth);
        data[ii].magnitude = atof(mag);
    }
    // return to calling function
    return;
};






























void print_array(SeismicEvent data[])
{
    int ii;
    for (ii = 0; ii < N; ii++)
    {
        printf("%s %s %lf %lf %lf %lf \n", data[ii].datestr, data[ii].timestr, data[ii].latitude, data[ii].longitude, data[ii].depth, data[ii].magnitude);
    }
}

double ave_mag(SeismicEvent data[])
{
    // local variables
    int ii;
    double sum;

    // initialize local variables

    ii = 0;
    sum = 0.0;

    // compute the average

    for (ii = 0; ii < N; ii++)
    {
        sum = sum + data[ii].magnitude;
    }
    return sum / N;
};

double ave_depth(SeismicEvent data[])
{
    // local variables
    int ii;
    double sum;

    // initialize local variables

    ii = 0;
    sum = 0.0;

    // compute the average

    for (ii = 0; ii < N; ii++)
    {
        sum = sum + data[ii].depth;
    }
    return sum / N;
};
