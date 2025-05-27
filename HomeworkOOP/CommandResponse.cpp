#include "CommandResponse.h"

CommandResponse::CommandResponse(bool success, MyString message) : success(success), message(message) {
}

bool CommandResponse::isSuccessful() const {
    return this->success;
}

const MyString& CommandResponse::getMessage() const {
    return this->message;
}
