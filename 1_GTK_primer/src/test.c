#include <gtk/gtk.h>

void print_msg(GtkWidget *widget, gpointer window)
{
	g_print("Button clicked\n");
}

void window_init(GtkWidget **window)
{
	GdkPixbuf *icon = NULL;
	GError *error = NULL;

	//创建窗口
	*window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

	//设置窗口基本属性
	gtk_window_set_title(GTK_WINDOW(*window), "Submenu menu");
	gtk_window_set_default_size(GTK_WINDOW(*window), 460, 300);
	gtk_window_set_position(GTK_WINDOW(*window), GTK_WIN_POS_CENTER);

	//设置程序图标(任务栏)
	icon = gdk_pixbuf_new_from_file("demo.png", &error);
	if (!icon) {
		fprintf(stderr, "%s\n", error->message);
		g_error_free(error);
	}
	gtk_window_set_icon(GTK_WINDOW(*window), icon);

	g_object_unref(icon);
}

void button_item_create(GtkWidget *box)
{
	GtkWidget *button = NULL;
	GtkWidget *halign = NULL;

	//创建按钮
	button = gtk_button_new_with_mnemonic("_B_u_t_t_o_n");
	gtk_widget_set_tooltip_text(button, "Button widget");
	g_signal_connect(button, "clicked", G_CALLBACK(print_msg), NULL);

	/*gtk_box_pack_end(GTK_BOX(box), button, FALSE, TRUE, 0); //将按钮放置在box底部*/
	//按钮layout布局
	halign = gtk_alignment_new(0, 0, 0, 0);
	gtk_container_add(GTK_CONTAINER(halign), button);
	gtk_container_add(GTK_CONTAINER(box), halign);
}

void submenu_item_file_create(GtkWidget *box, GtkWidget *window)
{
	GtkWidget *menubar = NULL;
	GtkWidget *fileMenu = NULL;
	GtkWidget *fileMi = NULL;
	GtkWidget *newMi = NULL;
	GtkWidget *openMi = NULL;
	GtkWidget *imprMi = NULL;
	GtkWidget *quitMi = NULL;

	GtkWidget *imprMenu = NULL;
	GtkWidget *feedMi = NULL;
	GtkWidget *bookMi = NULL;
	GtkWidget *mailMi = NULL;

	GtkWidget *sep = NULL;
	GtkAccelGroup *accel_group = NULL;

	menubar = gtk_menu_bar_new(); //创建菜单栏对象

	//菜单栏子对象: File
	fileMenu = gtk_menu_new();
	accel_group = gtk_accel_group_new();
	gtk_window_add_accel_group(GTK_WINDOW(window), accel_group);

	fileMi = gtk_menu_item_new_with_label("File"); //创建File主项
	/*quitMi = gtk_menu_item_new_with_label("Quit"); //创建File子项Quit*/
	newMi = gtk_image_menu_item_new_from_stock(GTK_STOCK_NEW, NULL); //创建File子项New
	openMi = gtk_image_menu_item_new_from_stock(GTK_STOCK_OPEN, NULL); //创建File子项Open
	quitMi = gtk_image_menu_item_new_from_stock(GTK_STOCK_QUIT, accel_group); //创建File子项Quit
	gtk_widget_add_accelerator(quitMi, "activate", accel_group, GDK_KEY_1, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);

	//菜单栏子对象: Import
	imprMenu = gtk_menu_new();
	imprMi = gtk_menu_item_new_with_label("Import"); //创建Import主项
	feedMi = gtk_menu_item_new_with_label("Import news feed..."); //创建Import子项feed
	bookMi = gtk_menu_item_new_with_label("Import bookmarks..."); //创建Import子项book
	mailMi = gtk_menu_item_new_with_label("Import mail...");      //创建Import子项mail

	sep = gtk_separator_menu_item_new(); //分隔线

	//组织菜单栏各项父子结构
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(imprMi), imprMenu); //设置Import主项为菜单栏子对象imprMenu
	gtk_menu_shell_append(GTK_MENU_SHELL(imprMenu), feedMi);    //添加feed子项到Import主项下
	gtk_menu_shell_append(GTK_MENU_SHELL(imprMenu), bookMi);    //添加book子项到Import主项下
	gtk_menu_shell_append(GTK_MENU_SHELL(imprMenu), mailMi);    //添加mail子项到Import主项下
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(fileMi), fileMenu); //设置File主项为菜单栏子对象fileMenu
	gtk_menu_shell_append(GTK_MENU_SHELL(fileMenu), newMi);     //添加Import主项到File主项下
	gtk_menu_shell_append(GTK_MENU_SHELL(fileMenu), openMi);    //添加Import主项到File主项下
	gtk_menu_shell_append(GTK_MENU_SHELL(fileMenu), imprMi);    //添加Import主项到File主项下
	gtk_menu_shell_append(GTK_MENU_SHELL(fileMenu), sep);       //添加分隔符
	gtk_menu_shell_append(GTK_MENU_SHELL(fileMenu), quitMi);    //添加Quit子项到File主项下
	gtk_menu_shell_append(GTK_MENU_SHELL(menubar), fileMi);    //添加菜单栏子对象File到菜单栏

	g_signal_connect(G_OBJECT(quitMi), "activate", G_CALLBACK(gtk_main_quit), NULL); //指定quitMi点击行为

	gtk_box_pack_start(GTK_BOX(box), menubar, FALSE, FALSE, 0); //将菜单栏绑定到子框box
}

int show_popup(GtkWidget *widget, GdkEvent *event)
{
	const gint RIGHT_CLICK = 3;

	if (event->type == GDK_BUTTON_PRESS) {
		GdkEventButton *bevent = (GdkEventButton *)event;
		if (bevent->button == RIGHT_CLICK) {
			gtk_menu_popup(GTK_MENU(widget), NULL, NULL, NULL, NULL, bevent->button, bevent->time);
		}
		return TRUE;
	}

	return FALSE;
}

void undo_redo(GtkWidget *widget, gpointer item)
{
	static gint count = 2;
	const gchar *name = gtk_widget_get_name(widget);

	if (g_strcmp0(name, "undo") ) {
		count++;
	} else {
		count--;
	}

	if (count < 0) {
		gtk_widget_set_sensitive(widget, FALSE);
		gtk_widget_set_sensitive(item, TRUE);
	}

	if (count > 5) {
		gtk_widget_set_sensitive(widget, FALSE);
		gtk_widget_set_sensitive(item, TRUE);
	}
}

void toolbar_item_create(GtkWidget *vbox)
{
	GtkWidget *toolbar = NULL;
	GtkToolItem *newTb = NULL;
	GtkToolItem *openTb = NULL;
	GtkToolItem *saveTb = NULL;
	GtkToolItem *undo = NULL;
	GtkToolItem *redo = NULL;
	GtkToolItem *sep = NULL;
	GtkToolItem *exitTb = NULL;
	GtkWidget *halign = NULL;

	toolbar = gtk_toolbar_new(); //创建工具栏
	gtk_toolbar_set_style(GTK_TOOLBAR(toolbar), GTK_TOOLBAR_ICONS); //设置工具栏风格

	gtk_container_set_border_width(GTK_CONTAINER(toolbar), 2); //设置宽度

	newTb = gtk_tool_button_new_from_stock(GTK_STOCK_NEW);
	gtk_toolbar_insert(GTK_TOOLBAR(toolbar), newTb, -1);     //添加new按钮到工具栏

	openTb = gtk_tool_button_new_from_stock(GTK_STOCK_OPEN);
	gtk_toolbar_insert(GTK_TOOLBAR(toolbar), openTb, -1);    //添加open按钮到工具栏

	saveTb = gtk_tool_button_new_from_stock(GTK_STOCK_SAVE);
	gtk_toolbar_insert(GTK_TOOLBAR(toolbar), saveTb, -1);    //添加save按钮到工具栏

	undo = gtk_tool_button_new_from_stock(GTK_STOCK_UNDO);
	gtk_widget_set_name(GTK_WIDGET(undo), "undo");
	gtk_toolbar_insert(GTK_TOOLBAR(toolbar), undo, -1);      //添加undo按钮到工具栏

	redo = gtk_tool_button_new_from_stock(GTK_STOCK_REDO);
	gtk_toolbar_insert(GTK_TOOLBAR(toolbar), redo, -1);      //添加redo按钮到工具栏

	sep = gtk_separator_tool_item_new();
	gtk_toolbar_insert(GTK_TOOLBAR(toolbar), sep, -1);       //添加工具栏分隔线

	exitTb = gtk_tool_button_new_from_stock(GTK_STOCK_QUIT);
	gtk_toolbar_insert(GTK_TOOLBAR(toolbar), exitTb, -1);    //添加exit按钮到工具栏

	g_signal_connect(G_OBJECT(undo), "clicked", G_CALLBACK(undo_redo), redo); //设置undo按钮点击行为
	g_signal_connect(G_OBJECT(redo), "clicked", G_CALLBACK(undo_redo), undo); //设置redo按钮点击行为
	g_signal_connect(G_OBJECT(exitTb), "clicked", G_CALLBACK(gtk_main_quit), NULL); //设置exit按钮点击行为

	/*gtk_box_pack_start(GTK_BOX(vbox), toolbar, FALSE, FALSE, 0); //将工具栏设置到vbox子框*/
	//工具栏布局并对齐
	halign = gtk_alignment_new(0, 0, 1, 0);
	gtk_container_add(GTK_CONTAINER(halign), toolbar);
	gtk_container_add(GTK_CONTAINER(vbox), halign);
}

void set_click_popmenu(GtkWidget *window)
{
	GtkWidget *pmenu = NULL;
	GtkWidget *hideMi = NULL;
	GtkWidget *quitMi = NULL;

	//创建弹出菜单
	pmenu = gtk_menu_new();

	//创建菜单子项Minimize
	hideMi = gtk_menu_item_new_with_label("Minimize");
	gtk_widget_show(hideMi);
	gtk_menu_shell_append(GTK_MENU_SHELL(pmenu), hideMi);
	//创建菜单子项Quit
	quitMi = gtk_menu_item_new_with_label("Quit");
	gtk_widget_show(quitMi);
	gtk_menu_shell_append(GTK_MENU_SHELL(pmenu), quitMi);

	//设置选项点击行为
	g_signal_connect_swapped(G_OBJECT(hideMi), "activate", G_CALLBACK(gtk_window_iconify), GTK_WINDOW(window));
	g_signal_connect(G_OBJECT(quitMi), "activate", G_CALLBACK(gtk_main_quit), NULL);

	//指定触发点击的对象, 并注册处理函数
	g_signal_connect_swapped(G_OBJECT(window), "button-press-event", G_CALLBACK(show_popup), pmenu);
}

void toggle_statusbar(GtkWidget *widget, gpointer statusbar)
{
	if (gtk_check_menu_item_get_active(GTK_CHECK_MENU_ITEM(widget))) {
		gtk_widget_show(statusbar);
	} else {
		gtk_widget_hide(statusbar);
	}
}

void submenu_item_view_create(GtkWidget *box)
{
	GtkWidget *menubar = NULL;
	GtkWidget *viewmenu = NULL;
	GtkWidget *view = NULL;
	GtkWidget *tog_stat = NULL;
	GtkWidget *statusbar = NULL;

	menubar = gtk_menu_bar_new();
	viewmenu = gtk_menu_new();

	view = gtk_menu_item_new_with_label("View"); //主标签
	tog_stat = gtk_check_menu_item_new_with_label("View statusbar"); //复选框样式选项
	gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(tog_stat), TRUE); //设置复选框初始默认值

	gtk_menu_item_set_submenu(GTK_MENU_ITEM(view), viewmenu);
	gtk_menu_shell_append(GTK_MENU_SHELL(viewmenu), tog_stat);
	gtk_menu_shell_append(GTK_MENU_SHELL(menubar), view);
	gtk_box_pack_start(GTK_BOX(box), menubar, FALSE, FALSE, 0);

	statusbar = gtk_statusbar_new(); //创建状态条
	gtk_box_pack_end(GTK_BOX(box), statusbar, FALSE, TRUE, 0); //将状态条添加到box底部

	g_signal_connect(G_OBJECT(tog_stat), "activate", G_CALLBACK(toggle_statusbar), statusbar); //设置复选框点击行为
}

void menubar_item_create(GtkWidget *vbox, GtkWidget *window)
{
	GtkWidget *menubox = NULL;

	menubox = gtk_box_new(FALSE, 0);

	//创建File菜单
	submenu_item_file_create(menubox, window);
	//创建View菜单
	submenu_item_view_create(menubox);

	gtk_box_pack_start(GTK_BOX(vbox), GTK_WIDGET(menubox), FALSE, FALSE, 0);
}

int main(int argc, char *argv[])
{
	GtkWidget *window = NULL;
	GtkWidget *vbox = NULL;

	gtk_init(&argc, &argv);

	//初始化主窗口
	window_init(&window);
	//创建子框, 并添加到主窗口中
	vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	gtk_container_add(GTK_CONTAINER(window), vbox);

	//创建菜单栏
	menubar_item_create(vbox, window);

	//使用工具条
	toolbar_item_create(vbox);

	//添加按钮
	button_item_create(vbox);

	//设置右键点击弹出菜单
	set_click_popmenu(window);


	//处理destroy(x)信号
	g_signal_connect(G_OBJECT(vbox), "destroy", G_CALLBACK(gtk_main_quit), NULL);

	//显示
	gtk_widget_show_all(window);
	gtk_main();
	return 0;
}
