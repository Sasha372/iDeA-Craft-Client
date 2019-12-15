#ifndef DOWNLOADWORKER_H
#define DOWNLOADWORKER_H

#include <QObject>
#include <QList>
#include <QString>
#include <QNetworkAccessManager>
#include <QCryptographicHash>
#include <backend/downloader/downloadfile.h>

class DownloadWorker : public QObject {
	Q_OBJECT
public:
	DownloadWorker();
	~DownloadWorker();
	void setFileList(QList<DownloadFile *> files);
	void start();

signals:
	void onDownloaded();
	void finished();

private slots:
	void nextFile();

private:
	QList<DownloadFile *> files;
	QNetworkAccessManager *http;
	DownloadFile *current = nullptr;

	void downloadFile();
};

#endif // DOWNLOADWORKER_H
