
static void Destroy (GtkWidget *window, gpointer data) {
	gtk_main_quit ();
}

static gboolean DeleteEvent (GtkWidget *window, GdkEvent *event, gpointer data) {
	return FALSE;
}

static void button1Clicked (GtkWidget *window, gpointer data) {
	builder = gtk_builder_new();
	gtk_builder_add_from_file (builder, "home.ui", NULL);

	gtk_widget_hide(GTK_WIDGET(form1.window));
	gtk_widget_show(GTK_WIDGET(form2.window));
	
	gtk_label_set_label(GTK_LABEL(form2.label1), "");
}

static void button2Clicked (GtkWidget *window, gpointer data) {
	gtk_window_set_title(GTK_WINDOW(form3.window), "Date Convert");
	gtk_widget_hide(GTK_WIDGET (form1.window));
	gtk_widget_show(GTK_WIDGET(form3.window));
	
	gtk_label_set_label(GTK_LABEL(form3.label1), "");
}


void form1UiDesign(GtkBuilder *builder) {
	form1.window = GTK_WIDGET (gtk_builder_get_object (builder, "window1"));
	form1.button1 = GTK_WIDGET (gtk_builder_get_object (builder, "button1"));
	form1.button2 = GTK_WIDGET (gtk_builder_get_object (builder, "button2"));
}

void form1SignalsConnector(){
	g_signal_connect (G_OBJECT (form1.window), "destroy", G_CALLBACK (Destroy), NULL);
	g_signal_connect (G_OBJECT (form1.window), "delete_event", G_CALLBACK (DeleteEvent), NULL);	
	g_signal_connect (G_OBJECT (form1.button1), "clicked", G_CALLBACK (button1Clicked), form1.button1);
	g_signal_connect (G_OBJECT (form1.button2), "clicked", G_CALLBACK (button2Clicked), form1.button2);
}
