#ifndef DOWNLOADFILE_H
#define DOWNLOADFILE_H

#include <QObject>
#include <QCryptographicHash>
#include <QDir>
#include <QFile>
#include <QString>
#include <QNetworkAccessManager>
#include <QNetworkReply>

class DownloadFile : public QObject {
	Q_OBJECT
public:
	DownloadFile(QString name, QString hash, QString path, QString uri, QCryptographicHash::Algorithm alg);
	~DownloadFile();
	bool isCorrect();

signals:
	void onDownload();
	void onError(QString);
	void onCorrect();

public slots:
	void get(QNetworkAccessManager *http);
	void take(QNetworkReply *reply);

private slots:
	void save();
	bool check();

private:
	QString name, hash, path, uri;
	QCryptographicHash::Algorithm alg;
	QByteArray data;
	QFile *file = nullptr;
	bool correct;
};

#endif // DOWNLOADFILE_H
