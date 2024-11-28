/*
 * Copyright 2023 Kevin Gee <info@controller.works>
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H
//#include "pmw3610.h"
#include "analog.h"
#include "pointing_device.h"
#include "./drivers/sensors/adns5050.h"
#include "./drivers/sensors/analog_joystick.h"
enum layers {
    _BASE = 0,
    _LOWER,
    _RAISE,
    _ADJUST
};

enum custom_keycodes {
#ifdef VIA_ENABLE
  //QWERTY = USER00,
  BASE = QK_KB_0,
  //QWERTY = CS00, // qmk v1.1.1
#else
  QWERTTY = SAFE_RANGE,
#endif
  LOWER,
  RAISE,
  ADJUST,
  JOYMODE,
  CPI
};

enum jmodes {
    _MOUSE = 0,
    _SCROLL,
    _JOYS,
    _WASD,
    _UWASD
};

enum cpis {
    _GEAR1 = 0,
    _GEAR2,
    _GEAR3,
    _GEAR4
};

const uint16_t CPIn[]={ 125, 500, 1000, 1375};

typedef union {
  uint32_t raw;
  struct {
    uint8_t jMode;
    uint8_t nCPI;
  };
} user_config_t;

user_config_t user_config;

uint8_t jMode;
uint8_t nCPI;

void joysitck_mode_INC(void) {
  if(jMode == _UWASD) {
    jMode = _MOUSE;
  }else{
    jMode++;
  }

  //user_config.jMode = jMode;
  //eeconfig_update_user(user_config.raw); 
}
void joysitck_mode_DEC(void) {
  if(jMode == _MOUSE) {
    jMode = _UWASD;
  }else{
    jMode--;
  }

  //user_config.jMode = jMode;
  //eeconfig_update_user(user_config.raw); 
}

void ADNS5050_CPI_INC(void){
  //uint16_t cpi_status;

  if(nCPI == 3) {
    nCPI = 0;
  }else{
    nCPI++;
  }
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_vertical_3x4(
  //,-----------------------------------------------------.
       KC_TAB,    KC_Q,    KC_W,    KC_E,
  //|--------+--------+--------+--------+--------+--------|
      KC_LCTL,    KC_A,    KC_S,    KC_D,
  //|--------+--------+--------+--------+--------+--------|
      KC_LSFT,    KC_Z,    KC_X,    KC_C,
  //|--------+--------+--------+--------+--------+--------|
      KC_LSFT,    KC_Z,    KC_X,    KC_C,
  //|--------+--------+--------+--------+--------+--------|
      KC_LSFT,    KC_Z,    KC_X,    KC_C
  //|--------+--------+--------+--------+--------+--------|
  ),

  [_LOWER] = LAYOUT_vertical_3x4(
  //,-----------------------------------------------------.
       KC_TAB,    KC_Q,    KC_W,    KC_E,
  //|--------+--------+--------+--------+--------+--------|
      KC_LCTL,    KC_A,    KC_S,    KC_D,
  //|--------+--------+--------+--------+--------+--------|
      KC_LSFT,    KC_Z,    KC_X,    KC_C,
  //|--------+--------+--------+--------+--------+--------|
      KC_LSFT,    KC_Z,    KC_X,    KC_C,
  //|--------+--------+--------+--------+--------+--------|
      KC_LSFT,    KC_Z,    KC_X,    KC_C
  //|--------+--------+--------+--------+--------+--------|
  ),

  [_RAISE] = LAYOUT_vertical_3x4(
  //,-----------------------------------------------------.
       KC_TAB,    KC_Q,    KC_W,    KC_E,
  //|--------+--------+--------+--------+--------+--------|
      KC_LCTL,    KC_A,    KC_S,    KC_D,
  //|--------+--------+--------+--------+--------+--------|
      KC_LSFT,    KC_Z,    KC_X,    KC_C,
  //|--------+--------+--------+--------+--------+--------|
      KC_LSFT,    KC_Z,    KC_X,    KC_C,
  //|--------+--------+--------+--------+--------+--------|
      KC_LSFT,    KC_Z,    KC_X,    KC_C
  //|--------+--------+--------+--------+--------+--------|
  ),

  [_ADJUST] = LAYOUT_vertical_3x4(
  //,-----------------------------------------------------.
       KC_TAB,    KC_Q,    KC_W,    KC_E,
  //|--------+--------+--------+--------+--------+--------|
      KC_LCTL,    KC_A,    KC_S,    KC_D,
  //|--------+--------+--------+--------+--------+--------|
      KC_LSFT,    KC_Z,    KC_X,    KC_C,
  //|--------+--------+--------+--------+--------+--------|
      KC_LSFT,    KC_Z,    KC_X,    KC_C,
  //|--------+--------+--------+--------+--------+--------|
      KC_LSFT,    KC_Z,    KC_X,    KC_C
  //|--------+--------+--------+--------+--------+--------|
  ),
};

#if 1
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case BASE:
      if (record->event.pressed) {
         print("mode just switched to qwerty and this is a huge string\n");
        set_single_persistent_default_layer(_BASE);
      }
      return false;
      //break;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      //break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      //break;
    case ADJUST:
      if (record->event.pressed) {
        layer_on(_ADJUST);
      } else {
        layer_off(_ADJUST);
      }
      return false;
      //break;

    case JOYMODE:
      if (record->event.pressed) {
        joysitck_mode_INC();
        user_config.jMode = jMode;
        eeconfig_update_user(user_config.raw); 
      }
      return false;

    case CPI:
      if (record->event.pressed) {
        ADNS5050_CPI_INC();
        user_config.nCPI = nCPI;
        eeconfig_update_user(user_config.raw);
        pointing_device_driver_set_cpi(CPIn[nCPI]);
      }
      return false;
  }
  return true;
}
#endif

#ifdef JOYSTICK_ENABLE

int16_t xPos = 0;
int16_t yPos = 0;

bool wasdShiftMode = false;
//bool autorun = false;

bool yDownHeld = false;
bool yUpHeld = false;
bool xLeftHeld = false;
bool xRightHeld = false;
bool shiftHeld = false;

#if 1
int16_t xOrigin, yOrigin;

int16_t maxisCoordinate(pin_t pin, uint16_t origin) {

    int8_t  direction;
    int16_t distanceFromOrigin;
    int16_t range;

    int16_t position = analogReadPin(pin);

    if (origin == position) {
        return 0;
    } else if (origin > position) {
        distanceFromOrigin = origin - position;
        range              = origin - _MIN;
        direction          = -1;
    } else {
        distanceFromOrigin = position - origin;
        range              = _MAX - origin;
        direction          = 1;
    }

    //return distanceFromOrigin * direction;

    //_J_REP_MAX

    float   percent    = (float)distanceFromOrigin / range;
    if(percent >1)percent =1;

    int16_t coordinate = (int16_t)(percent * _J_REP_MAX);

    return coordinate * direction;
#if 0
    int16_t coordinate = (int16_t)(percent * _CENTER);
    
    if (coordinate < 0) {
        return 0;
    } else if (coordinate > _CENTER) {
        return _CENTER * direction;
    } else {
        return coordinate * direction;
    }
#endif

}
#endif
void matrix_scan_user(void) {
        //-----------------------WASD mode---------------------------
    if (jMode == _UWASD) {
      // W & S
      //if (!autorun) {
      yPos = analogReadPin(JSV);      
      //yPos = maxisCoordinate(JSV, yOrigin);
      if (!yDownHeld && yPos >= _DOWN_TRESHOLD) {
        //register_code(KC_H);
        register_code(dynamic_keymap_get_keycode(biton32(layer_state),3,3));
        yDownHeld = true;
      } else if (yDownHeld && yPos < _DOWN_TRESHOLD) {
        yDownHeld = false;
        //unregister_code(KC_H);
        unregister_code(dynamic_keymap_get_keycode(biton32(layer_state),3,3));
      } else if (!yUpHeld && yPos <= _UP_TRESHOLD) {
        yUpHeld = true;
        //register_code(KC_F);
        register_code(dynamic_keymap_get_keycode(biton32(layer_state),2,3));
      } else if (yUpHeld && yPos > _UP_TRESHOLD) {
        yUpHeld = false;
        unregister_code(dynamic_keymap_get_keycode(biton32(layer_state),2,3));
        //unregister_code(KC_F);
      }
      //}
      
      xPos = analogReadPin(JSH);
      //xPos = maxisCoordinate(JSH, xOrigin);
      if (!xLeftHeld && xPos >= _DOWN_TRESHOLD) {
        //register_code(KC_T);
        register_code(dynamic_keymap_get_keycode(biton32(layer_state),0,4));
        xLeftHeld = true;
      } else if (xLeftHeld && xPos < _DOWN_TRESHOLD) {
        xLeftHeld = false;
        unregister_code(dynamic_keymap_get_keycode(biton32(layer_state),0,4));
        //unregister_code(KC_T);
      } else if (!xRightHeld && xPos <= _UP_TRESHOLD) {
        xRightHeld = true;
        register_code(dynamic_keymap_get_keycode(biton32(layer_state),1,4));
        //register_code(KC_G);
      } else if (xRightHeld && xPos > _UP_TRESHOLD) {
        xRightHeld = false;
        unregister_code(dynamic_keymap_get_keycode(biton32(layer_state),1,4));
        //unregister_code(KC_G);
      }

    //-----------------------WASD mode---------------------------
    }else if(jMode == _WASD) {
      // W & S
      //if (!autorun) {
      yPos = analogReadPin(JSV);      
      //yPos = maxisCoordinate(JSV, yOrigin);
      if (!yDownHeld && yPos >= _DOWN_TRESHOLD) {
        register_code(KC_A);
        yDownHeld = true;
      } else if (yDownHeld && yPos < _DOWN_TRESHOLD) {
        yDownHeld = false;
        unregister_code(KC_A);
      } else if (!yUpHeld && yPos <= _UP_TRESHOLD) {
        yUpHeld = true;
        register_code(KC_D);
      } else if (yUpHeld && yPos > _UP_TRESHOLD) {
        yUpHeld = false;
        unregister_code(KC_D);
      }
      //}
      
      xPos = analogReadPin(JSH);
      //xPos = maxisCoordinate(JSH, xOrigin);
      if (!xLeftHeld && xPos >= _DOWN_TRESHOLD) {
        register_code(KC_S);
        xLeftHeld = true;
      } else if (xLeftHeld && xPos < _DOWN_TRESHOLD) {
        xLeftHeld = false;
        unregister_code(KC_S);
      } else if (!xRightHeld && xPos <= _UP_TRESHOLD) {
        xRightHeld = true;
        register_code(KC_W);
      } else if (xRightHeld && xPos > _UP_TRESHOLD) {
        xRightHeld = false;
        unregister_code(KC_W);
      }
#if 0
      if (wasdShiftMode) {
        bool yShifted = yPos < _SHIFT;
        if (!shiftHeld && yShifted) {
          register_code(KC_LSFT);
          shiftHeld = true;
        } else if (shiftHeld && !yShifted) {
          unregister_code(KC_LSFT);
          shiftHeld = false;
        }
      }
#endif
    //---------------------joystick mode----------------------------
    }else if(jMode == _JOYS){
      int16_t jy = maxisCoordinate(JSH, xOrigin);
      int16_t jx = maxisCoordinate(JSV, yOrigin);

      //report_analog_joystick_t jdata;
      //jdata = analog_joystick_read();

      
      //int16_t jy = analogReadPin(JSH); 
      //int16_t jx = analogReadPin(JSV); 
      
      joystick_set_axis( 0, -jx);
      joystick_set_axis( 1, jy);
 

    //----------------------mouse mode------------------------------
    }else if(jMode == _MOUSE){


    //----------------------scroll mode-----------------------------
    }else if(jMode == _SCROLL){
      yPos = analogReadPin(JSV);
      if (!yDownHeld && yPos >= _DOWN_TRESHOLD) {
        register_code(KC_WH_L);
        yDownHeld = true;
      } else if (yDownHeld && yPos < _DOWN_TRESHOLD) {
        yDownHeld = false;
        unregister_code(KC_WH_L);
      } else if (!yUpHeld && yPos <= _UP_TRESHOLD) {
        yUpHeld = true;
        register_code(KC_WH_R);
      } else if (yUpHeld && yPos > _UP_TRESHOLD) {
        yUpHeld = false;
        unregister_code(KC_WH_R);
      }
      //}
      
      xPos = analogReadPin(JSH);
      if (!xLeftHeld && xPos >= _DOWN_TRESHOLD) {
        register_code(KC_WH_D);
        xLeftHeld = true;
      } else if (xLeftHeld && xPos < _DOWN_TRESHOLD) {
        xLeftHeld = false;
        unregister_code(KC_WH_D);
      } else if (!xRightHeld && xPos <= _UP_TRESHOLD) {
        xRightHeld = true;
        register_code(KC_WH_U);
      } else if (xRightHeld && xPos > _UP_TRESHOLD) {
        xRightHeld = false;
        unregister_code(KC_WH_U);
      }
    }
}

  //joystick config
  joystick_config_t joystick_axes[JOYSTICK_AXIS_COUNT] = {
    JOYSTICK_AXIS_VIRTUAL,
    JOYSTICK_AXIS_VIRTUAL
    //JOYSTICK_AXIS_IN(JSH, _MAX, _CENTER, _MIN),
    //JOYSTICK_AXIS_IN(JSV, _MIN, _CENTER, _MAX)  
  };
#endif // joystick

void pointing_device_driver_init(void) {

  analog_joystick_init();
  xOrigin = analogReadPin(JSH);
  yOrigin = analogReadPin(JSV);

  //pmw3610_sync();
  //pmw3610_init();
  adns5050_sync();
  adns5050_init();


}

report_mouse_t pointing_device_driver_get_report(report_mouse_t mouse_report){

     //report_pmw3610_t data = pmw3610_read_burst();
     report_adns5050_t data = adns5050_read_burst();
     mouse_report.x = data.dx;
     mouse_report.y = data.dy;
     //mouse_report.x = data.dx / nCPI; // fake cpi
     //mouse_report.y = data.dy / nCPI; // fake cpi
#if 1     
     if(jMode == _MOUSE){
      report_analog_joystick_t jdata = analog_joystick_read();
      //mouse_report.h = 0;
      //mouse_report.v = 0;
      mouse_report.x += -jdata.y;
      mouse_report.y += -jdata.x;
     }
#endif
     return mouse_report; 
}
uint16_t pointing_device_driver_get_cpi(void){
     //uint16_t cpi = pmw3610_get_cpi();
     uint16_t cpi = adns5050_get_cpi();
     return cpi;
}
void pointing_device_driver_set_cpi(uint16_t cpi){
    //pmw3610_set_cpi(cpi);
    adns5050_set_cpi(cpi);
}

#if 0
//#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise)
{
    if(clockwise){
      tap_code(KC_AUDIO_VOL_UP);
    }else{
      tap_code(KC_AUDIO_VOL_DOWN);
    }
    return true;
}
#else
bool encoder_update_user(uint8_t index, bool clockwise) {
	if(index == 0){
		if(clockwise){
			tap_code(dynamic_keymap_get_keycode(biton32(layer_state),0,3));
		}else{
			tap_code(dynamic_keymap_get_keycode(biton32(layer_state),1,3));
		}
    }
    return true;
}
#endif

#if 0
//#ifdef OLED_ENABLE
bool oled_task_user(void) {
    // Host Keyboard Layer Status
    oled_write_P(PSTR("Layer: "), false);

    switch (get_highest_layer(layer_state)) {
        case _BASE:
            oled_write_P(PSTR("BASE\n"), false);
            break;
        case _LOWER:
            oled_write_P(PSTR("LOWER\n"), false);
            break;
        case _RAISE:
            oled_write_P(PSTR("RAISE\n"), false);
            break;
        case _ADJUST:
            oled_write_P(PSTR("ADJUS\n"), false);
            break;
        default:
            // Or use the write_ln shortcut over adding '\n' to the end of your string
            oled_write_ln_P(PSTR("Undefined"), false);
    }

    // Host Keyboard LED Status
    led_t led_state = host_keyboard_led_state();
    oled_write_P(led_state.num_lock ? PSTR("NUM ") : PSTR("    "), false);
    oled_write_P(led_state.caps_lock ? PSTR("CAP ") : PSTR("    "), false);
    oled_write_P(led_state.scroll_lock ? PSTR("SCR ") : PSTR("    "), false);
    
    return false;
}
#endif

#ifdef OLED_ENABLE
#if 1
static void render_status(void) {
    // Host Keyboard Layer Status
    
    oled_write_P(PSTR("-----LAYER"), false);
    switch (get_highest_layer(layer_state)) {
        case _BASE:
            oled_write_P(PSTR(" BAS "), false);
            break;
        case _LOWER:
            oled_write_P(PSTR(" LWR "), false);
            break;
        case _RAISE:
            oled_write_P(PSTR(" RIS "), false);
            break;
        case _ADJUST:
            oled_write_P(PSTR(" ADJ "), false);
            break;
        default:
            oled_write_P(PSTR(" UDF "), false);
    }
    oled_write_P(PSTR("-----STATS-----"), false);
    //oled_write_P(PSTR("STATS"), false);
    //oled_write_P(PSTR("\n\n\n"), false);
    // Host Keyboard LED Status
    led_t led_state = host_keyboard_led_state();
    oled_write_P(led_state.num_lock ? PSTR("NUM:@") : PSTR("NUM:_"), false);
    oled_write_P(led_state.caps_lock ? PSTR("CAP:@") : PSTR("CAP:_"), false);
    oled_write_P(led_state.scroll_lock ? PSTR("SCR:@") : PSTR("SCR:_"), false);
    //oled_write_P(PSTR("-----JMODLEFT "), false);
    oled_write_P(PSTR("-----JYMOD"), false);
    //oled_write_P(PSTR("LEFT "), false);

    switch(jMode){
      case _MOUSE:
        oled_write_P(PSTR("MOUSE"), false);
        break;
      case _SCROLL:
        oled_write_P(PSTR("SCROL"), false);
        break;
      case _JOYS:
        oled_write_P(PSTR(" JOY "), false);
        break;
      case _WASD:
        oled_write_P(PSTR(" WASD"), false);
        break;
      case _UWASD:
        oled_write_P(PSTR("UWASD"), false);
        break;
      default:
        oled_write_P(PSTR(" XXX "), false);
        break;
    }

    oled_write_P(PSTR("----- CPI "), false);


    switch(nCPI){
      case 0:
        oled_write_P(PSTR(" 125 "), false);
        break;
      case 1:
        oled_write_P(PSTR(" 500 "), false);
        break;
      case 2:
        oled_write_P(PSTR(" 1000"), false);
        break;
      case 3:
        oled_write_P(PSTR(" 1375"), false);
        break;
      default:
        oled_write_P(PSTR(" 125 "), false);
        break;
    }
    //oled_write_P(PSTR(" 3200"), false);

#if 0
    if(is_drag_scroll_m){
        oled_write_P(PSTR(" Scl "), false);
    }else{
        oled_write_P(PSTR(" Mx"), false);
        oled_write_char((user_config.v99_dpi_master+48), false);
        oled_write_P(PSTR("\n"), false);
    }
    //oled_write_P(is_drag_scroll_m ? PSTR(" Scl  ") : PSTR(" Mx  "), false);
    //oled_write_P(PSTR(" Mx2 "), false);
    oled_write_P(PSTR("RIGHT"), false);
    if(is_drag_scroll_s){
        oled_write_P(PSTR(" Scl "), false);
    }else{
        oled_write_P(PSTR(" Mx"), false);
        oled_write_char((user_config.v99_dpi_slave+48), false);
        oled_write_P(PSTR("\n"), false);
    }

enum jmodes {
    _MOUSE = 0,
    _SCROLL,
    _JOYS,
    _WASD
};


#endif
    //oled_write_P(is_drag_scroll_s ? PSTR(" Scl  ") : PSTR(" Mx  "), false);
    //oled_write_P(PSTR(" Scl "), false);
    //oled_write_P(V99_X_TRANSFORM_M, false);
    //oled_write_char((get_highest_layer(layer_state)+48), false);
    oled_write_P(PSTR("-----"), false);
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
        return OLED_ROTATION_270;  // flips the display 270 degrees if offhand
    return rotation;
}

bool oled_task_kb(void) {
    if(!oled_task_user()) { return false; }
        render_status(); // Renders the current keyboard state (layer, lock, caps, scroll, etc)
    return true;
}
#else

static void render_logo(void) {
    static const char PROGMEM qmk_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0xB0, 0xB1, 0xB2, 0xB3, 0xB4,
        0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF, 0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0x00
    };

    oled_write_P(qmk_logo, false);
}

bool oled_task_user(void) {
    render_logo();
    return false;
}

#endif
#endif

#if 1
void eeconfig_init_user(void) {  // EEPROM is getting reset!

  bool dpi_change_f = false;
  user_config.raw = 0;


  user_config.raw = eeconfig_read_user();
  if(user_config.jMode > _UWASD || user_config.jMode < 0 ){
    user_config.jMode = _MOUSE;
    dpi_change_f = true;
  }
  //jMode = user_config.jMode;

  if((user_config.nCPI > 3) || (user_config.nCPI < 0) ){
    user_config.nCPI = _GEAR1;
    dpi_change_f = true;
  }
  //nCPI = user_config.nCPI;

  if(dpi_change_f){
    eeconfig_update_user(user_config.raw); // Write default value to EEPROM now
    pointing_device_driver_set_cpi(CPIn[nCPI]);
  }
  //user_config.nCPI = _GEAR3;
  //eeconfig_update_user(user_config.raw); // Write default value to EEPROM now
  //pointing_device_driver_set_cpi(1000);

}
#endif

#if 1
void matrix_init_user(void){
# ifdef CONSOLE_ENABLE
  dprintf("init MS XY transform value \n");
# endif
  eeconfig_init_user();
}

void keyboard_post_init_user(void) {
    //debug_enable=true;
    //debug_matrix=true;
    //transaction_register_rpc(USER_SYNCXY, user_sync_a_slave_handler);

    user_config.raw = eeconfig_read_user();
    jMode = user_config.jMode;
    nCPI = user_config.nCPI;
    pointing_device_driver_set_cpi(CPIn[nCPI]);
}
#endif
