#ifndef VALIDATOR_H
#define VALIDATOR_H

class Validator
{
private:
    static bool hasExtraCharactersInInput();

public:
    static void getValidatedInput(int& value, int minimumValue, int maximumValue);
};

#endif
