#include <iostream>

#include "ORM_Database.h"


void print_title();
void wait_user();
void main_menu(std::unique_ptr<ORM_Database>& orm_db);


int main() {
	setlocale(LC_ALL, "ru_RU.UTF-8");
	print_title();

	std::string username, db_name, password;
	std::unique_ptr<ORM_Database> orm_db;

	std::cout << "Введите имя пользователя(без пробелов): ";
	std::cin >> username;
	std::cout << "Введите название базы данных(без пробелов): ";
	std::cin >> db_name;
	std::cout << "Введите пароль(без пробелов): ";
	std::cin >> password;
	std::cout << std::endl;

	try {
		orm_db = std::make_unique<ORM_Database>(username, db_name, password);
		std::cout << "Подключение успешно установлено!" << std::endl;
		orm_db->adding_records_to_tables();
		wait_user();

		main_menu(orm_db);
	}
	catch (const Wt::Dbo::Exception& ex) {
		std::cout << ex.what() << std::endl;
		wait_user();
	}

	return 0;
}


void print_title() {
	system("cls");
	std::cout << "\tC++ и БД ORM\n\n" << std::endl;
}

void wait_user() {
	std::cout << "\nНажмите любую клавишу для продолжения..." << std::endl;
	system("pause > nul");
}

void main_menu(std::unique_ptr<ORM_Database>& orm_db) {
	std::vector<std::string> publishers;
	int select = 0;

	while (true) {
		print_title();

		publishers = orm_db->get_publishers();
		std::cout << "\tСписок писателей:" << std::endl;
		for (int i = 0; i < publishers.size(); ++i) {
			std::cout << i + 1 << ". " << publishers[i] << std::endl;
		}

		if (publishers.empty()) {
			std::cout << "В базе нет записей!" << std::endl;
			wait_user();
			exit(0);
		}

		std::cout << "\nВведите номер писателя, для вывода информации(0 - выход): ";
		std::cin >> select;
		while (select < 0 && select > publishers.size()) {
			std::cout << "Неккоректный ввод! Введите еще раз: ";
			std::cin >> select;
		}
		std::cout << std::endl << std::endl;

		if (select == 0) {
			return;
		}

		ORM_Database::PublisherInfo publisher = orm_db->get_info(publishers.at(select - 1));

		std::cout << publisher.get_name() << std::endl;
		std::cout << "\tКниги:" << std::endl;
		for (const auto& it_book : publisher.get_book_shops()) {
			std::cout << "\t\t" << it_book.first << std::endl;

			std::cout << "\t\t\tМагазины:" << std::endl;
			for (const auto& it_shop : it_book.second) {
				std::cout << "\t\t\t\t" << it_shop << std::endl;
			}
			std::cout << std::endl;
		}

		wait_user();
	}
}
