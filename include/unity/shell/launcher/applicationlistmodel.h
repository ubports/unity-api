#ifndef UNITY_SHELL_LAUNCHER_APPLICATIONLISTMODEL_H
#define UNITY_SHELL_LAUNCHER_APPLICATIONLISTMODEL_H

#include <QAbstractListModel>

class ApplicationListModel: public QAbstractListModel
{
    Q_OBJECT
public:
    explicit ApplicationListModel(QObject *parent = 0): QObject(parent) {}

    /**
      * @brief Add an application to the list of applications.
      * @param appId The ID of the application to be added.
      */
    virtual void addApplication(const QString &appId, int index) = 0;

    /**
      * @brief Remove an application from the list of applications.
      * @param appId The ID of the application to be removed.
      */
    virtual void removeApplication(const QString &appId) = 0;

    /**
      * @brief Move an application within the list
      * @param appId The ID of the application to be moved.
      * @param newIndex The new position for the entry.
      */
    virtual moveApplication(const QString &appId, int newIndex) = 0;
};

#endif
