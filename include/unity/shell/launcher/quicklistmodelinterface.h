#ifndef UNITY_SHELL_LAUNCHER_QUICKLISTMODEL_H
#define UNITY_SHELL_LAUNCHER_QUICKLISTMODEL_H

namespace unity
{
namespace shell
{
namespace launcher
{

/**
  * @brief A model containing QuickList actions for an application in the launcher.
  *
  * @description The model has the following roles:
  * - RoleLabel: The text entry in the QuickList menu (QString).
  * - RoleIcon: The icon to be shown for this entry (QString).
  * - RoleCheckable: Wether the item is checkable or not (bool).
  * - RoleGroup: A group this item is in. Items in the same group are exclusive (int). -1 for no group.
  */
class QuickListModelInterface: public QAbstractListModel
{
    Q_OBJECT

protected:
    /// @cond
    explicit QuickListModelInterface(QObject *parent = 0) : QAbstractListModel(parent) {}
    /// @endcond
public:
    enum Roles {
        RoleLabel,
        RoleIcon,
        RoleCheckable,
        RoleGroup
    }

    /// @cond
    virtual ~QuickListModelInterface() {}
    /// @endcond

    /// @cond
    QHash<int, QByteArray> roleNames() const {
        QHash<int, QByteArray> roles;
        roles.insert(RoleText, "label");
        roles.insert(RoleIcon, "icon");
        roles.insert(RoleCheckable, "checkable");
        roles.insert(RoleGroup, "group");
    }
    /// @endcond

}

} // launcher
} // shell
} // unity

#endif
