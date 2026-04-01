#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h> // used for system calls
#include <string.h>

#include "pbPlots.h"
#include "supportLib.h"

#define STB_DS_IMPLEMENTATION
#include "stb_ds.h"

#include <math.h>

int main() {
    printf("Reading results.csv .\n");

    FILE *fptr;
    fptr = fopen("results.csv", "r");

    char line[4096];

    double upto[6], basic[6], better[6], cached[6];
    double eratosthenes[6], pritchard[6], atkin[6], sundaram[6];

    double basic_empty[6] = {0,0,0,0,0,0};

    double basic_log[6],better_log[6],cached_log[6],eratosthenes_log[6],pritchard_log[6],atkin_log[6],sundaram_log[6];

    int idx = 0;

    while (fgets(line, sizeof(line), fptr) && idx < 6) {
        char *token = strtok(line, ",");
        if (token) upto[idx] = atof(token);

        token = strtok(NULL, ",");
        if (token) basic[idx] = atof(token);

        token = strtok(NULL, ",");
        if (token) better[idx] = atof(token);

        token = strtok(NULL, ",");
        if (token) cached[idx] = atof(token);

        token = strtok(NULL, ",");
        if (token) eratosthenes[idx] = atof(token);

        token = strtok(NULL, ",");
        if (token) pritchard[idx] = atof(token);

        token = strtok(NULL, ",");
        if (token) atkin[idx] = atof(token);

        token = strtok(NULL, ",");
        if (token) sundaram[idx] = atof(token);

        idx++;
    }

    fclose(fptr);


    // test print
    // for (int i = 0; i < idx; i++) {
    //     printf("%f %f %f %f %f %f %f %f\n",
    //         upto[i], basic[i], better[i], cached[i],
    //         eratosthenes[i], pritchard[i], atkin[i], sundaram[i]);
    // }

    // log10
    for (int i = 0; i < 6; i++) {
        int multiply_by = 1;
        basic_log[i] = log10(basic[i]*multiply_by);
        better_log[i] = log10(better[i]*multiply_by);
        cached_log[i] = log10(cached[i]*multiply_by);
        eratosthenes_log[i] = log10(eratosthenes[i]*multiply_by);
        pritchard_log[i] = log10(pritchard[i]*multiply_by);
        atkin_log[i] = log10(atkin[i]*multiply_by);
        sundaram_log[i] = log10(sundaram[i]*multiply_by);
    }

    // img stuff


    _Bool success;

    // scatter settings

    ScatterPlotSettings *settings = GetDefaultScatterPlotSettings();
    settings->width = 1920;
    settings->height = 1080;
    settings->autoBoundaries = true;
    settings->title = L"Prime Number Generation Algorithm Comparison";
	settings->titleLength = wcslen(settings->title);
    settings->xLabel = L"N";
	settings->xLabelLength = wcslen(settings->xLabel);
	settings->yLabel = L"Time in seconds";
	settings->yLabelLength = wcslen(settings->yLabel);

    // -------- series ------- //
    ScatterPlotSeries *series1 = GetDefaultScatterPlotSeriesSettings();
    series1->xs = upto;
    series1->xsLength = 6;
    series1->ys = basic;
    series1->ysLength = 6;
    series1->lineType = L"solid";
    series1->lineThickness = 4;
    series1->color = CreateRGBColor(0.9, 0.5, 0.3); // orange

    // better
    ScatterPlotSeries *series2 = GetDefaultScatterPlotSeriesSettings();
    series2->xs = upto;
    series2->xsLength = 6;
    series2->ys = better;
    series2->ysLength = 6;
    series2->lineType = L"solid";
    series2->color = CreateRGBColor(0.3, 0.9, 0.2); // green

    // cached
    ScatterPlotSeries *series3 = GetDefaultScatterPlotSeriesSettings();
    series3->xs = upto;
    series3->xsLength = 6;
    series3->ys = cached;
    series3->ysLength = 6;
    series3->lineType = L"solid";
    series3->color = CreateRGBColor(0.9, 0.1, 0.1); // red

    // eratosthenes
    ScatterPlotSeries *series4 = GetDefaultScatterPlotSeriesSettings();
    series4->xs = upto;
    series4->xsLength = 6;
    series4->ys = eratosthenes;
    series4->ysLength = 6;
    series4->lineType = L"solid";
    series4->color = CreateRGBColor(0.6, 0.3, 0.8); // purple

    
    // pritchard
    ScatterPlotSeries *series5 = GetDefaultScatterPlotSeriesSettings();
    series5->xs = upto;
    series5->xsLength = 6;
    series5->ys = pritchard;
    series5->ysLength = 6;
    series5->lineType = L"solid";
    series5->color = CreateRGBColor(0.45, 0.3, 0.1); // brown

    // sundaram
    ScatterPlotSeries *series6 = GetDefaultScatterPlotSeriesSettings();
    series6->xs = upto;
    series6->xsLength = 6;
    series6->ys = sundaram;
    series6->ysLength = 6;
    series6->lineType = L"solid";
    series6->color = CreateRGBColor(0.8, 0.2, 1.0); // pink

    // atkin
    ScatterPlotSeries *series7 = GetDefaultScatterPlotSeriesSettings();
    series7->xs = upto;
    series7->xsLength = 6;
    series7->ys = atkin;
    series7->ysLength = 6;
    series7->lineType = L"solid";
    series7->color = CreateRGBColor(0.2, 0.2, 1.0); // blue

    // add all series

    settings->scatterPlotSeries = malloc(sizeof(ScatterPlotSeries*) * 7);
    settings->scatterPlotSeries[0] = series1;
    settings->scatterPlotSeries[1] = series2;
    settings->scatterPlotSeries[2] = series3;
    settings->scatterPlotSeries[3] = series4;
    settings->scatterPlotSeries[4] = series5;
    settings->scatterPlotSeries[5] = series6;
    settings->scatterPlotSeries[6] = series7;
    settings->scatterPlotSeriesLength = 7;

    RGBABitmapImageReference *canvasReference = CreateRGBABitmapImageReference();
    
    StringReference *errorMessage = CreateStringReference(L"", 0);

    success = DrawScatterPlotFromSettings(canvasReference, settings, errorMessage);

    if (success) {
        size_t length;
        ByteArray *pngdata = ConvertToPNG(canvasReference->image);
        WriteToFile(pngdata, "graph_with_basic.png");
        DeleteImage(canvasReference -> image);
    } else {
        fprintf(stderr, "Error: ");
        for(int i = 0; i < errorMessage->stringLength; i++){
			fprintf(stderr, "%c", errorMessage->string[i]);
		}
		fprintf(stderr, "\n");
    }

    // graph with no settings
    ScatterPlotSeries *series1_no = GetDefaultScatterPlotSeriesSettings();
    series1_no->xs = upto;
    series1_no->xsLength = 6;
    series1_no->lineThickness = 1.0;
    series1_no->ys = basic_empty;
    series1_no->ysLength = 6;
    series1_no->lineType = L"solid";
    series1_no->color = CreateRGBColor(0.2, 0.2, 0.2); // gray
    settings->scatterPlotSeries[0] = series1_no;

    RGBABitmapImageReference *canvasReference2 = CreateRGBABitmapImageReference();
    
    StringReference *errorMessage2 = CreateStringReference(L"", 0);

    success = DrawScatterPlotFromSettings(canvasReference, settings, errorMessage);


    if (success) {
        size_t length;
        ByteArray *pngdata = ConvertToPNG(canvasReference->image);
        WriteToFile(pngdata, "graph_without_basic.png");
        DeleteImage(canvasReference -> image);
    } else {
        fprintf(stderr, "Error: ");
        for(int i = 0; i < errorMessage->stringLength; i++){
			fprintf(stderr, "%c", errorMessage->string[i]);
		}
		fprintf(stderr, "\n");
    }

    printf("Generated graphs. I couldn't figure out how to do the log scales work good so its linear unfortunately.\n");

    return 0;
}