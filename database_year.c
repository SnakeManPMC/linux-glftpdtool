/*

        Yeartop database creation

 */
int DataBase_YEAR()
{
	FILE *ybase;
	int dog = 0;

	ybase = fopen("yearscores.dat", "ab");
	if (!ybase)
	{
		printf("error at yearscores.dat, exiting\n");
		exit(1);
	}

	for (i = 0; i < maxuser; i++) tmptop[i] = db[i].mup_bytes;

	sorted = sort_top(tmptop);

	YS.monthtime = 0;
	YS.monthtime = time(0);
	bzero(YS.mup_user, sizeof(YS.mup_user));
	sprintf(YS.mup_user, "%s", db[sorted->num].username);
	bzero(YS.mup_user_locat, sizeof(YS.mup_user_locat));
	sprintf(YS.mup_user_locat, "%s", db[sorted->num].location);
	YS.mup_user_bytes = 0;
	YS.mup_user_bytes = db[sorted->num].mup_bytes;
	YS.mup_total = 0;

	for (i = 0; i < maxuser; i++) tmptop[i] = db[i].mup_bytes;

	sorted = sort_top(tmptop);
	dog = 0;

	while (sorted)
	{
		dog++;

		YS.mup_total += db[sorted->num].mup_bytes;
		sorted = sorted->next;
	}

#ifdef DEBUG
	printf("year up winner user: %s - %s - %llu bytes\n", db[sorted->num].username, db[sorted->num].location, db[sorted->num].mup_bytes);
#endif

	for (i = 0; i < maxuser; i++) tmptop[i] = db[i].mdn_bytes;

	sorted = sort_top(tmptop);

	bzero(YS.mdn_user, sizeof(YS.mdn_user));
	sprintf(YS.mdn_user, "%s", db[sorted->num].username);
	bzero(YS.mdn_user_locat, sizeof(YS.mdn_user_locat));
	sprintf(YS.mdn_user_locat, "%s", db[sorted->num].location);
	YS.mdn_user_bytes = 0;
	YS.mdn_user_bytes = db[sorted->num].mdn_bytes;
	YS.mdn_total = 0;

	for (i = 0; i < maxuser; i++) tmptop[i] = db[i].mdn_bytes;

	sorted = sort_top(tmptop);
	dog = 0;

	while (sorted)
	{
		dog++;

		YS.mdn_total += db[sorted->num].mdn_bytes;
		sorted = sorted->next;
	}

#ifdef DEBUG
	printf("year dn winner user: %s - %s - %llu bytes\n", db[sorted->num].username, db[sorted->num].location, db[sorted->num].mdn_bytes);
#endif

	for (i = 0; i < maxuser; i++) tmptop[i] = gp[i].mup_bytes;

	sorted = sort_top(tmptop);

	bzero(YS.mup_group, sizeof(YS.mup_group));
	sprintf(YS.mup_group, "%s", gp[sorted->num].name);
	YS.mup_group_bytes = 0;
	YS.mup_group_bytes = gp[sorted->num].mup_bytes;

	for (i = 0; i < maxuser; i++) tmptop[i] = gp[i].mdn_bytes;

	sorted = sort_top(tmptop);

	bzero(YS.mdn_group, sizeof(YS.mdn_group));
	sprintf(YS.mdn_group, "%s", gp[sorted->num].name);
	YS.mdn_group_bytes = 0;
	YS.mdn_group_bytes = gp[sorted->num].mdn_bytes;

	fwrite(&YS, sizeof(YearScores), 1, ybase);
	fclose(ybase);

	/* bot announce file making: user - bytes - yearup total*/
	Announce_Winner("yearup", YS.yearup_user, YS.yearup_user_bytes, YS.yearup_total);

	return 0;
}
