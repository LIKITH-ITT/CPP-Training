#ifndef INPUT_VALIDATOR_H
#define INPUT_VALIDATOR_H

class InputValidator
{
private:
    static bool hasExtraCharactersInInput();

public:
    static void getValidatedInput(int& value, int minimumValue, int maximumValue);
};

#endif
