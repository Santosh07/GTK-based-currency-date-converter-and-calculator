	char *fullname[] = {" ", "US Dollar", "Argentine Peso", "Australian Dollar", "Bahraini Dinar", "Botswana Pula", "Brazilian Real", "Bruneian Dollar", "Bulgarian Lev", "Canadian Dollar", "Chilean Peso", "Chinese Yuan Renminbi", "Colombian Peso", "Croatian Kuna", "Czech Koruna", "Danish Krone", "Euro", "Hong Kong Dollar", 		"Hungarian Forint", "Icelandic Krona", "Indian Rupee", "Indonesian Rupiah", "Iranian Rial", "Israeli Shekel", "Japanese Yen", 			"Kazakhstani Tenge", "South Korean Won", "Kuwaiti Dinar", "Latvian Lat", "Libyan Dinar", "Lithuanian Litas", "Malaysian Ringgit", 			"Mauritian Rupee","Mexican Peso", "Nepalese Rupee", "New Zealand Dollar", "Norwegian Krone", "Omani Rial", "Pakistani Rupee", 			"Philippine Peso", "Polish Zloty", "Qatari Riyal", "Romanian New Leu", "Russian Ruble", "Saudi Arabian Riyal", "Singapore Dollar", 			"South African Rand", "Sri Lankan Rupee", "Swedish Krona", "Swiss Franc", "Taiwan New Dollar", "Thai Baht", "Trinidadian Dollar", 			"Turkish Lira", "Emirati Dirham", "British Pound", "Venezuelan Bolivar" };

char line[100];
	
void form2Execute(char *);

static gboolean DeleteEvent1 (GtkWidget *window, GdkEvent *event, gpointer data) {
	gtk_widget_hide(GTK_WIDGET(form2.window));
	gtk_widget_show(GTK_WIDGET(form1.window));
	
	return TRUE;
}

static void button3Converter (GtkWidget *window, gpointer data) {
	char *ptr1, *ptr2;
	int i , from, to;
	char command[255] = "";
	const char *amount;
	int check;
	
	ptr1 = (char *)gtk_combo_box_text_get_active_text (GTK_COMBO_BOX_TEXT(form2.combobox1));
	ptr2 = (char *)gtk_combo_box_text_get_active_text (GTK_COMBO_BOX_TEXT(form2.combobox2));
	amount = gtk_entry_get_text(GTK_ENTRY(form2.textBox1));
	
	for (i = 0; i <= 56; i++) {
		if (!strcmp(ptr1, fullname[i])){
			from = i;
		}
		if (!strcmp(ptr2, fullname[i])) {
			to = i;
		}
	}

	check = (int)gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON(form2.checkBox1));
	
	if (check){
		sprintf (command, "./currencyconverter %d %d %s \n", from, to, amount);
	} else {
		sprintf (command, "./currencyconverter %d %d %s -nd \n", from, to, amount);
	}
	
	form2Execute(command);
	//printf("%s\n", line);
	gtk_label_set_text (GTK_LABEL(form2.label1), line);
	
}	
		
void form2SignalsConnector() {
	g_signal_connect (G_OBJECT (form2.window), "delete_event", G_CALLBACK (DeleteEvent1), NULL);
	g_signal_connect (G_OBJECT (form2.buttonConvert), "clicked", G_CALLBACK (button3Converter), form2.button3);
}


void form2UiDesign(GtkBuilder *builder) {
	form2.window = GTK_WIDGET (gtk_builder_get_object (builder, "window2"));
	form2.label1 = GTK_WIDGET (gtk_builder_get_object (builder, "label1"));
	form2.buttonConvert = GTK_WIDGET (gtk_builder_get_object (builder, "button3"));
	form2.combobox1 = GTK_WIDGET (gtk_builder_get_object (builder, "comboboxtext1"));
	form2.combobox2 = GTK_WIDGET (gtk_builder_get_object (builder, "comboboxtext8"));
	form2.textBox1 = GTK_WIDGET (gtk_builder_get_object (builder, "entry1"));
	form2.checkBox1 = GTK_WIDGET (gtk_builder_get_object (builder, "checkbutton1"));
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(form2.checkBox1), TRUE); 
	//form2.combobox1 = gtk_combo_box_text_new ();
	int i;
	 
	//printf("HERE \n");
	for (i = 1; i <= 56; i++) {
		gtk_combo_box_text_append (GTK_COMBO_BOX_TEXT(form2.combobox1), NULL,  fullname[i]);
		gtk_combo_box_text_append (GTK_COMBO_BOX_TEXT(form2.combobox2), NULL,  fullname[i]);
	}	
}

void form2Execute(char *command) {
	FILE *file;
	
	file = popen(command, "r");
	if (file == NULL) {
		printf("Reinstall program\n");
		return;
	}	
	getlines(file);		
}

int getlines(FILE *ptr) {
	int i;
	char s[2];

	for (i = 0;(fgets(s, sizeof(s), ptr) != NULL) && s[0] != '\n'; i++) {
			line[i] = s[0];			
	}
	line[i] = '\0';
	return i;
}		 

	
	
	




