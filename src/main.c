#include <pebble.h>

static Window *s_main_window;
static TextLayer *s_output_layer;

static int s_current_step = 0;
static const char *s_recipe[] = {
     "1.	Preheat oven to 350 degrees F ",
     "2.	In a medium bowl, stir together the flour, baking soda, and salt; set aside.",
     "3.	In a large bowl, cream together the margarine and 2 cups sugar until light and fluffy.",
     "4.	Beat in the eggs one at a time, then the vanilla.",
     "5.	Gradually stir in the dry ingredients until just blended.",
     "6.	Roll the dough into walnut sized balls and roll the balls in remaining 1/4 cup of sugar.",
     "7.	Place cookies 2 inches apart onto ungreased cookie sheets and flatten slightly.",
     "8.	Bake for 8 to 10 minutes in the preheated oven, until lightly browned at the edges.",
     "9.	Allow cookies to cool on baking sheet for 5 minutes before removing to a wire rack to cool completely."
 };
  

static void go_to_next(void){
    s_current_step++;
    text_layer_set_text(s_output_layer, s_recipe[s_current_step - 1]);
}

static void tap_handler(AccelAxisType axis, int32_t direction) {

    if (direction == 0) {
      return;
    }
  
    go_to_next();
  
  }


static void main_window_load(Window *window) {
  Layer *window_layer = window_get_root_layer(window);
  GRect window_bounds = layer_get_bounds(window_layer);

  // Create output TextLayer
  s_output_layer = text_layer_create(GRect(5, 0, window_bounds.size.w - 10, window_bounds.size.h));
  text_layer_set_font(s_output_layer, fonts_get_system_font(FONT_KEY_GOTHIC_24));
  text_layer_set_text(s_output_layer, "No data yet.");
  text_layer_set_overflow_mode(s_output_layer, GTextOverflowModeWordWrap);
  layer_add_child(window_layer, text_layer_get_layer(s_output_layer));
  
  go_to_next();
}

static void main_window_unload(Window *window) {
  // Destroy output TextLayer
  text_layer_destroy(s_output_layer);
}

static void init() {
  // Create main Window
    s_main_window = window_create();
    window_set_window_handlers(s_main_window, (WindowHandlers) {
    .load = main_window_load,
    .unload = main_window_unload
  });
  window_stack_push(s_main_window, true);
  accel_tap_service_subscribe(tap_handler);
  
}

static void deinit() {
  // Destroy main Window
  window_destroy(s_main_window);
  accel_tap_service_unsubscribe();
 
}

int main(void) {
  init();
  app_event_loop();
  deinit();
}