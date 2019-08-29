#include <gtk/gtk.h>
/*
GdkPixbuf *create_pixbuf(const gchar * filename)
{
    	GdkPixbuf *pixbuf;
    	GError *error = NULL;
    	pixbuf = gdk_pixbuf_new_from_file(filename, &error);
    	if(!pixbuf) {
        	fprintf(stderr, "%s\n", error->message);
        	g_error_free(error);
    	}
    	return pixbuf;
}
*/

enum
{
  	COLUMN = 0,
  	NUM_COLS
} ;

void  on_changed(GtkWidget *widget, gpointer statusbar) 
{
  	GtkTreeIter iter;
  	GtkTreeModel *model;
  	char *value;

  	if (gtk_tree_selection_get_selected(GTK_TREE_SELECTION(widget), &model, &iter)) 
	{
    	gtk_tree_model_get(model, &iter, COLUMN, &value,  -1);
    	gtk_statusbar_push(GTK_STATUSBAR(statusbar),
        gtk_statusbar_get_context_id(GTK_STATUSBAR(statusbar), value), value);
    	g_free(value);
  	}
}


static GtkTreeModel *create_and_fill_model (void)
{
  	GtkTreeStore *treestore;
  	GtkTreeIter toplevel, child;

  	treestore = gtk_tree_store_new(NUM_COLS,G_TYPE_STRING);

  	gtk_tree_store_append(treestore, &toplevel, NULL);
 	gtk_tree_store_set(treestore, &toplevel,COLUMN, "分组1",-1);

  	gtk_tree_store_append(treestore, &child, &toplevel);
  	gtk_tree_store_set(treestore, &child,COLUMN, "好友1", -1);

  	gtk_tree_store_append(treestore, &child, &toplevel);
  	gtk_tree_store_set(treestore, &child, COLUMN, "好友2",-1);

  	gtk_tree_store_append(treestore, &child, &toplevel);
  	gtk_tree_store_set(treestore, &child,COLUMN, "好友3", -1);

	gtk_tree_store_append(treestore, &child, &toplevel);
  	gtk_tree_store_set(treestore, &child,COLUMN, "好友4", -1);

  	gtk_tree_store_append(treestore, &toplevel, NULL);
  	gtk_tree_store_set(treestore, &toplevel, COLUMN, "分组 2",-1);

  	gtk_tree_store_append(treestore, &child, &toplevel);
  	gtk_tree_store_set(treestore, &child, COLUMN, "好友4", -1);

  	gtk_tree_store_append(treestore, &child, &toplevel);
  	gtk_tree_store_set(treestore, &child, COLUMN, "好友5", -1);

	gtk_tree_store_append(treestore, &toplevel, NULL);
  	gtk_tree_store_set(treestore, &toplevel, COLUMN, "分组 3",-1);

  	gtk_tree_store_append(treestore, &child, &toplevel);
  	gtk_tree_store_set(treestore, &child, COLUMN, "好友6", -1);

  	gtk_tree_store_append(treestore, &child, &toplevel);
  	gtk_tree_store_set(treestore, &child, COLUMN, "好友7", -1);

  	gtk_tree_store_append(treestore, &child, &toplevel);
  	gtk_tree_store_set(treestore, &child, COLUMN, "好友8", -1);

	gtk_tree_store_append(treestore, &child, &toplevel);
  	gtk_tree_store_set(treestore, &child, COLUMN, "好友9", -1);

  	return GTK_TREE_MODEL(treestore);
}


static GtkWidget *create_view_and_model (void)
{
  	GtkTreeViewColumn *col;
  	GtkCellRenderer *renderer;
  	GtkWidget *view;
  	GtkTreeModel *model;

  	view = gtk_tree_view_new();

  	col = gtk_tree_view_column_new();
	gtk_tree_view_column_set_title(col, "NickName                                                  IP Address");
  	gtk_tree_view_append_column(GTK_TREE_VIEW(view), col);

  	renderer = gtk_cell_renderer_text_new();
  	gtk_tree_view_column_pack_start(col, renderer, TRUE);
  	gtk_tree_view_column_add_attribute(col, renderer, "text", COLUMN);

  	model = create_and_fill_model();
  	gtk_tree_view_set_model(GTK_TREE_VIEW(view), model);
  	g_object_unref(model); 

  	return view;
}



int main(int argc, char *argv[])
{
	gtk_init(&argc, &argv);
    	//创建窗口
	GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title((GtkWindow*)window,"Linpop");//设置窗口标题
	gtk_widget_set_size_request(window,300,800);//设置窗口大小
	gtk_window_set_resizable((GtkWindow*)window,FALSE);//窗口大小不可变
	/*gtk_window_set_icon(GTK_WINDOW(window), create_pixbuf("./home/halo/圖片/logo.png"));//窗口图标*/
    	

	GtkWidget *button = gtk_button_new_with_label("头像");//头像按钮
	gtk_widget_set_size_request(button,100,100);//设置头像按钮大小
	GtkWidget *button1 = gtk_button_new_with_label("昵称");//昵称按钮
	gtk_widget_set_size_request(button1,200,100);//设置昵称按钮大小

	GtkWidget *fixed = gtk_fixed_new();//创建固定布局容器
	gtk_container_add((GtkContainer*)window, fixed);//添加固定布局到窗口
	
	gtk_fixed_put((GtkFixed*)fixed, button,0,0);//添加按钮到固定布局
	gtk_fixed_put((GtkFixed*)fixed, button1,100,0);//添加按钮到固定布局

	GtkWidget*entry = gtk_entry_new();//添加行编辑	
	gtk_fixed_put((GtkFixed*)fixed, entry,0,105);//添加行编辑到固定布局
	GtkWidget *button4 = gtk_button_new_with_label("搜索");//搜索按钮
	gtk_widget_set_size_request(button4,130,30);//设置搜索按钮大小
	gtk_fixed_put((GtkFixed*)fixed, button4,170,105);//添加搜索按钮到固定布局

	

	GtkWidget *vbox = gtk_vbox_new(FALSE, 2);
  	gtk_fixed_put((GtkFixed*)fixed, vbox,0,140);

  	GtkWidget *view = create_view_and_model();
  	GtkTreeSelection *selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(view));

 	gtk_box_pack_start(GTK_BOX(vbox), view, TRUE, TRUE, 1);

  	GtkWidget *statusbar = gtk_statusbar_new();
  	gtk_box_pack_start(GTK_BOX(vbox), statusbar, FALSE, TRUE, 1);



	gtk_widget_show_all(window);
	g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);//关闭窗口退出
	gtk_main();
    	return 0;
}
