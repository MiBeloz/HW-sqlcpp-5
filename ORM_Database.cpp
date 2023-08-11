#include "ORM_Database.h"

ORM_Database::ORM_Database(const std::string& username, const std::string& db_name, const std::string& password) :
	m_username(username), m_db_name(db_name), m_password(password) {

	auto postgres = std::make_unique<Wt::Dbo::backend::Postgres>(
		"host=localhost "
		"port=5432 "
		"dbname=" + m_db_name + " "
		"user=" + m_username + " "
		"password=" + m_password);

	m_session.setConnection(std::move(postgres));

	m_session.mapClass<Publisher>("publisher");
	m_session.mapClass<Book>("book");
	m_session.mapClass<Shop>("shop");
	m_session.mapClass<Stock>("stock");
	m_session.mapClass<Sale>("sale");

	try {
		m_session.createTables();
		std::cout << "Создание таблиц завершено." << std::endl;
	}
	catch (const Wt::Dbo::Exception& ex) {
		std::cout << "Создание таблиц пропущено - таблицы уже существуют." << std::endl;
	}
}

ORM_Database::~ORM_Database() {
	m_session.dropTables();
}

void ORM_Database::adding_records_to_tables() {
	//Publishers
	std::string pub_Agatha_Christie = "Агата Кристи";
	std::string pub_Stephen_King = "Стивен Кинг";
	std::string pub_Fedor_Dostoevsky = "Фёдор Достоевский";
	std::string pub_Mikhail_Lermontov = "Михаил Лермонтов";
	std::string pub_Alexander_Pushkin = "Александр Пушкин";

	//Books
	std::string book_AC_Murder_on_the_Orient_Express = "Убийство в «Восточном экспрессе»";
	std::string book_AC_Death_on_the_Nile = "Смерть на Ниле";
	std::string book_AC_The_Murder_of_Roger_Ackroyd = "Убийство Роджера Экройда";
	std::string book_AC_The_Mysterious_Affair_at_Styles = "Загадочное происшествие в Стайлзе";
	std::string book_AC_The_ABC_Murders = "Убийства по алфавиту";

	std::string book_SK_It = "Оно";
	std::string book_SK_The_Shining = "Сияние";
	std::string book_SK_Fairy_Tale = "Сказка";
	std::string book_SK_The_Stand = "Противостояние";
	std::string book_SK_Carrie = "Кэрри";

	std::string book_FD_Crime_and_Punishment = "Преступление и наказание";
	std::string book_FD_Brothers_Karamazov = "Братья Карамазовы";
	std::string book_FD_Demons = "Бесы";
	std::string book_FD_Notes_from_the_Underground = "Записки из подполья";
	std::string book_FD_White_Nights = "Белые ночи";

	std::string book_ML_Hero_of_our_time = "Герой нашего времени";
	std::string book_ML_Mtsyri = "Мцыри";
	std::string book_ML_Daemon = "Демон";
	std::string book_ML_Sail = "Парус";
	std::string book_ML_Three_Palms = "Три Пальмы";

	std::string book_AP_Captains_daughter = "Капитанская дочка";
	std::string book_AP_Dubrovsky = "Дубровский";
	std::string book_AP_Queen_of_Spades = "Пиковая дама";
	std::string book_AP_Blizzard = "Метель";
	std::string book_AP_Shot = "Выстрел";

	//Shops
	std::string shop_World_of_books = "Мир книг";
	std::string shop_Read_the_city = "Читай город";
	std::string shop_Center_book = "Центр книга";
	std::string shop_Hut_reading = "Изба читальня";
	std::string shop_Book_house = "Дом книг";

	//Sales
	std::string sale1 = "2022-06-09";
	std::string sale2 = "2022-07-25";
	std::string sale3 = "2022-08-03";
	std::string sale4 = "2022-09-15";
	std::string sale5 = "2022-11-16";


	add_record(
		pub_Agatha_Christie,
		book_AC_Murder_on_the_Orient_Express,
		{ shop_World_of_books, shop_Center_book, shop_Hut_reading },
		10,
		899.99,
		sale2,
		5);
	add_record(pub_Agatha_Christie,
		book_AC_Death_on_the_Nile,
		{ shop_Center_book, shop_Hut_reading },
		20,
		759.99,
		sale4,
		8);
	add_record(pub_Agatha_Christie,
		book_AC_The_Murder_of_Roger_Ackroyd,
		{ shop_World_of_books, shop_Center_book, shop_Book_house },
		15,
		999.99,
		sale1,
		5);
	add_record(pub_Agatha_Christie,
		book_AC_The_Mysterious_Affair_at_Styles,
		{ shop_Center_book, shop_Book_house },
		5,
		699.99,
		sale3,
		2);
	add_record(pub_Agatha_Christie,
		book_AC_The_ABC_Murders,
		{ shop_Read_the_city, shop_Center_book, shop_Hut_reading, shop_Book_house },
		8,
		599.99,
		sale5,
		4);

	add_record(pub_Stephen_King,
		book_SK_It,
		{ shop_Read_the_city, shop_Book_house },
		12,
		1299.99,
		sale3,
		8);
	add_record(pub_Stephen_King,
		book_SK_The_Shining,
		{ shop_Hut_reading },
		8,
		999.99,
		sale3,
		5);
	add_record(pub_Stephen_King,
		book_SK_Fairy_Tale,
		{ shop_World_of_books, shop_Read_the_city, shop_Center_book, shop_Hut_reading, shop_Book_house },
		10,
		929.99,
		sale1,
		4);
	add_record(pub_Stephen_King,
		book_SK_The_Stand,
		{ shop_Book_house },
		16,
		1199.99,
		sale5,
		12);
	add_record(pub_Stephen_King,
		book_SK_Carrie,
		{ shop_Center_book, shop_Hut_reading, shop_Book_house },
		18,
		569.99,
		sale1,
		10);

	add_record(pub_Fedor_Dostoevsky,
		book_FD_Crime_and_Punishment,
		{ shop_Book_house },
		2,
		1399.99,
		sale2,
		2);
	add_record(pub_Fedor_Dostoevsky,
		book_FD_Brothers_Karamazov,
		{ shop_World_of_books, shop_Read_the_city, shop_Hut_reading },
		4,
		789.99,
		sale5,
		4);
	add_record(pub_Fedor_Dostoevsky,
		book_FD_Demons,
		{ shop_World_of_books, shop_Read_the_city, shop_Book_house },
		5,
		1129.99,
		sale4,
		2);
	add_record(pub_Fedor_Dostoevsky,
		book_FD_Notes_from_the_Underground,
		{ shop_World_of_books, shop_Read_the_city, shop_Center_book, shop_Hut_reading, shop_Book_house },
		3,
		899.99,
		sale1,
		2);
	add_record(pub_Fedor_Dostoevsky,
		book_FD_White_Nights,
		{ shop_Center_book, shop_Hut_reading, shop_Book_house },
		4,
		689.99,
		sale5,
		2);

	add_record(pub_Mikhail_Lermontov,
		book_ML_Hero_of_our_time,
		{ shop_World_of_books, shop_Read_the_city, shop_Center_book, shop_Hut_reading },
		12,
		729.99,
		sale3,
		5);
	add_record(pub_Mikhail_Lermontov,
		book_ML_Mtsyri,
		{ shop_Book_house },
		15,
		959.99,
		sale1,
		7);
	add_record(pub_Mikhail_Lermontov,
		book_ML_Daemon,
		{ shop_Center_book, shop_Book_house },
		15,
		699.99,
		sale3,
		8);
	add_record(pub_Mikhail_Lermontov,
		book_ML_Sail,
		{ shop_Center_book },
		20,
		939.99,
		sale5,
		12);
	add_record(pub_Mikhail_Lermontov,
		book_ML_Three_Palms,
		{ shop_Read_the_city, shop_Center_book, shop_Hut_reading },
		15,
		1099.99,
		sale3,
		9);

	add_record(pub_Alexander_Pushkin,
		book_AP_Captains_daughter,
		{ shop_Book_house },
		11,
		559.99,
		sale1,
		6);
	add_record(pub_Alexander_Pushkin,
		book_AP_Dubrovsky,
		{ shop_Hut_reading },
		8,
		649.99,
		sale4,
		6);
	add_record(pub_Alexander_Pushkin,
		book_AP_Queen_of_Spades,
		{ shop_Read_the_city, shop_Center_book, shop_Hut_reading, shop_Book_house },
		9,
		689.99,
		sale2,
		4);
	add_record(pub_Alexander_Pushkin,
		book_AP_Blizzard,
		{ shop_Read_the_city, shop_Hut_reading, shop_Book_house },
		5,
		549.99,
		sale5,
		3);
	add_record(pub_Alexander_Pushkin,
		book_AP_Shot,
		{ shop_World_of_books, shop_Book_house },
		12,
		729.99,
		sale1,
		8);
}

void ORM_Database::add_record(const std::string& publisher_name, const std::string& book_title, const std::vector<std::string> shop_name,
	const int stock_count, const double price_sale, const std::string date_sale, const int count_sale) {
	Wt::Dbo::Transaction t(m_session);

	Wt::Dbo::ptr<Publisher> p_ptr = nullptr;
	Wt::Dbo::ptr<Book> b_ptr = nullptr;
	Wt::Dbo::ptr<Shop> sh_ptr = nullptr;
	Wt::Dbo::ptr<Stock> st_ptr = nullptr;
	Wt::Dbo::ptr<Sale> s_ptr = nullptr;

	Wt::Dbo::collection<Wt::Dbo::ptr<Publisher>> publishers = m_session.find<Publisher>();
	bool find_publisher = false;
	for (const Wt::Dbo::ptr<Publisher>& publisher : publishers) {
		if (publisher->name == publisher_name) {
			find_publisher = true;
			p_ptr = publisher;
		}
	}
	if (!find_publisher) {
		std::unique_ptr<Publisher> p = std::make_unique<Publisher>();
		p->name = publisher_name;
		p_ptr = m_session.add(std::move(p));
	}

	std::unique_ptr<Book> b = std::make_unique<Book>();
	b->title = book_title;
	b->publisher = p_ptr;
	b_ptr = m_session.add(std::move(b));

	for (const auto& it : shop_name) {
		Wt::Dbo::collection<Wt::Dbo::ptr<Shop>> shops = m_session.find<Shop>();
		bool find_shop = false;
		for (const Wt::Dbo::ptr<Shop>& shop : shops) {
			if (shop->name == it) {
				find_shop = true;
				sh_ptr = shop;
			}
		}
		if (!find_shop) {
			std::unique_ptr<Shop> sh = std::make_unique<Shop>();
			sh->name = it;
			sh_ptr = m_session.add(std::move(sh));
		}

		std::unique_ptr<Stock> st = std::make_unique<Stock>();
		st->count = stock_count;
		st->book = b_ptr;
		st->shop = sh_ptr;
		st_ptr = m_session.add(std::move(st));

		std::unique_ptr<Sale> s = std::make_unique<Sale>();
		s->price = price_sale;
		s->date_sale = date_sale;
		s->count = count_sale;
		s->stock = st_ptr;
		s_ptr = m_session.add(std::move(s));
	}

	t.commit();
}

std::vector<std::string> ORM_Database::get_publishers() {
	std::vector<std::string> v_publishers;

	Wt::Dbo::Transaction t(m_session);

	Wt::Dbo::collection<Wt::Dbo::ptr<Publisher>> publishers = m_session.find<Publisher>();
	for (const Wt::Dbo::ptr<Publisher>& publisher : publishers) {
		v_publishers.emplace_back(publisher->name);
	}

	t.commit();

	return v_publishers;
}

ORM_Database::PublisherInfo ORM_Database::get_info(const std::string& publisher_name) {
	std::map<std::string, std::vector<std::string>> v_book_shops;

	Wt::Dbo::Transaction transaction(m_session);

	Wt::Dbo::collection<Wt::Dbo::ptr<Publisher>> publishers = m_session.find<Publisher>().where("name = ?").bind(publisher_name);
	for (const auto& publisher : publishers) {
		for (const auto& book : publisher->books) {
			std::vector<std::string> v_shops;
			for (const auto& stock : book->stocks) {
				Wt::Dbo::collection<Wt::Dbo::ptr<Shop>> shops = m_session.find<Shop>().where("id = ?").bind(stock->shop);
				for (const auto& shop : shops) {
					v_shops.emplace_back(shop->name);
				}
			}
			v_book_shops.insert(std::make_pair(book->title, std::move(v_shops)));
		}
	}

	transaction.commit();

	return PublisherInfo(publisher_name, v_book_shops);
}
