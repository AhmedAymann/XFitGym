#include "Subscription.h"
Subscription::Subscription() {

}
Subscription::Subscription(QString name, string startDate) {
	if (name == "yearly") {
		this->name = name;
		this->price = 5500;
		this->startDate = startDate;
		this->endDate = startDate + " week";
	}
}