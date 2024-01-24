#include "PasswordService.h"

bool PasswordService::checkOrCreate(std::shared_ptr<User> usr) {
	auto iter = users.find(usr);
	if (iter != users.end()) {
		if (usr->getPassword() != (*iter)->getPassword())
			return false;
		else return true;
	}
	users.insert(usr);
	return true;
}