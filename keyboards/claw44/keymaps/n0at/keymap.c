#include QMK_KEYBOARD_H
#include <stdio.h>

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.

#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

bool is_alt_tab_active = false;
uint16_t alt_tab_timer = 0;
int RGB_current_mode;

enum layer_number {
    _QWERTY = 0,
    _RAISE,
    _LOWER,
};

enum custom_keycodes {
    IMEON = SAFE_RANGE,
    IMEOFF,
    ALT_TAB,
    RGB_RST,
};

typedef struct {
    bool    is_press_action;
    uint8_t state;
} tap;

// 必要な数のタップダンス状態のタイプを定義
enum { SINGLE_TAP = 1, SINGLE_HOLD, DOUBLE_TAP };

// タップダンス用のenum
enum {
    TD_CLN,
    TD_SSL,
    TD_MINS,
    TD_QUOT,
    TD_COMM,
    TD_DOT,
    TD_P,
    TD_Q,
    TD_Z,
    TD_LBRC,
    TD_RBRC,
    TD_GRV,
    TD_BSLS,
};

#define KC_R_ENT LT(_RAISE, KC_ENT)  // raise
#define KC_LOW TG(_LOWER)            // lower
#define KC_L_EN LT(_LOWER, KC_F24)   // lower
#define KC_L_ENT LT(_LOWER, KC_ENT)  // lower
#define KC_S_EN LSFT_T(KC_F24)       // shift
#define KC_S_TLD LSFT_T(KC_TILD)     // shift
#define KC_S_GRV RSFT_T(KC_GRV)      // shift
#define KC_S_BSL RSFT_T(KC_BSLS)      // shift
#define KC_S_SPC LSFT_T(KC_SPC)      // shift
#define KC_C_TAB LCTL_T(KC_TAB)      // ctrl
#define KC_S_TAB LSFT_T(KC_TAB)      // ctrl
#define KC_TCLN TD(TD_CLN)           // tap dance
// #define KC_TSLS TD(TD_SSL)           // tap dance
// #define KC_TMNS TD(TD_MINS)          // tap dance
// #define KC_TQT TD(TD_QUOT)           // tap dance
// #define KC_TCMM TD(TD_COMM)          // tap dance
// #define KC_TDT TD(TD_DOT)            // tap dance
// #define KC_TQ TD(TD_Q)               // tap dance
// #define KC_TZ TD(TD_Z)               // tap dance
// #define KC_TP TD(TD_P)               // tap dance
// #define KC_TLB TD(TD_LBRC)           // tap dance
// #define KC_TRB TD(TD_RBRC)           // tap dance
// #define KC_TGRV TD(TD_GRV)           // tap dance
// #define KC_TBSL TD(TD_BSLS)           // tap dance

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT(
        //,--------+--------+---------+--------+---------+---------.   ,--------+---------+---------+---------+--------+--------.
            KC_ESC , KC_Q   , KC_W    , KC_E   , KC_R    , KC_T    ,     KC_Y   , KC_U    , KC_I    , KC_O    , KC_P   , KC_MINS,
        //|--------+--------+---------+--------+---------+---------|   |--------+---------+---------+---------+--------+--------|
           KC_C_TAB, KC_A   , KC_S    , KC_D   , KC_F    , KC_G    ,     KC_H   , KC_J    , KC_K    , KC_L    , KC_TCLN, KC_QUOT,
        //|--------+--------+---------+--------+---------+---------|   |--------+---------+---------+---------+--------+--------|
           KC_S_GRV, KC_Z   , KC_X    , KC_C   , KC_V    , KC_B    ,     KC_N   , KC_M    , KC_COMM , KC_DOT  , KC_SLSH,KC_S_BSL,
        //`--------+--------+---------+--------+---------+---------/   \--------+---------+---------+---------+--------+--------'
                              KC_LALT , KC_LEAD, KC_S_SPC, KC_DEL  ,     KC_BSPC, KC_R_ENT, KC_L_ENT, KC_LGUI
        //                 `----------+--------+---------+---------'   `--------+---------+---------+---------'
        ),

    [_RAISE] = LAYOUT(
        //,--------+--------+--------+--------+--------+--------.   ,--------+--------+--------+--------+--------+--------.
            _______, KC_1   , KC_2   , KC_3   , KC_4   , KC_5   ,     KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , KC_UNDS,
        //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
            _______, KC_EXLM, KC_AT  , KC_HASH, KC_DLR , KC_PERC,     KC_EQL , KC_PLUS, KC_MINS, KC_PIPE, KC_SCLN, KC_DQT ,
        //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
            KC_LCBR, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN,     KC_LBRC, KC_RBRC, _______, _______, _______, KC_RCBR,
        //`--------+--------+--------+--------+--------+--------/   \--------+--------+--------+--------+--------+--------'
                              _______, _______, _______, _______,     _______, _______, _______, _______
        //                  `--------+--------+--------+--------'   `--------+--------+--------+--------'
        ),

    [_LOWER] = LAYOUT(
        //,--------+--------+--------+--------+--------+--------.   ,--------+--------+--------+--------+--------+--------.
            KC_F11 , KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  ,     KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_F12 ,
        //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
            _______, KC_EXLM, KC_AT  , KC_HASH, KC_DLR , KC_PERC,     KC_LEFT, KC_DOWN, KC_UP  , KC_RGHT, RGB_TOG, RGB_MOD,
        //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
            KC_LCBR, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN,     KC_LBRC, KC_RBRC, _______, _______, _______, RGB_RST,
        //`--------+--------+--------+--------+--------+--------/   \--------+--------+--------+--------+--------+--------'
                              _______, _______, _______, _______,     _______, _______, _______, _______
        //                  `--------+--------+--------+--------'   `--------+--------+--------+--------'
        ),
};

bool get_permissive_hold(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case SFT_T(KC_SPC):
            return true;
        default:
            return false;
    }
}

bool get_ignore_mod_tap_interrupt(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case SFT_T(KC_SPC):
            return true;
        default:
            return false;
    }
}

LEADER_EXTERNS();

void tap_prefix(void) {
    register_code(KC_LCTL);
    register_code(KC_W);
    unregister_code(KC_W);
    unregister_code(KC_LCTL);
}

void tap_with_prefix(uint16_t keycode) {
    tap_prefix();
    register_code(keycode);
    unregister_code(keycode);
}

void matrix_scan_user(void) {
    LEADER_DICTIONARY() {
        leading = false;

        SEQ_ONE_KEY(KC_ESC) {
            register_code(KC_LCTL);
            register_code(KC_LALT);
            register_code(KC_DEL);
            unregister_code(KC_DEL);
            unregister_code(KC_LALT);
            unregister_code(KC_LCTL);
        } else
        SEQ_ONE_KEY(KC_TAB) {
            register_code(KC_LCTL);
            register_code(KC_TAB);
            unregister_code(KC_TAB);
            unregister_code(KC_LCTL);
        } else
        SEQ_ONE_KEY(KC_W) {
            tap_code(KC_SPACE);
            tap_code(KC_W);
        } else
        SEQ_ONE_KEY(KC_B) {
            tap_with_prefix(KC_EQL);
        } else
        SEQ_ONE_KEY(KC_R) {
            tap_with_prefix(KC_R);
        } else
        SEQ_ONE_KEY(KC_C) {
            tap_with_prefix(KC_C);
        } else
        SEQ_ONE_KEY(KC_V) {
            tap_with_prefix(KC_V);
        } else
        SEQ_ONE_KEY(KC_P) {
            tap_with_prefix(KC_P);
        } else
        SEQ_ONE_KEY(KC_BSLS) {
            tap_with_prefix(KC_BSLS);
        } else
        SEQ_ONE_KEY(KC_MINS) {
            tap_with_prefix(KC_MINS);
        } else
        SEQ_ONE_KEY(KC_H) {
            tap_with_prefix(KC_H);
        } else
        SEQ_ONE_KEY(KC_J) {
            tap_with_prefix(KC_J);
        } else
        SEQ_ONE_KEY(KC_K) {
            tap_with_prefix(KC_K);
        } else
        SEQ_ONE_KEY(KC_L) {
            tap_with_prefix(KC_L);
        }
        leader_end();
    }
}

// タップダンスキーを機能に関連付けます
qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_CLN] = ACTION_TAP_DANCE_DOUBLE(KC_COLN, KC_SCLN),
    // [TD_Q]   = ACTION_TAP_DANCE_DOUBLE(KC_Q, KC_BSLS),
    // [TD_P]   = ACTION_TAP_DANCE_DOUBLE(KC_P, KC_PLUS),
    // [TD_Z]   = ACTION_TAP_DANCE_DOUBLE(KC_Z, KC_PIPE),
    // [TD_SSL]  = ACTION_TAP_DANCE_DOUBLE(KC_SLSH, KC_BSLS),
    // [TD_MINS] = ACTION_TAP_DANCE_DOUBLE(KC_MINS, KC_PLUS),
    // [TD_QUOT] = ACTION_TAP_DANCE_DOUBLE(KC_QUOT, KC_EQL),
    // [TD_COMM] = ACTION_TAP_DANCE_DOUBLE(KC_COMM, KC_PIPE),
    // [TD_DOT]  = ACTION_TAP_DANCE_DOUBLE(KC_DOT, KC_EQL),
    // [TD_LBRC] = ACTION_TAP_DANCE_DOUBLE(KC_LBRC, KC_LCBR),
    // [TD_RBRC] = ACTION_TAP_DANCE_DOUBLE(KC_RBRC, KC_RCBR),
    // [TD_GRV] = ACTION_TAP_DANCE_DOUBLE(KC_TILD, KC_GRV),
    // [TD_BSLS] = ACTION_TAP_DANCE_DOUBLE(KC_BSLS, KC_PIPE),
};

#ifdef OLED_DRIVER_ENABLE

void render_layer_state(void) {
    switch (get_highest_layer(layer_state)) {
        case _QWERTY:
            oled_write_ln_P(PSTR("Query"), false);
            break;
        case _RAISE:
            oled_write_ln_P(PSTR("Raise"), false);
            break;
        case _LOWER:
            oled_write_ln_P(PSTR("Lower"), false);
            break;
        default:
            oled_write_ln_P(PSTR("Undefined"), false);
    }
}

void render_logo(void) {
    static const char PROGMEM logo[] = {0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94, 0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4, 0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4, 0};
    oled_write_P(logo, false);
}


char keylog_str[29]  = {};
char keylogs_str[31] = {};
int  keylogs_str_idx = 0;

const char code_to_name[60] = {' ', ' ', ' ', ' ', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', 'R', 'E', 'B', 'T', '_', '-', '=', '[', ']', '\\', '#', ';', '\'', '`', ',', '.', '/', ' ', ' ', ' '};

void set_keylog(uint16_t keycode, keyrecord_t *record) {
    char name = ' ';
    if (keycode < 60) {
        name = code_to_name[keycode];
    }

    // update keylog
    snprintf(keylog_str, sizeof(keylog_str), "%dx%d, k%2d : %c", record->event.key.row, record->event.key.col, keycode, name);

    // update keylogs
    if (keylogs_str_idx == sizeof(keylogs_str) - 1) {
        keylogs_str_idx = 0;
        for (int i = 0; i < sizeof(keylogs_str) - 1; i++) {
            keylogs_str[i] = ' ';
        }
    }

    keylogs_str[keylogs_str_idx] = name;
    keylogs_str_idx++;
}

const char *read_keylog(void) { return keylog_str; }
const char *read_keylogs(void) { return keylogs_str; }

void oled_task_user(void) {
    if (is_keyboard_master()) {
        render_layer_state();
        oled_write_ln(read_keylog(), false);
        oled_write_ln(read_keylogs(), false);
    } else {
        render_logo();
    }
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (!is_keyboard_master()) return OLED_ROTATION_180;
    return OLED_ROTATION_270;
}

#endif

//A description for expressing the layer position in LED mode.
layer_state_t layer_state_set_user(layer_state_t state) {
#ifdef RGBLIGHT_ENABLE
    switch (get_highest_layer(state)) {
    case _QWERTY:
      rgblight_sethsv(HSV_CHARTREUSE);
      break;
    case _RAISE:
      rgblight_sethsv(HSV_MAGENTA);
      break;
    case _LOWER:
      rgblight_sethsv(HSV_SPRINGGREEN);
      break;
    default: //  for any other layers, or the default layer
      rgblight_sethsv(0, 0, 0);
      
      break;
    }
    rgblight_set_effect_range(1, 20);
#endif
return state;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    #ifdef OLED_DRIVER_ENABLE
    if (record->event.pressed) {
        set_keylog(keycode, record);
    }
    #endif

    switch (keycode) {
        case ALT_TAB:
            if (record->event.pressed) {
                if (!is_alt_tab_active) {
                    is_alt_tab_active = true;
                    register_code(KC_LALT);
                }
                alt_tab_timer = timer_read();
                register_code(KC_TAB);
            } else {
                unregister_code(KC_TAB);
            }
            break;
        #ifdef RGBLIGHT_ENABLE
        case RGB_MOD:
            if (record->event.pressed) {
                rgblight_mode(RGB_current_mode);
                rgblight_step();
                RGB_current_mode = rgblight_config.mode;
            }
            break;
        case RGB_RST:
            if (record->event.pressed) {
                eeconfig_update_rgblight_default();
                rgblight_enable();
                RGB_current_mode = rgblight_config.mode;
            }
            break;
        #endif
    }
    return true;
}