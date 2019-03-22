/*
 * Remmina - The GTK+ Remote Desktop Client
 * Copyright (C) 2016-2019 Antenore Gatta, Giovanni Panozzo
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA  02110-1301, USA.
 *
 *  In addition, as a special exception, the copyright holders give
 *  permission to link the code of portions of this program with the
 *  OpenSSL library under certain conditions as described in each
 *  individual source file, and distribute linked combinations
 *  including the two.
 *  You must obey the GNU General Public License in all respects
 *  for all of the code used other than OpenSSL. *  If you modify
 *  file(s) with this exception, you may extend this exception to your
 *  version of the file(s), but you are not obligated to do so. *  If you
 *  do not wish to do so, delete this exception statement from your
 *  version. *  If you delete this exception statement from all source
 *  files in the program, then also delete it here.
 *
 */

#ifdef __LINUX__

#include "config.h"
#include <gtk/gtk.h>
#include <glib/gi18n.h>

#include "remmina/remmina_unlock.h"
#include "remmina/remmina_trace_calls.h"

static RemminaUnlockDialog *remmina_unlock_dialog;
#define GET_OBJ(object_name) gtk_builder_get_object(remmina_unlock_dialog->builder, object_name)

GtkDialog* remmina_unlock_new(GtkWindow *parent)
{
    TRACE_CALL(__func__);
    GtkBuilder *builder = NULL;
    GtkWidget *widget;

    remmina_unlock_dialog = g_new0(RemminaUnlockDialog, 1);
    //remmina_unlock_dialog->priv = g_new0(RemminaUnlockDialogPriv, 1);

    remmina_unlock_dialog->builder = remmina_public_gtk_builder_new_from_file("remmina_unlock.glade");
    remmina_unlock_dialog->dialog = GTK_DIALOG(gtk_builder_get_object(remmina_unlock_dialog->builder, "RemminaUnlockDialog"));
    if (parent)
        gtk_window_set_transient_for(GTK_WINDOW(remmina_unlock_dialog->dialog), parent);

    remmina_unlock_dialog->entry_unlock = GTK_ENTRY(GET_OBJ("entry_unlock"));
    remmina_unlock_dialog->button_unlock = GTK_ENTRY(GET_OBJ("button_unlock"));
    remmina_unlock_dialog->button_unlock_cancel = GTK_ENTRY(GET_OBJ("button_unlock_cancel"));

    g_signal_connect(remmina_unlock_dialog->button_unlock, "clicked",
            G_CALLBACK(remmina_button_unlock_clicked), (gpointer)remmina_unlock_dialog);
    g_signal_connect(remmina_unlock_dialog->button_unlock_cancel, "clicked",
            G_CALLBACK(remmina_button_unlock_cancel_clicked), (gpointer)remmina_unlock_dialog);

    /* Connect signals */
    gtk_builder_connect_signals(remmina_unlock_dialog->builder, NULL);
}

#endif
