/*

        Glftpd Tool aka Luopio Daemon Tool (c) PMC 2003 - 2012

 */

FILE *userfile;

glob_t gl;

char U_File[20], verss[256];
int i = 0, x = 0, maxuser = 0, maxgroup = 0;
unsigned long long All_UL_Bytes;
unsigned long long All_DL_Bytes;

char user_path[80]; /* path to the user files */
char top_path[80];  /* path to the top files  */
char php_path[80];  /* path to the php file   */
char bot_path[80];  /* path to the bot announce file */

int alup_unum = 10;   /* max alup users */
int aldn_unum = 10;   /* max aldn users */
int wkup_unum = 10;   /* max wkup users */
int wkdn_unum = 10;   /* max wkdn users */
int mup_unum = 10;    /* max mup users  */
int mdn_unum = 10;    /* max mdn users  */
int yearup_unum = 10; /* max yearup users */
int yeardn_unum = 10; /* max yeardn users */

/*

        basic userfile shit to GLTOOL

 */
typedef struct
{
	char username[25];
	char location[25];
	char group[25];
	unsigned long long ul_bytes;
	long ul_files;
	unsigned long long dl_bytes;
	long dl_files;
	unsigned long long wkup_bytes;
	long wkup_files;
	unsigned long long wkdn_bytes;
	long wkdn_files;
	unsigned long long mup_bytes;
	long mup_files;
	unsigned long long mdn_bytes;
	long mdn_files;
	unsigned long long yeartop_up;
	unsigned long long yeartop_dn;
} Database;

/*

        alltime highscores

 */
typedef struct {
	char hwkup_user[25];
	unsigned long long hwkup_bytes;
	int hwkup_user_date;
	char hwkup_group[10];
	unsigned long long hwkup_group_bytes;
	int hwkup_group_date;
	char hwkdn_user[25];
	unsigned long long hwkdn_bytes;
	int hwkdn_user_date;
	char hwkdn_group[10];
	unsigned long long hwkdn_group_bytes;
	int hwkdn_group_date;
	char hmup_user[25];
	unsigned long long hmup_bytes;
	int hmup_user_date;
	char hmup_group[10];
	unsigned long long hmup_group_bytes;
	int hmup_group_date;
	char hmdn_user[25];
	unsigned long long hmdn_bytes;
	int hmdn_user_date;
	char hmdn_group[10];
	unsigned long long hmdn_group_bytes;
	int hmdn_group_date;

/* newstuff year */
	char hyearup_user[25];
	unsigned long long hyearup_user_bytes;
	int hyearup_user_date;
	char hyeardn_user[25];
	unsigned long long hyeardn_user_bytes;
	int hyeardn_user_date;

	unsigned long long site_wkup;
	int site_wkup_date;
	unsigned long long site_wkdn;
	int site_wkdn_date;
	unsigned long long site_mup;
	int site_mup_date;
	unsigned long long site_mdn;
	int site_mdn_date;

/* newstuff year */
	unsigned long long site_yeartop_up;
	int site_yeartop_up_date;
	unsigned long long site_yeartop_dn;
	int site_yeartop_dn_date;
} Scores;

Scores HS;

/*

        weektop highscores

 */
typedef struct {
	int weektime;
	char wkup_user[25];
	char wkup_user_locat[25];
	unsigned long long wkup_user_bytes;

	char wkup_group[14];
	unsigned long long wkup_group_bytes;

	char wkdn_user[25];
	char wkdn_user_locat[25];
	unsigned long long wkdn_user_bytes;

	char wkdn_group[14];
	unsigned long long wkdn_group_bytes;

	unsigned long long weekup_total;
	unsigned long long weekdn_total;
} WeekScores;

WeekScores WS;

/*

        monthtop highscores

 */
typedef struct {
	int monthtime;
	char mup_user[25];
	char mup_user_locat[25];
	unsigned long long mup_user_bytes;

	char mup_group[14];
	unsigned long long mup_group_bytes;

	char mdn_user[25];
	char mdn_user_locat[25];
	unsigned long long mdn_user_bytes;

	char mdn_group[14];
	unsigned long long mdn_group_bytes;

	unsigned long long mup_total;
	unsigned long long mdn_total;
} MonthScores;

MonthScores MS;

/*

        yeartop highscores

 */
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

/*

        group struct

 */
typedef struct {
	char name[14];                 /*  group name               */
	char fullname[30];             /*  full name of the group   */
	int num_members;               /*  number of members        */
	unsigned long long alup_bytes; /*  alltime bytes uploaded   */
	long alup_files;               /*  alltime files uploaded   */
	unsigned long long aldn_bytes; /*  alltime bytes downloaded */
	long aldn_files;               /*  alltime files downloaded */
	unsigned long long wkup_bytes; /*  weekly uploaded bytes    */
	long wkup_files;               /*  weekly uploaded files    */
	unsigned long long wkdn_bytes; /*  weekly downloaded bytes  */
	long wkdn_files;               /*  weekly downloaded files  */
	unsigned long long mup_bytes;  /*  monthly uploaded bytes   */
	long mup_files;                /*  monthly uploaded files   */
	unsigned long long mdn_bytes;  /*  monthly downloaded bytes */
	long mdn_files;                /*  monthly downloaded files */
} group;                               /*  120 groups available ;)  */

Time_Check(int fish)
{
	struct tm *tm;
	time_t t;

	char bah[60];

	t = fish;
	tm = localtime(&t);

	sprintf(bah, "%2.2d-%2.2d-%2.2d - %2.2d:%2.2d", tm->tm_mon + 1, tm->tm_mday, tm->tm_year % 100, tm->tm_hour, tm->tm_min);

	return bah;
}

Time_Check2(int dosh)
{
	struct tm *tm;
	time_t t;

	char bah2[60];

	t = dosh;
	tm = localtime(&t);

	sprintf(bah2, "%2.2d-%2.2d-%2.2d", tm->tm_mon + 1, tm->tm_mday, tm->tm_year % 100);

	return bah2;
}
