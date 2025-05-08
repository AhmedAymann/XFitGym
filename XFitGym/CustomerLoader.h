#pragma once

#include <QString>
#include <QVector>
#include "Customer.h"

class CustomerLoader {
public:
    static QVector<Customer> LoadCustomersFromFile(const QString& filename = "CustomerData.txt");
};