#pragma once

#include <QAbstractListModel>

namespace unity {
namespace shell {
namespace launcher {

class AppDrawerModelInterface: public QAbstractListModel
{
    Q_OBJECT
    Q_ENUMS(Roles)
public:
    enum Roles {
        RoleAppId,
        RoleName,
        RoleIcon,
        RoleUsage
    };

    AppDrawerModelInterface(QObject* parent = nullptr): QAbstractListModel(parent) {}

    QHash<int, QByteArray> roleNames() const override {
        QHash<int, QByteArray> roles;
        roles.insert(RoleAppId, "appId");
        roles.insert(RoleName, "name");
        roles.insert(RoleIcon, "icon");
        roles.insert(RoleUsage, "usage");
        return roles;
    }
};

}
}
}
