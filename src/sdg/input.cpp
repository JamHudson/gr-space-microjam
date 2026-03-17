#include "sdg/input.h"
#include <bn_keypad.h>
#include <bn_random.h>
#include <bn_log.h>

namespace sdg {

input::input(int difficulty, bn::random& random) : 
_progress(0),
_diff(difficulty),
 _random(random)
{
    // loop to add random code inputs
    for (int i = 0; i < _diff; i++) {
        int digit = _random.get_unbiased_int(4);
        _challenge.push_back(digit);
        
        // for debug purposes
        if (digit == 0) { BN_LOG("UP"); }
        if (digit == 1) { BN_LOG("RIGHT"); }
        if (digit == 2) { BN_LOG("DOWN"); }
        if (digit == 3) { BN_LOG("LEFT"); }
    }
};

// Reads the input from the D-Pad each frame
void input::update() {
    
    if(bn::keypad::up_pressed()) { _input = 0; }
    else if(bn::keypad::right_pressed()) { _input = 1; }
    else if(bn::keypad::down_pressed()) { _input = 2; }
    else if(bn::keypad::left_pressed()) { _input = 3; }
    // No input results in a default value
    else {_input = -1;}

    if (_input != -1 && _progress < _challenge.size()) {
        if(_input == input::_challenge[_progress]) {
            _progress += 1;
            BN_LOG("CODE IS CORRECT!");
        }
        // reset if incorrect
        else {
            _progress = 0;
            BN_LOG("CODE INCORRECT!");
        }
    }
}

// if code complete, victory is achieved
bool input::code_is_correct() const {
    return _progress == (_challenge.size());
}
const bn::vector<int, 10>& sdg::input::challenge() const
{
    return _challenge;
}

}