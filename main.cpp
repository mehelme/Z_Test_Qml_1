#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "database.h"
#include "listmodel.h"

int main(int argc, char *argv[])
{
	QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
	QApplication app(argc, argv);
	QQmlApplicationEngine engine;

	// Подключаемся к базе данных
	DataBase database;
	database.connectToDataBase();

	// Объявляем и инициализируем модель данных
	ListModel *model = new ListModel();

	// Обеспечиваем доступ к модели и классу для работы с базой данных из QML
	engine.rootContext()->setContextProperty("myModel", model);
	engine.rootContext()->setContextProperty("database", &database);

	const QUrl url(QStringLiteral("qrc:/main.qml"));
	QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
					 &app, [url](QObject *obj, const QUrl &objUrl) {
		if (!obj && url == objUrl)
			QCoreApplication::exit(-1);
	}, Qt::QueuedConnection);
	engine.load(url);

	return app.exec();
}

