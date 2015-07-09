#include <stdio.h>
#include <stdlib.h>
#include <glob.h>
#include <time.h>
#include "gltool.h"

int main()
{
	FILE *highscores;
	FILE *wbase;
	FILE *mbase;
	FILE *ybase;

/*

        All time High Scores

 */
	highscores = fopen("highscores.dat", "rb");
	if (!highscores)
	{
		printf("error at highscores.dat, exiting\n");
		exit(1);
	}

	fread(&HS, sizeof(Scores), 1, highscores);
	fclose(highscores);

	printf("Highscore records:\nwkup user: %s\nwkup bytes: %llu\nwkup group: %s\nwkup group bytes: %llu\nwkdn user: %s\nwkdn bytes: %llu\nwkdn group: %s\n\
wkdn group bytes: %llu\nmup user: %s\nmup bytes: %llu\nmup group: %s\nmup group bytes: %llu\nmdn user: %s\nmdn bytes: %llu\nmdn group: %s\n\
mdn group bytes: %llu\nsite wkup: %llu\nsite wkdn: %llu\nsite mup: %llu\nsite mdn: %llu\nsite yeartop up: %llu\nsite yeartop dn: %llu\n\
yearup user: %s - %llu\nyeardn user: %s - %llu\n", HS.hwkup_user, HS.hwkup_bytes, HS.hwkup_group, HS.hwkup_group_bytes,
	       HS.hwkdn_user, HS.hwkdn_bytes, HS.hwkdn_group, HS.hwkdn_group_bytes,
	       HS.hmup_user, HS.hmup_bytes, HS.hmup_group, HS.hmup_group_bytes, HS.hmdn_user, HS.hmdn_bytes,
	       HS.hmdn_group, HS.hmdn_group_bytes, HS.site_wkup, HS.site_wkdn, HS.site_mup, HS.site_mdn,
	       HS.site_yeartop_up, HS.site_yeartop_dn, HS.hyearup_user, HS.hyearup_user_bytes,
	       HS.hyeardn_user, HS.hyeardn_user_bytes);

	printf("LAMMAS! : %s\n", Time_Check(HS.hwkup_user_date));

/*

        Weektop Scores

 */
	printf("**************************************\n\t\tWEEKTOP RECORDS\n**********************************\n");

	wbase = fopen("weekscores.dat", "rb");
	if (!wbase)
	{
		printf("error at weekscores.dat, exiting\n");
		exit(1);
	}

	fread(&WS, sizeof(WeekScores), 1, wbase);

	while (!feof(wbase))
	{
		printf("\nWeekScore records for %s:\nwkup user: %s\nwkup bytes: %llu\nwkdn user: %s\nwkdn bytes: %llu\nwkup group: %s\nwkup group bytes: %llu\nwkdn group: %s\n\
wkdn group bytes: %llu\nwkup total: %llu\nwkdn total: %llu\n",
		       Time_Check(WS.weektime), WS.wkup_user, WS.wkup_user_bytes,
		       WS.wkdn_user, WS.wkdn_user_bytes, WS.wkup_group, WS.wkup_group_bytes,
		       WS.wkdn_group, WS.wkdn_group_bytes, WS.weekup_total, WS.weekdn_total);

		fread(&WS, sizeof(WeekScores), 1, wbase);
	}

	fclose(wbase);

/*

        Monthtop Scores

 */
	printf("**************************************\n\t\tMONTHTOP RECORDS\n**********************************\n");

	mbase = fopen("monthscores.dat", "rb");
	if (!mbase)
	{
		printf("error at monthscores.dat, exiting\n");
		exit(1);
	}

	fread(&MS, sizeof(MonthScores), 1, mbase);

	while (!feof(mbase))
	{
		printf("\nMonthScore records for %s:\nmup user: %s\nmup bytes: %llu\nmdn user: %s\nmdn bytes: %llu\nmup group: %s\nmup group bytes: %llu\nmdn group: %s\nmdn group bytes: %llu\n\
mup total: %llu\nmdn total: %llu\n",
		       Time_Check(MS.monthtime), MS.mup_user, MS.mup_user_bytes,
		       MS.mdn_user, MS.mdn_user_bytes, MS.mup_group, MS.mup_group_bytes,
		       MS.mdn_group, MS.mdn_group_bytes, MS.mup_total, MS.mdn_total);

		fread(&MS, sizeof(MonthScores), 1, mbase);
	}

	fclose(mbase);

/*

        Yeartop Scores

 */
	printf("**************************************\n\t\tYEARTOP RECORDS\n**********************************\n");

	ybase = fopen("yearscores.dat", "rb");
	if (!ybase)
	{
		printf("error at yearscores.dat, exiting\n");
		exit(1);
	}

	fread(&YS, sizeof(YearScores), 1, ybase);

	while (!feof(ybase))
	{
		printf("\nYearScore records for %s:\nyup user: %s\nyup bytes: %llu\nydn user: %s\nydn bytes: %llu\nyup group: %s\nyup group bytes: %llu\nydn group: %s\nydn group bytes: %llu\n\
yup total: %llu\nydn total: %llu\n",
		       Time_Check(YS.yeartime), YS.yearup_user, YS.yearup_user_bytes,
		       YS.yeardn_user, YS.yeardn_user_bytes, YS.yearup_group, YS.yearup_group_bytes,
		       YS.yeardn_group, YS.yeardn_group_bytes, YS.yearup_total, YS.yeardn_total);

		fread(&YS, sizeof(YearScores), 1, ybase);
	}

	return 0;
}