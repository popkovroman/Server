#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <iostream>
#include<locale.h>
#include <cstdio>
#include <cstring>
#include <winsock2.h>
#include <fstream>
#pragma comment(lib, "WS2_32.lib")

using namespace std;
const int SizeOfText = 8192;

int main()
{
	setlocale(LC_ALL, "Russian");
	WSADATA WSAData; //Данные
	SOCKET server, client; //Сокеты сервера и клиента
	SOCKADDR_IN serverAddr, clientAddr; //Адреса сокетов
	WSAStartup(MAKEWORD(2, 2), &WSAData);//инициализация библиотеки
	server = socket(AF_INET, SOCK_STREAM, NULL); //Создали сервер

	if (server == INVALID_SOCKET) //Не удалось создать сокет
	{
		cout << "Не удалось создать сокет." << endl;
		return -1;
	}

	//Привязываем сокет к IP адресу и порту с номером 2000+4
	serverAddr.sin_addr.s_addr = INADDR_ANY;
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(2004);//Номер порта

	if (bind(server, (LPSOCKADDR)&serverAddr, sizeof(serverAddr)) != 0) {
		cout << "Не удалось привязать сокет к адресу." << endl;
		return -1;
	}

	if (listen(server, 0) == SOCKET_ERROR) //Если не получили запрос
	{
		cout << "Запрос не был получен." << endl;
		return -1;
	}

	//Если никаких проблем не возникло то ждем подключения
	cout << "Ожидание входящих данных от клиента..." << endl;
	char Text[SizeOfText]; //Создаем буфер для данных, в котором будет хранится текст
	char Ansver[53] = "Сообщение успешно получшено";
	while (true) 
	{
		int clientAddrSize = sizeof(clientAddr);//размер структуры clientAddr
		if ((client = accept(server, (sockaddr*)&clientAddr, &clientAddrSize)) != INVALID_SOCKET) //Обработка очереди запросов
		{
			cout << "Соединение установлено." << endl;

			//прием данных
			if (recv(client, Text, SizeOfText, NULL) != SOCKET_ERROR)
			{
				cout << "Данные, введенные клиентом:" << endl << Text << endl;
				send(client, Ansver, 53, 0);
			}
		}
	}
	closesocket(client); //Закрыть сокет
	WSACleanup();
}