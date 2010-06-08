#include <gtk/gtk.h>
#include <glib.h>
#include <stdlib.h>
#include <unistd.h>
#include <hildon/hildon.h>
#include "minimal.h"

GdkImage *image;
HildonAnimationActor *actor;
GtkWidget *window, *drawing;
GdkGC *gc;

static gint X_SIZE = 320;
static gint Y_SIZE = 240;

static gint X_POS = 0;
static gint Y_POS = 56;

/* Using 800x424 as fullscreen */
static gdouble X_SCALE = 2.5;  /* width / X_SIZE */
static gdouble Y_SCALE = 1.77; /* height / Y_SIZE */

#define X_RES           800
#define Y_RES           480

int screen_size;
unsigned short* screenbuffer = NULL;

void hildon_init(int *argc, char ***argv)
{
	gtk_init (argc, argv);

	window = hildon_stackable_window_new ();
	gtk_widget_realize (window);
	gtk_window_fullscreen (GTK_WINDOW(window));
//	actor = HILDON_ANIMATION_ACTOR (hildon_animation_actor_new());

//	gtk_window_resize (GTK_WINDOW (actor), X_SIZE, Y_SIZE);
//	hildon_animation_actor_set_position (actor, X_POS, Y_POS);
//	hildon_animation_actor_set_parent (actor, GTK_WINDOW (window));
//	hildon_animation_actor_set_scale (actor, X_SCALE, Y_SCALE);

	drawing = gtk_image_new ();
	gc = gdk_gc_new (drawing->window);

	gtk_container_add (GTK_CONTAINER (window), drawing);
//	gtk_container_add (GTK_CONTAINER (actor), drawing);

//	gtk_widget_show_all (GTK_WIDGET (actor));
	gtk_widget_show_all (GTK_WIDGET (window));
}

void gp2x_change_res(int w, int h)
{
	printf("gp2x_change_res %dx%d\n", w, h);

	if (w <= 0 || h <= 0)
		return;

	if (image) gdk_image_destroy(image);
	image = gdk_image_new( GDK_IMAGE_FASTEST, gdk_visual_get_system(), w, h );

	screenbuffer = (unsigned short*) image->mem;
	screen_size = w * h * image->bpp;
}

unsigned long gp2x_joystick_read(void)
{
	/* process GTK+ events */
	while (gtk_events_pending())
		gtk_main_iteration();

	return 0;
}

void gp2x_video_RGB_clearscreen16(void)
{
	if (gp2x_screen16 && screen_size)
		memset(gp2x_screen16, 0, screen_size);
}

void updateScreen()
{
	//gdk_draw_image(
	//	drawing->window, gc,
	//	image, 0, 0, 0, 0, -1, -1);
	gtk_image_set_from_image (GTK_IMAGE(drawing), image, NULL);
}
