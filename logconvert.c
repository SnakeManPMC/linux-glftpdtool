#include <stdio.h>
#include <stdlib.h>
#include <glob.h>
#include <time.h>
#include <string.h>
#include "gltool.h"

int main()
{
	FILE *highscores;
	FILE *nhighscores;

	highscores = fopen("highscores.dat", "rb");
	if (!highscores)
	{
		printf("error at highscores.dat, exiting\n");
		exit(1);
	}

	fread(&HS, sizeof(Scores), 1, highscores);
	fclose(highscores);

	nhighscores = fopen("nhighscores.dat", "wb");
	if (!nhighscores)
	{
		printf("error at nhighscores.dat, exiting\n");
		exit(1);
	}

/*
    char hyearup_user[25];
    unsigned long long hyearup_user_bytes;
    int hyearup_user_date;
    char hyeardn_user[25];
    unsigned long long hyeardn_user_bytes;
    int hyeardn_user_date;
 */

	/* yeartop total */
	HS.site_yeartop_up = 2744006847;

	/* yeartop USER UL */
	bzero(HS.hyearup_user, sizeof(HS.hyearup_user));
	sprintf(HS.hyearup_user, "%s", "redzombie");
	HS.hyearup_user_bytes = 1079917737;

	/* yeartop dn total */
	HS.site_yeartop_dn = 2709108433;

	/* yeartop USER DN */
	bzero(HS.hyeardn_user, sizeof(HS.hyearup_user));
	sprintf(HS.hyeardn_user, "%s", "tulsa");
	HS.hyeardn_user_bytes = 433538723;

	fwrite(&HS, sizeof(Scores), 1, nhighscores);
	fclose(nhighscores);

	return 0;
}