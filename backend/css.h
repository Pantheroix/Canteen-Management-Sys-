#ifndef CSS_H
#define CSS_H

GtkCssProvider *load_css()
{
    GtkCssProvider *provider = gtk_css_provider_new();
    gtk_css_provider_load_from_string(provider,
                                      ".box {"
                                      "  border: 5px solid black;"
                                      "  border-radius: 8px;"
                                      "}"
                                      ".navbar {"
                                      "  border: 2px solid white;"
                                      "  border-radius: 8px;"
                                      "  background-color: #333333;"
                                      "  margin-top: 5px;"
                                      "  padding: 10px;"
                                      "}"
                                      ".navbar-label {"
                                      "  font-style: italic;"
                                      "  font-size: 32px;"
                                      "  color: red;"
                                      "}"
                                      ".Obtn {"
                                      "  background-color: green;"
                                      "  color: black;"
                                      "  min-width: 100px;"
                                      "  min-height: 40px;"
                                      "  margin-top: 10px;"
                                      "  margin-right: 20px;"
                                      "}"
                                      ".Hbtn {"
                                      "  background-color: green;"
                                      "  color: black;"
                                      "  min-width: 100px;"
                                      "  min-height: 40px;"
                                      "  margin-top: 10px;"
                                      "  margin-right: 20px;"
                                      "}"
                                      ".Mbtn {"
                                      "  background-color: green;"
                                      "  color: black;"
                                      "  min-width: 100px;"
                                      "  min-height: 40px;"
                                      "  margin-top: 10px;"
                                      "  margin-right: 20px;"
                                      "}"
                                      ".Menu_box {"
                                      "  border: 5px solid red;"
                                      "  border-radius: 8px;"
                                      "}"
                                      ".add-btn { background-color: green; color: black; border-radius: 5px; padding: 6px 12px; }"
                                      ".itembox { border: 3px solid purple; border-radius: 12px; margin: 10px; padding: 10px; background-color: #fafafa; }"
                                      ".item-name { font-weight: bold; font-size: 16px; }"
                                      ".priceBar {border: 3px solid purple; border-radius: 12px; margin: 10px; padding: 10px; background-color: #ffffff; }"
                                      ".price_label {font-weight:bold; font-size:36px;  margin: 10px; padding: 10px;  }"
                                      ".total_label {font-weight:bold; font-size:36px;  margin: 10px; padding: 10px;  }"
                                      ".checkout {color:black; border-radius: 5px; padding: 6px 12px;  }"
                                      ".clear {color:black; border-radius: 5px; padding: 6px 12px;  }"

    );

    gtk_style_context_add_provider_for_display(
        gdk_display_get_default(),
        GTK_STYLE_PROVIDER(provider),
        GTK_STYLE_PROVIDER_PRIORITY_USER);

    return provider;
}

#endif