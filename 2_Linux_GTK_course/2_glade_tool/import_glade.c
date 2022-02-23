/**************************************************************************** **
 * Copyright (C) 2001-2020 Inhand Networks, Inc.
 **************************************************************************** **/

/* ************************************************************************** **
 *     MODULE NAME            : system
 *     LANGUAGE               : C
 *     TARGET ENVIRONMENT     : Any
 *     FILE NAME              : import_glade.c
 *     FIRST CREATION DATE    : 2022/02/23
 * --------------------------------------------------------------------------
 *     Version                : 1.0
 *     Author                 : EExuke
 *     Last Change            : 2022/02/23
 *     FILE DESCRIPTION       :
** ************************************************************************** */

#include <stdio.h>
#include <gtk/gtk.h>

void prt_label(GtkWidget *button, gpointer window)
{
	const char *text = NULL;

	text = gtk_button_get_label(button);
	g_print("Button %s clicked\n", text);
}

int main(int argc,char *argv[])
{
	const char *text = NULL;

	//1.gtk初始化
	gtk_init(&argc,&argv);

	//2.创建GtkBuilder对象
	GtkBuilder *builder = gtk_builder_new();
	//3.读取test.glade文件的信息，保存在builder中
	if ( !gtk_builder_add_from_file(builder, "./glade_test.glade", NULL)) {
		printf("connot load file!\n");
	}

	//4.获取窗口指针，注意"window1"要和glade里面的标签名词(ID)匹配
	GtkWidget *window = GTK_WIDGET(gtk_builder_get_object(builder, "window"));
	//处理destroy(x)信号
	g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);

	//5.获取按钮指针
	GtkButton *button1 = GTK_BUTTON(gtk_builder_get_object(builder, "button1"));
	g_signal_connect(G_OBJECT(button1), "clicked", G_CALLBACK(prt_label), button1);
	GtkButton *button2 = GTK_BUTTON(gtk_builder_get_object(builder, "button2"));
	g_signal_connect(G_OBJECT(button2), "pressed", G_CALLBACK(prt_label), button2);

	text = gtk_button_get_label(button1);
	printf("text=%s\n", text);

	gtk_widget_show_all(window);

	gtk_main();
	return 0;
}

