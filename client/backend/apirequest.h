#ifndef APIREQUEST_H
#define APIREQUEST_H

#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QObject>
#include <QString>
#include <QUrlQuery>
#include <defines.h>

class APIRequest : public QObject {
	Q_OBJECT
public:
	explicit APIRequest(QString mathod);
	~APIRequest();
	void addQueryItem(QString key, QString value);
	static void addDefaultQueryItem(QString key, QString value);
	void send();

signals:
	void finished(QJsonObject *);

public slots:
	void reply(QNetworkReply *reply);

private:
	static std::vector<QString> defaultKeys, defaultValues;

	QNetworkAccessManager *mng = nullptr;
	QUrlQuery form;
	QString method;
};

#endif // APIREQUEST_H
