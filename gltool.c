/*

        Glftpd Tool, ie Glftpd Tool.

        last edits 01-18-12, fixed the new users file format for glftpd v2.01 upgrade

 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <glob.h>
#include "gltool.h"
#include <pmc.h>
// why was this included?
//#include <pmcparse.h>
#include "../example/sorter.h"

#define DEBUG

struct int_list *sorted;
unsigned long long tmptop[MAXUSERS];

//Database db;
//group gp;

// memory allocation for our global ugly arrays :)
Database *db[100];
group *gp[20];

db[0] = (Database *)malloc(sizeof(Database));
gp[0] = (group *)malloc(sizeof(group));

/*

        footer to display under the top's

 */
int Footer()
{
	sprintf(verss, ".----------------------------------------------------------------.\n"
	        "|    glftpd tool v0.3b 01-18-12 (c) snake man, pmc 2001-2015.    |\n"
	        "`----------------------------------------------------------------'");

	return 0;
}

/*

        Open user files

 */
int File_Select()
{
	char *utemp[10];
	char temp_gl[80];
	int ui = 0;
	i = 0;
#ifdef DEBUG
	printf("At file_select()\n");
#endif

	for (x = 0; x < gl.gl_pathc; x++)
	{
		bzero(temp_gl, sizeof(temp_gl));
		sprintf(temp_gl, "%s", gl.gl_pathv[x]);
#ifdef DEBUG
		printf("sucka dir: %s\n", temp_gl);
#endif
		ui = splitpath(utemp, temp_gl);
		sprintf(U_File, "%s", utemp[ui]);
		userfile = fopen(gl.gl_pathv[x], "rt");
		if (!userfile)
		{
			printf("Could not open userfile(s), exiting!\n");
			exit(1);
		}

		Info_Gather();
		fclose(userfile);
	}

	maxuser = i;

	return 0;
}

/*

        Read data from user files into array

 */
int Info_Gather()
{
	char ustmp[80], len[80], glen[25];
	char *p;
	unsigned long long tmp;
	long fls;

	if (strstr(gl.gl_pathv[x], "default.user"))
		return 0;
	if (strstr(gl.gl_pathv[x], "!!ERR!!"))
		return 0;

#ifdef DEBUG
	printf("at Info_Gather() loopers... booper, hih\n");
#endif

	i++;
	sprintf(db[i].username, "%s", U_File); /* username */
#ifdef DEBUG
	printf("db[%i].username: %s\n", i, db[i].username);
#endif
	/* skips ... */
	fgets(ustmp, 80, userfile); /* user added       */
	fgets(ustmp, 80, userfile); /* general	*/
	fgets(ustmp, 80, userfile); /* logins         */
	fgets(ustmp, 80, userfile); /* timeframe	*/
	fgets(ustmp, 80, userfile); /* flags		*/

	bzero(ustmp, sizeof(ustmp));
	fgets(ustmp, 80, userfile); /* tagline  */
	p = strtok(ustmp, " ");
	p = strtok(NULL, " ");
	bzero(len, sizeof(len));
	while (p)
	{
		strcat(len, p);
		strcat(len, " ");
		p = strtok(NULL, " ");
	}
	if (strlen(len) > 25)
		len[25] = '\0';
	strncpy(db[i].location, len, strlen(len) - 2);
#ifdef debug
	printf("db[%i].location: %s\n", i, db[i].location);
#endif
	fgets(ustmp, 80, userfile); /* dir		*/
	fgets(ustmp, 80, userfile); /* ADDED 0	*/
	fgets(ustmp, 80, userfile); /* EXPIRES 0	*/
	fgets(ustmp, 80, userfile); /* credits  */
	fgets(ustmp, 80, userfile); /* ratio	        */

	bzero(ustmp, sizeof(ustmp));
	fgets(ustmp, 80, userfile); /* alup	        */
#ifdef DEBUG
	printf("ustmp: %s", ustmp);
#endif
	p = strtok(ustmp, " ");
	p = strtok(NULL, " ");
	fls = 0;
	sscanf(p, "%lu", &fls);
	db[i].ul_files = fls;
	p = strtok(NULL, " ");
	tmp = 0;
	sscanf(p, "%llu", &tmp);
	db[i].ul_bytes = (tmp * 1024);

	bzero(ustmp, sizeof(ustmp));
	fgets(ustmp, 80, userfile); /* aldn	        */

	p = strtok(ustmp, " ");
	p = strtok(NULL, " ");
	fls = 0;
	sscanf(p, "%lu", &fls);
	db[i].dl_files = fls;
	p = strtok(NULL, " ");
	tmp = 0;
	sscanf(p, "%llu", &tmp);
	db[i].dl_bytes = (tmp * 1024);

	bzero(ustmp, sizeof(ustmp));
	fgets(ustmp, 80, userfile); /* wkup	        */

	p = strtok(ustmp, " ");
	p = strtok(NULL, " ");
	fls = 0;
	sscanf(p, "%lu", &fls);
	db[i].wkup_files = fls;
	p = strtok(NULL, " ");
	tmp = 0;
	sscanf(p, "%llu", &tmp);
	db[i].wkup_bytes = (tmp * 1024);

	bzero(ustmp, sizeof(ustmp));
	fgets(ustmp, 80, userfile); /* wkdn	        */

	p = strtok(ustmp, " ");
	p = strtok(NULL, " ");
	fls = 0;
	sscanf(p, "%lu", &fls);
	db[i].wkdn_files = fls;
	p = strtok(NULL, " ");
	tmp = 0;
	sscanf(p, "%llu", &tmp);
	db[i].wkdn_bytes = (tmp * 1024);

	fgets(ustmp, 80, userfile); /* dayup		*/
	fgets(ustmp, 80, userfile); /* daydn	        */

	bzero(ustmp, sizeof(ustmp));
	fgets(ustmp, 80, userfile); /* mup	        */

	p = strtok(ustmp, " ");
	p = strtok(NULL, " ");
	fls = 0;
	sscanf(p, "%lu", &fls);
	db[i].mup_files = fls;
	p = strtok(NULL, " ");
	tmp = 0;
	sscanf(p, "%llu", &tmp);
	db[i].mup_bytes = (tmp * 1024);

	bzero(ustmp, sizeof(ustmp));
	fgets(ustmp, 80, userfile); /* mdn	        */

	p = strtok(ustmp, " ");
	p = strtok(NULL, " ");
	fls = 0;
	sscanf(p, "%lu", &fls);
	db[i].mdn_files = fls;
	p = strtok(NULL, " ");
	tmp = 0;
	sscanf(p, "%llu", &tmp);
	db[i].mdn_bytes = (tmp * 1024);

	fgets(ustmp, 80, userfile); /* nuke		*/
	fgets(ustmp, 80, userfile); /* time	        */
//glftpd v2.01 doesn't have this anymore...
//    fgets(ustmp,80,userfile); /* slots	        */

	bzero(ustmp, sizeof(ustmp));
	fgets(ustmp, 80, userfile); /* group	        */
	p = strtok(ustmp, " ");
	p = strtok(NULL, " ");
	bzero(glen, sizeof(glen));
	sprintf(glen, "%s", p);
	// apparently this cut off last character of group names :)
	//strncpy(db[i].group, glen, strlen(glen) - 1);
	strcpy(db[i].group, glen);

#ifdef DEBUG
	printf("%s group is: %s\n\n", db[i].username, db[i].group);
#endif

	return 0;
}

/*

        Create top text files

 */
int Totals_Create(char *whus)
{
	FILE *total;

	char buf2[300];
	int dog = 0, unum = 0;

	unsigned long long weektop = 0;
	unsigned long long weektopdn = 0;
	unsigned long long mdn = 0;
	unsigned long long mup = 0;

	if (strcmp(whus, "alup") == 0)
	{
		printf("Lets do alup ...");

		total = fopen("total_alup.txt", "wt");
		if (!total)
		{
			printf("error at total_alup.txt, exiting\n");
			exit(1);
		}

		for (i = 0; i < maxuser; i++) tmptop[i] = db[i].ul_bytes;

		sorted = sort_top(tmptop);
		dog = 0;

		while (sorted)
		{
			dog++;

			bzero(buf2, sizeof(buf2));
			sprintf(buf2, "%llu", db[sorted->num].ul_bytes);
			fprintf(total, " %3d  %-10s %-26s %20s\n", dog, db[sorted->num].username,
			        db[sorted->num].location, f_format(buf2));
			sorted = sorted->next;
			if (dog == alup_unum)
				break;
		}

		bzero(buf2, sizeof(buf2));
		sprintf(buf2, "%llu", All_UL_Bytes);
		fprintf(total, "site alltime uploads: %s bytes\n", f_format(buf2));
		fprintf(total, "%s\n", verss);

		printf("Done!\n");
		fclose(total);
	}

	if (strcmp(whus, "aldn") == 0)
	{
		printf("Lets do aldn ...");

		total = fopen("total_aldn.txt", "wt");
		if (!total)
		{
			printf("error at total_aldn.txt, exiting\n");
			exit(1);
		}

		for (i = 0; i < maxuser; i++) tmptop[i] = db[i].dl_bytes;

		sorted = sort_top(tmptop);
		dog = 0;

		while (sorted)
		{
			dog++;

			bzero(buf2, sizeof(buf2));
			sprintf(buf2, "%llu", db[sorted->num].dl_bytes);
			fprintf(total, " %3d  %-10s %-26s %20s\n", dog, db[sorted->num].username,
			        db[sorted->num].location, f_format(buf2));
			sorted = sorted->next;
			if (dog == aldn_unum)
				break;
		}

		bzero(buf2, sizeof(buf2));
		sprintf(buf2, "%llu", All_DL_Bytes);
		fprintf(total, "site alltime downloads: %s bytes\n", f_format(buf2));
		fprintf(total, "%s\n", verss);

		printf("Done!\n");
		fclose(total);
	}

	if (strcmp(whus, "wkup") == 0)
	{
		unsigned long long wkup_total = 0;
		unsigned long long wkup_uscore = 0;

		printf("Lets do wkup ...");

		total = fopen("total_wkup.txt", "wt");
		if (!total)
		{
			printf("error at total_wkup.txt, exiting\n");
			exit(1);
		}

		for (i = 0; i < maxuser; i++) tmptop[i] = db[i].wkup_bytes;

		sorted = sort_top(tmptop);
		dog = 0;

		while (sorted)
		{
			dog++;

			if (dog <= wkup_unum)
			{
				bzero(buf2, sizeof(buf2));
				sprintf(buf2, "%llu", db[sorted->num].wkup_bytes);
				fprintf(total, " %3d  %-10s %-26s %20s\n", dog, db[sorted->num].username,
				        db[sorted->num].location, f_format(buf2));
			}
			wkup_total += db[sorted->num].wkup_bytes;
			/* does this if do any fucking thing, ehh? */
			if (wkup_uscore < db[sorted->num].wkup_bytes)
			{
				unum = sorted->num;
				wkup_uscore = db[sorted->num].wkup_bytes;
			}
			sorted = sorted->next;
		}

		bzero(buf2, sizeof(buf2));
		sprintf(buf2, "%llu", wkup_total);
		fprintf(total, "site weektop uploads: %s bytes\n", f_format(buf2));

		High_Score_Check("wkup", unum, wkup_total);

		bzero(buf2, sizeof(buf2));
		sprintf(buf2, "%llu", HS.hwkup_bytes);
		fprintf(total, "highscore user: %s - %s bytes\n", HS.hwkup_user, f_format(buf2));

		bzero(buf2, sizeof(buf2));
		sprintf(buf2, "%llu", HS.site_wkup);
		fprintf(total, "best site weektop: %s bytes\n", f_format(buf2));
		fprintf(total, "%s\n", verss);

		printf("Done!\n");
		fclose(total);
	}

	if (strcmp(whus, "wkdn") == 0)
	{
		unsigned long long wkdn_total = 0;
		unsigned long long wkdn_uscore = 0;

		printf("Lets do wkdn ...");

		total = fopen("total_wkdn.txt", "wt");
		if (!total)
		{
			printf("error at total_wkdn.txt, exiting\n");
			exit(1);
		}

		for (i = 0; i < maxuser; i++) tmptop[i] = db[i].wkdn_bytes;

		sorted = sort_top(tmptop);
		dog = 0;

		while (sorted)
		{
			dog++;

			if (dog <= wkdn_unum)
			{
				bzero(buf2, sizeof(buf2));
				sprintf(buf2, "%llu", db[sorted->num].wkdn_bytes);
				fprintf(total, " %3d  %-10s %-26s %20s\n", dog, db[sorted->num].username,
				        db[sorted->num].location, f_format(buf2));
			}
			wkdn_total += db[sorted->num].wkdn_bytes;
			if (wkdn_uscore < db[sorted->num].wkdn_bytes)
			{
				unum = sorted->num;
				wkdn_uscore = db[sorted->num].wkdn_bytes;
			}
			sorted = sorted->next;
		}

		bzero(buf2, sizeof(buf2));
		sprintf(buf2, "%llu", wkdn_total);
		fprintf(total, "site weektop downloads: %s bytes\n", f_format(buf2));

		High_Score_Check("wkdn", unum, wkdn_total);

		bzero(buf2, sizeof(buf2));
		sprintf(buf2, "%llu", HS.hwkdn_bytes);
		fprintf(total, "highscore user: %s - %s bytes\n", HS.hwkdn_user, f_format(buf2));

		bzero(buf2, sizeof(buf2));
		sprintf(buf2, "%llu", HS.site_wkdn);
		fprintf(total, "worst site weektop: %s bytes\n", f_format(buf2));
		fprintf(total, "%s\n", verss);

		printf("Done!\n");
		fclose(total);
	}

	if (strcmp(whus, "mup") == 0)
	{
		unsigned long long mup_total = 0;
		unsigned long long mup_uscore = 0;

		printf("Lets do mup ...");

		total = fopen("total_mup.txt", "wt");
		if (!total)
		{
			printf("error at total_mup.txt, exiting\n");
			exit(1);
		}

		for (i = 0; i < maxuser; i++) tmptop[i] = db[i].mup_bytes;

		sorted = sort_top(tmptop);
		dog = 0;

		while (sorted)
		{
			dog++;

			if (dog <= mup_unum)
			{
				bzero(buf2, sizeof(buf2));
				sprintf(buf2, "%llu", db[sorted->num].mup_bytes);
				fprintf(total, " %3d  %-10s %-26s %20s\n", dog, db[sorted->num].username,
				        db[sorted->num].location, f_format(buf2));
			}
			mup_total += db[sorted->num].mup_bytes;
			if (mup_uscore < db[sorted->num].mup_bytes)
			{
				unum = sorted->num;
				mup_uscore = db[sorted->num].mup_bytes;
			}
			sorted = sorted->next;
		}

		bzero(buf2, sizeof(buf2));
		sprintf(buf2, "%llu", mup_total);
		fprintf(total, "site monthtop uploads: %s bytes\n", f_format(buf2));

		High_Score_Check("mup", unum, mup_total);

		bzero(buf2, sizeof(buf2));
		sprintf(buf2, "%llu", HS.hmup_bytes);
		fprintf(total, "highscore user: %s - %s bytes\n", HS.hmup_user, f_format(buf2));

		bzero(buf2, sizeof(buf2));
		sprintf(buf2, "%llu", HS.site_mup);
		fprintf(total, "best site monthtop: %s bytes\n", f_format(buf2));
		fprintf(total, "%s\n", verss);

		printf("Done!\n");
		fclose(total);
	}

	if (strcmp(whus, "mdn") == 0)
	{
		unsigned long long mdn_total = 0;
		unsigned long long mdn_uscore = 0;

		printf("Lets do mdn ...");

		total = fopen("total_mdn.txt", "wt");
		if (!total)
		{
			printf("error at total_mdn.txt, exiting\n");
			exit(1);
		}

		for (i = 0; i < maxuser; i++) tmptop[i] = db[i].mdn_bytes;

		sorted = sort_top(tmptop);
		dog = 0;

		while (sorted)
		{
			dog++;

			if (dog <= mdn_unum)
			{
				bzero(buf2, sizeof(buf2));
				sprintf(buf2, "%llu", db[sorted->num].mdn_bytes);
				fprintf(total, " %3d  %-10s %-26s %20s\n", dog, db[sorted->num].username,
				        db[sorted->num].location, f_format(buf2));
			}
			mdn_total += db[sorted->num].mdn_bytes;
			if (mdn_uscore < db[sorted->num].mdn_bytes)
			{
				unum = sorted->num;
				mdn_uscore = db[sorted->num].mdn_bytes;
			}
			sorted = sorted->next;
		}

		bzero(buf2, sizeof(buf2));
		sprintf(buf2, "%llu", mdn_total);
		fprintf(total, "site monthtop downloads: %s bytes\n", f_format(buf2));

		High_Score_Check("mdn", unum, mdn_total);

		bzero(buf2, sizeof(buf2));
		sprintf(buf2, "%llu", HS.hmdn_bytes);
		fprintf(total, "highscore user: %s - %s bytes\n", HS.hmdn_user, f_format(buf2));

		bzero(buf2, sizeof(buf2));
		sprintf(buf2, "%llu", HS.site_mdn);
		fprintf(total, "worst site monthtop: %s bytes\n", f_format(buf2));
		fprintf(total, "%s\n", verss);

		printf("Done!\n");
		fclose(total);
	}

	if (strcmp(whus, "yearup") == 0)
	{
		unsigned long long yearup_total = 0;
		unsigned long long yearup_uscore = 0;

		printf("Lets do yearup ...");

		total = fopen("total_yearup.txt", "wt");
		if (!total)
		{
			printf("error at total_yearup.txt, exiting\n");
			exit(1);
		}

		for (i = 0; i < maxuser; i++) tmptop[i] = db[i].yeartop_up;

		sorted = sort_top(tmptop);
		dog = 0;

		while (sorted)
		{
			dog++;

			if (dog <= yearup_unum)
			{
				bzero(buf2, sizeof(buf2));
				sprintf(buf2, "%llu", db[sorted->num].yeartop_up);
				fprintf(total, " %3d  %-10s %-26s %20s\n", dog, db[sorted->num].username,
				        db[sorted->num].location, f_format(buf2));
			}
			yearup_total += db[sorted->num].yeartop_up;
			if (yearup_uscore < db[sorted->num].yeartop_up)
			{
				unum = sorted->num;
				yearup_uscore = db[sorted->num].yeartop_up;
			}
			sorted = sorted->next;
		}

		bzero(buf2, sizeof(buf2));
		sprintf(buf2, "%llu", yearup_total);
		fprintf(total, "site yeartop uploads: %s bytes\n", f_format(buf2));

		High_Score_Check("yearup", unum, yearup_total);

		bzero(buf2, sizeof(buf2));
		sprintf(buf2, "%llu", HS.hyearup_user_bytes);
		fprintf(total, "highscore user: %s - %s bytes\n", HS.hyearup_user, f_format(buf2));

		bzero(buf2, sizeof(buf2));
		sprintf(buf2, "%llu", HS.site_yeartop_up);
		fprintf(total, "best site yeartop uploads: %s bytes\n", f_format(buf2));
		fprintf(total, "%s\n", verss);

		printf("Done!\n");
		fclose(total);
	}

	if (strcmp(whus, "yeardn") == 0)
	{
		unsigned long long yeardn_total = 0;
		unsigned long long yeardn_uscore = 0;

		printf("Lets do yeardn ...");

		total = fopen("total_yeardn.txt", "wt");
		if (!total)
		{
			printf("error at total_yeardn.txt, exiting\n");
			exit(1);
		}

		for (i = 0; i < maxuser; i++) tmptop[i] = db[i].yeartop_dn;

		sorted = sort_top(tmptop);
		dog = 0;

		while (sorted)
		{
			dog++;

			if (dog <= yeardn_unum)
			{
				bzero(buf2, sizeof(buf2));
				sprintf(buf2, "%llu", db[sorted->num].yeartop_dn);
				fprintf(total, " %3d  %-10s %-26s %20s\n", dog, db[sorted->num].username,
				        db[sorted->num].location, f_format(buf2));
			}
			yeardn_total += db[sorted->num].yeartop_dn;
			if (yeardn_uscore < db[sorted->num].yeartop_dn)
			{
				unum = sorted->num;
				yeardn_uscore = db[sorted->num].yeartop_dn;
			}
			sorted = sorted->next;
		}

		bzero(buf2, sizeof(buf2));
		sprintf(buf2, "%llu", yeardn_total);
		fprintf(total, "site yeartop downloads: %s bytes\n", f_format(buf2));

		High_Score_Check("yeardn", unum, yeardn_total);

		bzero(buf2, sizeof(buf2));
		sprintf(buf2, "%llu", HS.hyeardn_user_bytes);
		fprintf(total, "highscore user: %s - %s bytes\n", HS.hyeardn_user, f_format(buf2));

		bzero(buf2, sizeof(buf2));
		sprintf(buf2, "%llu", HS.site_yeartop_dn);
		fprintf(total, "Worst site yeartop downloads: %s bytes\n", f_format(buf2));
		fprintf(total, "%s\n", verss);

		printf("Done!\n");
		fclose(total);
	}

	return 0;
}

/*

        highscores, summary? :)

 */
int All_Bytes_Stats()
{
	FILE *summars;
	FILE *highs;

	char bufa1[80], bufa2[80], bufa3[80];
	int al = 1;
	All_UL_Bytes = 0, All_DL_Bytes = 0;

	bzero(HS.hwkup_user, sizeof(HS.hwkup_user));
	HS.hwkup_bytes = 0;
	bzero(HS.hwkdn_user, sizeof(HS.hwkdn_user));
	HS.hwkdn_bytes = 0;
	bzero(HS.hmup_user, sizeof(HS.hmup_user));
	HS.hmup_bytes = 0;
	bzero(HS.hmdn_user, sizeof(HS.hmdn_user));
	HS.hmdn_bytes = 0;
	HS.site_wkup = 0;
	HS.site_wkdn = 0;
	HS.site_mup = 0;
	HS.site_mdn = 0;

	highs = fopen("highscores.dat", "rb");
	if (!highs)
	{
		printf("error at highs.dat, exiting\n");
		exit(1);
	}

	fread(&HS, sizeof(Scores), 1, highs);
	fclose(highs);

	summars = fopen("summary.txt", "wt");
	if (!summars)
	{
		printf("error at summary.txt, exiting.\n");
		exit(1);
	}

	while (al <= maxuser)
	{
		All_UL_Bytes += db[al].ul_bytes;
		All_DL_Bytes += db[al].dl_bytes;
		al++;
	}

	bzero(bufa1, sizeof(bufa1));
	bzero(bufa2, sizeof(bufa2));
	bzero(bufa3, sizeof(bufa3));
	sprintf(bufa1, "%llu", HS.hwkup_bytes);
	sprintf(bufa2, "%llu", HS.hwkdn_bytes);
	sprintf(bufa3, "%llu", HS.hmup_bytes);

	fprintf(summars, "Highscore records:\nwkup user: %s - %s bytes\nwkdn user: %s - %s bytes\nmup user: %s - %s bytes", HS.hwkup_user, f_format(bufa1), HS.hwkdn_user, f_format(bufa2), HS.hmup_user, f_format(bufa3));

	bzero(bufa1, sizeof(bufa1));
	bzero(bufa2, sizeof(bufa2));
	bzero(bufa3, sizeof(bufa3));
	sprintf(bufa1, "%llu", HS.hmdn_bytes);
	sprintf(bufa2, "%llu", HS.site_wkup);
	sprintf(bufa3, "%llu", HS.site_wkdn);

	fprintf(summars, "mdn user: %s - %s bytes\nsite wkup: %s bytes\nsite wkdn: %s bytes", HS.hmdn_user, f_format(bufa1), f_format(bufa2), f_format(bufa3));

	bzero(bufa1, sizeof(bufa1));
	bzero(bufa2, sizeof(bufa2));
	bzero(bufa3, sizeof(bufa3));
	sprintf(bufa1, "%llu", HS.site_mup);
	sprintf(bufa2, "%llu", HS.site_mdn);
	sprintf(bufa3, "%llu", HS.hwkup_group_bytes);

	fprintf(summars, "site mup: %s bytes\nsite mdn: %s bytes\nwkup group: %s - %s bytes", f_format(bufa1), f_format(bufa2), HS.hwkup_group, f_format(bufa3));

	bzero(bufa1, sizeof(bufa1));
	bzero(bufa2, sizeof(bufa2));
	bzero(bufa3, sizeof(bufa3));
	sprintf(bufa1, "%llu", HS.hwkdn_group_bytes);
	sprintf(bufa2, "%llu", HS.hmup_group_bytes);
	sprintf(bufa3, "%llu", HS.hmdn_group_bytes);

	fprintf(summars, "wkdn group: %s - %s bytes\nmup group: %s - %s bytes\nmdn group: %s - %s bytes", HS.hwkdn_group, f_format(bufa1), HS.hmup_group, f_format(bufa2), HS.hmdn_group, f_format(bufa3));

/*
        HS.site_yeartop_dn=amount; rec=1;
        HS.site_yeartop_dn_date=time(0);
        printf("yes new HS.site_yeartop_dn record: %llu\n",HS.site_yeartop_dn);
        }
    if (HS.hyeardn_user_bytes < db[unum].yeartop_dn) {
        HS.hyeardn_user_bytes = db[unum].yeartop_dn;
        bzero(HS.hyeardn_user,sizeof(HS.hyeardn_user));
        sprintf(HS.hyeardn_user,"%s",db[unum].username);
        HS.hyeardn_user_date=time(0);
 */
// yepper
	bzero(bufa1, sizeof(bufa1));
	bzero(bufa2, sizeof(bufa2));
	sprintf(bufa1, "%llu", HS.hyearup_user_bytes);
	sprintf(bufa2, "%llu", HS.hyeardn_user_bytes);
	fprintf(summars, "yearup: %s - %s bytes\nyeardn: %s - %s bytes", HS.hyearup_user, f_format(bufa1), HS.hyeardn_user, f_format(bufa2));

	bzero(bufa1, sizeof(bufa1));
	bzero(bufa2, sizeof(bufa2));
	sprintf(bufa1, "%llu", HS.site_yeartop_up);
	sprintf(bufa2, "%llu", HS.site_yeartop_dn);

	fprintf(summars, "site yeartop up: %s bytes\nsite yeartop dn: %s bytes\n", f_format(bufa1), f_format(bufa2));

	bzero(bufa1, sizeof(bufa1));
	bzero(bufa2, sizeof(bufa2));
	bzero(bufa3, sizeof(bufa3));
	sprintf(bufa1, "%llu", All_UL_Bytes);
	sprintf(bufa2, "%llu", All_DL_Bytes);
	sprintf(bufa3, "%llu", (All_UL_Bytes + All_DL_Bytes));

	fprintf(summars, "all ul: %s - all dl: %s - hoss: %s\n", f_format(bufa1), f_format(bufa2), f_format(bufa3));

	fprintf(summars, "%s\n", verss);

	fclose(summars);

	return 0;
}

/*

        Yeartop

 */
int YearTopGenerator()
{
	FILE *OldYear;

	Database YD;

	int olduser = 1, cx = 1, co = 1;

	OldYear = fopen("yeartop.dat", "rb");
	if (!OldYear)
	{
		printf("error in yeartop.dat, exiting\n");
		exit(1);
	}

	fread(&YD, sizeof(Database), 1, OldYear);
	fclose(OldYear);

/* list all usernames in the yeartop database */
	while (1)
	{
#ifdef DEBUG
		printf("whileing OLD YD[%i].username: %s - %llu bytes\n", olduser, YD[olduser].username, YD[olduser].ul_bytes);
#endif
		olduser++;
		if (strlen(YD[olduser].username) == 0)
			break;
	}
	olduser--;

#ifdef DEBUG
	printf("Last years top has %i users.\n", olduser);
#endif

/* calculate the new yeartop bytes for the existing users */
	while (cx <= maxuser)
	{
#ifdef DEBUG
		printf("Todays Yeartop All Users db[%i]: %s - %llu bytes\n", cx, db[cx].username, db[cx].ul_bytes);
#endif

		/* looping the USERS FROM BEGINNING OF THIS YEAR STUPID! */
		while (co <= olduser)
		{
			/* found match for our yeartop user */
			if (strcmp(YD[co].username, db[cx].username) == 0)
			{
		#ifdef DEBUG
				printf("YD[co] match user co: %s, db[cx]: %s - co: %llu bytes...", YD[co].username, db[cx].username, YD[co].ul_bytes);
		#endif

				/* count bytes from old database and new */
				if (db[cx].ul_bytes > YD[co].ul_bytes)
					db[cx].yeartop_up = (db[cx].ul_bytes - YD[co].ul_bytes);
				if (db[cx].dl_bytes > YD[co].dl_bytes)
					db[cx].yeartop_dn = (db[cx].dl_bytes - YD[co].dl_bytes);

		#ifdef DEBUG
				printf("NEW YD - %llu bytes!\n", db[cx].yeartop_up);
		#endif

				/* ok match found and we reset the oldusers to ONE and break loop */
				co = 1;
				break;
			}

			co++;
		}
#ifdef DEBUG
		printf("Ok we changed the CX (current) user to: %i +1 and of course resetted co (old) to 1. heh.\n", cx);
#endif
		cx++;
		co = 1;
	}

/* just display the counted bytes */
#ifdef DEBUG
	cx = 1;

	while (cx <= maxuser)
	{
		printf("--- YearTOP Current! for %s ul: %llu - dl: %llu\n", db[cx].username, db[cx].yeartop_up, db[cx].yeartop_dn);
		cx++;
	}
#endif

	return 0;
}

/*

        configuration file

 */
int CFG_Read()
{
	FILE *cfg_file;
	char temp[80];

	/* lets read the how_many_users_to_list */
	cfg_file = fopen("gltool.cfg", "rt");
	if (!cfg_file)
	{
		printf("error at gltool.cfg!\n");
		exit(1);
	}

	fscanf(cfg_file, "%s", user_path); /* path to the user files */
	fscanf(cfg_file, "%s", top_path);  /* path to the top files */
	fscanf(cfg_file, "%s", php_path);  /* path to the php file  */
	fscanf(cfg_file, "%s", bot_path);  /* bot announce file path */

	fscanf(cfg_file, "%i", &alup_unum);   /* max alup users */
	fscanf(cfg_file, "%i", &aldn_unum);   /* max aldn users */
	fscanf(cfg_file, "%i", &wkup_unum);   /* max wkup users */
	fscanf(cfg_file, "%i", &wkdn_unum);   /* max wkdn users */
	fscanf(cfg_file, "%i", &mup_unum);    /* max mup users */
	fscanf(cfg_file, "%i", &mdn_unum);    /* max mdn users */
	fscanf(cfg_file, "%i", &yearup_unum); /* max yearup users */
	fscanf(cfg_file, "%i", &yeardn_unum); /* max yeardn users */

#ifdef DEBUG
	printf("%s, alup_unum: %i, aldn_unum: %i\n", user_path, alup_unum, aldn_unum);
#endif

	fclose(cfg_file);
	return 0;
}

/*

        write highscores? :)

 */
int High_Score_Check(char *tscore, int unum, unsigned long long amount)
{
	FILE *highscores;
	int rec = 0;

	bzero(HS.hwkup_user, sizeof(HS.hwkup_user));
	HS.hwkup_bytes = 0;
	bzero(HS.hwkdn_user, sizeof(HS.hwkdn_user));
	HS.hwkdn_bytes = 0;
	bzero(HS.hmup_user, sizeof(HS.hmup_user));
	HS.hmup_bytes = 0;
	bzero(HS.hmdn_user, sizeof(HS.hmdn_user));
	bzero(HS.hyearup_user, sizeof(HS.hyearup_user));
	bzero(HS.hyeardn_user, sizeof(HS.hyeardn_user));
	HS.hmdn_bytes = 0;
	HS.site_wkup = 0;
	HS.site_wkdn = 0;
	HS.site_mup = 0;
	HS.site_mdn = 0;
	HS.hyearup_user_bytes = 0;
	HS.hyeardn_user_bytes = 0;
	HS.site_yeartop_up = 0;
	HS.site_yeartop_dn = 0;

	highscores = fopen("highscores.dat", "r+b");
	if (!highscores)
	{
		printf("error at highscores.dat, exiting\n");
		exit(1);
	}

	fread(&HS, sizeof(Scores), 1, highscores);

	if (strcmp(tscore, "wkup") == 0)
	{
		if (amount > HS.site_wkup)
		{
			HS.site_wkup = amount;
			rec = 1;
			HS.site_wkup_date = time(0);
			printf("yes new HS.site_wkup record: %llu\n", HS.site_wkup);
		}
		if (HS.hwkup_bytes < db[unum].wkup_bytes)
		{
			HS.hwkup_bytes = db[unum].wkup_bytes;
			bzero(HS.hwkup_user, sizeof(HS.hwkup_user));
			sprintf(HS.hwkup_user, "%s", db[unum].username);
			HS.hwkup_user_date = time(0);
			rec = 1;
			printf("new wkup user: %s - %llu bytes\n", db[unum].username, db[unum].wkup_bytes);
		}
	}

	if (strcmp(tscore, "wkdn") == 0)
	{
		if (amount > HS.site_wkdn)
		{
			HS.site_wkdn = amount;
			rec = 1;
			HS.site_wkdn_date = time(0);
			printf("yes new HS.site_wkdn record: %llu\n", HS.site_wkdn);
		}
		if (HS.hwkdn_bytes < db[unum].wkdn_bytes)
		{
			HS.hwkdn_bytes = db[unum].wkdn_bytes;
			bzero(HS.hwkdn_user, sizeof(HS.hwkdn_user));
			sprintf(HS.hwkdn_user, "%s", db[unum].username);
			HS.hwkdn_user_date = time(0);
			rec = 1;
			printf("new wkdn user: %s - %llu bytes\n", db[unum].username, db[unum].wkdn_bytes);
		}
	}

	if (strcmp(tscore, "mup") == 0)
	{
		if (amount > HS.site_mup)
		{
			HS.site_mup = amount;
			rec = 1;
			HS.site_mup_date = time(0);
			printf("yes new HS.site_mup record: %llu\n", HS.site_mup);
		}
		if (HS.hmup_bytes < db[unum].mup_bytes)
		{
			HS.hmup_bytes = db[unum].mup_bytes;
			bzero(HS.hmup_user, sizeof(HS.hmup_user));
			sprintf(HS.hmup_user, "%s", db[unum].username);
			HS.hmup_user_date = time(0);
			rec = 1;
			printf("new mup user: %s - %llu bytes\n", db[unum].username, db[unum].mup_bytes);
		}
	}

	if (strcmp(tscore, "mdn") == 0)
	{
		if (amount > HS.site_mdn)
		{
			HS.site_mdn = amount;
			rec = 1;
			HS.site_mdn_date = time(0);
			printf("yes new HS.site_mdn record: %llu\n", HS.site_mdn);
		}
		if (HS.hmdn_bytes < db[unum].mdn_bytes)
		{
			HS.hmdn_bytes = db[unum].mdn_bytes;
			bzero(HS.hmdn_user, sizeof(HS.hmdn_user));
			sprintf(HS.hmdn_user, "%s", db[unum].username);
			HS.hmdn_user_date = time(0);
			rec = 1;
			printf("new mdn user: %s - %llu bytes\n", db[unum].username, db[unum].mdn_bytes);
		}
	}

	if (strcmp(tscore, "yearup") == 0)
	{
		if (amount > HS.site_yeartop_up)
		{
			HS.site_yeartop_up = amount;
			rec = 1;
			HS.site_yeartop_up_date = time(0);
			printf("deeku! yes new HS.site_yeartop_up record: %llu\n", HS.site_yeartop_up);
		}
		if (HS.hyearup_user_bytes < db[unum].yeartop_up)
		{
			HS.hyearup_user_bytes = db[unum].yeartop_up;
			bzero(HS.hyearup_user, sizeof(HS.hyearup_user));
			sprintf(HS.hyearup_user, "%s", db[unum].username);
			HS.hyearup_user_date = time(0);
			rec = 1;
			printf("new yearup user: %s - %llu bytes\n", db[unum].username, db[unum].yeartop_up);
		}
	}

	if (strcmp(tscore, "yeardn") == 0)
	{
		if (amount > HS.site_yeartop_dn)
		{
			HS.site_yeartop_dn = amount;
			rec = 1;
			HS.site_yeartop_dn_date = time(0);
			printf("yes new HS.site_yeartop_dn record: %llu\n", HS.site_yeartop_dn);
		}
		if (HS.hyeardn_user_bytes < db[unum].yeartop_dn)
		{
			HS.hyeardn_user_bytes = db[unum].yeartop_dn;
			bzero(HS.hyeardn_user, sizeof(HS.hyeardn_user));
			sprintf(HS.hyeardn_user, "%s", db[unum].username);
			HS.hyeardn_user_date = time(0);
			rec = 1;
			printf("new yeardn user: %s - %llu bytes\n", db[unum].username, db[unum].yeartop_dn);
		}
	}

/* GSCORES */
	if (strcmp(tscore, "gpwkup") == 0)
	{
		if (HS.hwkup_group_bytes < gp[unum].wkup_bytes)
		{
			HS.hwkup_group_bytes = gp[unum].wkup_bytes;
			bzero(HS.hwkup_group, sizeof(HS.hwkup_group));
			sprintf(HS.hwkup_group, "%s", gp[unum].name);
			HS.hwkup_group_date = time(0);
			rec = 1;
			printf("new hwkup_group: %s - %llu bytes\n", gp[unum].name, gp[unum].wkup_bytes);
		}
	}

	if (strcmp(tscore, "gpwkdn") == 0)
	{
		if (HS.hwkdn_group_bytes < gp[unum].wkdn_bytes)
		{
			HS.hwkdn_group_bytes = gp[unum].wkdn_bytes;
			bzero(HS.hwkdn_group, sizeof(HS.hwkdn_group));
			sprintf(HS.hwkdn_group, "%s", gp[unum].name);
			HS.hwkdn_group_date = time(0);
			rec = 1;
			printf("new hwkdn_group: %s - %llu bytes\n", gp[unum].name, gp[unum].wkdn_bytes);
		}
	}

	if (strcmp(tscore, "gpmup") == 0)
	{
		if (HS.hmup_group_bytes < gp[unum].mup_bytes)
		{
			HS.hmup_group_bytes = gp[unum].mup_bytes;
			bzero(HS.hmup_group, sizeof(HS.hmup_group));
			sprintf(HS.hmup_group, "%s", gp[unum].name);
			HS.hmup_group_date = time(0);
			rec = 1;
			printf("new hwkdn_group: %s - %llu bytes\n", gp[unum].name, gp[unum].mup_bytes);
		}
	}

	if (strcmp(tscore, "gpmdn") == 0)
	{
		if (HS.hmdn_group_bytes < gp[unum].mdn_bytes)
		{
			HS.hmdn_group_bytes = gp[unum].mdn_bytes;
			bzero(HS.hmdn_group, sizeof(HS.hmdn_group));
			sprintf(HS.hmdn_group, "%s", gp[unum].name);
			HS.hmdn_group_date = time(0);
			rec = 1;
			printf("new hmdn_group: %s - %llu bytes\n", gp[unum].name, gp[unum].mdn_bytes);
		}
	}

	rewind(highscores);
	if (rec)
		fwrite(&HS, sizeof(Scores), 1, highscores);

	fclose(highscores);
	return 0;
}

/*

        Yeartop initialization when ran with /yeartop command line

 */
int Year_Top_Init()
{
	FILE *YearBase;
	int dog = 0;
	char buf2[256];

	unsigned long long year_user_bytes = 0;
	unsigned long long year_ann_total = 0;

	printf("Yeartop initilization, happy new year btw! ...");

	YearBase = fopen("yeartop.dat", "wb");
	if (!YearBase)
	{
		printf("error at yeartop.dat, exiting\n");
		exit(1);
	}

	fwrite(&db, sizeof(Database), 1, YearBase);

	printf("Done!\n");

	for (i = 0; i < maxuser; i++) tmptop[i] = db[i].yeartop_up;

	sorted = sort_top(tmptop);
	dog = 0;

	while (sorted)
	{
		dog++;

		if (dog == 1)
		{
			/* lets make yeartop USER + BYTES . . . */
			bzero(buf2, sizeof(buf2));
			sprintf(buf2, "%s", db[sorted->num].username);
			year_user_bytes = db[sorted->num].yeartop_up;
		}

		year_ann_total += db[sorted->num].yeartop_up;
		sorted = sorted->next;
	}

	Announce_Winner("yeartop", buf2, year_user_bytes, year_ann_total);

	fclose(YearBase);
	return 0;
}

/*

        Weektop database creation

 */
int DataBase_WEEK()
{
	FILE *wbase;
	FILE *dbwkdebug;
	int dog = 0;

	wbase = fopen("weekscores.dat", "ab");
	if (!wbase)
	{
		printf("error at weekscores.dat, exiting\n");
		exit(1);
	}

	dbwkdebug = fopen("dbwkdebug.txt", "wt");
	if (!dbwkdebug)
	{
		printf("error at dbwkdebug.txt, exiting\n");
		exit(1);
	}

#ifdef DEBUG
	printf("DataBase_WEEK() - files open...\n");
#endif

	for (i = 0; i < maxuser; i++) tmptop[i] = db[i].wkup_bytes;

#ifdef DEBUG
	printf("DataBase_WEEK() - 1st wkup_bytes loop done...\n");
#endif

	sorted = sort_top(tmptop);

	WS.weektime = 0;
	WS.weektime = time(0);
	bzero(WS.wkup_user, sizeof(WS.wkup_user));
	sprintf(WS.wkup_user, "%s", db[sorted->num].username);
	bzero(WS.wkup_user_locat, sizeof(WS.wkup_user_locat));
	sprintf(WS.wkup_user_locat, "%s", db[sorted->num].location);
	WS.wkup_user_bytes = 0;
	WS.wkup_user_bytes = db[sorted->num].wkup_bytes;
	/* snake latest addition trying to fix the
	   fucken weekscores too high */
	WS.weekup_total = 0;

	for (i = 0; i < maxuser; i++) tmptop[i] = db[i].wkup_bytes;

#ifdef DEBUG
	printf("DataBase_WEEK() - 2nd wkup_bytes loop done...\n");
#endif

	sorted = sort_top(tmptop);
	dog = 0;

#ifdef DEBUG
	printf("DataBase_WEEK() - sorted = sort_top( done...\n");
#endif

	while (sorted)
	{
		dog++;

		WS.weekup_total += db[sorted->num].wkup_bytes;
		fprintf(dbwkdebug, "%s - %llu\n", db[sorted->num].username, db[sorted->num].wkup_bytes);
#ifdef DEBUG
		printf("Looping %i - %s %llu\n", dog, db[sorted->num].username, db[sorted->num].wkup_bytes);
#endif
		sorted = sorted->next;
	}
#ifdef DEBUG
	printf("that while loop is now done.\n");
#endif
	fclose(dbwkdebug);

#ifdef DEBUG
	printf("dbwkdebug file closed.\n");
#endif

#ifdef DEBUG
// this segfaults, as sorted is ... not present or something?
//	printf("wkupwinner user: %s - %s - %llu bytes\n", db[sorted->num].username, db[sorted->num].location, db[sorted->num].wkup_bytes);
#endif

	for (i = 0; i < maxuser; i++) tmptop[i] = db[i].wkdn_bytes;

	sorted = sort_top(tmptop);

#ifdef DEBUG
	printf("wkdn bytes sorted...\n");
#endif

	bzero(WS.wkdn_user, sizeof(WS.wkdn_user));
	sprintf(WS.wkdn_user, "%s", db[sorted->num].username);
	bzero(WS.wkdn_user_locat, sizeof(WS.wkdn_user_locat));
	sprintf(WS.wkdn_user_locat, "%s", db[sorted->num].location);
	WS.wkdn_user_bytes = 0;
	WS.wkdn_user_bytes = db[sorted->num].wkdn_bytes;
	WS.weekdn_total = 0;

	for (i = 0; i < maxuser; i++) tmptop[i] = db[i].wkdn_bytes;

	sorted = sort_top(tmptop);
	dog = 0;

	while (sorted)
	{
		dog++;
#ifdef DEBUG
		printf("Looping wkdn_bytes : %i - %s %llu\n", dog, db[sorted->num].username, db[sorted->num].wkdn_bytes);
#endif
		WS.weekdn_total += db[sorted->num].wkdn_bytes;
		sorted = sorted->next;
	}

#ifdef DEBUG
// segfaults?
	printf("Yeah just before wkdnwinner part...\n");
	printf("wkdnwinner user: %s - %s - %llu bytes\n", db[sorted->num].username, db[sorted->num].location, db[sorted->num].wkdn_bytes);
#endif

	for (i = 0; i < maxuser; i++) tmptop[i] = gp[i].wkup_bytes;

#ifdef DEBUG
	printf("Okay wkdnwinner after for loop done...\n");
#endif
	sorted = sort_top(tmptop);

	bzero(WS.wkup_group, sizeof(WS.wkup_group));
	sprintf(WS.wkup_group, "%s", gp[sorted->num].name);
	WS.wkup_group_bytes = 0;
	WS.wkup_group_bytes = gp[sorted->num].wkup_bytes;

	for (i = 0; i < maxuser; i++) tmptop[i] = gp[i].wkdn_bytes;

#ifdef DEBUG
	printf("Another wkdnwinner for loop is done, wow.\n");
#endif
	sorted = sort_top(tmptop);

	bzero(WS.wkdn_group, sizeof(WS.wkdn_group));
	sprintf(WS.wkdn_group, "%s", gp[sorted->num].name);
	WS.wkdn_group_bytes = 0;
	WS.wkdn_group_bytes = gp[sorted->num].wkdn_bytes;

	fwrite(&WS, sizeof(WeekScores), 1, wbase);
#ifdef DEBUG
	printf("written weekscores!\n");
#endif
	fclose(wbase);

#ifdef DEBUG
	printf("closed wbase file.\n");
#endif

	/* bot announce filameking: user - bytes - weektop total */
	Announce_Winner("wkup", WS.wkup_user, WS.wkup_user_bytes, WS.weekup_total);

	return 0;
}

/*

        Monthtop database creation

 */
int DataBase_MONTH()
{
	FILE *mbase;
	int dog = 0;

	mbase = fopen("monthscores.dat", "ab");
	if (!mbase)
	{
		printf("error at monthscores.dat, exiting\n");
		exit(1);
	}

	for (i = 0; i < maxuser; i++) tmptop[i] = db[i].mup_bytes;

	sorted = sort_top(tmptop);

	MS.monthtime = 0;
	MS.monthtime = time(0);
	bzero(MS.mup_user, sizeof(MS.mup_user));
	sprintf(MS.mup_user, "%s", db[sorted->num].username);
	bzero(MS.mup_user_locat, sizeof(MS.mup_user_locat));
	sprintf(MS.mup_user_locat, "%s", db[sorted->num].location);
	MS.mup_user_bytes = 0;
	MS.mup_user_bytes = db[sorted->num].mup_bytes;
	MS.mup_total = 0;

	for (i = 0; i < maxuser; i++) tmptop[i] = db[i].mup_bytes;

	sorted = sort_top(tmptop);
	dog = 0;

	while (sorted)
	{
		dog++;

		MS.mup_total += db[sorted->num].mup_bytes;
		sorted = sorted->next;
	}

#ifdef DEBUG
	printf("mupwinner user: %s - %s - %llu bytes\n", db[sorted->num].username, db[sorted->num].location, db[sorted->num].mup_bytes);
#endif

	for (i = 0; i < maxuser; i++) tmptop[i] = db[i].mdn_bytes;

	sorted = sort_top(tmptop);

	bzero(MS.mdn_user, sizeof(MS.mdn_user));
	sprintf(MS.mdn_user, "%s", db[sorted->num].username);
	bzero(MS.mdn_user_locat, sizeof(MS.mdn_user_locat));
	sprintf(MS.mdn_user_locat, "%s", db[sorted->num].location);
	MS.mdn_user_bytes = 0;
	MS.mdn_user_bytes = db[sorted->num].mdn_bytes;
	MS.mdn_total = 0;

	for (i = 0; i < maxuser; i++) tmptop[i] = db[i].mdn_bytes;

	sorted = sort_top(tmptop);
	dog = 0;

	while (sorted)
	{
		dog++;

		MS.mdn_total += db[sorted->num].mdn_bytes;
		sorted = sorted->next;
	}

#ifdef DEBUG
	printf("mdnwinner user: %s - %s - %llu bytes\n", db[sorted->num].username, db[sorted->num].location, db[sorted->num].mdn_bytes);
#endif

	for (i = 0; i < maxuser; i++) tmptop[i] = gp[i].mup_bytes;

	sorted = sort_top(tmptop);

	bzero(MS.mup_group, sizeof(MS.mup_group));
	sprintf(MS.mup_group, "%s", gp[sorted->num].name);
	MS.mup_group_bytes = 0;
	MS.mup_group_bytes = gp[sorted->num].mup_bytes;

	for (i = 0; i < maxuser; i++) tmptop[i] = gp[i].mdn_bytes;

	sorted = sort_top(tmptop);

	bzero(MS.mdn_group, sizeof(MS.mdn_group));
	sprintf(MS.mdn_group, "%s", gp[sorted->num].name);
	MS.mdn_group_bytes = 0;
	MS.mdn_group_bytes = gp[sorted->num].mdn_bytes;

	fwrite(&MS, sizeof(MonthScores), 1, mbase);
	fclose(mbase);

	/* bot announce filameking: user - bytes - monthup total*/
	Announce_Winner("mup", MS.mup_user, MS.mup_user_bytes, MS.mup_total);

	return 0;
}

// PMCTODO database_year is missing!

/*

        grouptops? :)

 */
int GroupTop()
{
	FILE *gfile;

	char gline[80];
	char *gptr;
	int iz = 1;
	int ig = 1;

	gfile = fopen("/glftpd/etc/group", "rt");
	if (!gfile)
	{
		printf("error at /glftpd/etc/group!\n");
		exit(1);
	}

	fgets(gline, 80, gfile);
	maxgroup = 0;

	while (!feof(gfile))
	{
		maxgroup++;

		gptr = (char *)&gline;

		while (*gptr && (*gptr != ':'))
			gptr++;

		*gptr = 0;

		bzero(gp[maxgroup].name, sizeof(gp[maxgroup].name));
		sprintf(gp[maxgroup].name, "%s", gline);

		bzero(gline, sizeof(gline));
		fgets(gline, 80, gfile);
	}

	fclose(gfile);

#ifdef DEBUG
	printf("number of groups %i\n", maxgroup);

	while (iz <= maxgroup)
	{
		printf("group number %i - %s\n", iz, gp[iz].name);
		iz++;
	}
#endif

	/* init the first users group to be the first group
	   sprintf(gp[ig].name,"%s",db[iz].group);
	   gp[ig].num_members++;
	   gp[ig].alup_bytes += db[iz].ul_bytes;
	   gp[ig].aldn_bytes += db[iz].dl_bytes;
	   gp[ig].wkup_bytes += db[iz].wkup_bytes;
	   gp[ig].wkdn_bytes += db[iz].wkdn_bytes;
	   gp[ig].mup_bytes += db[iz].mup_bytes;
	   gp[ig].mdn_bytes += db[iz].mdn_bytes;
	   iz++;
	 */

	iz = 1;
	ig = 1;

#ifdef DEBUG
	printf("maxuser: %i maxgroup: %i\n", maxuser, maxgroup);
#endif

	while (iz <= maxuser)
	{
		while (ig <= maxgroup)
		{
			if (strcmp(gp[ig].name, db[iz].group) == 0)
			{
				gp[ig].num_members++;
				gp[ig].alup_bytes += db[iz].ul_bytes;
				gp[ig].aldn_bytes += db[iz].dl_bytes;
				gp[ig].wkup_bytes += db[iz].wkup_bytes;
				gp[ig].wkdn_bytes += db[iz].wkdn_bytes;
				gp[ig].mup_bytes += db[iz].mup_bytes;
				gp[ig].mdn_bytes += db[iz].mdn_bytes;
				ig = 1;
				break;
			}
			ig++;
		}
		iz++;
	}

#ifdef DEBUG
	printf("group top bull?\n");
	iz = 1;
	ig = 1;

	while (iz < maxgroup)
	{
		printf("gp[%i].name: %s - gp[].num_members: %i - alup %llu bytes\naldn %llu bytes - wkup %llu bytes - wkdn %llu bytes\nmup %llu bytes - mdn %llu bytes\n",
		       iz, gp[iz].name, gp[iz].num_members, gp[iz].alup_bytes, gp[iz].aldn_bytes,
		       gp[iz].wkup_bytes, gp[iz].wkdn_bytes, gp[iz].mup_bytes, gp[iz].mdn_bytes);
		iz++;
	}
#endif

	return 0;
}

/*

        grouptop totals

 */
int Totals_Groups(char *hoss)
{
	FILE *gtotal;
	char buf2[300];
	int dog = 0, gnum = 0;
	unsigned long long gscore = 0;

	if (strcmp(hoss, "gpup") == 0)
	{
		printf("Lets do gpup ...");

		gtotal = fopen("total_gpup.txt", "wt");
		if (!gtotal)
		{
			printf("error at total_gpup.txt, exiting\n");
			exit(1);
		}

		for (i = 0; i < maxuser; i++) tmptop[i] = gp[i].alup_bytes;

		sorted = sort_top(tmptop);
		dog = 0;

		while (sorted)
		{
			dog++;

			bzero(buf2, sizeof(buf2));
			sprintf(buf2, "%llu", gp[sorted->num].alup_bytes);
			fprintf(gtotal, " %3d  %-10s %20s\n", dog, gp[sorted->num].name, f_format(buf2));
			sorted = sorted->next;
		}
		fprintf(gtotal, "%s\n", verss);

		printf("Done!\n");
		fclose(gtotal);
	}

	if (strcmp(hoss, "gpdn") == 0)
	{
		printf("Lets do gpdn ...");

		gtotal = fopen("total_gpdn.txt", "wt");
		if (!gtotal)
		{
			printf("error at total_gpdn.txt, exiting\n");
			exit(1);
		}

		for (i = 0; i < maxuser; i++) tmptop[i] = gp[i].aldn_bytes;

		sorted = sort_top(tmptop);
		dog = 0;

		while (sorted)
		{
			dog++;

			bzero(buf2, sizeof(buf2));
			sprintf(buf2, "%llu", gp[sorted->num].aldn_bytes);
			fprintf(gtotal, " %3d  %-10s %20s\n", dog, gp[sorted->num].name, f_format(buf2));
			sorted = sorted->next;
		}
		fprintf(gtotal, "%s\n", verss);

		printf("Done!\n");
		fclose(gtotal);
	}

	if (strcmp(hoss, "gpwkup") == 0)
	{
		printf("Lets do gpwkup ...");

		gtotal = fopen("total_gpwkup.txt", "wt");
		if (!gtotal)
		{
			printf("error at total_gpwkup.txt, exiting\n");
			exit(1);
		}

		for (i = 0; i < maxuser; i++) tmptop[i] = gp[i].wkup_bytes;

		sorted = sort_top(tmptop);
		dog = 0;

		while (sorted)
		{
			dog++;

			bzero(buf2, sizeof(buf2));
			sprintf(buf2, "%llu", gp[sorted->num].wkup_bytes);
			fprintf(gtotal, " %3d  %-10s %20s\n", dog, gp[sorted->num].name, f_format(buf2));
			if (gscore < gp[sorted->num].wkup_bytes)
			{
				gnum = sorted->num;
				gscore = gp[sorted->num].wkup_bytes;
			}
			sorted = sorted->next;
		}

		High_Score_Check("gpwkup", gnum, gscore);

		bzero(buf2, sizeof(buf2));
		sprintf(buf2, "%llu", HS.hwkup_group_bytes);
		fprintf(gtotal, "highscore group: %s - %s bytes\n", HS.hwkup_group, f_format(buf2));
		fprintf(gtotal, "%s\n", verss);

		printf("Done!\n");
		fclose(gtotal);
	}

	if (strcmp(hoss, "gpwkdn") == 0)
	{
		printf("Lets do gpwkdn ...");

		gtotal = fopen("total_gpwkdn.txt", "wt");
		if (!gtotal)
		{
			printf("error at total_gpwkdn.txt, exiting\n");
			exit(1);
		}

		for (i = 0; i < maxuser; i++) tmptop[i] = gp[i].wkdn_bytes;

		sorted = sort_top(tmptop);
		dog = 0;

		while (sorted)
		{
			dog++;

			bzero(buf2, sizeof(buf2));
			sprintf(buf2, "%llu", gp[sorted->num].wkdn_bytes);
			fprintf(gtotal, " %3d  %-10s %20s\n", dog, gp[sorted->num].name, f_format(buf2));
			if (gscore < gp[sorted->num].wkdn_bytes)
			{
				gnum = sorted->num;
				gscore = gp[sorted->num].wkdn_bytes;
			}
			sorted = sorted->next;
		}

		High_Score_Check("gpwkdn", gnum, gscore);

		bzero(buf2, sizeof(buf2));
		sprintf(buf2, "%llu", HS.hwkdn_group_bytes);
		fprintf(gtotal, "worst group: %s - %s bytes\n", HS.hwkdn_group, f_format(buf2));
		fprintf(gtotal, "%s\n", verss);

		printf("Done!\n");
		fclose(gtotal);
	}

	if (strcmp(hoss, "gpmup") == 0)
	{
		printf("Lets do gpmup ...");

		gtotal = fopen("total_gpmup.txt", "wt");
		if (!gtotal)
		{
			printf("error at total_gpmup.txt, exiting\n");
			exit(1);
		}

		for (i = 0; i < maxuser; i++) tmptop[i] = gp[i].mup_bytes;

		sorted = sort_top(tmptop);
		dog = 0;

		while (sorted)
		{
			dog++;

			bzero(buf2, sizeof(buf2));
			sprintf(buf2, "%llu", gp[sorted->num].mup_bytes);
			fprintf(gtotal, " %3d  %-10s %20s\n", dog, gp[sorted->num].name, f_format(buf2));
			if (gscore < gp[sorted->num].mup_bytes)
			{
				gnum = sorted->num;
				gscore = gp[sorted->num].mup_bytes;
			}
			sorted = sorted->next;
		}

		High_Score_Check("gpmup", gnum, gscore);

		bzero(buf2, sizeof(buf2));
		sprintf(buf2, "%llu", HS.hmup_group_bytes);
		fprintf(gtotal, "highscore group: %s - %s bytes\n", HS.hmup_group, f_format(buf2));
		fprintf(gtotal, "%s\n", verss);

		printf("Done!\n");
		fclose(gtotal);
	}

	if (strcmp(hoss, "gpmdn") == 0)
	{
		printf("Lets do gpmdn ...");

		gtotal = fopen("total_gpmdn.txt", "wt");
		if (!gtotal)
		{
			printf("error at total_gpmdn.txt, exiting\n");
			exit(1);
		}

		for (i = 0; i < maxuser; i++) tmptop[i] = gp[i].mdn_bytes;

		sorted = sort_top(tmptop);
		dog = 0;

		while (sorted)
		{
			dog++;

			bzero(buf2, sizeof(buf2));
			sprintf(buf2, "%llu", gp[sorted->num].mdn_bytes);
			fprintf(gtotal, " %3d  %-10s %20s\n", dog, gp[sorted->num].name, f_format(buf2));
			if (gscore < gp[sorted->num].mdn_bytes)
			{
				gnum = sorted->num;
				gscore = gp[sorted->num].mdn_bytes;
			}
			sorted = sorted->next;
		}

		High_Score_Check("gpmdn", gnum, gscore);

		bzero(buf2, sizeof(buf2));
		sprintf(buf2, "%llu", HS.hmdn_group_bytes);
		fprintf(gtotal, "worst group: %s - %s bytes\n", HS.hmdn_group, f_format(buf2));
		fprintf(gtotal, "%s\n", verss);

		printf("Done!\n");
		fclose(gtotal);
	}

	return 0;
}

/*

                announcer for the bot

 */
int Announce_Winner(char *toh, char *auser, unsigned long long aubytes, unsigned long long sitebytes)
{
	FILE *ann;

	char bufa1[80], bufa2[80];

	ann = fopen(bot_path, "wt");
	if (!ann)
	{
		printf("error at %s file!, exiting\n", bot_path);
		exit(1);
	}

	bzero(bufa1, sizeof(bufa1));
	bzero(bufa2, sizeof(bufa2));
	sprintf(bufa1, "%llu", aubytes);
	sprintf(bufa2, "%llu", sitebytes);

	fprintf(ann, "%s win %s %s bytes, total %s bytes.", toh, auser, f_format(bufa1), f_format(bufa2));
	fclose(ann);

	return 0;
}

/*

        weektop highscores

 */
int Week_Winners()
{
	FILE *wbase;
	FILE *wsfile;
	FILE *wstats;

	char bufe1[1024];
	char bufe2[80];
	char bufe3[80];
	char bufe4[80];

	wbase = fopen("weekscores.dat", "rb");
	if (!wbase)
	{
		printf("error at weekscores.dat, exiting\n");
		exit(1);
	}

	wsfile = fopen("total_ws.txt", "wt");
	if (!wsfile)
	{
		printf("Error at total_ws.txt! exiting.\n");
		exit(1);
	}

	wstats = fopen("total_wscores.txt", "wt");
	if (!wstats)
	{
		printf("Error at total_wscores.txt! exiting.\n");
		exit(1);
	}

	fread(&WS, sizeof(WeekScores), 1, wbase);

#ifdef DEBUG
	printf("going into wbase loop...\n");
#endif

	fprintf(wsfile, "Date of the win  wkup user         wkup bytes      wkdn user          wkdn bytes\n");
	fprintf(wstats, "Date            wkup total               wkdn total       combined\n");

	while (!feof(wbase))
	{
/*
   printf("\nWeekScore records for %s:
   wkup user: %s
   wkup bytes: %llu
   wkdn user: %s
   wkdn bytes: %llu
   wkup group: %s
   wkup group bytes: %llu
   wkdn group: %s
   wkdn group bytes: %llu
   wkup total: %llu
   wkdn total: %llu\n",Time_Check(WS.weektime),WS.wkup_user,WS.wkup_user_bytes,
   WS.wkdn_user,WS.wkdn_user_bytes,WS.wkup_group,WS.wkup_group_bytes,
   WS.wkdn_group,WS.wkdn_group_bytes,WS.weekup_total,WS.weekdn_total);
 */

// first use of Time_Check function 01-23-12

		if ((WS.wkup_user_bytes > 0 || WS.wkdn_user_bytes > 0))
		{
			/* write the weektop user wins */
			sprintf(bufe2, "%llu", WS.wkup_user_bytes);
			sprintf(bufe3, "%llu", WS.wkdn_user_bytes);

			sprintf(bufe1, "%s. wkup: %-10s %15s. wkdn: %-10s %15s\n", Time_Check2(WS.weektime), WS.wkup_user, f_format(bufe2), WS.wkdn_user, f_format(bufe3));

			fprintf(wsfile, "%s", bufe1);
		}

		if ((WS.weekup_total > 0 || WS.weekdn_total > 0))
		{
			/* write the week scores all */
			sprintf(bufe2, "%llu", WS.weekup_total);
			sprintf(bufe3, "%llu", WS.weekdn_total);
			sprintf(bufe4, "%llu", (WS.weekup_total + WS.weekdn_total));

			sprintf(bufe1, "%s. wkups: %15s. wkdns: %15s. %15s\n", Time_Check2(WS.weektime), f_format(bufe2), f_format(bufe3), f_format(bufe4));

			fprintf(wstats, "%s", bufe1);
		}

		fread(&WS, sizeof(WeekScores), 1, wbase);
	}

#ifdef DEBUG
	printf("Done!\n");
#endif

	fprintf(wsfile, "%s\n", verss);

	fclose(wbase);
#ifdef DEBUG
	printf("Closed wbase file.\n");
#endif
	fclose(wsfile);
#ifdef DEBUG
	printf("Closed wsfile file.\n");
#endif
	fclose(wstats);
#ifdef DEBUG
	printf("Closed wstats file.\nWeek_Winners() is now DONE!\n");
#endif

	return 0;
}

/*

        Monthtop highscores

 */
int Month_Winners()
{
	FILE *mbase;
	FILE *msfile;
	FILE *mstats;

	char bufe1[1024], bufe2[80], bufe3[80], bufe4[80];

#ifdef DEBUG
	printf("At Month_Winners() ...\n");
#endif

	mbase = fopen("monthscores.dat", "rb");
	if (!mbase)
	{
		printf("error at monthscores.dat, exiting\n");
		exit(1);
	}

	msfile = fopen("total_ms.txt", "wt");
	if (!msfile)
	{
		printf("error at total_ms.txt, exiting\n");
		exit(1);
	}

	mstats = fopen("total_mscores.txt", "wt");
	if (!mstats)
	{
		printf("error at total_mscores.txt, exiting\n");
		exit(1);
	}

#ifdef DEBUG
	printf("Month_Winners() - files open...\n");
#endif

	fread(&MS, sizeof(MonthScores), 1, mbase);

	fprintf(msfile, "Date of the win  mup user         mup bytes       mdn user         mdn bytes\n");
	fprintf(mstats, "Month date     mup                   mdn              combined\n");

	while (!feof(mbase))
	{
/*
   printf("\nMonthScore records for %s:
   mup user: %s
   mup bytes: %llu
   mdn user: %s
   mdn bytes: %llu
   mup group: %s
   mup group bytes: %llu
   mdn group: %s
   mdn group bytes: %llu\n",Time_Check(MS.monthtime),MS.mup_user,MS.mup_user_bytes,
   MS.mdn_user,MS.mdn_user_bytes,MS.mup_group,MS.mup_group_bytes,
   MS.mdn_group,MS.mdn_group_bytes);
 */

// second use of Time_Check function 01-23-12

/* user wins */
		sprintf(bufe2, "%llu", MS.mup_user_bytes);
		sprintf(bufe3, "%llu", MS.mdn_user_bytes);

		sprintf(bufe1, "%s. mup: %-10s %15s. mdn: %-10s %15s\n", Time_Check2(MS.monthtime), MS.mup_user, f_format(bufe2), MS.mdn_user, f_format(bufe3));

		fprintf(msfile, "%s", bufe1);

/* total scores */
		sprintf(bufe2, "%llu", MS.mup_total);
		sprintf(bufe3, "%llu", MS.mdn_total);
		sprintf(bufe4, "%llu", (MS.mup_total + MS.mdn_total));

		sprintf(bufe1, "%s. mup: %15s. mdn: %15s. %15s\n", Time_Check2(MS.monthtime), f_format(bufe2), f_format(bufe3), f_format(bufe4));

		fprintf(mstats, "%s", bufe1);

		fread(&MS, sizeof(MonthScores), 1, mbase);
	}

#ifdef DEBUG
	printf("Month_Winners() - feof mbase loop done...\n");
#endif

	fprintf(msfile, "%s\n", verss);

	fclose(mbase);

#ifdef DEBUG
	printf("Month_Winners() - mbase file closed...\n");
#endif

	fclose(msfile);

#ifdef DEBUG
	printf("Month_Winners() - msfile file closed. all done!.\n");
#endif

	return 0;
}

/*

        Yeartop highscores

   typedef struct {
        int yeartime;
        char yearup_user[25];
        char yearup_user_locat[25];
        unsigned long long yearup_user_bytes;

        char yearup_group[14];
        unsigned long long yearup_group_bytes;

        char yeardn_user[25];
        char yeardn_user_locat[25];
        unsigned long long yeardn_user_bytes;

        char yeardn_group[14];
        unsigned long long yeardn_group_bytes;

        unsigned long long yearup_total;
        unsigned long long yeardn_total;
   } YearScores;

   YearScores YS;

 */
int Year_Winners()
{
	FILE *ybase;
	FILE *ysfile;
	FILE *ystats;

	char bufe1[1024], bufe2[80], bufe3[80], bufe4[80];

#ifdef DEBUG
	printf("At Year_Winners() ...\n");
#endif

	ybase = fopen("yearscores.dat", "rb");
	if (!ybase)
	{
		printf("error at yearscores.dat, exiting\n");
		exit(1);
	}

	ysfile = fopen("total_ys.txt", "wt");
	if (!ysfile)
	{
		printf("error at total_ys.txt, exiting\n");
		exit(1);
	}

	ystats = fopen("total_yscores.txt", "wt");
	if (!ystats)
	{
		printf("error at total_yscores.txt, exiting\n");
		exit(1);
	}

#ifdef DEBUG
	printf("Yeartop_Winners() - files open...\n");
#endif

	fread(&YS, sizeof(YearScores), 1, ybase);

	fprintf(ysfile, "Date of the win  year user         year up bytes       year down user         year down bytes\n");
	fprintf(ystats, "Year date     year up                   year down              combined\n");

	while (!feof(ybase))
	{
/* user wins */
		sprintf(bufe2, "%llu", YS.yearup_user_bytes);
		sprintf(bufe3, "%llu", YS.yeardn_user_bytes);

		sprintf(bufe1, "%s. year up: %-10s %15s. year down: %-10s %15s\n", Time_Check2(YS.yeartime), YS.yearup_user, f_format(bufe2), YS.yeardn_user, f_format(bufe3));

		fprintf(ysfile, "%s", bufe1);

/* total scores */
		sprintf(bufe2, "%llu", YS.yearup_total);
		sprintf(bufe3, "%llu", YS.yeardn_total);
		sprintf(bufe4, "%llu", (YS.yearup_total + YS.yeardn_total));

		sprintf(bufe1, "%s. year up: %15s. year dn: %15s. %15s\n", Time_Check2(YS.yeartime), f_format(bufe2), f_format(bufe3), f_format(bufe4));

		fprintf(ystats, "%s", bufe1);

		fread(&YS, sizeof(YearScores), 1, ybase);
	}

#ifdef DEBUG
	printf("Year_Winners() - feof ybase loop done...\n");
#endif

	fprintf(ysfile, "%s\n", verss);

	fclose(ybase);

#ifdef DEBUG
	printf("Year_Winners() - ybase file closed...\n");
#endif

	fclose(ysfile);

#ifdef DEBUG
	printf("Year_Winners() - ysfile file closed. all done!.\n");
#endif

	return 0;
}

int main(int argv, char *argc[])
{
	Footer();
	printf("%s\n", verss);

	CFG_Read();

	glob(user_path, 0, 0, &gl);

	File_Select();

	GroupTop();

	All_Bytes_Stats();

	YearTopGenerator();

	/* users */
	Totals_Create("alup");
	Totals_Create("aldn");
	Totals_Create("wkup");
	Totals_Create("wkdn");
	Totals_Create("mup");
	Totals_Create("mdn");
	Totals_Create("yearup");
	Totals_Create("yeardn");

	/* groups */
	Totals_Groups("gpup");
	Totals_Groups("gpdn");
	Totals_Groups("gpwkup");
	Totals_Groups("gpwkdn");
	Totals_Groups("gpmup");
	Totals_Groups("gpmdn");

	/* all weektop wins */
	Week_Winners();

	/* all monthtop wins */
	Month_Winners();

	/* all yeartop wins */
	Year_Winners();

	if (argv == 2)
	{
		if (strstr(argc[1], "/yeartop"))
			Year_Top_Init();
		if (strstr(argc[1], "/weektop"))
			DataBase_WEEK();
		if (strstr(argc[1], "/monthtop"))
			DataBase_MONTH();
	}

	globfree(&gl);

	return 0;
}
