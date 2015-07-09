/*

        Create yeartop manually
        01-29-12

 */
#include <stdio.h>
#include <stdlib.h>
#include <glob.h>
#include <time.h>
#include <string.h>
#include "gltool.h"

int main()
{
	FILE *yearscores;

	yearscores = fopen("yearscores.dat", "wb");
	if (!yearscores)
	{
		printf("error at yearscores.dat, exiting\n");
		exit(1);
	}

// 2002

	// year date in time format
	YS.yeartime = 1041379080;

	// clear user name
	bzero(YS.yearup_user, sizeof(YS.yearup_user));
	strcpy(YS.yearup_user, "redzombie");

	// yearup_user_bytes
	YS.yearup_user_bytes = 1079917737984;

	// yearup_group
	bzero(YS.yearup_group, sizeof(YS.yearup_group));
	strcpy(YS.yearup_group, "unknown");

	// yearup_group_bytes
	YS.yearup_group_bytes = 0;

	// yeardn_user
	bzero(YS.yeardn_user, sizeof(YS.yeardn_user));
	strcpy(YS.yeardn_user, "tulsa");

	// yeardn_user_bytes
	YS.yeardn_user_bytes = 433538723840;

	// yeardn_group
	bzero(YS.yeardn_group, sizeof(YS.yeardn_group));
	strcpy(YS.yeardn_group, "unknown");

	// yeardn_group_bytes
	YS.yeardn_group_bytes = 0;

	// yearup_total bytes
	YS.yearup_total = 2744006847488;

	// yeardn_total bytes
	YS.yeardn_total = 2709108433920;

	fwrite(&YS, sizeof(YearScores), 1, yearscores);

// 2003

	// year date in time format
	YS.yeartime = 1072915080;

	// clear user name
	bzero(YS.yearup_user, sizeof(YS.yearup_user));
	strcpy(YS.yearup_user, "");

	// yearup_user_bytes
	YS.yearup_user_bytes = 0;

	// yearup_group
	bzero(YS.yearup_group, sizeof(YS.yearup_group));
	strcpy(YS.yearup_group, "unknown");

	// yearup_group_bytes
	YS.yearup_group_bytes = 0;

	// yeardn_user
	bzero(YS.yeardn_user, sizeof(YS.yeardn_user));
	strcpy(YS.yeardn_user, "");

	// yeardn_user_bytes
	YS.yeardn_user_bytes = 0;

	// yeardn_group
	bzero(YS.yeardn_group, sizeof(YS.yeardn_group));
	strcpy(YS.yeardn_group, "unknown");

	// yeardn_group_bytes
	YS.yeardn_group_bytes = 0;

	// yearup_total bytes
	YS.yearup_total = 0;

	// yeardn_total bytes
	YS.yeardn_total = 0;

	fwrite(&YS, sizeof(YearScores), 1, yearscores);

// 2004

	// year date in time format
	YS.yeartime = 1104537480;

	// clear user name
	bzero(YS.yearup_user, sizeof(YS.yearup_user));
	strcpy(YS.yearup_user, "");

	// yearup_user_bytes
	YS.yearup_user_bytes = 0;

	// yearup_group
	bzero(YS.yearup_group, sizeof(YS.yearup_group));
	strcpy(YS.yearup_group, "unknown");

	// yearup_group_bytes
	YS.yearup_group_bytes = 0;

	// yeardn_user
	bzero(YS.yeardn_user, sizeof(YS.yeardn_user));
	strcpy(YS.yeardn_user, "");

	// yeardn_user_bytes
	YS.yeardn_user_bytes = 0;

	// yeardn_group
	bzero(YS.yeardn_group, sizeof(YS.yeardn_group));
	strcpy(YS.yeardn_group, "unknown");

	// yeardn_group_bytes
	YS.yeardn_group_bytes = 0;

	// yearup_total bytes
	YS.yearup_total = 0;

	// yeardn_total bytes
	YS.yeardn_total = 0;

	fwrite(&YS, sizeof(YearScores), 1, yearscores);

// 2005

	// year date in time format
	YS.yeartime = 1136073480;

	// clear user name
	bzero(YS.yearup_user, sizeof(YS.yearup_user));
	strcpy(YS.yearup_user, "tulsa");

	// yearup_user_bytes
	YS.yearup_user_bytes = 297662653440;

	// yearup_group
	bzero(YS.yearup_group, sizeof(YS.yearup_group));
	strcpy(YS.yearup_group, "unknown");

	// yearup_group_bytes
	YS.yearup_group_bytes = 0;

	// yeardn_user
	bzero(YS.yeardn_user, sizeof(YS.yeardn_user));
	strcpy(YS.yeardn_user, "snakeman");

	// yeardn_user_bytes
	YS.yeardn_user_bytes = 247762547712;

	// yeardn_group
	bzero(YS.yeardn_group, sizeof(YS.yeardn_group));
	strcpy(YS.yeardn_group, "unknown");

	// yeardn_group_bytes
	YS.yeardn_group_bytes = 0;

	// yearup_total bytes
	YS.yearup_total = 699317858304;

	// yeardn_total bytes
	YS.yeardn_total = 603613570048;

	fwrite(&YS, sizeof(YearScores), 1, yearscores);

// 2006

	// year date in time format
	YS.yeartime = 1167609480;

	// clear user name
	bzero(YS.yearup_user, sizeof(YS.yearup_user));
	strcpy(YS.yearup_user, "-");

	// yearup_user_bytes
	YS.yearup_user_bytes = 0;

	// yearup_group
	bzero(YS.yearup_group, sizeof(YS.yearup_group));
	strcpy(YS.yearup_group, "-");

	// yearup_group_bytes
	YS.yearup_group_bytes = 0;

	// yeardn_user
	bzero(YS.yeardn_user, sizeof(YS.yeardn_user));
	strcpy(YS.yeardn_user, "-");

	// yeardn_user_bytes
	YS.yeardn_user_bytes = 0;

	// yeardn_group
	bzero(YS.yeardn_group, sizeof(YS.yeardn_group));
	strcpy(YS.yeardn_group, "-");

	// yeardn_group_bytes
	YS.yeardn_group_bytes = 0;

	// yearup_total bytes
	YS.yearup_total = 0;

	// yeardn_total bytes
	YS.yeardn_total = 0;

	fwrite(&YS, sizeof(YearScores), 1, yearscores);

// 2007

	// year date in time format
	YS.yeartime = 1199145480;

	// clear user name
	bzero(YS.yearup_user, sizeof(YS.yearup_user));
	strcpy(YS.yearup_user, "-");

	// yearup_user_bytes
	YS.yearup_user_bytes = 0;

	// yearup_group
	bzero(YS.yearup_group, sizeof(YS.yearup_group));
	strcpy(YS.yearup_group, "-");

	// yearup_group_bytes
	YS.yearup_group_bytes = 0;

	// yeardn_user
	bzero(YS.yeardn_user, sizeof(YS.yeardn_user));
	strcpy(YS.yeardn_user, "-");

	// yeardn_user_bytes
	YS.yeardn_user_bytes = 0;

	// yeardn_group
	bzero(YS.yeardn_group, sizeof(YS.yeardn_group));
	strcpy(YS.yeardn_group, "-");

	// yeardn_group_bytes
	YS.yeardn_group_bytes = 0;

	// yearup_total bytes
	YS.yearup_total = 0;

	// yeardn_total bytes
	YS.yeardn_total = 0;

	fwrite(&YS, sizeof(YearScores), 1, yearscores);

// 2008

	// year date in time format
	YS.yeartime = 1230767880;

	// clear user name
	bzero(YS.yearup_user, sizeof(YS.yearup_user));
	strcpy(YS.yearup_user, "-");

	// yearup_user_bytes
	YS.yearup_user_bytes = 0;

	// yearup_group
	bzero(YS.yearup_group, sizeof(YS.yearup_group));
	strcpy(YS.yearup_group, "-");

	// yearup_group_bytes
	YS.yearup_group_bytes = 0;

	// yeardn_user
	bzero(YS.yeardn_user, sizeof(YS.yeardn_user));
	strcpy(YS.yeardn_user, "-");

	// yeardn_user_bytes
	YS.yeardn_user_bytes = 0;

	// yeardn_group
	bzero(YS.yeardn_group, sizeof(YS.yeardn_group));
	strcpy(YS.yeardn_group, "-");

	// yeardn_group_bytes
	YS.yeardn_group_bytes = 0;

	// yearup_total bytes
	YS.yearup_total = 0;

	// yeardn_total bytes
	YS.yeardn_total = 0;

	fwrite(&YS, sizeof(YearScores), 1, yearscores);

// 2009

	// year date in time format
	YS.yeartime = 1262303880;

	// clear user name
	bzero(YS.yearup_user, sizeof(YS.yearup_user));
	strcpy(YS.yearup_user, "-");

	// yearup_user_bytes
	YS.yearup_user_bytes = 0;

	// yearup_group
	bzero(YS.yearup_group, sizeof(YS.yearup_group));
	strcpy(YS.yearup_group, "-");

	// yearup_group_bytes
	YS.yearup_group_bytes = 0;

	// yeardn_user
	bzero(YS.yeardn_user, sizeof(YS.yeardn_user));
	strcpy(YS.yeardn_user, "-");

	// yeardn_user_bytes
	YS.yeardn_user_bytes = 0;

	// yeardn_group
	bzero(YS.yeardn_group, sizeof(YS.yeardn_group));
	strcpy(YS.yeardn_group, "-");

	// yeardn_group_bytes
	YS.yeardn_group_bytes = 0;

	// yearup_total bytes
	YS.yearup_total = 0;

	// yeardn_total bytes
	YS.yeardn_total = 0;

	fwrite(&YS, sizeof(YearScores), 1, yearscores);

// 2010

	// year date in time format
	YS.yeartime = 1293839880;

	// clear user name
	bzero(YS.yearup_user, sizeof(YS.yearup_user));
	strcpy(YS.yearup_user, "-");

	// yearup_user_bytes
	YS.yearup_user_bytes = 0;

	// yearup_group
	bzero(YS.yearup_group, sizeof(YS.yearup_group));
	strcpy(YS.yearup_group, "-");

	// yearup_group_bytes
	YS.yearup_group_bytes = 0;

	// yeardn_user
	bzero(YS.yeardn_user, sizeof(YS.yeardn_user));
	strcpy(YS.yeardn_user, "-");

	// yeardn_user_bytes
	YS.yeardn_user_bytes = 0;

	// yeardn_group
	bzero(YS.yeardn_group, sizeof(YS.yeardn_group));
	strcpy(YS.yeardn_group, "-");

	// yeardn_group_bytes
	YS.yeardn_group_bytes = 0;

	// yearup_total bytes
	YS.yearup_total = 0;

	// yeardn_total bytes
	YS.yeardn_total = 0;

	fwrite(&YS, sizeof(YearScores), 1, yearscores);

// 2011

	// year date in time format
	YS.yeartime = 1325375880;

	// clear user name
	bzero(YS.yearup_user, sizeof(YS.yearup_user));
	strcpy(YS.yearup_user, "snakeman");

	// yearup_user_bytes
	YS.yearup_user_bytes = 672505177088;

	// yearup_group
	bzero(YS.yearup_group, sizeof(YS.yearup_group));
	strcpy(YS.yearup_group, "-");

	// yearup_group_bytes
	YS.yearup_group_bytes = 0;

	// yeardn_user
	bzero(YS.yeardn_user, sizeof(YS.yeardn_user));
	strcpy(YS.yeardn_user, "snakeman");

	// yeardn_user_bytes
	YS.yeardn_user_bytes = 352172175360;

	// yeardn_group
	bzero(YS.yeardn_group, sizeof(YS.yeardn_group));
	strcpy(YS.yeardn_group, "-");

	// yeardn_group_bytes
	YS.yeardn_group_bytes = 0;

	// yearup_total bytes
	YS.yearup_total = 1576945999872;

	// yeardn_total bytes
	YS.yeardn_total = 726558661632;

	fwrite(&YS, sizeof(YearScores), 1, yearscores);

	fclose(yearscores);

	return 0;
}