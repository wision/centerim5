/*
 * Copyright (C) 2010 by CenterIM developers
 *
 * This file is part of CenterIM.
 *
 * CenterIM is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * CenterIM is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * */

#ifndef __REQUEST_H__
#define __REQUEST_H__

#include <libpurple/request.h>

#define REQUEST (Request::Instance())

class Request
{
	public:
		static Request *Instance();

	protected:

	private:

		PurpleRequestUiOps centerim_request_ui_ops;

		Request();
		Request(const Request&);
		Request& operator=(const Request&);
		~Request();

		static void *request_input_(const char *title, const char *primary,
				const char *secondary, const char *default_value,
				gboolean multiline, gboolean masked, gchar *hint,
				const char *ok_text, GCallback ok_cb, const char *cancel_text,
				GCallback cancel_cb, PurpleAccount *account, const char *who,
				PurpleConversation *conv, void *user_data)
			{ return REQUEST->request_input(title, primary, secondary,
					default_value, multiline, masked, hint, ok_text, ok_cb,
					cancel_text, cancel_cb, account, who, conv, user_data); }
		static void *request_choice_(const char *title, const char *primary,
				const char *secondary, int default_value, const char *ok_text,
				GCallback ok_cb, const char *cancel_text, GCallback cancel_cb,
				PurpleAccount *account, const char *who,
				PurpleConversation *conv, void *user_data, va_list choices)
			{ return REQUEST->request_choice(title, primary, secondary,
					default_value, ok_text, ok_cb, cancel_text, cancel_cb,
					account, who, conv, user_data, choices); }
		static void *request_action_(const char *title, const char *primary,
				const char *secondary, int default_action,
				PurpleAccount *account, const char *who,
				PurpleConversation *conv, void *user_data,
				size_t action_count, va_list actions)
			{ return REQUEST->request_action(title, primary, secondary,
					default_action, account, who, conv, user_data,
					action_count, actions); }
		static void *request_fields_(const char *title, const char *primary,
				const char *secondary, PurpleRequestFields *fields,
				const char *ok_text, GCallback ok_cb, const char *cancel_text,
				GCallback cancel_cb, PurpleAccount *account, const char *who,
				PurpleConversation *conv, void *user_data)
			{ return REQUEST->request_fields(title, primary, secondary,
					fields, ok_text, ok_cb, cancel_text, cancel_cb, account,
					who, conv, user_data); }
		static void *request_file_(const char *title, const char *filename,
				gboolean savedialog, GCallback ok_cb, GCallback cancel_cb,
				PurpleAccount *account, const char *who,
				PurpleConversation *conv, void *user_data)
			{ return REQUEST->request_file(title, filename, savedialog, ok_cb,
					cancel_cb, account, who, conv, user_data); }
		static void close_request_(PurpleRequestType type, void *ui_handle)
			{ REQUEST->close_request(type, ui_handle); }
		static void *request_folder_(const char *title, const char *dirname,
				GCallback ok_cb, GCallback cancel_cb, PurpleAccount *account,
				const char *who, PurpleConversation *conv, void *user_data)
			{ return REQUEST->request_folder(title, dirname, ok_cb, cancel_cb,
					account, who, conv, user_data); }
		static void *request_action_with_icon_(const char *title,
				const char *primary, const char *secondary,
				int default_action, PurpleAccount *account, const char *who,
				PurpleConversation *conv, gconstpointer icon_data,
				gsize icon_size, void *user_data, size_t action_count,
				va_list actions)
			{ return REQUEST->request_action_with_icon(title, primary,
					secondary, default_action, account, who, conv, icon_data,
					icon_size, user_data, action_count, actions); }

		void *request_input(const char *title, const char *primary,
				const char *secondary, const char *default_value,
				gboolean multiline, gboolean masked, gchar *hint,
				const char *ok_text, GCallback ok_cb, const char *cancel_text,
				GCallback cancel_cb, PurpleAccount *account, const char *who,
				PurpleConversation *conv, void *user_data);
		void *request_choice(const char *title, const char *primary,
				const char *secondary, int default_value, const char *ok_text,
				GCallback ok_cb, const char *cancel_text, GCallback cancel_cb,
				PurpleAccount *account, const char *who,
				PurpleConversation *conv, void *user_data, va_list choices);
		void *request_action(const char *title, const char *primary,
				const char *secondary, int default_action,
				PurpleAccount *account, const char *who,
				PurpleConversation *conv, void *user_data,
				size_t action_count, va_list actions);
		void *request_fields(const char *title, const char *primary,
				const char *secondary, PurpleRequestFields *fields,
				const char *ok_text, GCallback ok_cb, const char *cancel_text,
				GCallback cancel_cb, PurpleAccount *account, const char *who,
				PurpleConversation *conv, void *user_data);
		void *request_file(const char *title, const char *filename,
				gboolean savedialog, GCallback ok_cb, GCallback cancel_cb,
				PurpleAccount *account, const char *who,
				PurpleConversation *conv, void *user_data);
		void close_request(PurpleRequestType type, void *ui_handle);
		void *request_folder(const char *title, const char *dirname,
				GCallback ok_cb, GCallback cancel_cb, PurpleAccount *account,
				const char *who, PurpleConversation *conv, void *user_data);
		void *request_action_with_icon(const char *title, const char *primary,
				const char *secondary, int default_action,
				PurpleAccount *account, const char *who,
				PurpleConversation *conv, gconstpointer icon_data,
				gsize icon_size, void *user_data, size_t action_count,
				va_list actions);
};

#endif /* __REQUEST_H__ */