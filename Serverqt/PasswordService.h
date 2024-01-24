#include <unordered_set>
#include "User.h"
#include <QHash>

class PasswordService {
	struct Hash {
		size_t operator()(const std::shared_ptr<User>& userPtr) const {
			return static_cast<size_t>(qHash(userPtr->getUsername()));
		}
	};

	struct Equality {
		bool operator()(const std::shared_ptr<User>& usr1, const std::shared_ptr<User>& usr2) const {
			return usr1->getUsername() == usr2->getUsername();
		}
	};

private:
	std::unordered_set<std::shared_ptr<User>, Hash, Equality> users;

public:
	bool checkOrCreate(std::shared_ptr<User> usr);
};