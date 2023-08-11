#pragma once

#include <Wt/Dbo/Dbo.h>
#include <Wt/Dbo/backend/Postgres.h>


class ORM_Database final {
public:
	class Publisher;
	class Book;
	class Stock;
	class Sale;
	class Shop;

	class PublisherInfo final {
	public:
		PublisherInfo(const std::string& name, const std::map<std::string, std::vector<std::string>>& book_shops) :
			m_name(name), m_book_shops(book_shops) {}
		~PublisherInfo() {}

		std::string get_name() { return m_name; }
		std::map<std::string, std::vector<std::string>> get_book_shops() { return m_book_shops; }

	private:
		std::string m_name;
		std::map<std::string, std::vector<std::string>> m_book_shops;
	};

	explicit ORM_Database(const std::string& username, const std::string& db_name, const std::string& password);
	~ORM_Database();

	ORM_Database(const ORM_Database& other) = delete;
	ORM_Database(ORM_Database&& other) noexcept = delete;
	ORM_Database& operator=(const ORM_Database& other) = delete;
	ORM_Database& operator=(ORM_Database&& other) noexcept = delete;

	void adding_records_to_tables();
	void add_record(const std::string& publisher_name, const std::string& book_title, const std::vector<std::string> shop_name,
		const int stock_count, const double price_sale, const std::string date_sale, const int count_sale);

	std::vector<std::string> get_publishers();

	PublisherInfo get_info(const std::string& publisher);

	class Publisher final {
	public:
		std::string name;
		Wt::Dbo::collection<Wt::Dbo::ptr<Book>> books;

		template<class Action>
		void persist(Action& a) {
			Wt::Dbo::field(a, name, "name");
			Wt::Dbo::hasMany(a, books, Wt::Dbo::ManyToOne, "publisher");
		}
	};

	class Book final {
	public:
		std::string title;
		Wt::Dbo::ptr<Publisher> publisher;
		Wt::Dbo::collection<Wt::Dbo::ptr<Stock>> stocks;

		template<class Action>
		void persist(Action& a) {
			Wt::Dbo::field(a, title, "title");
			Wt::Dbo::belongsTo(a, publisher, "publisher");
			Wt::Dbo::hasMany(a, stocks, Wt::Dbo::ManyToOne, "book");
		}
	};

	class Shop final {
	public:
		std::string name;
		Wt::Dbo::collection<Wt::Dbo::ptr<Stock>> stocks;

		template<class Action>
		void persist(Action& a) {
			Wt::Dbo::field(a, name, "name");
			Wt::Dbo::hasMany(a, stocks, Wt::Dbo::ManyToOne, "shop");
		}
	};

	class Stock final {
	public:
		int count = 0;
		Wt::Dbo::ptr<Book> book;
		Wt::Dbo::ptr<Shop> shop;
		Wt::Dbo::collection<Wt::Dbo::ptr<Sale>> sales;

		template<class Action>
		void persist(Action& a) {
			Wt::Dbo::field(a, count, "count");
			Wt::Dbo::belongsTo(a, book, "book");
			Wt::Dbo::belongsTo(a, shop, "shop");
			Wt::Dbo::hasMany(a, sales, Wt::Dbo::ManyToOne, "stock");
		}
	};

	class Sale final {
	public:
		double price = 0.0;
		std::string date_sale;
		int count = 0;
		Wt::Dbo::ptr<Stock> stock;

		template<class Action>
		void persist(Action& a) {
			Wt::Dbo::field(a, price, "price");
			Wt::Dbo::field(a, date_sale, "date_sale");
			Wt::Dbo::field(a, count, "count");
			Wt::Dbo::belongsTo(a, stock, "stock");
		}
	};

private:
	std::string m_username;
	std::string m_db_name;
	std::string m_password;
	Wt::Dbo::Session m_session;
};
