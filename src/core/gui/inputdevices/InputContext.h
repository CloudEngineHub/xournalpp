/*
 * Xournal++
 *
 * [Header description]
 *
 * @author Xournal++ Team
 * https://github.com/xournalpp/xournalpp
 *
 * @license GNU GPLv2 or later
 */

#pragma once


#include <memory>  // for unique_ptr
#include <set>     // for set
#include <string>  // for string

#include <gdk/gdk.h>  // for GdkEvent, GdkModifierType
#include <glib.h>     // for gulong
#include <gtk/gtk.h>  // for GtkWidget

#include "gui/widgets/XournalWidget.h"  // for GtkXournal

class GeometryToolInputHandler;
class KeyboardInputHandler;
class MouseInputHandler;
class ScrollHandling;
class Settings;
class StylusInputHandler;
class ToolHandler;
class TouchDrawingInputHandler;
class TouchInputHandler;
class XournalView;

class InputContext final {

private:
    XournalView* view;
    ScrollHandling* scrollHandling;

    gulong signal_id{0};
    std::unique_ptr<StylusInputHandler> stylusHandler;
    std::unique_ptr<MouseInputHandler> mouseHandler;
    std::unique_ptr<TouchDrawingInputHandler> touchDrawingHandler;
    std::unique_ptr<KeyboardInputHandler> keyboardHandler;
    std::unique_ptr<TouchInputHandler> touchHandler;
    std::unique_ptr<GeometryToolInputHandler> geometryToolInputHandler;

    GtkWidget* widget = nullptr;

    std::set<std::string> knownDevices;

public:
    enum DeviceType {
        MOUSE,
        STYLUS,
        TOUCHSCREEN,
    };

public:
    InputContext(XournalView* view, ScrollHandling* scrollHandling);
    ~InputContext();

private:
    /**
     * Callback used by Glib to notify for new events
     * @param widget The widget the event happened in
     * @param event The event
     * @param self A pointer to our handler
     * @return Whether the event was handled
     */
    static bool eventCallback(GtkWidget* widget, GdkEvent* event, InputContext* self);

    /**
     * Handle the events
     * @param event The event to handle
     * @return Whether the event was handled
     */
    bool handle(GdkEvent* event);

    /**
     * Print debug output
     */
    void printDebug(GdkEvent* event);

public:
    /**
     * Connect the input handling to the window to receive events
     */
    void connect(GtkWidget* widget);

    GtkXournal* getXournal();
    XournalView* getView();
    ToolHandler* getToolHandler();
    Settings* getSettings();
    ScrollHandling* getScrollHandling();
    void setGeometryToolInputHandler(std::unique_ptr<GeometryToolInputHandler> handler);
    GeometryToolInputHandler* getGeometryToolInputHandler() const;
    void resetGeometryToolInputHandler();

    void focusWidget();
    void blockDevice(DeviceType deviceType);
    void unblockDevice(DeviceType deviceType);
    bool isBlocked(DeviceType deviceType);
};
