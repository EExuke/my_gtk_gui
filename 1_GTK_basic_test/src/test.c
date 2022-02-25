/* ************************************************************************** **
 *     MODULE NAME            : system
 *     LANGUAGE               : C
 *     TARGET ENVIRONMENT     : Any
 *     FILE NAME              : test.c
 *     FIRST CREATION DATE    : 2022/02/22
 * --------------------------------------------------------------------------
 *     Version                : 1.0
 *     Author                 : xuke
 *     Last Change            : 2022/02/22
 *     FILE DESCRIPTION       : GTK+ test
** ************************************************************************** */
#include <gtk/gtk.h>
#include <gdk/gdkkeysyms-compat.h>

void print_msg(GtkWidget *widget, gpointer window)
{
	g_print("Button clicked\n");
}

void button_sensitive(GtkWidget *widget, gpointer window)
{
	gtk_widget_set_sensitive(widget, FALSE); //按钮置灰
}

void window_init(GtkWidget **window)
{
	GdkPixbuf *icon = NULL;
	GError *error = NULL;

	//创建窗口
	*window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	/**window = gtk_window_new(GTK_WINDOW_POPUP);*/

	//设置窗口基本属性
	gtk_window_set_title(GTK_WINDOW(*window), "Submenu menu"); //标题
	gtk_window_set_default_size(GTK_WINDOW(*window), 960, 600); //大小
	/*gtk_widget_set_size_request(GTK_WINDOW(*window), 460, 300);*/
	gtk_window_set_resizable(GTK_WINDOW(*window), TRUE); //可伸缩性
	gtk_window_set_position(GTK_WINDOW(*window), GTK_WIN_POS_CENTER); //位置:GTK_WIN_POS_NONE, GTK_WIN_POS_CENTER, GTK_WIN_POS_MOUSE, GTK_WIN_POS_CENTER_ALWAYS

	//设置程序图标(任务栏)
	icon = gdk_pixbuf_new_from_file("demo.png", &error);
	if (!icon) {
		fprintf(stderr, "%s\n", error->message);
		g_error_free(error);
	}
	gtk_window_set_icon(GTK_WINDOW(*window), icon);

	//处理destroy(x)信号: 关闭窗口
	g_signal_connect(G_OBJECT(*window), "destroy", G_CALLBACK(gtk_main_quit), NULL);

	g_object_unref(icon);
}

void button_item_create(GtkWidget *box)
{
	GtkWidget *buttonbox = NULL;

	buttonbox = gtk_box_new(FALSE, 0);

	//创建带助记符的按钮
	GtkWidget *button1 = gtk_button_new_with_mnemonic("_B_u_t_t_o_n_1");
	gtk_widget_set_tooltip_text(button1, "button1 widget");
	g_signal_connect(button1, "clicked", G_CALLBACK(print_msg), NULL);
	gtk_container_add(GTK_CONTAINER(buttonbox), button1); //添加按钮到buttonbox

	//创建带标签的按钮
	GtkWidget *button2 = gtk_button_new_with_label("Button2");
	g_signal_connect(button2, "clicked", G_CALLBACK(print_msg), NULL);
	gtk_container_add(GTK_CONTAINER(buttonbox), button2);

	//创建空按钮
	GtkWidget *button3 = gtk_button_new();
	/*gtk_button_set_label(button3, "Button3"); //设置按钮文本内容*/
	/*const gchar *str = gtk_button_get_label(button3); //获取按钮的文本内容*/
	g_signal_connect(button3, "clicked", G_CALLBACK(button_sensitive), NULL); //按下按钮,按钮置灰
	//给按钮设置图片
	GdkPixbuf *new_pixbuf = gdk_pixbuf_new_from_file("./p4.png", NULL); //创建图片资源对象pixbuf
	GdkPixbuf *pixbuf = gdk_pixbuf_scale_simple(new_pixbuf, 200, 30, GDK_INTERP_BILINEAR); //设置图片大小
	GtkWidget *b_image = gtk_image_new_from_pixbuf(pixbuf); //通过pixbuf创建图片控件image
	g_object_unref(new_pixbuf); //释放GdkPixbuf资源
	g_object_unref(pixbuf); //释放GdkPixbuf资源
	gtk_button_set_image(GTK_BUTTON(button3), b_image); //给按钮设置一张图片
	/*b_image = gtk_button_get_image(button3); //获取按钮图片*/
	gtk_button_set_relief(GTK_BUTTON(button3), GTK_RELIEF_NONE); //设置按钮透明背景色
	gtk_container_add(GTK_CONTAINER(buttonbox), button3);

	gtk_container_add(GTK_CONTAINER(box), buttonbox); //将buttonbox添加到box
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

void table_item_create(GtkWidget *box)
{
	GtkWidget *table = NULL;
	GtkWidget *button = NULL;

	table = gtk_table_new(2, 2, FALSE); //创建2x2表格,内部等大

	//填充表格内容
	button = gtk_button_new_with_label("button1"); //创建一个button
	gtk_table_attach_defaults(GTK_TABLE(table), button, 0, 1, 0, 1); //将button加入到table, 前,后,上,下
	button = gtk_button_new_with_label("button2");
	gtk_table_attach_defaults(GTK_TABLE(table), button, 1, 2, 0, 1);
	button = gtk_button_new_with_label("button3");
	gtk_table_attach_defaults(GTK_TABLE(table), button, 0, 2, 1, 2);

	gtk_container_add(GTK_CONTAINER(box), table); //添加表格到box
}

void fixed_item_create(GtkWidget *box)
{
	GtkWidget *fixed = NULL;

	fixed = gtk_fixed_new(); //创建一个固定布局容器fixed

	GtkWidget *button1 = gtk_button_new_with_label("button1"); //创建一个button按钮
	gtk_fixed_put(GTK_FIXED(fixed), button1, 0, 0); //将button1添加到固定容器fixed中(0,0)位置

	GtkWidget *button2 = gtk_button_new_with_label("button2");
	gtk_fixed_put(GTK_FIXED(fixed), button2, 0, 0);
	gtk_fixed_move(GTK_FIXED(fixed), button2, 150, 0); //移动button2到(150,0)的位置
	gtk_widget_set_size_request(button2, 100, 50);     //设置button2的大小

	gtk_container_add(GTK_CONTAINER(box), fixed); //添加固定布局控件到box
}

void entry_callback(GtkWidget *widget, gpointer entry)
{
	const gchar *entry_text;

	entry_text = gtk_entry_get_text(GTK_ENTRY(entry)); //获取文本内容

	printf("entry content: %s\n", entry_text);
}

void row_entry_item_create(GtkWidget *box)
{
	GtkWidget *entry = NULL;

	entry = gtk_entry_new(); //创建一个编辑控件

	gtk_entry_set_max_length(GTK_ENTRY(entry), 64); //设置行编辑内容的最大长度
	gtk_editable_set_editable(GTK_ENTRY(entry), TRUE); //设置允许编辑

	gtk_entry_set_text(GTK_ENTRY(entry), "input some"); //设置编辑内容

	gtk_entry_set_visibility(GTK_ENTRY(entry), FALSE); //设置行编辑的内容是否可视(密码模式)

	//当我们在行编辑中敲回车的时候执行的动作
	g_signal_connect(entry, "activate", G_CALLBACK(entry_callback), entry);

	gtk_container_add(GTK_CONTAINER(box), entry); //添加固定布局控件到box
}

void label_item_create(GtkWidget *box)
{
	GtkWidget *labelbox = NULL;
	GtkWidget *eventlbox = NULL;
	GtkWidget *label_1 = NULL;
	GtkWidget *label_2 = NULL;
	const char *str = NULL;

	//创建标签盒子
	labelbox = gtk_box_new(FALSE, 0);

	//创建标签
	label_1 = gtk_label_new("label: ");
	str = gtk_label_get_label(GTK_LABEL(label_1)); //获取标签文本内容
	printf("label_1 str=%s\n", str);
	//给label_1创建事件盒子
	eventlbox = gtk_event_box_new();
	g_signal_connect(eventlbox, "button_press_event", G_CALLBACK(print_msg), NULL);
	gtk_container_add(GTK_CONTAINER(eventlbox), label_1); //添加标签到box
	gtk_container_add(GTK_CONTAINER(labelbox), eventlbox);

	label_2 = gtk_label_new("label 2");
	gtk_container_add(GTK_CONTAINER(labelbox), label_2);
	gtk_label_set_text(GTK_LABEL(label_2), "row of the label text"); //设置label_2的标签的内容

	//创建字体、大小
	PangoFontDescription *font = pango_font_description_from_string("Arial Black"); //设置字体
	pango_font_description_set_size(font, 20*PANGO_SCALE);             //设置字体大小
	gtk_widget_modify_font(GTK_WIDGET(label_2), font); //设置字体到标签
	pango_font_description_free(font); //释放字体对象

	gtk_container_add(GTK_CONTAINER(box), labelbox); //添加标签盒子到box
}

void image_item_create(GtkWidget *box)
{
	GtkWidget *imagebox = NULL;
	GtkWidget *image = NULL;

	//创建图片盒子
	imagebox = gtk_box_new(FALSE, 0);

	//方法1.以图片默认大小来显示，不能修改其大小
	/*image = gtk_image_new_from_file("./demo.png");*/

	//方法2.使用图片资源GdkPixbuf
	GdkPixbuf *new_pixbuf = gdk_pixbuf_new_from_file("./demo.png", NULL); //创建图片资源对象pixbuf
	GdkPixbuf *pixbuf = gdk_pixbuf_scale_simple(new_pixbuf, 200, 200, GDK_INTERP_BILINEAR); //设置图片大小
	image = gtk_image_new_from_pixbuf(pixbuf); //通过pixbuf创建图片控件image
	/*gtk_image_set_from_pixbuf(image, pixbuf);  //图片控件替换图片*/

	g_object_unref(new_pixbuf); //释放GdkPixbuf资源
	g_object_unref(pixbuf); //释放GdkPixbuf资源

	gtk_container_add(GTK_CONTAINER(imagebox), image); //添加图片到图片盒子

	gtk_container_add(GTK_CONTAINER(box), imagebox); //添加图片盒子到box
}

void progress_update(GtkWidget *widget, gpointer data)
{
	char text[8] = "0%";
	gdouble new_val = gtk_progress_bar_get_fraction(GTK_PROGRESS_BAR(data)) + 0.05;

	if (new_val > 1.0) {
		new_val = 0.0;
	}

	//设置进度条新值
	gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(data), new_val);

	gdouble now_progress = gtk_progress_bar_get_fraction(GTK_PROGRESS_BAR(data)); //获取进度条显示的进度比例
	snprintf(text, sizeof(text), "%d %%", (int)(100*now_progress));
	gtk_progress_bar_set_text(GTK_PROGRESS_BAR(data), text); //设置滑槽上的文本显示

	return;
}

void progress_item_create(GtkWidget *box)
{
	GtkWidget *progress = NULL;
	GtkWidget *pbutton = NULL;
	char text[8] = "0%";

	progress = gtk_progress_bar_new(); //创建进度条控件

	gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(progress), 0.0); //设置进度条显示的进度比例

	gdouble now_progress = gtk_progress_bar_get_fraction(GTK_PROGRESS_BAR(progress)); //获取进度条显示的进度比例
	snprintf(text, sizeof(text), "%d %%", (int)(100*now_progress));

	gtk_progress_bar_set_show_text(GTK_PROGRESS_BAR(progress), TRUE); //打开滑槽文本显示
	gtk_progress_bar_set_text(GTK_PROGRESS_BAR(progress), text); //设置滑槽上的文本显示

	pbutton = gtk_button_new_with_mnemonic("up progress");
	g_signal_connect(G_OBJECT(pbutton), "clicked", G_CALLBACK(progress_update), progress);

	gtk_container_add(GTK_CONTAINER(box), progress); //添加进度条到box
	gtk_container_add(GTK_CONTAINER(box), pbutton); //添加进度条按钮到box
}

void deal_switch_page(GtkNotebook *notebook, gpointer page, guint page_num, gpointer data)
{
	printf("我是第%d个页面\n", page_num+1);
}

void notebook_item_create(GtkWidget *box)
{
	GtkWidget *notebook = NULL;

	notebook = gtk_notebook_new(); //创建笔记本控件
	/*当切换页面时，会触发"switch-page"信号*/

	gtk_notebook_set_tab_pos(notebook, GTK_POS_TOP); //设置页标签的位置: GTK_POS_LEFT, GTK_POS_RIGHT, GTK_POS_TOP, GTK_POS_BOTTOM

	gtk_notebook_append_page(notebook, gtk_label_new("notebook 1"), gtk_label_new("box")); //追加页面; 成功返回值页面值(从0开始)，失败返回-1

	gtk_notebook_insert_page(notebook, gtk_label_new("notebook 2"), gtk_label_new("box"), -1); //在指定位置添加页面(从0开始)

	gtk_notebook_set_current_page(notebook, 0); //设置起始页,从0开始算

	//处理信号，当切换页面的时候，会触发“switch-page”信号
	g_signal_connect(notebook, "switch-page", G_CALLBACK(deal_switch_page), NULL);

	gtk_container_add(GTK_CONTAINER(box), notebook); //添加笔记本到box
}

void layout_item_create(GtkWidget *window, GtkWidget **layout)
{
	gint width, height;

	gtk_window_get_size(window, &width, &height); //获取窗口大小

	*layout = gtk_layout_new(NULL, NULL); //创建layout层

	//使用图片资源GdkPixbuf
	GdkPixbuf *new_pixbuf = gdk_pixbuf_new_from_file("./background.png", NULL); //创建图片资源对象pixbuf
	GdkPixbuf *pixbuf = gdk_pixbuf_scale_simple(new_pixbuf, width, height, GDK_INTERP_BILINEAR); //设置图片大小

	GtkWidget *image = gtk_image_new_from_pixbuf(pixbuf); //通过pixbuf创建图片控件image
	g_object_unref(new_pixbuf); //释放GdkPixbuf资源
	g_object_unref(pixbuf);

	gtk_layout_put(GTK_LAYOUT(*layout), image, 0, 0);
	gtk_container_add(GTK_CONTAINER(window), *layout);
}

gboolean deal_time(gpointer* label)
{
	char buf[5] = {0};
	static int num = 10;

	sprintf(buf, "%d", --num);
	gtk_label_set_text(GTK_LABEL(label), buf);

	if (0 == num) {
		num = 11;
		/*g_source_remove(timer); // 移除定时器*/
		/*return FALSE; //返回FALSE停止*/
	}

	return TRUE; //返回TRUE再次定时
}

void timer_item_create(GtkWidget *box)
{
	GtkWidget *timebox = NULL;
	guint time_ms = 1000; //计时时间,ms

	//创建图片盒子
	timebox = gtk_box_new(FALSE, 0);

	//倒计时显示区
	GtkWidget *label = gtk_label_new("10");
	gtk_container_add(GTK_CONTAINER(timebox), label);
	PangoFontDescription *font = pango_font_description_from_string("Arial Black"); //设置字体
	pango_font_description_set_size(font, 50*PANGO_SCALE);             //设置字体大小
	gtk_widget_modify_font(GTK_WIDGET(label), font); //设置字体到标签
	pango_font_description_free(font); //释放字体对象

	//定时器的创建
	guint timer = g_timeout_add(time_ms, (GSourceFunc)deal_time, (gpointer)label); //当回调函数返回值为FALSE时停止执行,返回TRUE时再次定时;
	(void)timer;

	gtk_container_add(GTK_CONTAINER(box), timebox); //添加定时器盒子到box
}

/*鼠标点击事件产生的信号：button-press-event
 *鼠标释放事件产生的信号：button-release-event
 *鼠标移动事件产生的信号：motion-notify-event
 */
gboolean deal_mouse_press(GtkWidget *widget, GdkEventButton *event, gpointer data)
{
	switch (event->button) {   // 判断鼠标点击的类型
		case 1:
			printf("Left Button!!\n");
			break;
		case 2:
			printf("Middle Button!!\n");
			break;
		case 3:
			printf("Right Button!!\n");
			break;
		default:
			/*printf("Unknown Button!!\n");*/
			break;
	}

	if(event->type == GDK_2BUTTON_PRESS){
		printf("double click\n");
	}

	// 获得点击的坐标值，距离窗口左顶点
	printf("press_x = %f, press_y = %f\n", event->x, event->y);

	return TRUE;
}

void mouse_event_set(GtkWidget *box)
{
	//使控件接收相应事件
	gtk_widget_add_events(box, GDK_BUTTON_PRESS_MASK | GDK_BUTTON_MOTION_MASK);
	/*GDK_BUTTON_PRESS_MASK：鼠标点击;
	 *GDK_BUTTON_RELEASE_MASK：鼠标释放;
	 *GDK_BUTTON_MOTION_MASK：鼠标移动;
	 *GDK_KEY_PRESS_MASK：键盘按下;
	 *GDK_ENTER_NOTIFY_MASK：进入控件区域;
	 */

	// "button-press-event" 鼠标点击事件
	g_signal_connect(box, "button-press-event", G_CALLBACK(deal_mouse_press), NULL);
	// "motion-notify-event" 鼠标移动事件
	/*g_signal_connect(box, "motion-notify-event", G_CALLBACK(deal_mouse_press), NULL);*/
}

// 键盘按下事件处理函数
gboolean deal_key_press(GtkWidget *widget, GdkEventKey  *event, gpointer data)
{
	switch(event->keyval){   // 键盘键值类型
		case GDK_Up:
			printf("Up\n");
			break;
		case GDK_Left:
			printf("Left\n");
			break;
		case GDK_Right:
			printf("Right\n");
			break;
		case GDK_Down:
			printf("Down\n");
			break;
	}

	printf("keyval = %d\n", event->keyval); //获取键盘键值类型

	return TRUE;
}

/*键盘事件定义: /usr/include/gtk-3.0/gdk/gdkkeysyms-compat.h*/
void key_event_set(GtkWidget *window)
{
	//注册"key-press-event"处理
	g_signal_connect(window, "key-press-event", G_CALLBACK(deal_key_press), NULL); 
	//键盘按下事件产生的信号：key-press-event
	//键盘释放事件产生的信号：key-release-event
}

//当窗口初始化，被移动或拉伸时，会触发属性改变事件
gboolean on_configure_event(GtkWidget * widget, GdkEventConfigure * event, gpointer data)
{
	// 窗口的起点坐标
	printf("x = %d, y = %d\n", event->x, event->y);
	// 窗口的宽度和高度
	printf("w = %d, h = %d\n", event->width, event->height);

	return TRUE;
}

void config_change_event_set(GtkWidget *window)
{
	//属性改变事件产生的信号：configure_event
	g_signal_connect(window, "configure_event", G_CALLBACK(on_configure_event), NULL);
}

int main(int argc, char *argv[])
{
	GtkWidget *window = NULL;
	GtkWidget *vbox = NULL;
	/*GtkWidget *layout = NULL;*/

	gtk_init(&argc, &argv);

	//初始化主窗口
	window_init(&window);

	//layout层
	/*layout_item_create(window);*/

	//创建子框, 并添加到主窗口中
	vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	gtk_container_add(GTK_CONTAINER(window), vbox);

	//创建菜单栏
	menubar_item_create(vbox, window);

	//使用工具条
	toolbar_item_create(vbox);

	//添加行编辑控件
	row_entry_item_create(vbox);

	//添加按钮
	button_item_create(vbox);

	//添加表格控件
	table_item_create(vbox);

	//添加固定布局控件
	fixed_item_create(vbox);

	//设置右键点击弹出菜单
	set_click_popmenu(window);

	//添加标签
	label_item_create(vbox);

	//添加图片
	image_item_create(vbox);

	//添加进度条
	progress_item_create(vbox);

	//添加多标签笔记本控件
	notebook_item_create(vbox);

	//添加定时器控件
	timer_item_create(vbox);

	//设置鼠标事件
	mouse_event_set(vbox);

	//设置键盘事件
	/*key_event_set(window);*/

	//设置属性改变事件
	config_change_event_set(window);


	//显示所有
	gtk_widget_show_all(window);

	gtk_main();
	return 0;
}
