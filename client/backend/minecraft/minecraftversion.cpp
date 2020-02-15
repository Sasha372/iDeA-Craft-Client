#include "minecraftversion.h"

MinecraftVersion::MinecraftVersion(QString version) : QObject() {
	/*
	 * NOTE Work only with Minecraft 1.7.10.
	 * For others need parse large json (https://launchermeta.mojang.com/mc/game/version_manifest.json)
	 */

	// Close app for not 1.7.10
	if(version != "1.7.10") {
		qCritical() << "Version " << version << " not supported";
	}
	this->version = version;

	if (QSysInfo::kernelType() == "linux") {
		this->dir.setPath(QStandardPaths::writableLocation(QStandardPaths::HomeLocation));
	} else if (QSysInfo::kernelType() == "winnt") {
		this->dir.setPath(QStandardPaths::writableLocation(QStandardPaths::AppDataLocation));
		this->dir.cdUp();
	}

	if (!this->dir.exists(".minecraft")) {
		qDebug() << "Minecraft dir not exist. Creating...";
		this->dir.mkdir(".minecraft");
	}
	this->dir.cd(".minecraft");
}

MinecraftVersion::~MinecraftVersion() {

}

void MinecraftVersion::update() {
	connect(&this->mng, &QNetworkAccessManager::finished, this, &MinecraftVersion::replyVersionMeta);
	QNetworkRequest req;

	req.setUrl(QUrl("https://launchermeta.mojang.com/v1/packages/2e818dc89e364c7efcfa54bec7e873c5f00b3840/1.7.10.json"));

	this->mng.get(req);
}

void MinecraftVersion::download() {
	// Libraries
	this->assets = new AssetsDownloader(this->dir, this->assetIndex);


	connect(this->assets, &AssetsDownloader::metaUpdated, this->assets, &AssetsDownloader::startDownload);
	connect(this->assets, &AssetsDownloader::onProgressUpdate, this, &MinecraftVersion::progressChanged);

	this->assets->update();
}

void MinecraftVersion::replyVersionMeta(QNetworkReply *reply) {
	if (reply->error()) {
		qCritical() << "Can not take version metadate";
	} else {
		QJsonObject root = QJsonDocument::fromJson(reply->readAll()).object();
		reply->deleteLater();

		QJsonValue vId = root.value("id");
		if (!vId.isString()) {
			qCritical() << "id is incorrect: " << vId.type();
		}
		if (vId.toString() != this->version) {
			qCritical() << "Version id is incorrect: " << vId.toString();
		}

		QJsonValue vAssetIndex = root.value("assetIndex");
		if (!vAssetIndex.isObject()) {
			qCritical() << "AssetIndex is incorrect: " << vAssetIndex.type();
		}
		this->assetIndex = vAssetIndex.toObject();

		QJsonValue vLibraries = root.value("libraries");
		if (!vLibraries.isArray()) {
			qCritical() << "Libraries is incorrect: " << vLibraries.type();
		}
		this->libraries = vLibraries.toArray();

		QJsonValue vMainClass = root.value("mainClass");
		if (!vMainClass.isString()) {
			qCritical() << "MainClass is incorrect: " << vMainClass.type();
		}
		this->mainClass = vMainClass.toString();

		QJsonValue vMinecraftArguments = root.value("minecraftArguments");
		if (!vMinecraftArguments.isString()) {
			qCritical() << "MinecraftArguments is incorrect: " << vMinecraftArguments.type();
		}
		this->minecraftArguments = vMinecraftArguments.toString();

		this->isUpdated = true;
		emit this->updated();
	}
}

void MinecraftVersion::progressChanged(int progress) {
	emit this->downloadProgress("Test", progress);
}

QString MinecraftVersion::getVersion() const {
    return version;
}

QString MinecraftVersion::getMinecraftArguments() const {
	return minecraftArguments;
}

QString MinecraftVersion::getMainClass() const {
	return mainClass;
}
