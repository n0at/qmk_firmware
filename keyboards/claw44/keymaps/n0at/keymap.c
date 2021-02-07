#include QMK_KEYBOARD_H
#include <stdio.h>

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.

enum layer_number {
    _QWERTY = 0,
    _RAISE,
    _LOWER,
};

enum custom_keycodes {
  IMEON = SAFE_RANGE,
  IMEOFF
};

typedef struct {
    bool is_press_action;
    uint8_t state;
} tap;

// 必要な数のタップダンス状態のタイプを定義
enum {
    SINGLE_TAP = 1,
    SINGLE_HOLD,
    DOUBLE_TAP
};

// タップダンス用のenum
enum {
    CT_CLN
};

// #define KC_ KC_TRNS
// #define KC_RST RESET
// #define KC_L_SPC LT(_LOWER, KC_SPC)  // lower
#define KC_R_ENT LT(_RAISE, KC_ENT)  // raise
// #define KC_S_JA LSFT_T(KC_F23)     // shift
// #define KC_C_EN LCTL_T(KC_F24)     // ctrl
#define KC_L_EN LT(_LOWER, KC_F24) // ctrl
// #define KC_C_JA LCTL_T(KC_F23)     // shift
// #define KC_S_EN LSFT_T(KC_F24)     // ctrl
// #define KC_G_JA LGUI_T(KC_LANG1)     // cmd or win
// #define KC_G_EN LGUI_T(KC_LANG2)     // cmd or win
// #define KC_C_BS LCTL_T(KC_BSPC)      // ctrl
// #define KC_A_DEL ALT_T(KC_DEL)       // alt
// #define KC_G_DEL LGUI_T(KC_DEL)      // alt
#define KC_TCLN TD(CT_CLN)          // tap dance
// #define KC_MSBTN TD(MS_BTN)          // tap dance
// #define KC_MSACL TD(MS_ACL)          // tap dance
// #define KC_PREF LCTL(KC_W)           // ctrl w
#define KC_C_TAB LCTL_T(KC_TAB)      // ctrl
// #define KC_C_BSLS LCTL_T(KC_BSLS)    // ctrl
// #define KC_C_SPC LCTL_T(KC_SPC)      // ctrl
#define KC_S_SPC LSFT_T(KC_SPC)      // ctrl
// #define KC_S_QT LSFT_T(KC_QUOT)      // shift

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT( \
    //,--------+--------+---------+--------+---------+--------.   ,--------+---------+--------+---------+--------+--------.
        KC_ESC , KC_Q   , KC_W    , KC_E   , KC_R    , KC_T   ,     KC_Y   , KC_U    , KC_I   , KC_O    , KC_P   , KC_MINS,
    //|--------+--------+---------+--------+---------+--------|   |--------+---------+--------+---------+--------+--------|
       KC_C_TAB, KC_A   , KC_S    , KC_D   , KC_F    , KC_G   ,     KC_H   , KC_J    , KC_K   , KC_L    , KC_TCLN,KC_QUOT,
    //|--------+--------+---------+--------+---------+--------|   |--------+---------+--------+---------+--------+--------|
        KC_LSFT, KC_Z   , KC_X    , KC_C   , KC_V    , KC_B   ,     KC_N   , KC_M    , KC_COMM, KC_DOT  , KC_SLSH, KC_RSFT,
    //`--------+--------+---------+--------+---------+--------/   \--------+---------+--------+---------+--------+--------'
                          KC_LALT , KC_LCTL, KC_S_SPC, KC_DEL ,     KC_BSPC, KC_R_ENT, KC_L_EN, KC_LGUI
    //                 `----------+--------+---------+--------'   `--------+---------+--------+---------'
    ),

    [_RAISE] = LAYOUT( \
    //,--------+--------+--------+--------+--------+--------.   ,--------+--------+--------+--------+--------+--------.
        _______, _______, KC_LPRN, KC_LCBR, KC_LBRC, KC_GRV ,     KC_TILD, KC_RBRC, KC_RCBR, KC_RPRN, KC_DLR , _______,
    //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
        _______, KC_1   , KC_2   , KC_3   , KC_4   , KC_5   ,     KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , _______,
    //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
        _______, KC_BSLS, KC_UNDS, KC_EQL , KC_PLUS, KC_MINS,     KC_PIPE, KC_AMPR, _______, _______, _______, RGB_MOD,
    //`--------+--------+--------+--------+--------+--------/   \--------+--------+--------+--------+--------+--------'
                          _______, _______, _______, _______,     _______, _______, _______, _______
    //                  `--------+--------+--------+--------'   `--------+--------+--------+--------'
    ),

    [_LOWER] = LAYOUT( \
    //,--------+--------+--------+--------+--------+--------.   ,--------+--------+--------+--------+--------+--------.
        _______, KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  ,     KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, KC_BTN1, KC_BTN2,
    //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
        _______, KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 ,     KC_LEFT, KC_DOWN, KC_UP  , KC_RGHT, _______, _______,
    //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
        _______, KC_F11, KC_F12  , _______, KC_HOME, KC_PGUP,     KC_PGDN, KC_END, _______, _______, _______, RGB_TOG,
    //`--------+--------+--------+--------+--------+--------/   \--------+--------+--------+--------+--------+--------'
                          _______, _______, _______, _______,     _______, _______, _______, _______
    //                  `--------+--------+--------+--------'   `--------+--------+--------+--------'
    ),
};

void dance_cln_finished(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        register_code16(KC_COLN);
    } else {
        register_code(KC_SCLN);
    }
}

void dance_cln_reset(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        unregister_code16(KC_COLN);
    } else {
        unregister_code(KC_SCLN);
    }
}

// タップダンスキーを機能に関連付けます
qk_tap_dance_action_t tap_dance_actions[] = {
    [CT_CLN] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_cln_finished, dance_cln_reset),
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

const char code_to_name[60] = {
    ' ', ' ', ' ', ' ', 'a', 'b', 'c', 'd', 'e', 'f',
    'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
    'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
    '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
    'R', 'E', 'B', 'T', '_', '-', '=', '[', ']', '\\',
    '#', ';', '\'', '`', ',', '.', '/', ' ', ' ', ' '};

void set_keylog(uint16_t keycode, keyrecord_t *record) {
    char name = ' ';
    if (keycode < 60) {
        name = code_to_name[keycode];
    }

    // update keylog
    snprintf(keylog_str, sizeof(keylog_str), "%dx%d, k%2d : %c",
            record->event.key.row, record->event.key.col,
            keycode, name);

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

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        set_keylog(keycode, record);
    }
    return true;
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (!is_keyboard_master()) return OLED_ROTATION_180;
    return OLED_ROTATION_270;
}

#endif
