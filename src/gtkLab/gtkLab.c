#include <gtk/gtk.h> 
#include <time.h>
#include <stdlib.h>

static void flip(GtkWidget *window, GtkWidget *box, GtkWidget *headsImageBox, GtkWidget *tailsImageBox){
	if(rand() % 2 == 0){
		// gtk_widget_show(GTK_WIDGET(headsImageBox));
		// gtk_widget_hide(GTK_WIDGET(tailsImageBox));
		gtk_widget_hide(GTK_WIDGET(box));
	// image = gtk_image_new_from_file("heads.jpg");
	// gtk_container_add(GTK_CONTAINER(box), image);
	} else {
		gtk_widget_show(GTK_WIDGET(box));
		// gtk_widget_show(GTK_WIDGET(tailsImageBox));
		// gtk_widget_hide(GTK_WIDGET(headsImageBox));
	}
}

int main (int argc, char *argv[]){
	GtkWidget *window, *label, *button, *button_box, *box, *headsImage, *tailsImage, *headsImageBox, *tailsImageBox;

	/* Initialize GTK+ and all of its supporting libraries. */
	gtk_init (&argc, &argv);

	/* Create new window, give it a title and display to the user. */
	window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
	gtk_widget_set_size_request (window, 800, 400);
	label = gtk_label_new("Pongs");
	button_box = gtk_button_box_new (GTK_ORIENTATION_HORIZONTAL);
	button = gtk_button_new_with_label ("Flip");
	headsImage = gtk_image_new_from_file("heads.jpg");
	tailsImage = gtk_image_new_from_file("tails.jpg");
	headsImageBox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
	tailsImageBox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
	gtk_container_add(GTK_CONTAINER(headsImageBox), headsImage);
	gtk_container_add(GTK_CONTAINER(tailsImageBox), tailsImage);
	gtk_label_set_selectable(GTK_LABEL(label), TRUE);
	// // gtk_window_set_title (GTK_WINDOW (window), "Pings");
	// imageBin = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
	gtk_container_add(GTK_CONTAINER(button_box), button);
	gtk_container_add(GTK_CONTAINER (box), button_box);
	gtk_container_add(GTK_CONTAINER(box), label);
	gtk_container_add(GTK_CONTAINER(box), tailsImageBox);
	gtk_container_add(GTK_CONTAINER(box), headsImageBox);
	gtk_container_add(GTK_CONTAINER(window), box);
	// gtk_container_add(GTK_CONTAINER(button_box),);
	gtk_widget_show_all(window);
	if(rand() % 2 == 0){
		// gtk_widget_show(GTK_WIDGET(headsImageBox));
		// gtk_widget_hide(GTK_WIDGET(tailsImageBox));
		gtk_widget_hide(GTK_WIDGET(box));
	} else {
		// gtk_widget_show(GTK_WIDGET(tailsImageBox));
		// gtk_widget_hide(GTK_WIDGET(headsImageBox));
		gtk_widget_show(GTK_WIDGET(box));
	}
	 g_signal_connect (button, "clicked", G_CALLBACK (flip), NULL);
	/* Hand control over to the main loop. */
	gtk_main ();
	return 0;
}