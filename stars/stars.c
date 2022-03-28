/* vim: ts=4 sts=4 sw=4 noet: 
*/
#include <proto/intuition.h>
#include <proto/dos.h>
#include <intuition/screens.h>
#include <graphics/rastport.h>
#include <hardware/cia.h>
#include <stdio.h>

#define BLACK 0x000
#define WHITE 0xfff

#define NUM_STARS 100
#define Z_MAX 256

#define SCREEN_X 320
#define SCREEN_Y 256

/* ticks, 50 per second = 20 ms */
#define UPDATE_DELAY 0
/*#define SPEED_Z (UPDATE_DELAY*3) */
#define SPEED_Z 6
#define NUM_COLORS 16
#define MAX_COLOR (NUM_COLORS - 1)

#define CENTER_X (SCREEN_X / 2)
#define CENTER_Y (SCREEN_Y / 2)


__far extern struct CIA ciaa;

static struct Screen *screen0 = NULL;
static UWORD colortable[NUM_COLORS] = {};

struct Star {
	WORD x;
	WORD y;
	WORD z;
};

static struct Star stars[NUM_STARS] = {};

static struct Screen * initScreen();
static void drawStar(struct RastPort *rp, struct Star *star);
static void initStar(struct Star *star);
static void update();
static BOOL isMouseClicked();

void main() {

	screen0 = initScreen();
	if (screen0 == NULL) {
		printf("Failed to create screen!\n");
		return;
	}

	for (int i = 0; i < NUM_STARS; i++) {
		initStar(&stars[i]);
		drawStar(&screen0->RastPort, &stars[i]);
	}

	while (1) {
		update();
		if (isMouseClicked()) {
			printf("Mouse clicked, exiting\n");
			break;
		}
		if (UPDATE_DELAY)
			Delay(UPDATE_DELAY);

		WaitTOF();
	}

	printf("bye\n");

	CloseScreen(screen0);
}

static struct Screen * initScreen() {

	struct Screen *screen;
	screen = OpenScreenTags(NULL,
		SA_Left, 0, SA_Top, 0, SA_Width, SCREEN_X, SA_Height, SCREEN_Y,
		SA_Depth, 5,
		SA_Quiet, TRUE,
		SA_Type, CUSTOMSCREEN, TAG_DONE);

	if (NULL == screen) {
		return NULL;
	}

	/* init colors, 0 = BLACK, 15 = WHITE */
	for (int i=0; i < NUM_COLORS; i++) {
		colortable[i] = 0x111 * i;
	}
	LoadRGB4(&screen->ViewPort, colortable, NUM_COLORS);
	ScreenToFront(screen);
	return screen;
}

static void initStar(struct Star *star) {

	WORD maxX = SCREEN_X;
	WORD maxY = SCREEN_Y;
	star->x = RangeRand(maxX * 2) - maxX;
	star->y = RangeRand(maxY * 2) - maxY;
	if (star->x == 0 && star->y == 0) {
		star->x = 1;
	}
	star->z = Z_MAX;
}

static void drawStar(struct RastPort *rp, struct Star *star) {
	WORD gx, gy;
	/* calculate brightness */
	UWORD color = (Z_MAX - star->z) * MAX_COLOR / Z_MAX + 1;
	if (color >= MAX_COLOR) {
		color = MAX_COLOR;
	}
	SetAPen(rp, color);
	gx = star->x * 256 / star->z + CENTER_X;
	gy = star->y * 256 / star->z + CENTER_Y;
	if (gx < SCREEN_X && gx >= 0 && gy < SCREEN_Y && gy >= 0) {
		WritePixel(rp, gx, gy);
	}
	else {
		initStar(star);
	}
}

static void update() {
	/* paint it black */
	SetRast(&screen0->RastPort, 0);
	for (int i = 0; i < NUM_STARS; i++) {
		drawStar(&screen0->RastPort, &stars[i]);
		stars[i].z -= SPEED_Z;
		if (stars[i].z == 0) {
			stars[i].z = -1;
		}
	}
}

static BOOL isMouseClicked() {
	static BOOL mouseClicked = FALSE;
	BOOL ciaStatus = (ciaa.ciapra & CIAF_GAMEPORT0) != 0;

	if (!mouseClicked && ciaStatus) {
		mouseClicked = TRUE;
		return FALSE;
	}
	else if (mouseClicked && !ciaStatus) {
		mouseClicked = FALSE;
		return TRUE;
	}
	else {
		return FALSE;
	}
}
